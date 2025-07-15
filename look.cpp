/////////////////////////////////////////////////////////////////////////
// /home/doug/public_html/fw/look.cpp 2025/07/14                       //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * Checks if a login session has expired based on the given last login timestamp.
 *
 * @param lastLoginStr A string representing the last login timestamp in seconds
 *                     since the Unix epoch. If the string is empty or invalid,
 *                     the method treats the login as expired.
 * @return True if the login session has expired or if the timestamp is invalid;
 *         otherwise, returns false.
 */
bool isLoginExpired(const std::string& lastLoginStr);
/**
 * Prompts the user to log in by entering a username and password, authenticates the credentials,
 * and updates the provided configuration object with the authentication details.
 *
 * @param config A reference to a cfgini object where the login credentials,
 *               authentication handle, and last login timestamp will be stored.
 */
void queryUserForLogin(cfgini& config);
/**
 * @brief Prompts the user for a password input without echoing characters.
 *
 * This function captures the user's password input securely by disabling
 * terminal character echoing during the input process. The password is
 * then returned as a string.
 *
 * @return The password input by the user.
 */
std::string getPassword();

/**
 * @brief Specifies the timeout duration for login sessions.
 *
 * LOGIN_TIMEOUT defines the maximum amount of time, in seconds,
 * that a login session remains valid without activity. If the time
 * since the last login exceeds this value, the session is considered
 * expired. LOGIN_TIMEOUT_SECONDS is defined in include/fw-limits.h
 */
const time_t LOGIN_TIMEOUT = LOGIN_TIMEOUT_SECONDS;

/**
 * Checks whether the login session has expired based on the last login timestamp.
 *
 * @param lastLoginStr The last login timestamp as a string.
 *                     It should be convertible to a time_t value.
 *                     If empty or invalid, the session is considered expired.
 * @return True if the login session has expired, false otherwise.
 *         If the timestamp cannot be parsed, it is treated as expired.
 */
bool isLoginExpired(const std::string& lastLoginStr)
{
    if (lastLoginStr.empty())
    {
        printf("DEBUG: No last login timestamp found\n");
        return true;
    }

    try
    {
        // Convert string to time_t
        time_t lastLogin = static_cast<time_t>(std::stoll(lastLoginStr));
        time_t currentTime = time(nullptr);

        printf("DEBUG: Last login timestamp: %ld\n", lastLogin);
        printf("DEBUG: Current timestamp: %ld\n", currentTime);
        printf("DEBUG: Time difference: %ld seconds\n",
               currentTime - lastLogin);
        printf("DEBUG: Timeout threshold: %ld seconds\n", LOGIN_TIMEOUT);

        // Check if current time minus last login exceeds timeout
        bool expired = (currentTime - lastLogin) > LOGIN_TIMEOUT;
        printf("DEBUG: Login expired: %s\n", expired ? "YES" : "NO");

        return expired;
    }
    catch (const std::exception& e)
    {
        printf("ERROR: Failed to parse last login timestamp: %s\n", e.what());
        return true; // Treat parsing errors as expired
    }
}

/**
 * Prompts the user for their username and password for VPA login, verifies the credentials,
 * and updates the configuration object with authentication details.
 *
 * The method fetches the username and password from the user, verifies the credentials via
 * the password lookup functionality, and updates the configuration object with the authenticated
 * user's information, including the username, authentication handle, and the last login time.
 *
 * @param config A reference to a cfgini object where the login credentials and authentication details
 *               will be stored or updated.
 */
void queryUserForLogin(cfgini& config)
{
    printf("\n=== VPA Login Required ===\n");

    // Get username
    std::string username;
    printf("Username: ");
    std::flush(std::cout);
    std::getline(std::cin, username);

    if (username.empty())
    {
        printf("Username cannot be empty. Exiting.\n");
        return;
    }

    // Get password (renamed variable to avoid conflict with class name)
    std::string userPassword = getPassword();

    if (userPassword.empty())
    {
        printf("Password cannot be empty. Exiting.\n");
        return;
    }

    // Use the existing password lookup function like vpalogin.cpp does
    password passwordObj;
    int handle = passwordObj.lookup_username_password(username, userPassword);

    if (handle <= 0)
    {
        printf("Authentication failed. Invalid username or password.\n");
        return;
    }

    printf("Authentication successful. Handle: %d\n", handle);

    // Create or update the config
    config.addSection("Credentials");
    config.setVariable("Credentials", "authusername", username);

    // Set current time as last_login
    time_t currentTime = time(nullptr);
    std::string timeStr = std::to_string(currentTime);
    config.setVariable("Credentials", "last_login", timeStr);

    printf("DEBUG: Setting last_login to: %s\n", timeStr.c_str());

    // Set the actual handle from password lookup (e.g., "4" for doug)
    config.setVariable("Credentials", "handle", std::to_string(handle));

    // Save the configuration
    if (config.save())
    {
        printf("Login credentials saved successfully.\n");
    }
    else
    {
        printf("ERROR: Failed to save login credentials.\n");
    }
}

