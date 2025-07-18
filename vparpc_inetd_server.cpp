/////////////////////////////////////////////////////////////////////
// ~/public_html/fw/vparpc_inetd_server.cpp 2025-07-15 18:16 dwg - //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.   //
// This file is part of MultiWare Engineering's VPA and FrameWork  //
/////////////////////////////////////////////////////////////////////

/**
 * @file vparpc_inetd_server.cpp
 * @brief Virtual Protocol Adapter RPC Server - inetd version
 * 
 * This file implements an inetd-compatible version of the VPA RPC server that
 * provides the same RPC functionality as vparpc_server.cpp but operates through
 * inetd/xinetd for connection management.
 * 
 * ## Key Differences from Standalone Server:
 * - **Connection Management**: Uses inetd for socket handling (STDIN/STDOUT)
 * - **Process Model**: One process per client connection
 * - **UI Display**: No visual interface (daemon mode)
 * - **Service Registration**: Configured through inetd.conf or xinetd.d
 * 
 * ## Supported RPC Operations:
 * - Version information queries (/GET version)
 * - Unique identifier retrieval (/GET szRpcUuid)
 * - Custom command processing (extensible)
 * 
 * @author Douglas Wade Goodall
 * @date 2025/05/01 16:54
 * @version 5.5.10.2
 * @copyright Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.
 */

#include "mwfw2.h"

/**
 * @brief Specifies the size of the buffer for reading or writing operations.
 *
 * This constant represents the size of the buffer that is used for
 * input/output operations, such as reading data from or writing data to
 * a stream or client request. The size is set to the standard library-defined
 * constant `BUFSIZ`.
 *
 * It is commonly used to allocate fixed-size buffer arrays to ensure consistent
 * memory management and avoid dynamic allocation for processing operations.
 */
const int BUFFER_SIZE = BUFSIZ;


/**
 * @brief Handles the authentication request received from a connected client.
 *
 * This function processes the authentication request contained in the provided buffer.
 * It validates the pre-shared key (PSK) sent by the client and determines the authentication status.
 * Upon successful authentication, it assigns a new UUID to the request and logs the result.
 *
 * @param buffer Pointer to the buffer containing the authentication request.
 *               It is expected to be of type `vparpc_request_auth_t`.
 * @param pWin Pointer to a `window` object used for displaying debugging and processing
 *             details within a graphical interface.
 */
void handle_auth_request(char* buffer, window* pWin)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    here;
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Processing AUTH request");
#endif // DISPLAY_PROCESS_DETAILS
    vparpc_request_auth_t* pReq = (vparpc_request_auth_t*)buffer;
    if (0 == strcmp((char*)CFG_VPA_RPC_PSK, (const char*)pReq->szPSK))
    {
        strcpy(pReq->szAuth, gpSh->m_pShMemng->szRpcUuid);
#ifdef DISPLAY_PROCESS_DETAILS
        std::string ssPSKmsg = "  Current Auth is: ";
        ssPSKmsg += pReq->szAuth;
        pWin->add_row(ssPSKmsg);
#endif // DISPLAY_PROCESS_DETAILS
        pReq->eStatus = VPARPC_STATUS_OK;
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  PSK match, authentication successful");
#endif // DISPLAY_PROCESS_DETAILS
    }
    else
    {
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  PSK mismatch, authentication failed");
#endif // DISPLAY_PROCESS_DETAILS
        pReq->eStatus = VPARPC_STATUS_AUTH_FAILED;
    }
#ifdef DISPLAY_PROCESS_DETAILS
    std::string ssPktSize = "  Packet size is: ";
    ssPktSize += std::to_string(pReq->nSize);
    pWin->add_row(ssPktSize);
    pWin->render();
#endif // DISPLAY_PROCESS_DETAILS
    memcpy(&gpVpaRpc->m_req_auth, pReq, sizeof(vparpc_request_t));
}


/**
 * Handles the processing of a version request.
 * Verifies the authorization token from the request and sets the version
 * information and status accordingly. The result is also logged and optionally
 * displayed in a user-defined window if debugging is enabled.
 *
 * @param buffer Pointer to the buffer containing the incoming version request.
 *               This buffer must be type-castable to `vparpc_request_version_t`.
 * @param pWin Pointer to the `window` object used for logging detailed
 *             progress information during processing. This parameter
 *             is used only if debugging or display process details are
 *             enabled.
 */
