/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/test.cpp 2025/01/10    //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * @brief Array storing the names of various tests.
 *
 * The `test_names` array provides human-readable identifiers for each
 * of the defined test cases. These identifiers correspond to specific
 * bits in the test bitfield and can be used for logging or referencing
 * test outcomes.
 *
 * Array size is defined by `NUM_TESTS`, and each name corresponds to
 * a specific test:
 * - "Test-1": Corresponds to TEST1.
 * - "Test-2": Corresponds to TEST2.
 * - "Test-2.1": Corresponds to TEST2_1.
 * - "Test-3": Corresponds to TEST3.
 * - "Test-4": Corresponds to TEST4.
 * - "Test-5": Corresponds to TEST5.
 *
 * This mapping is crucial for maintaining clarity and consistency
 * across test result logs and processing functions.
 */
std::string test_names[NUM_TESTS] = { "Test-1", "Test-2", "Test-2.1",
                                      "Test-3", "Test-4", "Test-5"};
/**
 * Constructor for the test class. Initializes logging, resets shared memory values,
 * sets test environment state, and runs mandatory tests. Keeps track of test start
 * and end times, and stores the overall test result.
 *
 * @param bDebug Enables or disables debug mode. If true, debug logging is activated.
 * @param bCGI Indicates whether to run the tests in CGI mode. If true, tests are
 *             executed under CGI-related conditions.
 * @return None
 */
test::test(bool bDebug, bool bCGI) {
    m_pSysLog = new CSysLog();
    if(bDebug) {
        m_pSysLog->loginfo("test::test(true) called");
    } else {
        m_pSysLog->loginfo("test::test(false) called");
    }
    m_bDebug = false;

    gpSh->m_pShMemng->tests_processed_bits = 0;

    gpSh->m_pShMemng->tests_passed_bits    = 0;
    gpSh->m_pShMemng->tests_failed_bits    = 0;
    gpSh->m_pShMemng->tests_skipped_bits   = 0;

    gpSh->m_pShMemng->num_tests_processed  = 0;
    gpSh->m_pShMemng->num_tests_skipped    = 0;
    gpSh->m_pShMemng->num_tests_passed     = 0;
    gpSh->m_pShMemng->num_tests_failed     = 0;

    gpSh->m_pShMemng->tests_started        = true;

    time(&gpSh->m_pShMemng->time_started);

    gpSh->m_pShMemng->overall_test_results =
        runMandatoryTests(bCGI);

    gpSh->m_pShMemng->tests_completed = true;
    time(&gpSh->m_pShMemng->time_completed);

}


/**
 * @brief Logs various test histogram statistics and detailed information.
 *
 * Logs information about the number of tests that were processed, skipped, passed,
 * and failed. Additionally, logs the names of tests categorized under each of these
 * groups (processed, passed, failed, and skipped).
 *
 * This function utilizes a shared memory management structure to retrieve and organize
 * the test statistics. It iterates through the total count of tests, checking bitfields
 * for processed, passed, failed, and skipped tests. Each category of tests is logged
 * separately to the system log for detailed reporting.
 *
 * The function formats the output using a temporary character buffer before sending
 * it to the logging system.
 *
 * Preconditions:
 * - Ensure proper initialization of shared memory (`gpSh->m_pShMemng`) and system log
 *   object (`m_pSysLog`).
 * - `test_names` should contain valid names corresponding to the tests being tracked.
 * - Constants like `NUM_TESTS` should accurately reflect the total number of tests.
 */
