
////////////////////////////////////////////////////////////////////
// ~/public_html/fw/install.cpp 2025-08-09 09:30 dwg -            //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

/**
 * @file installer.cpp
 * @brief Installation program for the Virtual Protocol Adapter and Multiware FrameWork
 * 
 * This is the install program for the Virtual Protocol Adapter and
 * Multiware FrameWork. Running this program should do everything
 * necessary to prepare a debian based operating system to build and
 * run the Multiware System. The only mandatory prerequisite is that
 * the user account owning the Multiware source tree must have sudo
 * privileges.
 * 
 * The installer performs various diagnostic and setup operations including:
 * - System environment validation
 * - Service configuration and registration
 * - Shared memory initialization
 * - Configuration file management
 * - User authentication setup
 * - Network service diagnostics
 * 
 * @author MultiWare Engineering
 * @version Uses version constants from version.h
 * @date 2025-08-09
 */

#include "mwfw2.h"
#include "installer.h"

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
 * @brief Outputs the sizes and padding information for various request structure types.
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

/**
 * @brief Service Management Features Documentation
 * 
 * The CServices Class provides comprehensive service management capabilities:
 * 
 * **Service Existence Check**:
 * - `hasService()` - Check if a service exists by name
 * - `hasService(name, protocol)` - Check if a service exists for a specific protocol
 * 
 * **Service Addition**:
 * - `addService()` - Add new services to `/etc/services` with validation
 * - Prevents duplicate entries and validates input
 * 
 * **Service Retrieval**:
 * - `getService()` - Get service information by name
 * - `getServiceByPort()` - Get service by port and protocol
 * - `getServicePort()` - Get port number for a service
 * - `getServiceName()` - Get service name for a port
 * 
 * **Service Management**:
 * - `removeService()` - Remove services from `/etc/services`
 * - `findServices()` - Search for services by pattern
 * - `reloadCache()` - Refresh the internal cache
 * 
 * **Safety Features**:
 * - `createBackup()` - Create backup before modifications
 * - `restoreFromBackup()` - Restore from backup if needed
 * - `isServicesFileWritable()` - Check permissions before writing
 */

/**
 * @brief Performs diagnostic operations related to service management.
 *
 * This function interacts with an instance of the CServices class to:
 * - Check the existence of specific services.
 * - Add services if they do not already exist, specifying their name, port, protocol, and aliases.
 * - Retrieve a list of services matching a specific pattern ("http").
 * - Log outputs to indicate the status of service operations such as existence checks or successful additions.
 * 
 * The function manages VPA-related services including:
 * - vpa: Main VPA service on port 5164/tcp
 * - vpa-disc: Discovery service on port 5164/udp
 * - vpad-start: Start service on port 65353/tcp
 * - vpa-netstat: Network statistics service on port 65354/tcp
 * - vpa-ip: IP service on port 65355/tcp
 * - vpa-curl: CURL service on port 5164/tcp
 * - vpa-http: HTTP service on port 65357/tcp
 * - vpa-https: HTTPS service on port 65358/tcp
 * - vpa-ipcs: IPC service on port 65359/tcp
 * - vpa-iphone: iPhone service on port 65360/tcp
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
 * @brief Performs logging diagnostic operations.
 * 
 * Creates a CLog instance and writes a test message to demonstrate
 * the logging functionality. Uses the current file and function
 * name for log context.
 */
void log_diag()
{
    CLog log(__FILE__, __FUNCTION__);
    log.write("test message");
}

/**
 * @brief Validates that the source is installed in the correct development location.
 *
 * Checks if the installer source code is located in the expected development
 * directory structure. The expected location is `/home/{username}/public_html/fw/`.
 * This validation ensures that the installer is running from the proper
 * development environment before proceeding with installation operations.
 * 
 * @return true if source is installed in acceptable location, false otherwise
 */
bool installer::is_devo_root()
{
    std::string ssDevoRoot = gpOS->file2path(__FILE__);
    std::string ssDevoRoot2 = "/home/";
    ssDevoRoot2.append(gpSh->m_pShMemng->szUser);
    ssDevoRoot2.append("/public_html/fw/");
    if (ssDevoRoot == ssDevoRoot2) {
        m_pWin->add_row("is_devo_root() returning true");
        return true;
    }
    m_pWin->add_row("is_devo_root() returning false");
    return false;
}