void handle_version_request(char* buffer, window* pWin)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Processing VERSION request");
#endif // DISPLAY_PROCESS_DETAILS

    vparpc_request_version_t* pReq = (vparpc_request_version_t*)buffer;

    if (0 == strcmp(gpSh->m_pShMemng->szRpcUuid, (const char*)pReq->szAuth))
    {
        strcpy(pReq->szVersion,RSTRING);
        pReq->eStatus = VPARPC_STATUS_OK;

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth match, authentication successful");
#endif // DISPLAY_PROCESS_DETAILS
    }
    else
    {
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth mismatch, authentication failed");
#endif // DISPLAY_PROCESS_DETAILS

        pReq->eStatus = VPARPC_STATUS_AUTH_FAILED;
    }
    memcpy(&gpVpaRpc->m_req_version, pReq, sizeof(vparpc_request_version_t));
}


/**
 * @brief Handles a lookup request and processes the associated operation
 *
 * @param request The lookup request to be processed
 * @param response The response that will be populated as a result of processing the request
 */
void handle_lookup_request(char* buffer, window* pWin)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    gpSysLog->loginfo(__PRETTY_FUNCTION__);

#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Processing LOOKUP request");
#endif // DISPLAY_PROCESS_DETAILS

    vparpc_request_lookup_t* pReq = (vparpc_request_lookup_t*)buffer;

    // Initialize iHandle to a default value
    pReq->iHandle = -1;

    if (0 == strcmp(gpSh->m_pShMemng->szRpcUuid, (const char*)pReq->szAuth))
    {
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth match, authentication successful");
        pWin->add_row("  Username: " + std::string(pReq->szUsername));
        pWin->add_row("  Password: " + std::string(pReq->szPassword));
#endif // DISPLAY_PROCESS_DETAILS

        gpCsv = nullptr;
        gpSysLog->loginfo(
            "Trying to load CSV from /home/devo/public_html/fw/schemas/v1/passwd.csv");
        //gpCsv = new readCsv("/home/devo/public_html/fw/schemas/v1/passwd.csv");
        gpCsv = new readCsv("passwd.csv");
        gpSysLog->loginfo("Successfully loaded CSV");


        gpSysLog->loginfo("calling gpCsv->parseData()");
        gpCsv->parseData();
        gpSysLog->loginfo("gpCsv->parseData() returned");

        // char szDebug[128];
        // sprintf(szDebug, "m_iRow is %d", gpCsv->m_iRow);
        // gpSysLog->loginfo(szDebug);


        if (!gpCsv)
        {
            gpSysLog->loginfo(
                "Could not find passwd.csv in any expected location");
            pReq->iHandle = -1;
            pReq->eStatus = VPARPC_STATUS_ERROR;
            return;
        }

        // Perform the lookup
        gpSysLog->loginfo("calling gpPassword->lookup_username_password()");
        int handle = gpPassword->lookup_username_password(
            pReq->szUsername, pReq->szPassword);
        gpSysLog->loginfo("gpPassword->lookup_username_password() returned");

        char szLogger2[128];
        sprintf(szLogger2, "Lookup completed: handle=%d", handle);
        gpSysLog->loginfo(szLogger2);

        pReq->iHandle = handle;

#ifdef DISPLAY_PROCESS_DETAILS
            pWin->add_row("  Lookup result - Handle: " + std::to_string(pReq->iHandle));
#endif // DISPLAY_PROCESS_DETAILS

        // Log the result
        char szLogger[128];
        sprintf(szLogger,
                "Lookup completed: username=%s, password=%s, handle=%d",
                pReq->szUsername, pReq->szPassword, pReq->iHandle);
        gpSysLog->loginfo(szLogger);
        if (pReq->iHandle >= 0)
        {
            pReq->eStatus = VPARPC_STATUS_OK;
        }
        else
        {
            pReq->eStatus = VPARPC_STATUS_AUTH_FAILED;
        }

        // Clean up CSV reader
        delete gpCsv;
        gpCsv = nullptr;

        // } catch (const std::exception& e) {
        //     gpSysLog->loginfo("Error during lookup");
        //     pReq->iHandle = -1;
        //     pReq->eStatus = VPARPC_STATUS_ERROR;
        //
        //     if (gpCsv) {
        //         delete gpCsv;
        //         gpCsv = nullptr;
        //     }
        // }
    }
    else
    {
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth mismatch, authentication failed");
#endif // DISPLAY_PROCESS_DETAILS

        gpSysLog->loginfo("Auth mismatch in lookup request");
        pReq->iHandle = -1;
        pReq->eStatus = VPARPC_STATUS_AUTH_FAILED;
    }

