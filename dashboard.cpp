/////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/dashboard.cpp  2025/01/14  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.      //
/////////////////////////////////////////////////////////////////////////////


#define SHOW_PRIVILEGE_LEVEL
#define SHOW_AUTHENTICATED_USER
//#define SHOW_AUTHENTICATION_HANDLE

#define SHOW_SCHEMA_BUTTONS
#define SHOW_SHMVAR_BUTTONS
#define SHOW_ENVVAR_BUTTONS
#define SHOW_VPAD_BUTTONS

#include "dashboard.h"

/****************************************************
 * This is the constructor for the dashboard class
 * @param handle The index into the passwd.csv
 * @param buttons A bitfield of requested buttons
 * @param pszFile The cgo file name to execute
 * @param ssUsername The username for authentication
 * @param ssPassword The password for authentication
 ****************************************************/
dashboard::dashboard(
    int handle,
    int buttons,
    const char *pszFile,
    std::string ssUsername,
    std::string ssPassword)
{
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

    int iBorder;

    std::string ssFile;
    std::string ssFilePath;
    std::string ssCgiName;

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
        gpSh->m_pShMemng->bDisplaySchema  = false;
        gpSh->m_pShMemng->bDisplayShmVars = false;
        gpSh->m_pShMemng->bDisplayEnvVars = false;
    }

    /*
     * Look up the users credentials and copy to member data so it's
     * available to the dashboard code.
     */
    strcpy(m_szAuthUserName, gpSh->m_pShMemng->creds[handle].szAuthUserName);
    strcpy(m_szAuthFirstName,gpSh->m_pShMemng->creds[handle].szAuthFirstName);
    strcpy(m_szAuthLastName, gpSh->m_pShMemng->creds[handle].szAuthLastName);
    strcpy(m_szAuthLevel,    gpSh->m_pShMemng->creds[handle].szAuthLevel);
    strcpy(m_szAuthUUID,     gpSh->m_pShMemng->creds[handle].szAuthUUID);

    ssFile     = pszFile;
    ssFilePath = std::filesystem::path(ssFile).remove_filename();
    ssCgiName  = ssFile.substr(ssFilePath.length(),ssFile.length());
    ssCgiName  = std::filesystem::path(ssCgiName).replace_extension(".cgi");

    /*
     * Use the iBorder variable so we can avoid using a magic number in the
     * cout stream below/
     */
    iBorder=2;
    std::cout
        << "<table border=" << iBorder << ">"
        << "<tr><h3><th>Goodall MultiWare Framework Dashboard</th></h3></tr>"
        << "</table>"
        << std::endl;


    std::cout << "<table border=1>";

#ifdef SHOW_AUTHENTICATED_USER
    if (bAuthenticated) {
        std::cout << "<tr>"
                  << "<th>Authenticated User</th>"
                  << "<td>" << m_szAuthFirstName << " "
                            << m_szAuthLastName  << "</td>"
                  << "</tr>";
    }
#endif // SHOW_AUTHENTICATED_USER

#ifdef SHOW_PRIVILEGE_LEVEL
    if (bAuthenticated) {
        std::cout << "<tr>"
                  << "<th>Privilege Level</th>"
                  << "<td>" << m_szAuthLevel << "</td>"
                  << "</tr>";
    }
#endif // SHOW_PRIVILEGE_LEVEL

#ifdef SHOW_AUTHENTICATION_HANDLE
    if (bAuthenticated) {
        std::cout << "<tr>"
                  << "<th>Authentication Handle</th>"
                  << "<td>" << handle << "</td>"
                  << "</tr>";
    }
#endif // SHOW_AUTHENTICATION_HANDLE

    std::cout << "</table>";

    /*
     * The call to navbar uses the iEffectiveButtons instead of the
     * buttons provided by the caller. In the case the user is
     * unauthenticated, iEffectiveButtons has been set to 0 so the
     * user doesn't get any buttons before authentication.
     */
    navbar(handle,iEffectiveButtons,ssCgiName,ssUsername,ssPassword);
}


