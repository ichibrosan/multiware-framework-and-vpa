////////////////////////////////////////////////////////////////////
// ~/public_html/fw/look.cpp 2025-07-15 18:16 dwg -               //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"


/**
 * @brief Creates and renders a graphical window with specific appearance and content.
 *
 * This function initializes a new window object and applies semigraphics cosmetics
 * using predefined characters for corners, separators, and lines. It displays the
 * version information of the "Virtual Protocol Adapter Look Utility" formatted using
 * predefined version constants. Additionally, it appends copyright information and
 * renders the window.
 *
 * The function relies on:
 * - Semigraphics cosmetic details defined in semigraphics.h
 * - Version constants defined in version.h
 * - The window class and associated methods for rendering.
 *
 * No arguments are required, and the function does not return any value.
 *
 * Key operations:
 * - Configure the semigraphics cosmetics for the window.
 * - Set the title with version information using formatted strings.
 * - Add a copyright footer with compatible symbols.
 * - Render the constructed window.
 *
 * Note:
 * Make sure that appropriate memory management is handled for the window object since
 * it is dynamically allocated.
 */
void sine()
{
    auto* pWin = new window();
    gpSemiGr->cosmetics(
        SRUL, SRUR, SRLL, // Corner characters: ┌ ┐ └ ┘
        SRLR, SVSR, SVSL, // Right corner and separators
        SH, SV); // Horizontal ─ and vertical │ lines
    char szVersion[64];
    sprintf(szVersion, "Virtual Protocol Adapter Look Utility "
            "Ver %d.%d.%d.%d",RMAJ,RMIN,RREV,RBLD);
    pWin->set_title(szVersion);
    std::string ssCopr = "  License ";
    ssCopr.append(RCOPR); // Append copyright symbol for compatibility
    pWin->add_row(ssCopr);
    pWin->render();
}

/**
 * @brief Manages the shared memory operations and prints the status of test statistics.
 *
 * This method uses a shared memory manager to update the signature of the shared memory.
 * It increments the `iSignature` field of the shared memory object twice, each time using
 * a different shared memory management instance. After locking, updating, and releasing
 * shared memory, it prints the counts of tests processed, skipped, passed, and failed.
 * Additionally, it resets the `num_tests_processed` field to zero and prints binary projections
 * of test metrics using the available printBinary utility.
 *
 * @details
 * - Updates the signature of the shared memory using two different shared memory managers.
 * - Outputs the count of tests:
 *   - processed
 *   - skipped
 *   - passed
 *   - failed
 * - Resets the number of processed tests to zero.
 * - Uses a binary representation (printBinary) to display the processed, passed, failed,
 *   and skipped test metrics.
 *
 * The structure and purpose of `gpSh` and `gpShMemMgr` are assumed to provide global access
 * to shared memory and its manager, respectively.
 */
