//////////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/vparpc_inetd_server.cpp 2025/05/01 16:54 dwg - //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.       //
//////////////////////////////////////////////////////////////////////////////

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

const int BUFFER_SIZE = BUFSIZ;



/**
 * @brief Handles an authentication request by verifying the pre-shared key (PSK)
 *
 * Processes an incoming authentication request, verifies the provided pre-shared key (PSK),
 * and updates the request structure with the authentication status and corresponding data.
 * Augments the provided window object with status messages for logging the operation progress.
 *
 * If the provided PSK matches the expected value, the function sets the authentication status
 * to success and populates the `szAuth` field with a UUID. Otherwise, it marks the request as
 * authentication failed. The size of the packet is also logged in the provided window object.
 *
 * @param buffer The incoming request buffer containing the authentication details, including the
 *               pre-shared key and packet metadata. Must be properly cast to a
 *               `vparpc_request_auth_t` structure.
 * @param pWin   A pointer to a `window` object used for logging status messages during processing.
 */
void handle_auth_request(char *buffer, window* pWin) {
#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Processing AUTH request");
#endif // DISPLAY_PROCESS_DETAILS
    vparpc_request_auth_t * pReq = (vparpc_request_auth_t *)buffer;
    if (0 == strcmp((char *)CFG_VPA_RPC_PSK,(const char *)pReq->szPSK) ) {
        strcpy( pReq->szAuth,gpSh->m_pShMemng->szRpcUuid);
#ifdef DISPLAY_PROCESS_DETAILS
        std::string ssPSKmsg = "  Current Auth is: ";
        ssPSKmsg += pReq->szAuth;
        pWin->add_row(ssPSKmsg);
#endif // DISPLAY_PROCESS_DETAILS
        pReq->eStatus =  VPARPC_STATUS_OK;
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  PSK match, authentication successful");
#endif // DISPLAY_PROCESS_DETAILS
    } else {
#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  PSK mismatch, authentication failed");
#endif // DISPLAY_PROCESS_DETAILS
        pReq->eStatus =  VPARPC_STATUS_AUTH_FAILED;
    }
#ifdef DISPLAY_PROCESS_DETAILS
    std::string ssPktSize = "  Packet size is: ";
    ssPktSize += std::to_string(pReq->nSize);
    pWin->add_row(ssPktSize);
    pWin->render();
#endif // DISPLAY_PROCESS_DETAILS
    memcpy(&gpVpaRpc->m_req_auth,pReq,sizeof(vparpc_request_t));
}


/**
 * @brief Handles a version request by validating authentication and responding with the application version
 *
 * Processes a request to retrieve the application version. It validates the authentication token
 * provided in the request and either returns the version information upon successful authentication
 * or indicates an authentication failure. Additionally, logs the processing steps to a debug window.
 *
 * @param buffer Pointer to the raw request buffer containing the version request structure
 * @param pWin Pointer to a window object used for debugging and displaying status messages
 *
 * @note The authentication is performed by comparing the provided token with the UUID in shared memory
 * @note Sets the status field in the request structure based on the authentication result
 *
 * @warning Assumes the buffer contains a properly formatted `vparpc_request_version_t` structure
 * @warning Overwrites the provided buffer with the response data
 */
void handle_version_request(char * buffer, window* pWin) {
#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Processing VERSION request");
#endif // DISPLAY_PROCESS_DETAILS

    vparpc_request_version_t * pReq = (vparpc_request_version_t *)buffer;

    if (0 == strcmp(gpSh->m_pShMemng->szRpcUuid,(const char *)pReq->szAuth) ) {
        strcpy( pReq->szVersion,RSTRING);
        pReq->eStatus =  VPARPC_STATUS_OK;

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth match, authentication successful");
#endif // DISPLAY_PROCESS_DETAILS

    } else {

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth mismatch, authentication failed");
#endif // DISPLAY_PROCESS_DETAILS

        pReq->eStatus =  VPARPC_STATUS_AUTH_FAILED;
    }
        memcpy(&gpVpaRpc->m_req_version,pReq,sizeof(vparpc_request_version_t));

}


/**
 * Handles a lookup request.
 *
 * @param buffer The request buffer containing lookup parameters
 * @param pWin Window object for debug output
 */
