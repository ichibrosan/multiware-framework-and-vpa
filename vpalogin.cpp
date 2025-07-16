////////////////////////////////////////////////////////////////////
// ~/public_html/fw/vpalogin.cpp 2025-07-15 18:16 dwg -           //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

window* gpWin;

// Function to read password without echoing to terminal
std::string getPassword()
{
    std::string password;
    char ch;

    // Read characters one by one
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (ch == '\b' || ch == 127)
        {
            // Handle backspace
            if (!password.empty())
            {
                password.pop_back();
                std::cout << "\b \b";
                // Move cursor back, print space, move back again
                std::cout.flush();
            }
        }
        else
        {
            password += ch;
            std::cout << '*'; // Show asterisk for each character
            std::cout.flush();
        }
    }

    return password;
}

/**************************************************************
 * Display Retro Header Information IBM 5150 Monochrome style *
 **************************************************************/
void sine()
{
    gpWin = new window();
    gpSemiGr->cosmetics(
        SRUL, SRUR, SRLL, // Corner characters: ┌ ┐ └ ┘
        SRLR, SVSR, SVSL, // Right corner and separators
        SH, SV); // Horizontal ─ and vertical │ lines
    char szVersion[64];
    sprintf(szVersion, "Virtual Protocol Adapter vpalogin Utility "
            "Ver %d.%d.%d.%d",RMAJ,RMIN,RREV,RBLD);
    gpWin->set_title(szVersion);
    std::string ssCopr = "  Copyright ";
    ssCopr.append("(c)"); // Append copyright symbol for compatibility
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");
    gpWin->add_row(ssCopr);
    //    gpWin->render();
}

void set_configini_creds(int handle)
{
    char szConfigFQFS[FQFS_SIZE_MAX];
    time_t t = time(NULL);

    strcpy(szConfigFQFS, gpSh->m_pShMemng->szConfigRoot);
    strcat(szConfigFQFS, "/config.ini");
    cfgini config(szConfigFQFS);
    if (!config.load())
    {
        config.createNew();
    }
    config.addSection("Credentials");
    config.setVariable(
        "Credentials",
        "authusername",
        gpSh->m_pShMemng->creds[handle].szAuthUserName);
    config.setVariable(
        "Credentials",
        "authfirstname",
        gpSh->m_pShMemng->creds[handle].szAuthFirstName);

    config.setVariable(
        "Credentials",
        "authlastname",
        gpSh->m_pShMemng->creds[handle].szAuthLastName);

    config.setVariable(
        "Credentials",
        "authlevel",
        gpSh->m_pShMemng->creds[handle].szAuthLevel);


    config.setVariable(
        "Credentials",
        "handle",
        std::to_string(handle));
    config.setVariable(
        "Credentials",
        "last_login",
        std::to_string(t));
    config.save();
}