bool installer::can_user_sudo()
{   bool bFinalRetcode;
    std::string ssTemp = __FUNCTION__;
    ssTemp.append("()");
    m_pWin->add_row(ssTemp);

    int iRetcode = system("sudo mkdir -p /etc/installer.test");
    char szTemp[128];
    sprintf(szTemp, "iRetcode is %d",iRetcode);

    if (256==iRetcode)
    {
        m_pWin->add_row("  test failed, manual visudo required");
        bFinalRetcode = false;
    }
    if (0==iRetcode)
    {
        m_pWin -> add_row("  test successful, user sudo enabled");
        bFinalRetcode = true;
        system("sudo rm -r -f /etc/installer.test");
    }

    return bFinalRetcode;
}


/**
 * @brief Validates that the development user has appropriate sudo privileges.
 * 
 * Tests sudo access by attempting to create the `/etc/installer` directory.
 * This is a critical requirement for the installer to function properly,
 * as many installation operations require elevated privileges to modify
 * system files and directories.
 * 
 * @return true if user has default sudo privileges, false otherwise
 */
bool installer::is_etc_installer()
{   bool bFinalRetcode;

    int iRetcode = system("sudo mkdir -p /etc/installer");
    char szTemp[128];
    sprintf(szTemp, "iRetcode is %d",iRetcode);

    if (256==iRetcode)
    {
        m_pWin->add_row("is_etc_installer() returning false");
        bFinalRetcode = false;
    }
    if (0==iRetcode)
    {
        m_pWin -> add_row("is_etc_installer() returning true");
        bFinalRetcode = true;
    }

    return bFinalRetcode;
}

/**
 * @brief Checks if xinetd is installed and installs it if necessary.
 *
 * Verifies that the xinetd service is installed on the system by checking
 * for the presence of the xinetd binary. If xinetd is not found, attempts
 * to install it using the system package manager (apt-get for Debian-based
 * systems). This is a prerequisite for the VPA xinetd configuration to work
 * properly.
 *
 * @return true if xinetd is installed or successfully installed, false otherwise
 */
bool installer::is_xinetd_installed()
{
    // First check if xinetd is already installed
    int iRetcode = system("which xinetd > /dev/null 2>&1");
    if (0 == iRetcode)
    {   m_pWin->add_row("is_xinetd_installed() returned true");
        return true;
    }

    // xinetd is not installed, attempt to install it
    m_pWin->add_row("xinetd not found, installing...");

    // Update package lists first
    m_pWin->add_row("Updating package lists...");
    iRetcode = system("sudo apt-get update > /dev/null 2>&1");
    if (0 != iRetcode)
    {
        m_pWin->add_row("WARNING: Failed to update package lists");
        // Continue anyway as this might not be critical
    }

    // Install xinetd
    m_pWin->add_row("Upgrading package lists...");
    iRetcode = system("sudo apt-get install -y xinetd > /dev/null 2>&1");

    if (0 == iRetcode)
    {
        // Verify installation was successful
        iRetcode = system("which xinetd > /dev/null 2>&1");
        if (0 == iRetcode)
        {
            m_pWin->add_row("xinetd successfully installed");

            // Enable and start xinetd service
            system("sudo systemctl enable xinetd > /dev/null 2>&1");
            system("sudo systemctl start xinetd > /dev/null 2>&1");

            return true;
        }
        else
        {
            m_pWin->add_row("ERROR: xinetd installation verification failed");
            return false;
        }
    }
    else
    {
        m_pWin->add_row("ERROR: Failed to install xinetd");
        m_pWin->add_row("Please install xinetd manually: sudo apt-get install xinetd");
        return false;
    }
}