void shmvars()
{
    shared::SharedMemoryManager manager;
    manager.lockSharedMemory();
    gpSh->m_pShMemng->iSignature++;
    manager.releaseSharedMemory();

    gpShMemMgr->lockSharedMemory();
    gpSh->m_pShMemng->iSignature++;
    gpShMemMgr->releaseSharedMemory();

    printf("num_tests_processed is %d\n",
           gpSh->m_pShMemng->num_tests_processed);
    printf("num_tests_skipped is %d\n",
           gpSh->m_pShMemng->num_tests_skipped);
    printf("num_tests_passed is %d\n",
           gpSh->m_pShMemng->num_tests_passed);
    printf("num_tests_failed is %d\n\n",
           gpSh->m_pShMemng->num_tests_failed);
    gpSh->m_pShMemng->num_tests_processed = 0;
    int iNumTests = 7;
    printf("tests_processed_bits are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_processed_bits, iNumTests);
    printf("\ntests_passed_bits    are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_passed_bits, iNumTests);
    printf("\ntests_failed_bits    are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_failed_bits, iNumTests);
    printf("\ntests_skipped_bits   are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_skipped_bits, iNumTests);
}

/**
 * @brief Displays the credentials of authenticated users from shared memory.
 *
 * This function iterates through the authenticated users stored in shared memory
 * and prints their credentials to the console. It excludes metadata rows and
 * only processes user entries starting at a predetermined offset (`ROW_DATA`).
 * If a user has a valid authentication handle (`iAuthHandle > 0`), their details
 * are printed in a formatted manner, including username, first name, last name,
 * UUID, authentication handle, and HTTP user agent string.
 *
 * The function depends on predefined constants such as `ROW_DATA`, `CFG_MAX_USERS`,
 * and assumes a shared memory structure pointed to by `gpSh`.
 */
void auth_users()
{
    printf("Credentials of Authenticated Users:");
    for (int iRow = 3; iRow < CFG_MAX_USERS + ROW_DATA; iRow++)
    {
        if (0 < gpSh->m_pShMemng->creds[iRow].iAuthHandle)
        {
            printf("\n-------------------------------------------\n");
            printf("szAuthUserName  is %s\n",
                   gpSh->m_pShMemng->creds[iRow].szAuthUserName);
            printf("szAuthFirstname is %s\n",
                   gpSh->m_pShMemng->creds[iRow].szAuthFirstName);
            printf("szAuthLastName  is %s\n",
                   gpSh->m_pShMemng->creds[iRow].szAuthLastName);
            printf("szAuthUUID      is %s\n",
                   gpSh->m_pShMemng->creds[iRow].szAuthUUID);
            printf("iAuthHandle     is %d\n",
                   gpSh->m_pShMemng->creds[iRow].iAuthHandle);
            printf("iHttpUserAgent  is %s\n",
                   gpSh->m_pShMemng->creds[iRow].szHttpUserAgent);
        }
    }
}

/**
 * @brief Configures and manages an INI file.
 *
 * This function handles the creation, loading, updating, and saving of an
 * INI configuration file. It uses a custom `cfgini` class to manage the
 * configuration details, including the addition of new sections, setting
 * variables, and saving them back to the file.
 *
 * The function performs the following actions:
 * 1. Attempts to load an existing configuration file. If unable to load, it creates a new one.
 * 2. Adds configuration details under pre-defined sections such as "Database" and "Logging".
 * 3. Writes configuration variables for database connection and logging settings.
 * 4. Saves the updated configuration back to the file.
 * 5. Reads and prints certain variables from the configuration for verification.
 *
 * The configuration includes:
 * - A "Database" section containing host, port, and database name settings.
 * - A "Logging" section specifying the logging level and log file.
 *
 * This function demonstrates interaction with configuration management in
 * an application context.
 */
void configini()
{
    cfgini config(gpSh->m_pShMemng->szConfigFQFS);

    // Create a new config or load existing
    if (!config.load())
    {
        config.createNew();
    }

    // Add sections and variables
    config.addSection("Database");
    config.setVariable("Database", "host", "localhost");
    config.setVariable("Database", "port", "3306");
    config.setVariable("Database", "name", "mydb");

    config.addSection("Logging");
    config.setVariable("Logging", "level", "info");
    config.setVariable("Logging", "file", "app.log");

    // Save the configuration
    config.save();

    // Read values
    std::string host = config.getVariable("Database", "host", "localhost");
    std::cout << "Database host is " << host << std::endl;
    std::string logLevel = config.getVariable("Logging", "level", "debug");
    std::cout << "Logging level is " << logLevel << std::endl;
}

/**
 * Outputs the sizes and padding information for various request structure types.
 *
 * This function calculates the size of several predefined data structures
 * related to `vparpc` requests and outputs their size and padding.
 * Padding is calculated as the difference between the fixed size of
 * 1080 bytes and the actual size of the structure. The results are
 * printed to the standard output.
 *
 * Structures displayed include:
 * - `vparpc_request_generic_t`
 * - `vparpc_request_auth_t`
 * - `vparpc_request_version_t`
 * - `vparpc_request_lookup_t`
 * - `vparpc_request_creds_t`
 * - `vparpc_request_urls_t`
 */
void struct_diag()
{
    std::cout << "sizeof(vparpc_request_generic_t) is " << sizeof(
        vparpc_request_generic_t) << std::endl;
    std::cout << "sizeof(vparpc_request_auth_t) is " << sizeof(
        vparpc_request_auth_t) << std::endl;
    std::cout << "sizeof(vparpc_request_version_t) is " << sizeof(
        vparpc_request_version_t) << std::endl;
    std::cout << "sizeof(vparpc_request_lookup_t) is " << sizeof(
        vparpc_request_lookup_t) << std::endl;
    std::cout << "sizeof(vparpc_request_creds_t) is " << sizeof(
        vparpc_request_creds_t) << std::endl;
    std::cout << "sizeof(vparpc_request_urls_t) is " << sizeof(
        vparpc_request_urls_t) << std::endl;

    std::cout << "vparpc_request_generic_t padding is " << 1080 - sizeof(
        vparpc_request_generic_t) << std::endl;
    std::cout << "vparpc_request_auth_t    padding is " << 1080 - sizeof(
        vparpc_request_auth_t) << std::endl;
    std::cout << "vparpc_request_version_t padding is " << 1080 - sizeof(
        vparpc_request_version_t) << std::endl;
    std::cout << "vparpc_request_lookup_t  padding is " << 1080 - sizeof(
        vparpc_request_lookup_t) << std::endl;
    std::cout << "vparpc_request_creds_t   padding is " << 1080 - sizeof(
        vparpc_request_creds_t) << std::endl;
    std::cout << "vparpc_request_urls_t    padding is " << 1080 - sizeof(
        vparpc_request_urls_t) << std::endl;
}

/*
## Features of the CServices Class:
1. **Service Existence Check**:
    - `hasService()` - Check if a service exists by name
    - `hasService(name, protocol)` - Check if a service exists for a specific protocol

2. **Service Addition**:
    - `addService()` - Add new services to `/etc/services` with validation
    - Prevents duplicate entries and validates input

3. **Service Retrieval**:
    - `getService()` - Get service information by name
    - `getServiceByPort()` - Get service by port and protocol
    - `getServicePort()` - Get port number for a service
    - `getServiceName()` - Get service name for a port

4. **Service Management**:
    - `removeService()` - Remove services from `/etc/services`
    - `findServices()` - Search for services by pattern
    - `reloadCache()` - Refresh the internal cache

5. **Safety Features**:
    - `createBackup()` - Create backup before modifications
    - `restoreFromBackup()` - Restore from backup if needed
    - `isServicesFileWritable()` - Check permissions before writing

 */

/**
 * @brief Performs diagnostic operations related to service management.
 *
 * This function interacts with an instance of the CServices class to:
 * - Check the existence of specific services.
 * - Add services if they do not already exist, specifying their name, port, protocol, and aliases.
 * - Retrieve a list of services matching a specific pattern ("http").
 * - Log outputs to indicate the status of service operations such as existence checks or successful additions.
 */
void services_diag()
{
    CServices services;

    // Check if a service exists
    if (services.hasService("vpa"))
    {
        std::cout << "vpa service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa", 5164, "tcp", {"vpa-alias"}))
        {
            std::cout << "Service added successfully - vpa" << std::endl;
        }
    }

    if (services.hasService("vpa-disc"))
    {
        std::cout << "vpa-disc service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-disc", 5164, "udp", {"vpa-disc-alias"}))
        {
            std::cout << "Service added successfully - vpa-disc" << std::endl;
        }
    }


    if (services.hasService("vpad-start"))
    {
        std::cout << "vpa-start service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpad-start", 65353, "tcp",
                                {"vpa-start-alias"}))
        {
            std::cout << "Service added successfully - vpad-start" << std::endl;
        }
    }

    if (services.hasService("vpa-netstat"))
    {
        std::cout << "vpa-netstat service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-netstat", 65354, "tcp",
                                {"vpa-netstat-alias"}))
        {
            std::cout << "Service added successfully - vpa-netstat" <<
                std::endl;
        }
    }

    if (services.hasService("vpa-ip"))
    {
        std::cout << "vpa-ip service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-ip", 65355, "tcp", {"vpa-ip-alias"}))
        {
            std::cout << "Service added successfully - vpa-ip" << std::endl;
        }
    }

    if (services.hasService("vpa-curl"))
    {
        std::cout << "vpa-curl service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-curl", 5164, "tcp", {"vpa-curl-alias"}))
        {
            std::cout << "Service added successfully - vpa-curl" << std::endl;
        }
    }

    if (services.hasService("vpa-http"))
    {
        std::cout << "vpa-http service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-http", 65357, "tcp", {"vpa-http-alias"}))
        {
            std::cout << "Service added successfully - vpa-http" << std::endl;
        }
    }

    if (services.hasService("vpa-https"))
    {
        std::cout << "vpa-https service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-https", 65358, "tcp", {"vpa-https-alias"}))
        {
            std::cout << "Service added successfully - vpa-https" << std::endl;
        }
    }

    if (services.hasService("vpa-ipcs"))
    {
        std::cout << "vpa-ipcs service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-ipcs", 65359, "tcp", {"vpa-ipcs-alias"}))
        {
            std::cout << "Service added successfully - vpa" << std::endl;
        }
    }

    if (services.hasService("vpa-iphone"))
    {
        std::cout << "vpa-iphone service exists" << std::endl;
    }
    else
    {
        if (services.addService("vpa-iphone", 65360, "tcp", {"vpa-iphone-alias"}))
        {
            std::cout << "Service added successfully - vpa-iphone" << std::endl;
        }
    }


    // Find services by pattern
    auto webServices = services.findServices("http");
    for (const auto& service : webServices)
    {
        std::cout << service.name << " on port " << service.port << std::endl;
    }
}