void test::logHistograms() {
    char szTemp[128];

    sprintf(szTemp,"num_tests_processed are %d",
        gpSh->m_pShMemng->num_tests_processed);
    m_pSysLog->loginfo(szTemp);

    sprintf(szTemp,"num_tests_skipped are %d",
        gpSh->m_pShMemng->num_tests_skipped);
    m_pSysLog->loginfo(szTemp);

    sprintf(szTemp,"num_tests_passed are %d",
        gpSh->m_pShMemng->num_tests_passed);
    m_pSysLog->loginfo(szTemp);

    sprintf(szTemp,"num_tests_failed are %d",
        gpSh->m_pShMemng->num_tests_failed);
    m_pSysLog->loginfo(szTemp);

    int index;

    m_pSysLog->loginfo("Tests Processed:");
    for (index = 0; index < NUM_TESTS; index++) {
        if (gpSh->m_pShMemng->tests_processed_bits & (1 << index)) {
            m_pSysLog->loginfo(test_names[index].c_str());
        }
    }

    m_pSysLog->loginfo("Tests Passed:");
    for (index = 0; index < NUM_TESTS; index++) {
        if (gpSh->m_pShMemng->tests_passed_bits & (1 << index)) {
            m_pSysLog->loginfo(test_names[index].c_str());
        }
    }

    m_pSysLog->loginfo("Tests Failed:");
    for (index = 0; index < NUM_TESTS; index++) {
        if (gpSh->m_pShMemng->tests_failed_bits & (1 << index)) {
            m_pSysLog->loginfo(test_names[index].c_str());
        }
    }

    m_pSysLog->loginfo("Tests Skipped:");
    for (index = 0; index < NUM_TESTS; index++) {
        if (gpSh->m_pShMemng->tests_skipped_bits & (1 << index)) {
            m_pSysLog->loginfo(test_names[index].c_str());
        }
    }

}


/**
 * Runs a series of mandatory tests to verify various functionalities
 * including http, https, and CGI-based features. Updates shared memory
 * statistics regarding the results of the tests, such as tests passed,
 * failed, skipped, or processed. Logs relevant information during the
 * execution process.
 *
 * @param bCGI Specifies whether CGI functionality should be included in
 *             the testing process. If false, only non-CGI tests are run.
 *
 * @return Returns true if all mandatory tests pass successfully. Returns
 *         false if one or more tests fail.
 */
bool test::runMandatoryTests(bool bCGI) {

    gpSh->m_pShMemng->tests_skipped_bits   = 0;
    gpSh->m_pShMemng->tests_passed_bits    = 0;
    gpSh->m_pShMemng->tests_failed_bits    = 0;
    gpSh->m_pShMemng->tests_processed_bits = 0;

    gpSh->m_pShMemng->num_tests_processed  = 0;
    gpSh->m_pShMemng->num_tests_skipped    = 0;
    gpSh->m_pShMemng->num_tests_failed     = 0;
    gpSh->m_pShMemng->num_tests_passed     = 0;


    m_pSysLog->loginfo("test::runMandatoryTests() called");
    if (bCGI == false) {
      std::cout << "Running Mandatory Tests" << std::endl;
    }

    bool bRetVal = true;

    // Verify http:// functionality
    if (test0()) {
        gpSh->m_pShMemng->tests_passed_bits |= TEST0;
        gpSh->m_pShMemng->num_tests_passed++;
    } else {
        bRetVal = false;
        gpSh->m_pShMemng->tests_failed_bits |= TEST0;
        gpSh->m_pShMemng->num_tests_failed++;
    }
    gpSh->m_pShMemng->num_tests_processed++;
    gpSh->m_pShMemng->tests_processed_bits |= TEST0;


    // Verify http:// functionality
    if (test1()) {
        gpSh->m_pShMemng->tests_passed_bits |= TEST1;
        gpSh->m_pShMemng->num_tests_passed++;
    } else {
        bRetVal = false;
        gpSh->m_pShMemng->tests_failed_bits |= TEST1;
        gpSh->m_pShMemng->num_tests_failed++;
    }
    gpSh->m_pShMemng->num_tests_processed++;
    gpSh->m_pShMemng->tests_processed_bits |= TEST1;

    gpSh->m_pShMemng->tests_skipped_bits |= TEST2;
    gpSh->m_pShMemng->num_tests_skipped++;

    // Verify https:// functionality
    if (test2_1(false)) {
        gpSh->m_pShMemng->tests_passed_bits |= TEST2_1;
        gpSh->m_pShMemng->num_tests_passed++;
    } else {
        bRetVal = false;
        gpSh->m_pShMemng->tests_failed_bits |= TEST2_1;
        gpSh->m_pShMemng->num_tests_failed++;
    }
    gpSh->m_pShMemng->num_tests_processed++;
    gpSh->m_pShMemng->tests_processed_bits |= TEST2_1;

    // Verify CGI functionality
    if (test3(false, bCGI)) {
        gpSh->m_pShMemng->tests_passed_bits |= TEST3;
        gpSh->m_pShMemng->num_tests_passed++;
    } else {
        bRetVal = false;
        gpSh->m_pShMemng->tests_failed_bits |= TEST3;
        gpSh->m_pShMemng->num_tests_failed++;
    }
    gpSh->m_pShMemng->num_tests_processed++;
    gpSh->m_pShMemng->tests_processed_bits |= TEST3;

    // Verify cgicc functionality
    if (test5(__FILE__, __FUNCTION__, false)) {

        gpSh->m_pShMemng->tests_passed_bits |= TEST5;

        gpSh->m_pShMemng->num_tests_passed++;

    } else {

        bRetVal = false;
        gpSh->m_pShMemng->tests_failed_bits |= TEST5;
        gpSh->m_pShMemng->num_tests_failed++;
    }

    gpSh->m_pShMemng->num_tests_processed++;
    gpSh->m_pShMemng->tests_processed_bits |= TEST5;

    return bRetVal;
}