bool installer::is_xinet_configured()
{
    xinetcfg config;

    std::string ssTemp = __FUNCTION__;
    ssTemp.append("()");
    m_pWin->add_row(ssTemp);

    // Test VPA configuration generation
    // std::cout << "=== VPA Xinetd Configuration Test ===" << std::endl;
    // std::cout << "Number of services configured: " << config.getServiceCount()
    //           << std::endl;

    char szTemp[128];
    sprintf(szTemp,
            "  Number of services configured: %ld",
            config.getServiceCount());
    m_pWin->add_row(szTemp);



    // Display service status
    //config.displayVpaServiceStatus();

    // Generate and display configuration
    //std::cout << "\n=== Generated VPA Configuration ===" << std::endl;

    std::string vpaConfig = config.generateVpaXinetdConfig();
    //std::cout << vpaConfig << std::endl;

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
    //std::cout << "\nSaving configuration to /etc/xinetd.d/vpa..." << std::endl;
    m_pWin->add_row("  Saving configuration to /etc/xinetd.d/vpa...");

    // Create backup first
    //std::cout << "Creating backup of existing configuration..." << std::endl;
    if (!config.createBackup())
    {
        m_pWin->add_row("  WARNING: Could not create backup file.");
        //std::cout << "WARNING: Could not create backup file." << std::endl;
    }

    // Save the configuration
    if (config.saveConfig())
    {
            // std::cout << "SUCCESS: Configuration saved to /etc/xinetd.d/vpa" <<
            //     std::endl;
        m_pWin->add_row("  Configuration saved to /etc/xinetd.d/vpa");

        // Automatically reload xinetd
        // std::cout << "Reloading xinetd service..." << std::endl;
        m_pWin->add_row("  Reloading xinetd service...");

        if (config.reloadXinetd())
        {
            //std::cout << "SUCCESS: xinetd reloaded successfully." << std::endl;
            m_pWin->add_row("  xinetd reloaded successfully.");
        }
        else
        {
            // std::cout <<
            //     "ERROR: Failed to reload xinetd. You may need to restart it manually."
            //     << std::endl;
            m_pWin->add_row("  ERROR: Failed to reload xinetd.");
            m_pWin->add_row("  ERROR: You may need to restart it manually.");

        }
    }
    else
    {
        // std::cout << "ERROR: Failed to save configuration to /etc/xinetd.d/vpa"
        //     << std::endl;
        m_pWin->add_row("  ERROR: Failed to save configuration to /etc/xinetd.d/vpa");
        return 1;
    }

    return 0;
}




/**
 * @brief Constructor for the installer class.
 * 
 * Initializes the installer with a graphical window interface and sets up
 * the display cosmetics using semi-graphics characters. Creates the main
 * installer window with appropriate title and license information.
 * 
 * The window is configured with:
 * - Semi-graphics border characters for a professional appearance
 * - Version information from the build constants
 * - Creative Commons CC0 license information
 */
installer::installer()
{
    m_pWin = new window();
    gpSemiGr->cosmetics(
            SRUL, SRUR, SRLL, // Corner characters: ┌ ┐ └ ┘
            SRLR, SVSR, SVSL, // Right corner and separators
            SH, SV); // Horizontal ─ and vertical │ lines
    char szVersion[64];
    sprintf(szVersion, "Virtual Protocol Adapter Installer Utility "
                "Ver %d.%d.%d.%d",RMAJ,RMIN,RREV,RBLD);
    m_pWin->set_title(szVersion);
    m_pWin->set_license("Creative Commons CC0 1.0 Universal Public Domain License");
}

/**
 * @brief Destructor for the installer class.
 * 
 * Renders the final window display before cleanup. This ensures that
 * all installation progress and results are properly displayed to
 * the user before the installer terminates.
 */
installer::~installer()
{
    m_pWin->render();
}

/**
 * @brief Main entry point of the VPA installer application.
 * 
 * The main entry point of the application. This function initializes
 * necessary components, executes core functionality by invoking specific
 * diagnostic and utility methods, and manages the overall application logic.
 * 
 * The main function performs the following operations:
 * 1. Initializes the Multiware Framework (mwfw2)
 * 2. Creates and configures the installer instance
 * 3. Validates the development environment and sudo privileges
 * 4. Provides access to various diagnostic functions (currently commented out)
 * 
 * Available diagnostic functions include:
 * - shmvars(): Shared memory diagnostics
 * - auth_users(): User authentication diagnostics  
 * - configini(): Configuration file management
 * - struct_diag(): Structure size diagnostics
 * - services_diag(): Network service management
 * - xinetdcfg_diag(): Xinetd configuration management
 * - log_diag(): Logging system diagnostics
 *
 * @return EXIT_SUCCESS upon successful completion
 */
