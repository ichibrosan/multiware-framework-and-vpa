// File: look.cpp - Updated 2025-07-14 15:30:00
// This is the complete corrected implementation for look.cpp
// Includes proper authentication using existing password::lookup_username_password()

#include "mwfw2.h"
#include "cfgini.h"
#include "xinetdcfg.h"
#include "password.h"  // Add this include for password class
#include "CVpaRpc.h"   // Add this include for VPA RPC functionality
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cstdlib>

// Function declarations
bool isLoginExpired(const std::string& lastLoginStr);
void queryUserForLogin(cfgini& config);
std::string getPassword();

// Login timeout in seconds (24 hours = 86400 seconds)
const time_t LOGIN_TIMEOUT = 60; // 86400;

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

/**************************************************************
 * Display Retro Header Information IBM 5150 Monochrome style *
 **************************************************************/
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

/****************************************
 * Display Some Shared Memory Variables *
 ****************************************/
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