/**
 * Executes a series of tests and logs the results. This includes verifying
 * various functionalities such as HTTP, HTTPS, shared region, CGI, and other
 * specific features. Updates the shared memory with the test outcomes.
 *
 * @param bCGI A boolean flag indicating whether CGI-related tests should be executed.
 * @return True if all tests pass, false if any test fails.
 */
bool test::runAllTests(bool bCGI) {
    m_pSysLog->loginfo("test::runAllTests() called");

    bool bRetVal = true;

    // Verify http:// functionality
    if (test1()) {
        gpSh->m_pShMemng->tests_passed_bits |= TEST1;
        gpSh->m_pShMemng->num_tests_passed++;
    } else {
        bRetVal = false;
        gpSh->m_pShMemng->tests_failed_bits |= TEST1;
        gpSh->m_pShMemng->num_tests_failed++;
    }
    gpSh->m_pShMemng->num_tests_processed++;
    gpSh->m_pShMemng->tests_processed_bits |= TEST1;

    // Verify https:// functionality
    if (test2()) {
        gpSh->m_pShMemng->tests_passed_bits |= TEST2;
        gpSh->m_pShMemng->num_tests_passed++;
    } else {
        bRetVal = false;
        gpSh->m_pShMemng->tests_failed_bits|= TEST2;
        gpSh->m_pShMemng->num_tests_failed++;
    }
    gpSh->m_pShMemng->num_tests_processed++;
    gpSh->m_pShMemng->tests_processed_bits |= TEST2;

    // verify shared region
    if (test2_1(false)) {
        gpSh->m_pShMemng->tests_passed_bits |= TEST2_1;
        gpSh->m_pShMemng->num_tests_passed++;
    } else {
        bRetVal = false;
        gpSh->m_pShMemng->tests_failed_bits |= TEST2_1;
        gpSh->m_pShMemng->num_tests_failed++;
    }
    gpSh->m_pShMemng->num_tests_processed++;
    gpSh->m_pShMemng->tests_processed_bits |= TEST2_1;


    // Verify CGI functionality
    if (test3(false, bCGI)) {
        gpSh->m_pShMemng->tests_passed_bits |= TEST3;
        gpSh->m_pShMemng->num_tests_passed++;
    } else {
        bRetVal = false;
        gpSh->m_pShMemng->tests_failed_bits |= TEST3;
        gpSh->m_pShMemng->num_tests_failed++;
    }
    gpSh->m_pShMemng->num_tests_processed++;
    gpSh->m_pShMemng->tests_processed_bits |= TEST3;


    // Verify cgicc functionality
    if (test5(__FILE__, __FUNCTION__, false)) {
        gpSh->m_pShMemng->tests_passed_bits |= TEST5;
        gpSh->m_pShMemng->num_tests_passed++;
    } else {
        bRetVal = false;
        gpSh->m_pShMemng->tests_failed_bits |= TEST5;
        gpSh->m_pShMemng->num_tests_failed++;
    }
    gpSh->m_pShMemng->num_tests_processed++;
    gpSh->m_pShMemng->tests_processed_bits |= TEST5;

    return bRetVal;
}