int main()
{
    auto * pMwFw = new mwfw2(__FILE__, __FUNCTION__);
    auto * pInst = new installer();
    pInst->is_devo_root();
    pInst->can_user_sudo();
    pInst->is_etc_installer();
    pInst->is_xinetd_installed();
    pInst->is_xinet_configured();
    pInst->is_apache2_installed();
    pInst->check_dir_index_cgi();


    // Diagnostic functions available for testing and validation
    // Uncomment as needed for specific installation tasks
    //shmvars();
    //auth_users();
    //configini();
    //struct_diag();
    //services_diag();
    //xinetdcfg_diag();
    //cliLogin::checkPreviousLogin("/home/doug/.config/multiware/config.ini");
    //log_diag();

    delete pInst;
    delete pMwFw;
    return EXIT_SUCCESS;
}

/**
 * @brief Check if Apache2 userdir module is enabled
 *
 * @return true if userdir.conf exists in mods-enabled, false otherwise
 */
bool installer::check_userdir_enabled()
{
    int iRetcode = system("test -f /etc/apache2/mods-enabled/userdir.conf 2>/dev/null");

    if (0 == iRetcode)
    {
        std::cout << "userdir module is enabled" << std::endl;
        return true;
    }
    else
    {
        std::cout << "userdir module is not enabled" << std::endl;
        return false;
    }
}

/**
 * @brief Check if userdir.conf contains ExecCGI option
 *
 * @return true if ExecCGI is found in userdir.conf, false otherwise
 */
bool installer::check_userdir_execcgi()
{
    // First check if the file exists
    int iRetcode = system("test -f /etc/apache2/mods-enabled/userdir.conf 2>/dev/null");

    if (0 != iRetcode)
    {
        std::cout << "userdir.conf not found" << std::endl;
        return false;
    }

    // Search for ExecCGI in the file (case-insensitive)
    iRetcode = system("grep -i 'ExecCGI' /etc/apache2/mods-enabled/userdir.conf > /dev/null 2>&1");

    if (0 == iRetcode)
    {
        std::cout << "ExecCGI found in userdir.conf" << std::endl;
        return true;
    }
    else
    {
        std::cout << "ExecCGI not found in userdir.conf" << std::endl;
        return false;
    }
}

