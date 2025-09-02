
////////////////////////////////////////////////////////////////////////
// ~/public_html/fw/discovery_inetd_server.cpp 2025-08-31 08:15 Q dwg - //
// This file is part of MultiWare Engineering's VPA and FrameWork     //
////////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

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


struct discovery_request_t
{
    vparpc_version_t eVersion;
    size_t nSize;
    vparpc_func_t eFunc;
    char8_t szAuth[UUID_SIZE];
    vparpc_status_t eStatus;
    char szVersion[VERSION_SIZE_MAX];

    char szServerIP[DNS_FQDN_SIZE_MAX];
    int  iRmaj;
    int  iRmin;
    int  iRRev;
    int  iRbld;
    char szPadding[1000-(4*sizeof(int))];
};


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
void handle_discovery_request(char* buffer, window* pWin)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);
    gpSysLog->loginfo(__PRETTY_FUNCTION__);

#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Processing Discovery request");
#endif // DISPLAY_PROCESS_DETAILS

    auto * pReq = (discovery_request_t*)buffer;
//    memcpy(&gpVpaRpc->m_req_version, pReq, sizeof(vparpc_request_version_t));
    // TODO: this needs fixing
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

    handle_discovery_request(pszBuffer,pWin);

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
    gpSysLog->loginfo("*** VPA Discovery inetd server started)");
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
