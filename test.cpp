/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/test.cpp 2025/01/10    //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#include "test.h"
//#include <time.h>

std::string test_names[NUM_TESTS] = { "Test-1", "Test-2", "Test-2.1",
                                      "Test-3", "Test-4", "Test-5"};
/********************************************
 * This is the constructor for the test class
 ********************************************/
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


/**************************
 * Show Histograms
 **************************/
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


/******************************************************
 * Run Mandatory Tests
 * @return
 ******************************************************/
bool test::runMandatoryTests(bool bCGI) {

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
    if (test4(false)) {
        gpSh->m_pShMemng->tests_passed_bits |= TEST4;
        gpSh->m_pShMemng->num_tests_passed++;
    } else {
        bRetVal = false;
        gpSh->m_pShMemng->tests_failed_bits |= TEST4;
        gpSh->m_pShMemng->num_tests_failed++;
    }
    gpSh->m_pShMemng->num_tests_processed++;
    gpSh->m_pShMemng->tests_processed_bits |= TEST4;

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


/************************************************
 * Run All Tests
 * @return
 ************************************************/
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
    if (test4(false)) {
        gpSh->m_pShMemng->tests_passed_bits |= TEST4;
        gpSh->m_pShMemng->num_tests_passed++;
    } else {
        bRetVal = false;
        gpSh->m_pShMemng->tests_failed_bits |= TEST4;
        gpSh->m_pShMemng->num_tests_failed++;
    }
    gpSh->m_pShMemng->num_tests_processed++;
    gpSh->m_pShMemng->tests_processed_bits |= TEST4;

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

/**********************************************************************
 * verify shared env values
 * @return true or false
 * 2025/01/26 02:37 dwg  - test for values depended on for operation
 * of osIface functions.
 **********************************************************************/
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
 * verify that Apache HTTP Server is operating and can retrieve static
 * html pages using http:// protocol.
 * @return
 * Note: 2025/01/25 12:34 dwg - test1 calls genHtmlUrl which requires
 * the shared variables such as szProtocol to be present, Therefore
 * the environment class must be previously instantiated.
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

/*********************************************************************
 * verify that Apache HTTP Server is operating and can retrieve static
 * html pages using https:// protocol.
 * @return
 *********************************************************************/
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

/***************************************************************************
 * Verify shared region version
 * @param bDebug
 * @return
 ***************************************************************************
 * doug@daphne:~/Desktop$ ipcs
 * ------ Message Queues --------
 * key        msqid      owner      perms      used-bytes   messages
 *
 * ------ Shared Memory Segments --------
 * key        shmid      owner      perms      bytes      nattch     status
 * 0x00000000 27         doug       600        524288     2          dest
 *
 * 0x00005164 45         doug       660        4928       0
 * ^^^^^^^^^^ ^^         ^^^^       ^^^        ^^^^       ^
 *
 * 0x00000000 622652     doug       600        204660     2          dest
 *
 * ------ Semaphore Arrays --------
 * key        semid      owner      perms      nsems
 * 0xcb060002 0          doug       600        1
 * 0xcc060002 1          doug       600        1
 * 0xcd060002 2          doug       600        1
 * 0xce060002 3          doug       600        1
 ***************************************************************************/
bool test::test2_1(bool bDebug)
{
    m_pSysLog->loginfo("test::test2_1() called, "
                       "verify shared region version");

    struct SMS_T {
        std::string key;
        std::string shmid;
        std::string owner;
        std::string perms;
        std::string bytes;
        std::string nattach;
    } sms;

    system("ipcs > /tmp/ipcs.stdout 2> /tmp/ipcs.stderr");
    const std::string filename = "/tmp/ipcs.stdout";
    std::ifstream ifs(filename);
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
 * verify that Apache HTTP Server is operating and can execute
 * CGI scripts using http:// protocol.
 * @return
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


/*************************************************************
 * verify that Apache HTTP Server is operating and can execute
 * binary CGI scripts using http:// protocol.
 * @return
 * 2025/01/09 20:32 new version uses pOS->genCgiCBD()
 *************************************************************/
bool test::test4(bool bDebug) {
    m_pSysLog->loginfo("test::test4() called, "
                        "verify apache can execute binary CGI scripts");

    std::string ssPath = gpOS->genCgiCBDPath("fw-test4.cgi", false);

    if (0 != access(ssPath.c_str(), F_OK)) {
        std::cout << "Target fw-test4.cgi Not Built!!" << std::endl;
        std::cout << "Program Aborted." << std::endl;
        exit(EXIT_FAILURE);
    }


    std::string ssCommand;

    ssCommand = "curl ";

    ssCommand.append(gpOS->genCgiCBDUrl("fw-test4.cgi", false));

    ssCommand.append(" > /tmp/fw-test4.stdout 2> /tmp/fw-test4.stderr");

    system(ssCommand.c_str());

    std::string filename = "/tmp/fw-test4.stdout";
    std::ifstream ifs(filename);
    std::string inbuf;
    ifs >> inbuf;


    std::string token = inbuf.substr(0, 6);
    if (0 == token.compare("Apache")) {
        return true;
    } else {
        return false;
    }
}


/***********************************************************************
 * verify that osIface::genLogFQFS() is operating.
 * @return
 ***********************************************************************/
bool test::test5(const char *pszFile, const char *pszFunction, bool bDebug) {
    m_pSysLog->loginfo("test::test5() called, verify genLogFQFS");

    strncpy(m_szLogFQFS,
            gpOS->genLogFQFS(__FILE__, __FUNCTION__, false),
            sizeof(m_szLogFQFS));

    if (0 < strlen(m_szLogFQFS)) {
        CLog log(__FILE__, __FUNCTION__);
        log.truncate();
        // write a unique uuid into the log for the test
        log.write("51cbd444-ceaf-11ef-9da5-97e0560975f4");

        std::ifstream ifs(m_szLogFQFS);
        std::string inbuf;
        ifs >> inbuf;

        ifs >> inbuf;

        ifs >> inbuf;

        // check for the unique uuid in the log entry
        if (0 == strcmp("51cbd444-ceaf-11ef-9da5-97e0560975f4",
                        inbuf.c_str())) {
            return true;
        } else {
            exit( 0);

            return false;
        }
    } else {
        return false;
    }
    exit( 0);

}


/*************************************************
 * This is the empty destructor for the test class
 *************************************************/
test::~test() {
}

////////////////////
// eof - test.cpp //
////////////////////