/**
 * @brief Prompts the user to input a password with input echo disabled.
 *
 * This function disables terminal echo mode to securely capture the user's
 * password without displaying it on the screen. Echo mode is restored after
 * the password input is retrieved. In case of an error with terminal settings,
 * the password will still be captured, but without echo being disabled.
 *
 * @return The password entered by the user as a string.
 */
std::string getPassword()
{
    std::string password;
    printf("Password: ");
    std::flush(std::cout);

    // Turn off echo for password input
    struct termios old_term, new_term;
    if (tcgetattr(STDIN_FILENO, &old_term) != 0)
    {
        printf("ERROR: Failed to get terminal attributes\n");
        std::getline(std::cin, password);
        return password;
    }

    new_term = old_term;
    new_term.c_lflag &= ~(ECHO);

    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term) != 0)
    {
        printf("ERROR: Failed to set terminal attributes\n");
        std::getline(std::cin, password);
        return password;
    }

    std::getline(std::cin, password);

    // Restore echo
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);

    printf("\n");
    return password;
}

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
    std::string ssCopr = "  Copyright ";
    ssCopr.append("(c)"); // Append copyright symbol for compatibility
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");
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
    cfgini config("/home/doug/config.ini");

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

    // // Get service information
    // ServiceInfo httpService = services.getService("http", "tcp");
    // if (!httpService.name.empty()) {
    //     std::cout << "HTTP runs on port " << httpService.port << std::endl;
    // }

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

/**
 * @brief Checks for previous login credentials stored in the configuration file.
 *
 * This function attempts to load the user's configuration file to retrieve
 * authentication credentials, such as username, last login timestamp, and
 * authentication handle. If no configuration is found or if the credentials
 * are invalid, the user will be prompted to provide new login credentials.
 *
 * Behavior:
 * - Attempts to load the configuration file located at `/home/doug/.config/multiware/config.ini`.
 * - If the configuration file cannot be loaded, the user is prompted to provide fresh credentials.
 * - Checks for the presence of the VPA login section and reads the following:
 *   - `authusername`: The username used for authentication.
 *   - `last_login`: Timestamp of the last successful login.
 *   - `handle`: The authentication handle.
 * - Validates the retrieved credentials:
 *   - If the last login timestamp is present, checks whether the login has expired.
 *   - If expired, prompts the user to re-authenticate.
 *   - If no last login timestamp exists, prompts the user to re-authenticate.
 * - If valid credentials are found, prints the previous login details and confirms the login is still valid.
 * - If no credentials are found, prompts the user to provide new credentials.
 */
void check_previous_vpalogin()
{
    cfgini config("/home/doug/.config/multiware/config.ini");

    // Try to load existing config
    if (!config.load())
    {
        printf("No previous vpalogin configuration found.\n");
        // Query user for login credentials similar to vpalogin.cpp
        queryUserForLogin(config);
        return;
    }

    // Check for vpalogin section and credentials
    std::string username = config.
        getVariable("Credentials", "authusername", "");
    std::string lastLogin = config.getVariable("Credentials", "last_login", "");
    std::string authHandle = config.getVariable("Credentials", "handle", "");

    if (!username.empty())
    {
        printf("=== Previous VPA Login Information ===\n");
        printf("Username: %s\n", username.c_str());

        if (!lastLogin.empty())
        {
            printf("Last Login: %s\n", lastLogin.c_str());

            // Check if login has timed out
            if (isLoginExpired(lastLogin))
            {
                printf("Login has expired. Please re-authenticate.\n");
                queryUserForLogin(config);
                return;
            }
        }
        else
        {
            printf("No last login timestamp found. Please re-authenticate.\n");
            queryUserForLogin(config);
            return;
        }

        if (!authHandle.empty())
        {
            printf("Auth Handle: %s\n", authHandle.c_str());
        }

        printf("======================================\n");
        printf("Login is still valid.\n");
    }
    else
    {
        printf("No previous vpalogin credentials found in config.\n");
        queryUserForLogin(config);
    }
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
    //services_diag();
    //xinetdcfg_diag();
    check_previous_vpalogin();
    return EXIT_SUCCESS;
}