/*******************************************************
 * Emit the Navigation Bar
 * @param handle The index into the passwd.csv file
 * @param buttons A bitfield of button to show
 * @param ssCgiName The filename of the CGI file to run
 * @param ssUsername The username for authentication
 * @param ssPassword The password for authentication
 *******************************************************/
void dashboard::navbar(
    int handle,
    int buttons,
    std::string ssCgiName,
    std::string ssUsername,std::string ssPassword)
{
    process_toggles(ssCgiName,ssUsername,ssPassword,handle);

    if (buttons & JOURNAL) {
        std::string ssCgiJournal = form_cgi("journal.cgi",handle);
        gpHtml->ahref(ssCgiJournal.c_str(),"btn_journal.png",150,38);
    }
    if (buttons & LOGOUT) {
        std::string ssCgiLogout = form_cgi("logout.cgi",handle);
        gpHtml->ahref(ssCgiLogout.c_str(),"btn_logout.png",150,38);
    }

    std::string ssSelfCgi = ssCgiName;

//    process_toggles(ssCgiName,ssUsername,ssPassword,handle);

    if (0 == strcmp("admin",m_szAuthLevel) ||
        0 == strcmp("devo",m_szAuthLevel)  ) {

#ifdef SHOW_VPAD_BUTTONS
        if (gpSh->m_pShMemng->vpad_running) {
            std::string ssCgiVpa = form_cgi(ssSelfCgi.c_str(),handle);
            ssCgiVpa.append("&bTermVpad=true");
            ssCgiVpa.append("&username=");
            ssCgiVpa.append(ssUsername);
            ssCgiVpa.append("&pwname=");
            ssCgiVpa.append(ssPassword);
            gpHtml->ahref(ssCgiVpa.c_str(),"btn_term_vpad.png",150,38);
        } else {
            std::string ssCgiVpa = form_cgi(ssSelfCgi.c_str(),handle);
            ssCgiVpa.append("&bStartVpad=true");
            ssCgiVpa.append("&username=");
            ssCgiVpa.append(ssUsername);
            ssCgiVpa.append("&pwname=");
            ssCgiVpa.append(ssPassword);
            gpHtml->ahref(ssCgiVpa.c_str(),"btn_start_vpad.png",150,38);

        }
#endif // SHOW_VPAD_BUTTONS

#ifdef SHOW_SCHEMA_BUTTONS
        if(gpSh->m_pShMemng->bDisplaySchema) {
            std::string ssCgiMenu = form_cgi(ssSelfCgi.c_str(),handle);
            ssCgiMenu.append("&bDisplaySchema=false");
            ssCgiMenu.append("&username=");
            ssCgiMenu.append(ssUsername);
            ssCgiMenu.append("&pwname=");
            ssCgiMenu.append(ssPassword);
            gpHtml->ahref(ssCgiMenu.c_str(),"btn_minus_schema.png",150,38);
        } else {
            std::string ssCgiMenu = form_cgi(ssSelfCgi.c_str(),handle);
            ssCgiMenu.append("&bDisplaySchema=true");
            ssCgiMenu.append("&username=");
            ssCgiMenu.append(ssUsername);
            ssCgiMenu.append("&pwname=");
            ssCgiMenu.append(ssPassword);
            gpHtml->ahref(ssCgiMenu.c_str(),"btn_plus_schema.png",150,38);
        }
#endif // SHOW_SCHEMA_BUTTONS

#ifdef SHOW_SHMVAR_BUTTONS
        if(gpSh->m_pShMemng->bDisplayShmVars) {
            std::string ssCgiMenu = form_cgi(ssSelfCgi.c_str(),handle);
            ssCgiMenu.append("&bDisplayShmVars=false");
            ssCgiMenu.append("&username=");
            ssCgiMenu.append(ssUsername);
            ssCgiMenu.append("&pwname=");
            ssCgiMenu.append(ssPassword);
            gpHtml->ahref(ssCgiMenu.c_str(),"btn_minus_shmvars.png",150,38);
        } else {
            std::string ssCgiMenu = form_cgi(ssSelfCgi.c_str(),handle);
            ssCgiMenu.append("&bDisplayShmVars=true");
            ssCgiMenu.append("&username=");
            ssCgiMenu.append(ssUsername);
            ssCgiMenu.append("&pwname=");
            ssCgiMenu.append(ssPassword);
            gpHtml->ahref(ssCgiMenu.c_str(),"btn_plus_shmvars.png",150,38);
        }
#endif // SHOW_SHMVAR_BUTTONS

#ifdef SHOW_ENVVAR_BUTTONS
        if(gpSh->m_pShMemng->bDisplayEnvVars) {
            std::string ssCgiMenu = form_cgi(ssSelfCgi.c_str(),handle);
            ssCgiMenu.append("&bDisplayEnvVars=false");
            ssCgiMenu.append("&username=");
            ssCgiMenu.append(ssUsername);
            ssCgiMenu.append("&pwname=");
            ssCgiMenu.append(ssPassword);
            gpHtml->ahref(ssCgiMenu.c_str(),"btn_minus_envvars.png",150,38);
        } else {
            std::string ssCgiMenu = form_cgi(ssSelfCgi.c_str(),handle);
            ssCgiMenu.append("&bDisplayEnvVars=true");
            ssCgiMenu.append("&username=");
            ssCgiMenu.append(ssUsername);
            ssCgiMenu.append("&pwname=");
            ssCgiMenu.append(ssPassword);
            gpHtml->ahref(ssCgiMenu.c_str(),"btn_plus_envvars.png",150,38);
        }
#endif // SHOW_ENVVAR_BUTTONS
    }
}