/**
 * Tests the validity of shared environment values by verifying if
 * specific shared memory content is correctly initialized and contains
 * valid, non-empty data.
 *
 * The method checks if the `iSignature` field in shared memory matches
 * the expected `UNIVERSAL_ANSWER` value. It also verifies that several
 * configurable string parameters such as hostname, IP, interface,
 * protocol, image root, CGI root, and user are non-empty.
 *
 * @return true if all environment values are verified correctly as valid;
 *         false if any value is invalid or uninitialized.
 */
bool test::test0()
{
    m_pSysLog->loginfo("test::test0() called, verify env values");
    bool bRetVal = true;    // set default return value

    if (UNIVERSAL_ANSWER != gpSh->m_pShMemng->iSignature) {
        bRetVal = false;
    }

    /**
     * Test Environment based values not empty null strings
     */
    if ( 0 == strlen(gpSh->m_pShMemng->szHostname) ||
         0 == strlen(gpSh->m_pShMemng->szIP)       ||
         0 == strlen(gpSh->m_pShMemng->szIface)    ||
         0 == strlen(gpSh->m_pShMemng->szProtocol) ||
         0 == strlen(gpSh->m_pShMemng->szImgRoot)  ||
         0 == strlen(gpSh->m_pShMemng->szCgiRoot)  ||
         0 == strlen(gpSh->m_pShMemng->szUser) ) {
        bRetVal = false;
    }
    return bRetVal;
}

/**
 * Performs a test to verify HTTP functionality by generating and opening a specific HTML URL,
 * reading the generated output file, and checking its content.
 *
 * This method generates a URL using an external system function, executes the URL,
 * and then opens an output file to validate the content.
 * The file content is checked against the expected "<!DOCTYPE" prefix to determine success.
 *
 * @return true if the content of the output file starts with "<!DOCTYPE", indicating success;
 *         false otherwise.
 */