bool installer::add_index_cgi_to_dir()
{
    // First check if the file exists
    int iRetcode = system("test -f /etc/apache2/mods-enabled/dir.conf 2>/dev/null");

    if (0 != iRetcode)
    {
        std::cout << "dir.conf not found" << std::endl;
        return false;
    }

    // Check if index.cgi is already present
    iRetcode = system("grep -i 'index\\.cgi' /etc/apache2/mods-enabled/dir.conf > /dev/null 2>&1");

    if (0 == iRetcode)
    {
        std::cout << "index.cgi already exists in dir.conf" << std::endl;
        return true;
    }

    // Create backup first
    iRetcode = system("sudo cp /etc/apache2/mods-enabled/dir.conf /etc/apache2/mods-enabled/dir.conf.backup");

    if (0 != iRetcode)
    {
        std::cout << "Failed to create backup of dir.conf" << std::endl;
        return false;
    }

    // Add index.cgi to DirectoryIndex line using sed
    // This adds index.cgi as the first entry in DirectoryIndex
    iRetcode = system("sudo sed -i '/^[[:space:]]*DirectoryIndex/ s/DirectoryIndex/DirectoryIndex index.cgi/' /etc/apache2/mods-enabled/dir.conf");

    if (0 == iRetcode)
    {
        // Verify the change was made
        iRetcode = system("grep -i 'index\\.cgi' /etc/apache2/mods-enabled/dir.conf > /dev/null 2>&1");

        if (0 == iRetcode)
        {
            std::cout << "index.cgi successfully added to dir.conf" << std::endl;
            return true;
        }
        else
        {
            std::cout << "Failed to verify index.cgi addition" << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Failed to modify dir.conf" << std::endl;
        return false;
    }
}


/**
 * @brief Check if dir.conf contains index.cgi in DirectoryIndex
 *
 * @return true if index.cgi is found in dir.conf, false otherwise
 */
bool installer::check_dir_index_cgi()
{

    // Search for index.cgi in the file
    int iRetcode = system("grep -i 'index\\.cgi' /etc/apache2/mods-enabled/dir.conf > /dev/null 2>&1");

    if (0 == iRetcode)
    {
        m_pWin->add_row("  index.cgi found in dir.conf");
        return true;
    }
    else
    {
        m_pWin->add_row("  index.cgi not found in dir.conf");
        add_index_cgi_to_dir();
        m_pWin->add_row("  DirectoryIndex index.cgi added to dir.conf");
        return true;
    }
}



/**
 * @brief Checks if Apache2 web server is installed and detects its status.
 *
 * Verifies that the Apache2 web server is installed on the system by checking
 * for the presence of the apache2 binary and service. This function performs
 * multiple checks to ensure Apache2 is properly installed and configured:
 * - Checks for apache2 binary existence
 * - Verifies apache2 service status
 * - Tests configuration validity
 * 
 * This is important for the VPA framework as it may need to integrate with
 * or configure Apache2 for web-based components.
 * 
 * @return true if Apache2 is installed and properly configured, false otherwise
 */
bool installer::is_apache2_installed()
{
    std::string ssTemp = __FUNCTION__;
    ssTemp.append("()");
    m_pWin->add_row(ssTemp);
    
    // Check if apache2 binary exists
    int iRetcode = system("which apache2 > /dev/null 2>&1");
    
    if (0 != iRetcode)
    {
        // Try alternative apache2ctl command
        iRetcode = system("which apache2ctl > /dev/null 2>&1");
        if (0 != iRetcode)
        {
            m_pWin->add_row("  Apache2 binary not found");
            m_pWin->add_row("  is_apache2_installed() returning false");
            return false;
        }
    }
    
    m_pWin->add_row("  Apache2 binary found");
    
    // Check if apache2 service is available
    iRetcode = system("systemctl list-unit-files | grep -q apache2.service 2>/dev/null");
    
    if (0 == iRetcode)
    {
        m_pWin->add_row("  Apache2 service is available");
        
        // Check service status
        iRetcode = system("systemctl is-active apache2 > /dev/null 2>&1");
        if (0 == iRetcode)
        {
            m_pWin->add_row("  Apache2 service is active");
        }
        else
        {
            m_pWin->add_row("  Apache2 service is not active");
        }
        
        // Check if service is enabled
        iRetcode = system("systemctl is-enabled apache2 > /dev/null 2>&1");
        if (0 == iRetcode)
        {
            m_pWin->add_row("  Apache2 service is enabled");
        }
        else
        {
            m_pWin->add_row("  Apache2 service is not enabled");
        }
    }
    else
    {
        m_pWin->add_row("  Apache2 service not found in systemctl");
    }
    
    // Test Apache2 configuration
    iRetcode = system("apache2ctl configtest > /dev/null 2>&1");
    if(0 == iRetcode)
    {
        m_pWin->add_row("  Apache2 configuration is valid");
    }
    else
    {
        m_pWin->add_row("  Apache2 configuration has issues");
    }

    // Check for common Apache2 directories
    iRetcode = system("test -d /etc/apache2 2>/dev/null");
    if (0 == iRetcode)
    {
        m_pWin->add_row("  Apache2 configuration directory exists");
    }
    else
    {
        m_pWin->add_row("  Apache2 configuration directory not found");
    }

    // Check for Apache2 modules directory
    iRetcode = system("test -d /etc/apache2/mods-available 2>/dev/null");
    if (0 == iRetcode)
    {
        m_pWin->add_row("  Apache2 modules directory exists");
    }

    bool bUserdirEnabled = check_userdir_enabled();
    if (bUserdirEnabled)
    {
        m_pWin->add_row("  userdir module was enabled");
    } else
    {
        system("sudo a2enmod userdir");
        m_pWin->add_row("  userdir module now enabled");
    }

    bool bUserdirExecCGI = check_userdir_execcgi();
    if (bUserdirExecCGI)
    {
        m_pWin->add_row("  ExecCGI option was found in userdir.conf");
    } else {
        //system("sudo sed -i 's/ExecCGI/ExecCGI\n\tSetHandler cgi-script/' /etc/apache2/mods-enabled/userdir.conf");
        m_pWin->add_row("  ExecCGI option was not found in userdir.conf");
        iRetcode = system("sudo sed -i '/^[[:space:]]*Options/ { /ExecCGI/!s/Options\\([[:space:]]\\)/Options ExecCGI\\1/ }' /etc/apache2/mods-enabled/userdir.conf");
        m_pWin->add_row("  ExecCGI option has been added in userdir.conf");
     }












    // Final determination - Apache2 is considered installed if binary exists
    m_pWin->add_row("  is_apache2_installed() returning true");
    return true;
}

