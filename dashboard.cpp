////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/dashboard.cpp  2025/02/19                //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#define SHOW_PRIVILEGE_LEVEL
#define SHOW_AUTHENTICATED_USERNAME
#define SHOW_AUTHENTICATED_REAL_NAMES
//#define SHOW_AUTHENTICATION_HANDLE

#define SHOW_SCHEMA_BUTTONS
#define SHOW_SHMVAR_BUTTONS
#define SHOW_ENVVAR_BUTTONS
#define SHOW_VPAD_BUTTONS

#include "mwfw2.h"

/**
 * Constructs a dashboard object and initializes the display and
 * configurations of an authenticated or unauthenticated user's dashboard
 * based on the input credentials. It manages UI components including
 * headers, tables, and a navigation bar depending on the authentication
 * status.
 *
 * @param handle The authentication handle for the user. A valid handle
 * ensures the user is authenticated, while an invalid one leads to an
 *               unauthenticated state.
 * @param buttons The set of buttons available for the authenticated user.
 * This is replaced with default values if the user is unauthenticated.
 * @param pszFile The file path string for the dashboard setup. Used to
 * determine additional configuration details such as CGI file name.
 * @param ssUsername The username provided for authentication.
 * @param ssPassword The password provided for authentication.
 * @return None. This is a constructor and does not return a value.
 */