#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Final handle value: " + std::to_string(pReq->iHandle));
    pWin->add_row("  Final status: " + std::to_string(pReq->eStatus));
#endif // DISPLAY_PROCESS_DETAILS
}

/**
 * Processes a request to retrieve and authenticate credentials, and updates the request buffer with
 * appropriate credentials and status information.
 *
 * @param buffer A pointer to the buffer containing the credential request data. Must point to a properly
 *               formatted `vparpc_request_creds_t` structure.
 * @param pWin A pointer to a `window` object used to display diagnostic information
 *             during the processing of the request.
 */
void handle_creds_request(char* buffer, window* pWin)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    gpSysLog->loginfo(__PRETTY_FUNCTION__);

#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Processing CREDS request");
#endif // DISPLAY_PROCESS_DETAILS

    vparpc_request_creds_t* pReq = (vparpc_request_creds_t*)buffer;
    if (0 == strcmp(gpSh->m_pShMemng->szRpcUuid, (const char*)pReq->szAuth))
    {
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth match, authentication successful");
#endif // DISPLAY_PROCESS_DETAILS

        strcpy(pReq->szAuthUserName,
               gpSh->m_pShMemng->creds[pReq->iHandle].szAuthUserName);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  AuthUserName: " + std::string(pReq->szAuthUserName));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy(pReq->szAuthFirstName,
               gpSh->m_pShMemng->creds[pReq->iHandle].szAuthFirstName);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  AuthFirstName: " + std::string(pReq->szAuthFirstName));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy(pReq->szAuthLastName,
               gpSh->m_pShMemng->creds[pReq->iHandle].szAuthLastName);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  AuthLastName: " + std::string(pReq->szAuthLastName));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy(pReq->szAuthUUID,
               gpSh->m_pShMemng->creds[pReq->iHandle].szAuthUUID);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth UUID: " + std::string(pReq->szAuthUUID));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy(pReq->szAuthLevel,
               gpSh->m_pShMemng->creds[pReq->iHandle].szAuthLevel);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  AuthLevel: " + std::string(pReq->szAuthLevel));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy(pReq->szRemoteHost,
               gpSh->m_pShMemng->creds[pReq->iHandle].szRemoteHost);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  RemoteHost: " + std::string(pReq->szRemoteHost));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy(pReq->szRemoteAddr,
               gpSh->m_pShMemng->creds[pReq->iHandle].szRemoteAddr);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  RemoteAddr: " + std::string(pReq->szRemoteAddr));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy(pReq->szHttpUserAgent,
               gpSh->m_pShMemng->creds[pReq->iHandle].szHttpUserAgent);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  HttpUserAgent: " + std::string(pReq->szHttpUserAgent));
#endif // DISPLAY_PROCESS_DETAILS

        pReq->eStatus = VPARPC_STATUS_OK;
    }
    else
    {
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth mismatch, authentication failed");
#endif // DISPLAY_PROCESS_DETAILS

        pReq->eStatus = VPARPC_STATUS_AUTH_FAILED;
    }
}


/**
 * Handles the processing of a URL request by validating authentication details
 * and populating the request structure with required system values.
 *
 * @param buffer A pointer to a buffer containing the incoming URL request data.
 *               Expected to be formatted as a vparpc_request_urls_t structure.
 * @param pWin A pointer to a window object used for displaying log information
 *             (if DISPLAY_PROCESS_DETAILS is enabled).
 */
void handle_urls_request(char* buffer, window* pWin)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    gpSysLog->loginfo(__PRETTY_FUNCTION__);