int main(int argc, char** argv)
{
    auto gpMwFw = new mwfw2(__FILE__, __FUNCTION__);
    sine();
    std::string username;
    std::string password;

    // Prompt for username
    std::cout << "Username: ";
    std::getline(std::cin, username);

    // Prompt for password (hidden input)
    std::cout << "Password: ";

    // Disable buffering and echo for password input
    struct termios oldTermios, newTermios;
    tcgetattr(STDIN_FILENO, &oldTermios);
    newTermios = oldTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);

    password = getPassword();

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);

    std::cout << std::endl; // Add newline since password input doesn't echo

    // Validate that both fields are not empty
    if (username.empty() || password.empty())
    {
        std::cerr << "Error: Username and password cannot be empty." <<
            std::endl;
        return 1;
    }

    // Display confirmation (don't show the actual password)
    //std::cout << "Login attempt for user: " << username << std::endl;

    /**
      * @brief Initialize and parse the password database
      *
      * Creates a CSV reader instance for the passwd.csv file and parses
      * the user credential data into memory for authentication processing.
      */
    gpCsv = new readCsv("passwd.csv");
    gpCsv->parseData();

    /**
     * @brief Authenticate user credentials
     *
     * Performs username/password lookup against the parsed CSV data.
     * Returns a handle (index) to the user record if authentication succeeds,
     * or RETURN_FAILURE if authentication fails.
     */
    int handle =
        gpPassword->lookup_username_password(username, password);

    // Here you would typically authenticate the user
    // For demonstration, just show success message
    //std::cout << "Authentication data received successfully." << std::endl;

    //std::cout << "User handle: " << handle << std::endl;

    if (handle < 4)
    {
        std::cout << "Synchronization Error!!" << std::endl;
        exit(1);
    }
    else
    {
        //std::cout << "User is a valid member of the VPA." << std::endl;

        /**
         * @brief Initialize VPA RPC client
         *
         * Creates the CVpaRpc client instance with connection parameters:
         * - Server hostname: "daphne"
         * - Service name: "vpa"
         *
         * The constructor automatically initiates the authentication process
         * by sending a VPARPC_FUNC_GET_AUTH request to the server.
         */
        //CVpaRpc* pVpaRpc = new CVpaRpc(argv[1], argv[2]);
        CVpaRpc* pVpaRpc = new CVpaRpc("192.168.4.17", "vpa");

        /**
         * @brief Display authentication request/response details
         *
         * Outputs comprehensive debugging information about the authentication
         * process, including both the request parameters sent to the server
         * and the response data received back.
         */
        // ====================================================================
        // SERVER VERSION INFORMATION RETRIEVAL SECTION
        // ====================================================================

        /**
         * @brief Retrieve server version information
         *
         * Sends a VPARPC_FUNC_VERSION request to the server to obtain
         * version information about the remote RPC service.
         */
        pVpaRpc->get_version();

        /**
         * @brief Display version request/response details
         *
         * Outputs debugging information about the version request operation,
         * showing both the request parameters and the server's version
         * response.
         */
        // ====================================================================
        // USER LOOKUP OPERATION SECTION
        // ====================================================================

        /**
         * @brief Perform user lookup operation
         *
         * Executes a VPARPC_FUNC_LOOKUP request to authenticate a user
         * and obtain a session handle for subsequent operations.
         */
        pVpaRpc->get_lookup();

        /**
         * @brief Display lookup request/response details
         *
         * Outputs comprehensive debugging information about the lookup
         * operation, including authentication parameters, user credentials,
         * and the resulting session handle.
         *
         * Request structure includes:
         * - eVersion: Protocol version
         * - nSize: Request size
         * - eFunc: Function identifier (VPARPC_FUNC_LOOKUP)
         * - szAuth: Authentication token
         * - szUsername: User's login name
         * - szPassword: User's password
         *
         * Response structure includes:
         * - eStatus: Operation status
         * - iHandle: Session handle for future requests
         */
        // ====================================================================
        // USER CREDENTIALS RETRIEVAL SECTION
        // ====================================================================

        /**
         * @brief Retrieve comprehensive user credentials
         *
         * Executes a VPARPC_FUNC_CREDS request using the session handle
         * obtained from the lookup operation to retrieve detailed user
         * information and session metadata.
         */
        pVpaRpc->get_creds();


        set_configini_creds(handle);


        /**
         * @brief Display credentials request/response details
         *
         * Outputs extensive debugging information about the credentials
         * operation,
         * including both request parameters and the comprehensive user data
         * returned by the server.
         *
         * Request structure includes:
         * - eVersion: Protocol version
         * - nSize: Request size
         * - eFunc: Function identifier (VPARPC_FUNC_CREDS)
         * - szAuth: Authentication token
         * - iHandle: Session handle from lookup operation
         *
         * Response structure includes:
         * - eStatus: Operation status
         * - szAuthUserName: User's login name
         * - szAuthFirstName: User's first name
         * - szAuthLastName: User's last name
         * - szAuthUUID: User's unique identifier
         * - szAuthLevel: User's authorization level
         * - szRemoteHost: Remote hostname information
         * - szRemoteAddr: Remote IP address information
         * - szHttpUserAgent: HTTP user agent string
         */
        //pVpaRpc->get_urls();

        // ====================================================================
        // WINDOW DISPLAY FORMATTING SECTION
        // ====================================================================

        // /**
        //  * @brief Format and display authentication token
        //  *
        //  * Retrieves the authentication token from the RPC client and
        //  * formats it for display in the main window.
        //  */
        // char szAuthToken[64];
        // sprintf(szAuthToken, "  auth:         %s",
        //         pVpaRpc->get_auth().c_str());
        // gpWin->add_row(szAuthToken);

        // /**
        //  * @brief Format and display server version
        //  *
        //  * Retrieves the server version information and formats it
        //  * for display in the main window.
        //  */
        // char szVersion[64];
        // sprintf(szVersion, "  version:      %s",
        //         pVpaRpc->get_version_version().c_str());
        // gpWin->add_row(szVersion);
        //
        // /**
        //  * @brief Format and display session handle
        //  *
        //  * Retrieves the session handle from the lookup operation
        //  * and formats it for display in the main window.
        //  */
        // int iHandle = pVpaRpc->m_vparpc_request_lookup.iHandle;
        // char szHandle[64];
        // sprintf(szHandle, "  handle:       %d", iHandle);
        // gpWin->add_row(szHandle);
        //
        // /**
        //  * @brief Format and display user credential information
        //  *
        //  * Retrieves various user credential fields and formats them
        //  * for display in the main window. Uses a reusable buffer
        //  * for efficient memory usage.
        //  */
        char szBuffer[BUFSIZ];
        // Display username
        sprintf(szBuffer,
                "  UserName:     %s",
                pVpaRpc->get_creds_username().c_str());
        gpWin->add_row(szBuffer);
        // Display first name
        sprintf(szBuffer,
                "  FirstName:    %s",
                pVpaRpc->get_creds_firstname().c_str());
        gpWin->add_row(szBuffer);
        // Display last name
        sprintf(szBuffer,
                "  LastName:     %s",
                pVpaRpc->get_creds_lastname().c_str());
        gpWin->add_row(szBuffer);

        // // Display authentication UUID
        // sprintf(szBuffer,
        //         "  Auth:         %s",
        //         pVpaRpc->get_creds_auth().c_str());
        // gpWin->add_row(szBuffer);

        // Display authorization level
        sprintf(szBuffer,
                "  Level:        %s",
                pVpaRpc->get_creds_level().c_str());
        gpWin->add_row(szBuffer);
        //
        // // Display IP
        // sprintf(szBuffer,
        //         "  IP:           %s",
        //         pVpaRpc->get_urls_ip().c_str());
        // gpWin->add_row(szBuffer);
        //
        // // Display szCgiRoot
        // sprintf(szBuffer,
        //         "  szCgiRoot:    %s",
        //         pVpaRpc->get_urls_cgiroot().c_str());
        // gpWin->add_row(szBuffer);
        //
        // // Display szStylesRoot
        // sprintf(szBuffer,
        //         "  szStylesRoot: %s",
        //         pVpaRpc->get_urls_stylesroot().c_str());
        // gpWin->add_row(szBuffer);
        //
        // // ====================================================================
        // // FINAL RENDERING AND CLEANUP SECTION
        // // ====================================================================
        //
        // /**
        //  * @brief Render the final window display
        //  *
        //  * Processes all the added rows and displays the complete window
        //  * with formatted borders, title, and content to the console.
        //  */
        gpWin->render();

        /**
         * @brief Return success status
         *
         * Indicates successful completion of all RPC operations and
         * window display functionality.
         */
        return EXIT_SUCCESS;
    }
}