dashboard::dashboard(
    int handle,
    int buttons,
    const char *pszFile,
    std::string ssUsername,
    std::string ssPassword) {
    /*
     * In the case a user supplies invalid credentials to index.cgi,
     * we enter login.cgi without the ability to authenticate. This
     * leaves us with an invalid handle on entry to the dashboard.
     * We still want to put up the Goodall MultiWare Framework Dashboard
     * header, but no the empty Authenticated User and Privilege Level
     * fields. Hence, the bAuthenticated boolean.
     */
    bool bAuthenticated = false;
    int iEffectiveButtons = 0;

    int iBorder = 2;

    std::string ssFile = pszFile;
    m_pCgiBind = new cgibind();

    /*
     * Assure the handle is valid (user is authenticated)
     * If so, set bAuthenticated and use the callers buttons.
     * Otherwise, use the default iEffectiveButton (0) and turn
     * off the debug displays.
     */
    if (ROW_DATA_HDR < handle) {
        bAuthenticated = true;
        iEffectiveButtons = buttons;
    } else {
        gpSh->m_pShMemng->bDisplaySchema = false;
        gpSh->m_pShMemng->bDisplayShmVars = false;
        gpSh->m_pShMemng->bDisplayEnvVars = false;
    }

    /*
     * Look up the users credentials and copy to member data so it's
     * available to the dashboard code.
     */
    strcpy(m_szAuthUserName,
           gpSh->m_pShMemng->creds[handle].szAuthUserName);
    strcpy(m_szAuthFirstName,
           gpSh->m_pShMemng->creds[handle].szAuthFirstName);
    strcpy(m_szAuthLastName,
           gpSh->m_pShMemng->creds[handle].szAuthLastName);
    strcpy(m_szAuthLevel,
           gpSh->m_pShMemng->creds[handle].szAuthLevel);
    strcpy(m_szAuthUUID,gpSh->m_pShMemng->creds[handle].szAuthUUID);

//    ssFile = pszFile;
    std::string ssFilePath =
        std::filesystem::path(ssFile).remove_filename();
    std::string ssCgiName =
        ssFile.substr(ssFilePath.length(), ssFile.length());
    ssCgiName =
        std::filesystem::path(ssCgiName).replace_extension(".cgi");

    std::string ssAvatar = m_szAuthUserName;
    ssAvatar.append("-avatar.png");
    bool bAvatarExists = false;
    if (std::filesystem::is_regular_file(
        gpOS->genImgPath(ssAvatar.c_str(),F_OK))) {
        bAvatarExists = true;
        gpHtml->open_table(4);
        std::cout << "<tr><td class=\"dashboard\">";
        gpHtml->imgsrc(ssAvatar.c_str(), 110, 110);
        std::cout << "</td><td class=\"dashboard\">";
    }

    /*
     * Use the iBorder variable so we can avoid using a magic number in the
     * cout stream below/
     */

    std::cout
            << "<table border=" << iBorder << ">" << std::endl
            << "<tr><h3><th>Goodall MultiWare Framework Dashboard"
               "</th></h3></tr>"
            << "</table>"
            << std::endl;

    std::cout << "<table border=1>" << std::endl;

#ifdef SHOW_AUTHENTICATED_USERNAME
    if (bAuthenticated) {
        std::cout << "<tr>"
                << "<th>Authenticated Username</th>"
                << "<td>" << m_szAuthUserName << "</td>"
                << "<th>Semantic Version</th>"
                << "<td>" << RVERSION_STRING_LONG
                << " ("
                << RVERSION_STRING_TYPE
                << ")"
                << "</td>"
                << "</tr>"
                << std::endl;
    }
#endif // SHOW_AUTHENTICATED_USERNAME

#ifdef SHOW_AUTHENTICATED_REAL_NAMES
    if (bAuthenticated) {
        std::cout << "<tr>"
                << "<th>Authenticated User</th>"
                << "<td>" << m_szAuthFirstName << " "
                << m_szAuthLastName << "</td>"
                << "<th>Current Build</th>"
                << "<td>"
                << RVERSION_STRING_DATE
                << " "
                << RVERSION_STRING_TIME
                << "</td>"
                << "</tr>"
                << std::endl;
    }
#endif // SHOW_AUTHENTICATED_REAL_NAMES

#ifdef SHOW_PRIVILEGE_LEVEL
    if (bAuthenticated) {
        std::cout << "<tr>"
                << "<th>Privilege Level</th>"
                << "<td>" << m_szAuthLevel << "</td>"

                << "</tr>"
                << std::endl;
    }
#endif // SHOW_PRIVILEGE_LEVEL

#ifdef SHOW_AUTHENTICATION_HANDLE
    if (bAuthenticated) {
        std::cout << "<tr>"
                  << "<th>Authentication Handle</th>"
                  << "<td>" << handle << "</td>"
                  << "</tr>"
                  << std::endl;
    }
#endif // SHOW_AUTHENTICATION_HANDLE

    std::cout << "</table>" << std::endl;

    /*
     * The call to navbar uses the iEffectiveButtons instead of the
     * buttons provided by the caller. In the case the user is
     * unauthenticated, iEffectiveButtons has been set to 0 so the
     * user doesn't get any buttons before authentication.
     */
    navbar(handle, iEffectiveButtons,
         ssCgiName, ssUsername, ssPassword);

    if (bAvatarExists) {
        std::cout << "</td></tr>" << std::endl;
        gpHtml->close_table();
    }
}


/***************************************************************************
 * Generates and displays navigation buttons for a web-based dashboard.
 * Based on the specified parameters, the function determines which buttons
 * to include in the navbar, such as "Journal", "Logout", and other
 * administrative or customizable buttons depending on user roles and
 * settings.
 *
 * @param handle A unique identifier for the session or request being
 * processed.
 * @param buttons A bitmask specifying which buttons to include in the
 * navbar. Flags such as JOURNAL and LOGOUT determine the displayed buttons.
 * @param ssCgiName The CGI name of the current page or context, indicating
 * the source.
 * @param ssUsername The username of the currently authenticated user, used
 *                   for authorization or specific actions.
 * @param ssPassword The password of the currently authenticated user,
 *                   typically used for authentication of specific requests
 *                   or actions.
 ***************************************************************************/