#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Processing URLS request");
#endif // DISPLAY_PROCESS_DETAILS

    vparpc_request_urls_t* pReq = (vparpc_request_urls_t*)buffer;

    if (0 == strcmp(gpSh->m_pShMemng->szRpcUuid, (const char*)pReq->szAuth))
    {
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth match, authentication successful");
#endif // DISPLAY_PROCESS_DETAILS

        strcpy(pReq->szIP,
               gpSh->m_pShMemng->szIP);
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  szIP: " + std::string(pReq->szIP
#endif // DISPLAY_PROCESS_DETAILS

        strcpy(pReq->szCgiRoot,
               gpSh->m_pShMemng->szCgiRoot);
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  szCgiRoot: " + std::string(pReq->szCgiRoot));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy(pReq->szStylesRoot,
               gpSh->m_pShMemng->szStylesRoot);
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  szStylesRoot: " + std::string(pReq->szStylesRoot));
#endif // DISPLAY_PROCESS_DETAILS

        pReq->eStatus = VPARPC_STATUS_OK;
    }
    else
    {
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth mismatch, authentication failed");
#endif // DISPLAY_PROCESS_DETAILS

        pReq->eStatus = VPARPC_STATUS_AUTH_FAILED;
    }
}


/**
 * @brief Processes the given input data based on the implemented logic.
 *
 * @param data The input data that needs to be processed.
 */
void process(char* pszBuffer)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    gpSysLog->loginfo(__PRETTY_FUNCTION__);

    // std::cout << "vparpc::process()" << std::endl;
    // std::cout << "vparpc::process() at line # " << __LINE__ << std::endl;

    // Create window for debugging/monitoring
    auto* pWin = new window();
    pWin->set_title("vparpc::process()");
    gpSemiGr->cosmetics(
        SRUL, SRUR,
        SRLL, SRLR,
        SVSR, SVSL,
        SH, SV);

    // We don't know what type of request it is yet, we we cast it
    // generic long enough to decode the eFunc
    const auto* request = (const vparpc_request_generic_t*)pszBuffer;

    size_t response;

    switch (request->eFunc)
    {
    case VPARPC_FUNC_GET_AUTH:
        gpSysLog->loginfo("VPA RPC: GET_AUTH");
        handle_auth_request(pszBuffer, pWin);
        break;

    case VPARPC_FUNC_VERSION:
        gpSysLog->loginfo("VPA RPC: VERSION");
        handle_version_request(pszBuffer, pWin);
        break;

    case VPARPC_FUNC_LOOKUP:

        handle_lookup_request(pszBuffer, pWin);
        break;

    case VPARPC_FUNC_CREDS:
        gpSysLog->loginfo("VPA RPC: CREDS");
        handle_creds_request(pszBuffer, pWin);
        break;

    case VPARPC_FUNC_URLS:
        gpSysLog->loginfo("VPA RPC: URLS");
        handle_urls_request(pszBuffer, pWin);
        break;

    default:
        break;
    }

#ifdef DISPLAY_PROCESS_INFO
        pWin->render();
#endif // DISPLAY_PROCESS_INFO

    delete pWin;
}

/**
 * The main function serves as the entry point of the program.
 * It performs the initialization and triggers execution.
 *
 * @return An integer value indicating the program's execution result.
 *         Typically, returning 0 indicates successful execution,
 *         while non-zero values represent errors.
 */
int main()
{
    // Initialize the middleware framework
    auto* pMwFw = new mwfw2(__FILE__, __FUNCTION__);
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    gpSysLog->loginfo(__PRETTY_FUNCTION__);


    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    // Log server startup
    gbHere = true;
    gpSysLog->loginfo(
        "-----------------------------------------------");
    gpSysLog->loginfo("*** VPA RPC inetd server started (version 5.5.10.2)");
    here;

    // Read the RPC request from client (via inetd)
    bytesRead = read(STDIN_FILENO, buffer, sizeof(vparpc_request_t));

    if (bytesRead > 0)
    {
        gpSysLog->loginfo("Received bytes from client");

        // Process the RPC request (this modifies the buffer in-place)
        process(buffer);

        // Write the processed buffer back to client (via inetd)
        // Make sure we write the exact same size we read
        ssize_t bytesWritten = write(STDOUT_FILENO, buffer, bytesRead);

        if (bytesWritten > 0)
        {
            gpSysLog->loginfo("Response sent: bytes");
        }
        else
        {
            gpSysLog->loginfo("Failed to send response");
        }
    }
    else
    {
        gpSysLog->loginfo("Failed to read request from client");
    }

    // Log normal termination
    gpSysLog->loginfo("VPA RPC inetd server session completed");

    // Clean up
    delete pMwFw;

    return 0;
}