bool test::test1() {
    m_pSysLog->loginfo("test::test1() called, verify http:// read");

    system(gpOS->genHtmlUrl("fw-test1.html",false).c_str());

    const std::string filename = "/tmp/fw-test1.stdout";
    std::ifstream ifs(filename);
    std::string inbuf;
    ifs >> inbuf;
    if (0 == inbuf.compare("<!DOCTYPE")) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Tests the `https://` functionality by generating and invoking an HTML page
 * and verifying the output in a temporary file.
 *
 * The function generates a URL for the HTML page "fw-test2.html" using the `osIface`
 * instance, executes a system command to process the page, and then reads the resulting
 * output from a temporary file. It compares the start of the output to a predefined
 * string ("<!DOCTYPE") to verify if the operation was successful.
 *
 * @return true if the output starts with "<!DOCTYPE", indicating validation success.
 * @return false otherwise, indicating validation failure.
 */
bool test::test2() {
    m_pSysLog->loginfo("test::test2() called, verify https:// read");

    system(gpOS->genHtmlUrl("fw-test2.html",false).c_str());

    const std::string filename = "/tmp/fw-test2.stdout";
    std::ifstream ifs(filename);
    std::string inbuf;
    ifs >> inbuf;
    if (0 == inbuf.compare("<!DOCTYPE")) {
        return true;
    } else {
        return false;
    }
}

/**
 * Verifies the version and parameters of a specified shared memory region
 * by analyzing system-shared segment metadata.
 *
 * @param bDebug A boolean flag indicating whether debug mode is enabled.
 *               If true, additional log information may be produced.
 * @return true if the shared memory segment matches the expected size,
 *         ownership, and permissions; false otherwise.
 * 0x00005164 557072     doug       660        22976      1

 */
bool test::test2_1(bool bDebug)
{
    m_pSysLog->loginfo("test::test2_1() called, "
                       "verify shared region version");

    /**
     * @struct SMS_T
     * @brief Represents the details of a shared memory segment.
     *
     * The SMS_T structure is used to store attributes of a shared memory segment
     * obtained through system calls or inter-process communication details.
     */
    struct SMS_T {
        /**
         * @brief Represents the key of a shared memory segment.
         *
         * The `key` variable is used to identify a shared memory segment,
         * allowing access and manipulation of the specific segment during runtime.
         * It typically stores a hexadecimal string value corresponding to the
         * system-assigned key for the shared segment. This is instrumental in
         * inter-process communication (IPC) where shared memory is utilized.
         */
        std::string key;
        /**
         * @brief Represents the shared memory ID associated with a shared memory segment.
         *
         * This variable stores a unique identifier for a shared memory segment,
         * allowing processes to access or manage the specific shared memory region.
         * It typically corresponds to a value obtained or set when working with
         * system-level shared memory operations.
         */
        std::string shmid;
        /**
         * Represents the owner of a shared memory segment.
         *
         * This variable is typically used to store the identifier of the
         * owner entity that created or is managing a shared memory segment.
         */
        std::string owner;
        /**
         * @brief Represents the current access permissions associated with a shared memory region.
         *
         * The `perms` variable holds the access permission bits for a shared memory segment, typically
         * represented as a string (e.g., "660"). These permissions are usually in octal notation and
         * define the allowed read, write, or execute access levels for different users (owner, group,
         * and others).
         */
        std::string perms;
        /**
         * Represents a string value capturing the size in bytes of a particular shared memory segment
         * as obtained from system shared memory resources.
         * It is used for comparison and validation to ensure the memory segment size aligns
         * with expected values during shared memory management operations.
         */
        std::string bytes;
        /**
         * @brief Represents the number of processes currently attached
         *        to a shared memory segment.
         *
         * The `nattach` variable typically stores a string representation
         * of the count of active processes attached to a specific shared
         * memory segment. This value can be extracted from system commands
         * or shared memory metadata and is used to monitor or validate shared
         * memory usage in a multi-process environment.
         */
        std::string nattach;
    } sms;

    gpXinetd->trigger(VPA_IPCS_PORT);
    sleep(1);
    std::string ssIpcsFQFS = gpOS->genTempFQFS("ipcs.stdout",
                                                false);

    std::ifstream ifs(ssIpcsFQFS);
    std::string inbuf;

    ifs >> inbuf;
    while(0 != inbuf.compare("Message")) {
        ifs >> inbuf;
    }

    ifs >> inbuf;

    while(0 != inbuf.compare("Shared")) {
        ifs >> inbuf;
    }

    ifs >> inbuf;
    while(0 != inbuf.compare("Semaphore")) {

        ifs >> inbuf;

        /**
         * Is it my shared region key="0x00005164" ?
         */
        if(0 == inbuf.compare("0x00005164")) {
            /**
             * That is our key :-)
             */
            /**
             * Pick up the fields...
             */
                     sms.key = inbuf;
            ifs   >> sms.shmid;
            ifs   >> sms.owner;
            ifs   >> sms.perms;
            ifs   >> sms.bytes;
            ifs   >> sms.nattach;

            /**
             * What is the size of our shared structure?
             */

            std::size_t shmemsize = atoi(sms.bytes.c_str()); // kludge

            /**
             * What is the size of the existing segment?
             */
            std::string bytes = sms.bytes;

            int bytesize = atoi(bytes.c_str());
            /**
             * Check the size to make sure its what we are expecting"
             */
            if(shmemsize != bytesize) {
                m_pSysLog->loginfo("Wrong size of shared segment, "
                                    "not current ver");
                return false;
            }
            /**
             * segment size was correct
             */
            if(0 != strcmp(gpSh->m_pShMemng->szUser,sms.owner.c_str())) {
                // We are not the existing segment's owner
                return false;
            }
            /**
             * segment owner was correct
             */
            if(0 != strcmp("660",sms.perms.c_str())) {
                // Not the permissions we were expecting
                return false;
            }
            return true;
        } // not our key, go back to while and try another
    }    // ran out of Shared Memory Segments without finding our key
    return false;
}


/**
 * Verifies the ability of the system to handle CGI (Common Gateway Interface) scripts.
 * If `bCGI` is true, the method directly returns true indicating CGI functionality is enabled.
 * Otherwise, it executes a specific CGI script, retrieves its output, and compares the output
 * to a predefined key to determine success or failure.
 *
 * @param bDebug Specifies whether the debug mode is enabled. Currently not utilized in this implementation.
 * @param bCGI If true, the method assumes CGI functionality is enabled and returns true.
 *             If false, the function tests CGI execution by validating the output of a predefined script.
 * @return Returns true if CGI functionality is verified successfully, false otherwise.
 */
bool test::test3(bool bDebug, bool bCGI) {
    m_pSysLog->loginfo("test::test3() called, "
                        "verify apache can execute CGI scripts");

    if (bCGI) {
	    return true;
    }

    else {

            system(gpOS->genCgiBinUrl("fw-test3.py",false).c_str());

            const std::string filename = "/tmp/fw-test3.stdout";
            std::ifstream ifs(filename);
            std::string inbuf;
            ifs >> inbuf;
            if (0 == inbuf.compare("2d57309e-ce1f-11ef-b73d-0f5dbc92dd58")) {
                return true;
            } else {
                return false;
	    }
    }
}



/**
 * Validates the functionality of the logging system by writing a unique identifier
 * to a log file and checking if it is correctly written and retrievable. The log file
 * location is generated using the genLogFQFS function.
 *
 * @param pszFile The file name where the function is being invoked.
 * @param pszFunction The name of the function invoking the method.
 * @param bDebug A boolean indicating whether debugging mode is enabled.
 * @return True if the unique identifier is successfully written and retrieved from
 *         the log file; false if the log file could not be generated or the unique
 *         identifier is not found.
 */
bool test::test5(const char *pszFile, const char *pszFunction, bool bDebug) {
    m_pSysLog->loginfo("test::test5() called, verify genLogFQFS");

    strncpy(m_szLogFQFS,
            gpOS->genLogFQFS(__FILE__, __FUNCTION__, false),
            sizeof(m_szLogFQFS));
    m_pSysLog->loginfo(gpOS->genLogFQFS(__FILE__, __FUNCTION__, false));
    if (0 < strlen(m_szLogFQFS)) {
        CLog log(__FILE__, __FUNCTION__);
        log.truncate();
        // write a unique uuid into the log for the test
        log.write("51cbd444-ceaf-11ef-9da5-97e0560975f4");

        std::ifstream ifs(m_szLogFQFS);
        std::string inbuf;
        ifs >> inbuf;
        m_pSysLog->loginfo(inbuf.c_str());

        ifs >> inbuf;
        m_pSysLog->loginfo(inbuf.c_str());

        ifs >> inbuf;
        m_pSysLog->loginfo(inbuf.c_str());

        // check for the unique uuid in the log entry
        if (0 == strcmp("51cbd444-ceaf-11ef-9da5-97e0560975f4",
                        inbuf.c_str())) {
            m_pSysLog->loginfo("test5 returning true");
            return true;
        } else {
            m_pSysLog->loginfo("test5 returning false");
            return false;
        }
    } else {
        return false;
    }
    exit( 0);

}


/**
 * @brief Destructor for the `test` class.
 *
 * This destructor is responsible for cleaning up resources allocated
 * during the lifetime of a `test` object. If any dynamic memory or
 * external resources are used by the class, they should be released
 * within this destructor.
 *
 * It handles deinitialization of any members and ensures proper
 * cleanup to prevent memory leaks or undefined behavior when the
 * object is destroyed.
 */
test::~test() {
}

////////////////////
// eof - test.cpp //
////////////////////