void dashboard::navbar(
    int handle,
    int buttons,
    std::string ssCgiName,
    std::string ssUsername, std::string ssPassword) {
    process_toggles(ssCgiName, ssUsername, ssPassword, handle);

    if (buttons & JOURNAL) {
        std::string ssCgiJournal = form_cgi("journal.cgi", handle);
        gpHtml->ahref(ssCgiJournal.c_str(), "btn_journal.png", 150, 38);
    }
    if (buttons & LOGOUT) {
        std::string ssCgiLogout = form_cgi("logout.cgi", handle);
        gpHtml->ahref(ssCgiLogout.c_str(), "btn_logout.png", 150, 38);
    }
    if (buttons & PREFS) {
        std::string ssCgiPrefs = form_cgi("prefs.cgi", handle);
        gpHtml->ahref(ssCgiPrefs.c_str(), "btn_prefs.png", 150, 38);
    }

    std::string ssSelfCgi = ssCgiName;

    //    process_toggles(ssCgiName,ssUsername,ssPassword,handle);

    if (0 == strcmp("admin", m_szAuthLevel) ||
        0 == strcmp("devo", m_szAuthLevel)) {
#ifdef SHOW_VPAD_BUTTONS
        if (gpSh->m_pShMemng->vpad_running) {
            std::string ssCgiVpa =
                form_cgi(ssSelfCgi.c_str(), handle);
            ssCgiVpa.append("&bTermVpad=true");
            ssCgiVpa.append("&username=");
            ssCgiVpa.append(ssUsername);
            ssCgiVpa.append("&pwname=");
            ssCgiVpa.append(ssPassword);
            gpHtml->ahref(ssCgiVpa.c_str(), "btn_term_vpad.png", 150, 38);
        } else {
            std::string ssCgiVpa =
                form_cgi(ssSelfCgi.c_str(), handle);
            ssCgiVpa.append("&bStartVpad=true");
            ssCgiVpa.append("&username=");
            ssCgiVpa.append(ssUsername);
            ssCgiVpa.append("&pwname=");
            ssCgiVpa.append(ssPassword);
            gpHtml->ahref(ssCgiVpa.c_str(), "btn_start_vpad.png", 150, 38);
        }
#endif // SHOW_VPAD_BUTTONS

#ifdef SHOW_SCHEMA_BUTTONS
        if (gpSh->m_pShMemng->bDisplaySchema) {
            std::string ssCgiMenu =
                form_cgi(ssSelfCgi.c_str(), handle);
            ssCgiMenu.append("&bDisplaySchema=false");
            ssCgiMenu.append("&username=");
            ssCgiMenu.append(ssUsername);
            ssCgiMenu.append("&pwname=");
            ssCgiMenu.append(ssPassword);
            gpHtml->ahref(ssCgiMenu.c_str(),
                "btn_minus_schema.png", 150, 38);
        } else {
            std::string ssCgiMenu =
                form_cgi(ssSelfCgi.c_str(), handle);
            ssCgiMenu.append("&bDisplaySchema=true");
            ssCgiMenu.append("&username=");
            ssCgiMenu.append(ssUsername);
            ssCgiMenu.append("&pwname=");
            ssCgiMenu.append(ssPassword);
            gpHtml->ahref(ssCgiMenu.c_str(), "btn_plus_schema.png", 150, 38);
        }
#endif // SHOW_SCHEMA_BUTTONS

#ifdef SHOW_SHMVAR_BUTTONS
        if (gpSh->m_pShMemng->bDisplayShmVars) {
            std::string ssCgiMenu =
                form_cgi(ssSelfCgi.c_str(), handle);
            ssCgiMenu.append("&bDisplayShmVars=false");
            ssCgiMenu.append("&username=");
            ssCgiMenu.append(ssUsername);
            ssCgiMenu.append("&pwname=");
            ssCgiMenu.append(ssPassword);
            gpHtml->ahref(ssCgiMenu.c_str(),
                "btn_minus_shmvars.png", 150, 38);
        } else {
            std::string ssCgiMenu =
                form_cgi(ssSelfCgi.c_str(), handle);
            ssCgiMenu.append("&bDisplayShmVars=true");
            ssCgiMenu.append("&username=");
            ssCgiMenu.append(ssUsername);
            ssCgiMenu.append("&pwname=");
            ssCgiMenu.append(ssPassword);
            gpHtml->ahref(ssCgiMenu.c_str(),
                "btn_plus_shmvars.png", 150, 38);
        }
#endif // SHOW_SHMVAR_BUTTONS

#ifdef SHOW_ENVVAR_BUTTONS
        if (gpSh->m_pShMemng->bDisplayEnvVars) {
            std::string ssCgiMenu =
                form_cgi(ssSelfCgi.c_str(), handle);
            ssCgiMenu.append("&bDisplayEnvVars=false");
            ssCgiMenu.append("&username=");
            ssCgiMenu.append(ssUsername);
            ssCgiMenu.append("&pwname=");
            ssCgiMenu.append(ssPassword);
            gpHtml->ahref(ssCgiMenu.c_str(),
                "btn_minus_envvars.png", 150, 38);
        } else {
            std::string ssCgiMenu =
                form_cgi(ssSelfCgi.c_str(), handle);
            ssCgiMenu.append("&bDisplayEnvVars=true");
            ssCgiMenu.append("&username=");
            ssCgiMenu.append(ssUsername);
            ssCgiMenu.append("&pwname=");
            ssCgiMenu.append(ssPassword);
            gpHtml->ahref(ssCgiMenu.c_str(), "btn_plus_envvars.png", 150, 38);
        }
#endif // SHOW_ENVVAR_BUTTONS
    }
}