/**
 * Generates, displays, and optionally saves an updated Xinetd configuration
 * for the VPA service. If the necessary permissions to modify the
 * configuration file are not available, the method operates in "dry-run" mode.
 *
 * The method performs the following steps:
 * - Displays the number of configured services.
 * - Displays the status of VPA services.
 * - Generates and displays the Xinetd configuration for VPA.
 * - If permissions allow, creates a backup of the current configuration,
 *   saves the new configuration, and reloads the Xinetd service.
 *
 * If unable to proceed due to insufficient privileges or errors during
 * saving/reloading, the relevant errors and instructions are displayed.
 *
 * @return 0 on successful save or dry-run completion, or 1 if saving
 *         the configuration fails.
 */
int xinetdcfg_diag()
{
    xinetcfg config;

    // Test VPA configuration generation
    std::cout << "=== VPA Xinetd Configuration Test ===" << std::endl;
    std::cout << "Number of services configured: " << config.getServiceCount()
        << std::endl;

    // Display service status
    config.displayVpaServiceStatus();

    // Generate and display configuration
    std::cout << "\n=== Generated VPA Configuration ===" << std::endl;
    std::string vpaConfig = config.generateVpaXinetdConfig();
    std::cout << vpaConfig << std::endl;

    // Check permissions before attempting to save
    if (!config.canModifyXinetd())
    {
        std::cout << "\n=== PERMISSION NOTICE ===" << std::endl;
        std::cout <<
            "Cannot modify /etc/xinetd.d/vpa - insufficient privileges." <<
            std::endl;
        config.displaySudoInstructions();
        std::cout << "\nConfiguration displayed above (dry-run mode)." <<
            std::endl;
        return 0;
    }

    // Automatically save the configuration without prompting
    std::cout << "\nSaving configuration to /etc/xinetd.d/vpa..." << std::endl;

    // Create backup first
    std::cout << "Creating backup of existing configuration..." << std::endl;
    if (!config.createBackup())
    {
        std::cout << "WARNING: Could not create backup file." << std::endl;
    }

    // Save the configuration
    if (config.saveConfig())
    {
        std::cout << "SUCCESS: Configuration saved to /etc/xinetd.d/vpa" <<
            std::endl;

        // Automatically reload xinetd
        std::cout << "Reloading xinetd service..." << std::endl;
        if (config.reloadXinetd())
        {
            std::cout << "SUCCESS: xinetd reloaded successfully." << std::endl;
        }
        else
        {
            std::cout <<
                "ERROR: Failed to reload xinetd. You may need to restart it manually."
                << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR: Failed to save configuration to /etc/xinetd.d/vpa"
            << std::endl;
        return 1;
    }

    return 0;
}

void log_diag()
{
    CLog log(__FILE__, __FUNCTION__);
    log.write("test message");
}

/**
 * The main entry point of the application. This function initializes
 * necessary components, executes core functionality by invoking specific
 * diagnostic and utility methods, and manages the overall application logic.
 *
 * @return An integer indicating the application's exit status. EXIT_SUCCESS
 * is returned upon successful completion.
 */
int main()
{
    auto* pMwFw = new mwfw2(__FILE__, __FUNCTION__);
    sine();
    //shmvars();
    //auth_users();
    //configini();
    //struct_diag();
    services_diag();
    xinetdcfg_diag();

    // cliLogin::checkPreviousLogin(
    //     "/home/doug/.config/multiware/config.ini");
    //
    // log_diag();

    return EXIT_SUCCESS;
}