void handle_lookup_request(char * buffer, window* pWin) {
    gpSysLog->loginfo("handle_lookup_request()");

#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Processing LOOKUP request");
#endif // DISPLAY_PROCESS_DETAILS

    vparpc_request_lookup_t * pReq = (vparpc_request_lookup_t *)buffer;
    
    // Initialize iHandle to a default value
    pReq->iHandle = -1;
    
    if (0 == strcmp(gpSh->m_pShMemng->szRpcUuid,(const char *)pReq->szAuth) ) {

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth match, authentication successful");
        pWin->add_row("  Username: " + std::string(pReq->szUsername));
        pWin->add_row("  Password: " + std::string(pReq->szPassword));
#endif // DISPLAY_PROCESS_DETAILS

            gpCsv = nullptr;
            gpSysLog->loginfo("Trying to load CSV from /home/devo/public_html/fw/schemas/v1/passwd.csv");
            //gpCsv = new readCsv("/home/devo/public_html/fw/schemas/v1/passwd.csv");
            gpCsv = new readCsv("passwd.csv");
            gpSysLog->loginfo("Successfully loaded CSV");


            gpSysLog->loginfo("calling gpCsv->parseData()");
            gpCsv->parseData();
            gpSysLog->loginfo("gpCsv->parseData() returned");
           char szDebug[128];
            sprintf(szDebug,"m_iRow is %d",gpCsv->m_iRow);
            gpSysLog->loginfo(szDebug);

            
            if (!gpCsv) {
                gpSysLog->loginfo("Could not find passwd.csv in any expected location");
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
            sprintf(szLogger2, "Lookup completed: handle=%d",handle);
            gpSysLog->loginfo(szLogger2);

            pReq->iHandle = handle;
            
#ifdef DISPLAY_PROCESS_DETAILS
            pWin->add_row("  Lookup result - Handle: " + std::to_string(pReq->iHandle));
#endif // DISPLAY_PROCESS_DETAILS
            
            // Log the result
            char szLogger[128];
            sprintf(szLogger, "Lookup completed: username=%s, password=%s, handle=%d",
                            pReq->szUsername, pReq->szPassword, pReq->iHandle);
            gpSysLog->loginfo(szLogger);
            if (pReq->iHandle >= 0) {
                pReq->eStatus = VPARPC_STATUS_OK;
            } else {
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
        
    } else {

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
 * Handles a credentials request, processing any necessary validation or operations
 * based on the provided parameters.
 *
 * @param request_id Unique identifier for the credentials request.
 * @param user_data Data associated with the user making the request.
 * @param token Authentication token used to verify the request.
 */
void handle_creds_request(char * buffer, window* pWin) {
#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Processing CREDS request");
#endif // DISPLAY_PROCESS_DETAILS

    vparpc_request_creds_t * pReq = (vparpc_request_creds_t *)buffer;
    if (0 == strcmp(gpSh->m_pShMemng->szRpcUuid,(const char *)pReq->szAuth) ) {

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth match, authentication successful");
#endif // DISPLAY_PROCESS_DETAILS

        strcpy( pReq->szAuthUserName,
                gpSh->m_pShMemng->creds[pReq->iHandle].szAuthUserName);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  AuthUserName: " + std::string(pReq->szAuthUserName));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy( pReq->szAuthFirstName,
                gpSh->m_pShMemng->creds[pReq->iHandle].szAuthFirstName);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  AuthFirstName: " + std::string(pReq->szAuthFirstName));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy( pReq->szAuthLastName,
                gpSh->m_pShMemng->creds[pReq->iHandle].szAuthLastName);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  AuthLastName: " + std::string(pReq->szAuthLastName));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy( pReq->szAuthUUID,
                gpSh->m_pShMemng->creds[pReq->iHandle].szAuthUUID);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth UUID: " + std::string(pReq->szAuthUUID));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy( pReq->szAuthLevel,
                gpSh->m_pShMemng->creds[pReq->iHandle].szAuthLevel);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  AuthLevel: " + std::string(pReq->szAuthLevel));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy( pReq->szRemoteHost,
                gpSh->m_pShMemng->creds[pReq->iHandle].szRemoteHost);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  RemoteHost: " + std::string(pReq->szRemoteHost));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy( pReq->szRemoteAddr,
                gpSh->m_pShMemng->creds[pReq->iHandle].szRemoteAddr);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  RemoteAddr: " + std::string(pReq->szRemoteAddr));
#endif // DISPLAY_PROCESS_DETAILS

        strcpy( pReq->szHttpUserAgent,
                gpSh->m_pShMemng->creds[pReq->iHandle].szHttpUserAgent);

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  HttpUserAgent: " + std::string(pReq->szHttpUserAgent));
#endif // DISPLAY_PROCESS_DETAILS

        pReq->eStatus =  VPARPC_STATUS_OK;
    } else {

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth mismatch, authentication failed");
#endif // DISPLAY_PROCESS_DETAILS

        pReq->eStatus = VPARPC_STATUS_AUTH_FAILED;
    }
}


void  process(char * pszBuffer) {
        // std::cout << "vparpc::process()" << std::endl;
        // std::cout << "vparpc::process() at line # " << __LINE__ << std::endl;

        // Create window for debugging/monitoring
        auto * pWin = new window();
        pWin->set_title("vparpc::process()");
        gpSemiGr->cosmetics(
            SRUL,       SRUR,
            SRLL,       SRLR,
            SVSR,  SVSL,
            SH,    SV);

        // We don't know what type of request it is yet, we we cast it
        // generic long enough to decode the eFunc
        const auto* request = (const vparpc_request_generic_t*)pszBuffer;

        size_t response;

        switch (request->eFunc) {

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

        default:
                break;
        }

#ifdef DISPLAY_PROCESS_INFO
        pWin->render();
#endif // DISPLAY_PROCESS_INFO

        delete pWin;
}

/**
 * @brief Main entry point for inetd-based VPA RPC Server
 */
int main() {
    // Initialize the middleware framework
    auto * pMwFw = new mwfw2(__FILE__, __FUNCTION__);
    
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    
    // Log server startup
    gpSysLog->loginfo("VPA RPC inetd server started (version 5.5.10.2)");
    
    // Read the RPC request from client (via inetd)
    bytesRead = read(STDIN_FILENO, buffer, sizeof(vparpc_request_t));
    
    if (bytesRead > 0) {
        gpSysLog->loginfo("Received bytes from client");
        
        // Process the RPC request (this modifies the buffer in-place)
        process(buffer);
        
        // Write the processed buffer back to client (via inetd)
        // Make sure we write the exact same size we read
        ssize_t bytesWritten = write(STDOUT_FILENO, buffer, bytesRead);
        
        if (bytesWritten > 0) {
            gpSysLog->loginfo("Response sent: bytes");
        } else {
            gpSysLog->loginfo("Failed to send response");
        }
    } else {
        gpSysLog->loginfo("Failed to read request from client");
    }

    // Log normal termination
    gpSysLog->loginfo("VPA RPC inetd server session completed");
    
    // Clean up
    delete pMwFw;
    
    return 0;
}