/****************************************************************************
 * Generates a CGI URL with an appended handle parameter.
 *
 * @param pszName The name used to generate the base CGI URL.
 * @param handle An integer value representing the handle to be appended to
 * the URL.
 * @return A string representing the complete CGI URL with the handle
 * parameter included.
 ***************************************************************************/
std::string dashboard::form_cgi(const char *pszName, int handle) {
    char szHandle[128];
    std::string ssBuffer = gpOS->genCgiCBDUrl(pszName, false);
    ssBuffer.append("?handle=");
    sprintf(szHandle, "%d", handle);
    ssBuffer.append(szHandle);
    return ssBuffer;
}


/***************************************************************************
 * Processes CGI toggle inputs and modifies shared memory variables
 * or initiates specific actions based on the provided flags.
 * Access to toggle actions is restricted to users with admin or
 * developer authorization levels.
 *
 * @param ssCgiName The CGI name string used for processing form variables.
 * @param ssUsername The username string for authorization verification.
 * @param ssPassword The password string for authorization verification.
 * @param handle An integer handle used for processing connections/sessions.
 ***************************************************************************/
void dashboard::process_toggles(
    std::string ssCgiName,
    std::string ssUsername,
    std::string ssPassword,
    int handle) {
    /*
     * If we are admin or devo, we get to see the debug toggle links
     */
    if (0 == strcmp("admin", m_szAuthLevel) ||
        0 == strcmp("devo", m_szAuthLevel)) {
        // https://stackoverflow.com/questions/13519933/
        //  executing-script-on-receiving-incoming-connection-with-xinetd

        std::string ssbStartVpad =
                m_pCgiBind->get_form_variable("bStartVpad");
        if ("true" == ssbStartVpad) {
            start_vpad();
            sleep(1);
        }

        std::string ssbTermVpad =
                m_pCgiBind->get_form_variable("bTermVpad");
        if ("true" == ssbTermVpad) {
            gpSh->m_pShMemng->vpad_running = false;
            //std::cout << "hello there" << std::endl;
            sleep(2);

            char szCommand[1024];
            sprintf(szCommand,"kill -9 %d",
                gpSh->m_pShMemng->vpad_child_pid);
            system(szCommand);

        }

        std::string ssbDisplaySchema =
                m_pCgiBind->get_form_variable("bDisplaySchema");
        if (ssbDisplaySchema == "true") {
            gpSh->m_pShMemng->bDisplaySchema = true;
        }
        if (ssbDisplaySchema == "false") {
            gpSh->m_pShMemng->bDisplaySchema = false;
        }

        /*
         * Modify the shared boolean for the display of
         * the apache environment variables per the query string.
         */
        std::string ssbDisplayEnvVars =
                m_pCgiBind->get_form_variable("bDisplayEnvVars");
        if (ssbDisplayEnvVars == "true") {
            gpSh->m_pShMemng->bDisplayEnvVars = true;
        }
        if (ssbDisplayEnvVars == "false") {
            gpSh->m_pShMemng->bDisplayEnvVars = false;
        }

        /*
         * Modify the shared boolean for the display of
         * the shared memory variables per the query string.
         */
        std::string ssbDisplayShmVars =
                m_pCgiBind->get_form_variable("bDisplayShmVars");
        if (ssbDisplayShmVars == "true") {
            gpSh->m_pShMemng->bDisplayShmVars = true;
        }
        if (ssbDisplayShmVars == "false") {
            gpSh->m_pShMemng->bDisplayShmVars = false;
        }
    }
}