/******************************************************
 * Form a cgi invocation with required query parameters
 * @param pszName The name of the CGI file requested
 * @param handle AN index into the passwd.csv file
 * @return
 ******************************************************/
std::string dashboard::form_cgi(const char* pszName, int handle)
{
    char szHandle[128];
    std::string ssBuffer;
    ssBuffer = gpOS->genCgiCBDUrl(pszName,false);
    ssBuffer.append("?handle=");
    sprintf(szHandle,"%d",handle);
    ssBuffer.append(szHandle);
    return ssBuffer;
}

/***************************************************************************
 * Process the query string and modify the shared display booleans as needed
 ***************************************************************************/
void dashboard::process_toggles(
    std::string ssCgiName,
    std::string ssUsername,
    std::string ssPassword,
    int handle)
{
    /*
     * If we are admin or devo, we get to see the debug toggle links
     */
    if (0 == strcmp("admin",m_szAuthLevel) ||
        0 == strcmp("devo",m_szAuthLevel)  ) {

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
        }

        std::string ssbDisplaySchema  =
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


/************************************************************
 * Start the vpad by accessing port 5164 and waking up xinetd
 ************************************************************/
void dashboard::start_vpad()
{

    unsigned short port;       /* port client will connect to         */
    char buf[12];              /* data buffer for sending & receiving */
    struct hostent *hostnm;    /* server host name information        */
    struct sockaddr_in server; /* server address                      */
    int s;                     /* client socket                       */
    hostnm = gethostbyname("localhost");

    /*
     * Put the server information into the server structure.
     * The port must be put into network byte order.
     */
    server.sin_family      = AF_INET;

    /*
     * Convert the port number from host to network byte order
     */
    server.sin_port        = htons(VPA_PORT);

    /*
     * Set the IP address of the target
     */
    server.sin_addr.s_addr = *((unsigned long *)hostnm->h_addr);

    /*
     * Get a stream socket.
     */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("%s","socket error");
        exit(3);
    }

    /*
     * Connect to the server.
     */
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("%s","connect error");
        exit(4);
    }

    /*
     * Send a message to the destination to wake up xinetd
     */
    char szBuffer[] = {"Hello World!!"};
    if (send(s, szBuffer, sizeof(szBuffer), 0) < 0)
    {
        printf("%s","Send error");
        exit(5);
    }

    /*
     * Close the session and socket
     */
    close(s);

}
/////////////////////////
// eof - dashboard.cpp //
/////////////////////////