/***************************************************************************
 * @brief Establishes a connection to a server and sends a wake-up message.
 *
 * This method connects to a local server on a designated port, sends a
 * predefined message ("Hello World!!"), and then closes the connection.
 *
 * The server host is identified by resolving "localhost". The connection
 * is established using a TCP socket, and the port number is defined
 * by the macro `VPA_PORT`. If any step of the execution fails (e.g.,
 * socket creation, connection, or message sending), the method will print
 * an error message and terminate the process with a specific exit code.
 *
 * Function process:
 * 1. Resolves the "localhost" hostname to an IP address.
 * 2. Initializes a `sockaddr_in` structure with server details,
 *    including the port number and IP address in network byte order.
 * 3. Creates a TCP socket.
 * 4. Connects to the server using the initialized `sockaddr_in` structure.
 * 5. Sends a predefined "Hello World!!" message to the server.
 * 6. Closes the socket and terminates the session.
 *
 * @note This function directly exits the program on errors, making it
 * unsuitable for exception-safe environments or usage in libraries.
 ***************************************************************************/
void dashboard::start_vpad() {

  #define USE_STREAM_SOCKET
//#define USE_DGRAM_SOCKET

    // The attempt to use the DGRAM  to start the vpad didn't work

    struct hostent *hostnm;         /* server host name information        */
    struct sockaddr_in server;      /* server address                      */
    int s;                          /* client socket                       */
    hostnm = gethostbyname("localhost");

    /*
     * Put the server information into the server structure.
     * The port must be put into network byte order.
     */
    server.sin_family = AF_INET;    /* Address Family: Internet           */

    /*
     * Convert the port number from host to network byte order
     */
    server.sin_port = htons(VPAD_START_PORT);

    /*
     * Set the IP address of the target
     */
    server.sin_addr.s_addr = *((unsigned long *) hostnm->h_addr);

    /*
     * Get a socket.
     */
    if ((s = socket(AF_INET,
#ifdef USE_STREAM_SOCKET
                    SOCK_STREAM
#endif
#ifdef USE_DGRAM_SOCKET
                            SOCK_DGRAM
#endif
                    , 0)) < 0) {
        printf("%s", "socket error");
        exit(3);
    }

#ifdef USE_STREAM_SOCKET
    /*
     * Connect to the server.
     */
    if (connect(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("%s", "connect error");
        exit(4);
    }
#endif

    /*
     * Send a message to the destination to wake up xinetd
     */
    char szBuffer[] = {"Hello World!!"};
#ifdef USE_STREAM_SOCKET
    if (send(s, // socket descriptor
             szBuffer, // output buffer
             sizeof(szBuffer), // size of output buffer
             0) < 0) // flags (none required)
    {
        printf("%s", "Send error");
        exit(5);
    }
#endif
#ifdef USE_DGRAM_SOCKET
    sendto(s,                                   // socket descriptor
           szBuffer,                            // output buffer
           sizeof(szBuffer),                    // size of output buffer
           0,                                   // flags (none required)
           (const struct sockaddr *)&server,    // server structure of dest'n
           server_address_length);              // size of server structure
#endif

    /*
     * Close the session and socket
     */
    close(s);
}

/////////////////////////
// eof - dashboard.cpp //
/////////////////////////
