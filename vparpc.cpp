//////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/vparpc.cpp 2025/01/17 - dwg //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.       //
//////////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"
#include <string.h>
#include "vparpc.h"

#include <netdb.h>
#include <arpa/inet.h>

#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <cctype>

//#define DISPLAY_MAIN_SERVER_LOOP_INFO
//#define DISPLAY_PROCESS_INFO
//#define DISPLAY_PROCESS_DETAILS


/**
 * @brief Array of RPC function name strings for use in debugging or display purposes
 *
 * This constant array maps the internal identifiers for RPC functions to their
 * corresponding human-readable names. The names are prefixed with "Function"
 * for clarity during debugging, logging, or monitoring operations.
 *
 * The functions represented in this array include:
 * - "Function None": Indicates no operation or a placeholder function.
 * - "Function Get_Auth": Represents the function used to obtain authentication details.
 * - "Function Host2ipv4addr": Converts a hostname to its corresponding IPv4 address.
 * - "Function Version": Retrieves the version of the application or service.
 * - "Function Lookup": Performs a lookup operation based on specific parameters.
 * - "Function Creds": Handles credential-related operations.
 *
 * This data is typically used by window-based debugging utilities to present a
 * clear and user-friendly description of the operations being processed.
 *
 * @note The indices in this array correspond directly to the enumerated values
 *       for function identifiers (e.g., `VPARPC_FUNC_GET_AUTH`).
 *
 * @warning Ensure that any changes to the function enumeration or identifiers
 *          are reflected in this array to avoid mismatches or incorrect mappings.
 */
const char * vparpc_func_names[] = {
    "  Function None",
    "  Function Get_Auth",
    "  Function Host2ipv4addr",
    "  Function Version",
    "  Function Lookup",
    "  Function Creds",
    "  Function URLS"
};

/**
 * @return The result or status from the vparpc function execution.
 */
vparpc::vparpc() {
}

/**
 * Processes the given input and performs operations as defined in the implementation.
 *
 * @param input Represents the input data to be processed.
 */
// #####   #####    ####    ####   ######   ####    ####
// #    #  #    #  #    #  #    #  #       #       #
// #    #  #    #  #    #  #       #####    ####    ####
// #####   #####   #    #  #       #            #       #
// #       #   #   #    #  #    #  #       #    #  #    #
// #       #    #   ####    ####   ######   ####    ####
//
void  vparpc::process(char * pszBuffer) {
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
                handle_auth_request(pszBuffer, pWin);
                break;
                
            case VPARPC_FUNC_VERSION:
                handle_version_request(pszBuffer, pWin);
                break;

            case VPARPC_FUNC_LOOKUP:
                handle_lookup_request(pszBuffer, pWin);
                break;

            case VPARPC_FUNC_CREDS:
                handle_creds_request(pszBuffer, pWin);
                break;

            case VPARPC_FUNC_URLS:
                handle_urls_request(pszBuffer,pWin);
            default:
                 break;
        }

#ifdef DISPLAY_PROCESS_INFO
    pWin->render();
#endif // DISPLAY_PROCESS_INFO

        delete pWin;
}


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
void vparpc::handle_auth_request(char *buffer, window* pWin) {
#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Processing AUTH request");
#endif // DISPLAY_PROCESS_DETAILS
    // Cast the buffer to a vparpc_request_auth_t structure so we can pick up the PSK
    // out of the request packet, and know more about the response fields.
    vparpc_request_auth_t * pReq = (vparpc_request_auth_t *)buffer;
    if (0 == strcmp((char *)CFG_VPA_RPC_PSK,(const char *)pReq->szPSK) ) {
        // Caller presented correct pre-shared key
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
void vparpc::handle_version_request(char * buffer, window* pWin) {
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
}


/**
 * Handles a lookup request.
 *
 * @param requestId Unique identifier for the lookup request.
 * @param requestPayload Data associated with the lookup request.
 * @param responseBuffer Buffer to store the response generated by the lookup.
 * @param errorCallback Callback function to handle any errors encountered during the lookup process.
 */
void vparpc::handle_lookup_request(char * buffer, window* pWin) {
#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Processing LOOKUP request");
#endif // DISPLAY_PROCESS_DETAILS

    vparpc_request_lookup_t * pReq = (vparpc_request_lookup_t *)buffer;
    if (0 == strcmp(gpSh->m_pShMemng->szRpcUuid,(const char *)pReq->szAuth) ) {

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth match, authentication successful");
#endif // DISPLAY_PROCESS_DETAILS

        gpCsv = new readCsv("passwd.csv");
        gpCsv->parseData();
        pReq->iHandle =
                gpPassword->lookup_username_password(
                    pReq->szUsername, pReq->szPassword);
        pReq->eStatus =  VPARPC_STATUS_OK;
    } else {

#ifdef DISPLAY_PROCESS_DETAILS
        pWin->add_row("  Auth mismatch, authentication failed");
#endif // DISPLAY_PROCESS_DETAILS

        pReq->eStatus =  VPARPC_STATUS_AUTH_FAILED;
    }
}

/**
 * Handles a credentials request, processing any necessary validation or operations
 * based on the provided parameters.
 *
 * @param request_id Unique identifier for the credentials request.
 * @param user_data Data associated with the user making the request.
 * @param token Authentication token used to verify the request.
 */
void vparpc::handle_creds_request(char * buffer, window* pWin) {
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


void vparpc::handle_urls_request(char * buffer, window* pWin) {
    gpSysLog->loginfo(__PRETTY_FUNCTION__);
#ifdef DISPLAY_PROCESS_DETAILS
    pWin->add_row("  Processing URLS request");
#endif // DISPLAY_PROCESS_DETAILS

    vparpc_request_urls_t * pReq = (vparpc_request_urls_t *)buffer;

    if (0 == strcmp(gpSh->m_pShMemng->szRpcUuid,(const char *)pReq->szAuth) ) {
        strcpy(pReq->szIP,gpSh->m_pShMemng->szIP);
        strcpy(pReq->szCgiRoot,gpSh->m_pShMemng->szCgiRoot);
        strcpy(pReq->szStylesRoot,gpSh->m_pShMemng->szStylesRoot);
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
}



/**
 * @brief Starts a TCP server that listens for incoming connections on a specified service port
 *
 * Initializes a TCP server that resolves the provided service name to a port number and begins
 * listening for client connections. Each client connection is processed sequentially, and received
 * data is appropriately handled. Responses are sent back to connected clients before closing the connection.
 * Diagnostics and status information are displayed on visual windows during the operation of the server.
 *
 * The main server loop runs indefinitely to handle incoming connections.
 *
 * @param ssService The service name (e.g., "http") or port number as a string to resolve into an actual port
 *
 * @note This function creates visual diagnostic windows for both server and client events
 * @note Each client connection is managed synchronously, with data received and processed in sequence
 *
 * @warning This function operates in an infinite loop and does not terminate under normal circumstances
 * @warning No advanced error handling or timeout policies are implemented for client connectivity
 * @warning No authentication or security features are implemented (e.g., encryption, access control)
 */

/**
 * @brief Starts a TCP server that listens for incoming client connections
 * 
 * Creates a TCP server socket that binds to the specified service port and enters
 * an infinite loop to handle client connections. Each client connection is processed
 * synchronously, receiving data and sending appropriate responses based on the
 * received commands.
 * 
 * Supported commands:
 * - "/GET version": Returns the application version string (RSTRING)
 * - "/GET szRpcUuid": Returns the RPC UUID from shared memory
 * 
 * @param ssService The service name to resolve to a port number using system service lookup
 * 
 * @note This function runs indefinitely and will not return under normal circumstances
 * @note Each client connection is handled sequentially (not multi-threaded)
 * @note Creates a visual window to display server status and client interactions
 * @note Memory allocated for window objects is properly cleaned up after each client
 * 
 * @warning The server socket cleanup code at the end is unreachable due to infinite loop
 * @warning No authentication or authorization is implemented
 * @warning Buffer overflow protection relies on BUFSIZ-1 limit
 */
void vparpc::server(std::string ssService) {

    // BlockCipher cipher(16);
    // cipher.setKey("DouglasWGoodall");
    // char ciphertext[sizeof(vparpc_request_t)];
    // char  plaintext[sizeof(vparpc_request_t)];

    std::string response;

    // Create visual window for server status display
    auto * pWin = new window();
    gpSemiGr->cosmetics( SRUL,  SRUR,  SRLL,
                    SRLR,SVSR,SVSL,
                    SH,  SV);

    // Resolve service name to port number
    int iPort = svc2port(ssService);

    // Set window title with server information
    std::string ssSine = "vparpc::server() - Starting TCP server on port " + std::to_string(iPort);
    pWin->set_title(ssSine);
    
    // Socket file descriptors
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFSIZ];  // Buffer for receiving client data (typically 8192 bytes)


    // Create TCP socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        pWin->add_row("  Error: socket creation failed");
        pWin->render();
        return;
    }
    pWin->add_row("  Server socket created");

    // Set socket options to allow address reuse (prevents "Address already in use" errors)
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        pWin->add_row("  Error: setsockopt failed");
        pWin->render();
        close(server_fd);
        return;
    }
    pWin->add_row("  Socket options set");

    // Configure server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Listen on all available interfaces
    server_addr.sin_port = htons(iPort);       // Convert port to network byte order
    
    // Bind socket to the specified address and port
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        pWin->add_row("  Error: bind failed");
        pWin->render();
        close(server_fd);
        return;
    }
    pWin->add_row("  Server bound to port "+ std::to_string(iPort) );

    // Start listening for incoming connections (queue up to 5 pending connections)
    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        close(server_fd);
        return;
    }
    
    pWin->add_row("Server listening on port " + std::to_string(iPort));
    
    // Main server loop - handles clients sequentially
    while (true) {
        // Create new window for each client connection
        auto * pWin = new window();
        pWin->set_title("  Main server loop");

        // Accept incoming client connection (blocking call)
        if ((client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len)) < 0) {
            pWin->add_row("  Error: accept failed");
            continue;  // Continue to next iteration on error
        }
        
        // Extract client address and port information
        std::string ssClientAddr = inet_ntoa(client_addr.sin_addr);
        std::string ssClientPort = std::to_string(ntohs(client_addr.sin_port));
        std::string ssClient = ssClientAddr + ":" + ssClientPort;
        pWin->add_row("  Client connected from " + ssClient);

        // Clear receive buffer
        memset(buffer, 0, BUFSIZ);
        
        // Receive data from client
        ssize_t bytes_received = recv(client_fd, buffer, BUFSIZ - 1, 0);
        //ssize_t bytes_received = recv(client_fd, ciphertext, BUFSIZ - 1, 0);
        if (bytes_received < 0) {
            pWin->add_row("  Error: recv failed");
        } else if (bytes_received == 0) {
            pWin->add_row("  Error: Client disconnected");
        } else {
            buffer[bytes_received] = '\0';  // Null-terminate the received data
            //ciphertext[bytes_received] = '\0';  // Null-terminate the received data
            pWin->add_row("  Received "+std::to_string(bytes_received));

        //  #####   #####    ####    ####   ######   ####    ####
        //  #    #  #    #  #    #  #    #  #       #       #
        //  #    #  #    #  #    #  #       #####    ####    ####
        //  #####   #####   #    #  #       #            #       #
        //  #       #   #   #    #  #    #  #       #    #  #    #
        //  #       #    #   ####    ####   ######   ####    ####
        //


            //cipher.decryptData((const uint8_t *)ciphertext,sizeof(plaintext),(uint8_t *)plaintext);
            process(buffer);
            //cipher.encryptData((uint8_t *)plaintext,sizeof(plaintext),(uint8_t *)ciphertext);

            // Send response back to client
            ssize_t bytes_sent = send(client_fd, buffer, bytes_received, 0);

            pWin->add_row("  Sent     "+std::to_string(bytes_sent));

            if (bytes_sent < 0) {
                pWin->add_row("  Error: send failed");
            } else {
                pWin->add_row("  Response sent to client");
            }
        }
        
        // Close client connection
        close(client_fd);
        pWin->add_row("  Client connection closed");
#ifdef DISPLAY_MAIN_SERVER_LOOP_INFO
        pWin->render();
#endif
        delete pWin;  // Clean up window memory
    }
    
    // Close server socket (unreachable code due to infinite loop above)
    close(server_fd);
}

/**
 * Sends a request to a specified client and processes the response.
 *
 * @param clientId The unique identifier of the client to which the request will be sent.
 * @param request The request data to be sent to the client.
 * @param timeout The timeout value in milliseconds for waiting for the client response.
 * @param isSecure A boolean flag indicating whether the request should use a secure connection.
 * @param response A reference to a string where the client's response will be stored.
 *
 * @return True if the request was successful and a response was received, false otherwise.
 */

/**
 * @brief Establishes a TCP client connection to a remote server and sends data
 * 
 * Creates a TCP client socket, resolves the target hostname, connects to the
 * specified service port, sends a data packet, receives the response, and
 * displays all communication details in a visual window.
 * 
 * @param ssHostName The hostname or IP address of the target server
 * @param ssServiceName The service name to resolve to a port number
 * @param packet The data packet to send to the server
 * 
 * @note Creates a visual window to display connection progress and data transfer
 * @note Uses gethostbyname() for hostname resolution (IPv4 only)
 * @note Synchronous operation - blocks until completion or error
 * @note Automatically closes connection after single request-response cycle
 * 
 * @warning Uses deprecated gethostbyname() function (not thread-safe)
 * @warning No timeout mechanism implemented for network operations
 * @warning Response buffer limited to BUFSIZ (typically 8192 bytes)
 */
void vparpc::client(std::string ssHostName, std::string ssServiceName, void * packet,size_t pktlen) {

    // Create visual window for client status display
    auto * pWin = new window();
    gpSemiGr->cosmetics( SRUL,  SRUR,  SRLL,
                        SRLR,SVSR,SVSL,
                        SH,  SV);
    
    // Build copyright string
    std::string ssCopr = "Copyright ";
    ssCopr.append("(c)");
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");
    
    // Set window title with connection parameters
    pWin->set_title("vparpc::client(" + ssHostName + "," + ssServiceName + ")");

    int client_fd;
    struct sockaddr_in server_addr;
    struct hostent *host_entry;
    char response_buffer[BUFSIZ];       // Response buffer (BUFSIZ = 8192)
    
    // Resolve hostname to IP address using system DNS lookup
    host_entry = gethostbyname(ssHostName.c_str());
    if (host_entry == nullptr) {
        pWin->add_row(" Error: Could not resolve hostname "+ssHostName);
        pWin->render();
        return;
    }

    vparpc_request_generic_t * pReq = (vparpc_request_generic_t *)packet;
    pWin->add_row(vparpc_func_names[pReq->eFunc]);

    pWin->add_row("  Host resolved: "+ssHostName);

    // Create TCP client socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        pWin->add_row(" Error: socket creation failed");
        pWin->render();
        return;
    }
    pWin->add_row("  Client socket created");

    // Configure server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(svc2port(ssServiceName));  // Convert service to port
    server_addr.sin_addr.s_addr = *((unsigned long *) host_entry->h_addr);  // Set IP address
    
    pWin->add_row("  Connecting to port "+std::to_string(svc2port(ssServiceName)));

    // Establish connection to server
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        pWin->add_row(" Error: connection failed");
        close(client_fd);
        return;
    }
    pWin->add_row("  Connected to server");

     // Send data packet to server
    ssize_t bytes_sent = send(client_fd, packet, pktlen, 0);
    if (bytes_sent < 0) {
        pWin->add_row(" Error: send failed");
        close(client_fd);
        pWin->render();
        return;
    }
    pWin->add_row("  Sent     "+std::to_string(bytes_sent)+" bytes");


    // Receive response from server
    ssize_t bytes_received = recv(client_fd, packet, pktlen, 0);
    if (bytes_received < 0) {
        perror("recv failed");
    } else if (bytes_received == 0) {
        std::cout << "  Server closed connection" << std::endl;
    } else {
        response_buffer[bytes_received] = '\0';  // Null-terminate response
        pWin->add_row("  Received "+std::to_string(bytes_received));
    }

    //cipher.decryptData((uint8_t *)ciphertext,pktlen,(uint8_t *)packet);

    // Close client connection
    close(client_fd);
    pWin->add_row("  Client connection closed");
    pWin->render();
}


/**
 * @brief Resolves a service name to its corresponding port number
 *
 * This method attempts to resolve the provided service name into a port number
 * using the system's service database. It first checks for the service
 * under the TCP protocol and, if not found, proceeds to check under the
 * UDP protocol. If the service cannot be resolved under either protocol,
 * the method returns -1.
 *
 * @param ssSvcName The name of the service to resolve (e.g., "http", "ftp").
 *
 * @return The port number (in host byte order) corresponding to the given
 *         service name if found, or -1 if the service name could not be resolved.
 */
int vparpc::svc2port(std::string ssSvcName) {

    struct servent *serviceEntry;
    
    // First try TCP protocol lookup
    serviceEntry = getservbyname(ssSvcName.c_str(), "tcp");

    if (serviceEntry != nullptr) {
        // Convert network byte order to host byte order
        return ntohs(serviceEntry->s_port);
    }

    // If TCP lookup failed, try UDP protocol
    serviceEntry = getservbyname(ssSvcName.c_str(), "udp");

    if (serviceEntry != nullptr) {
        // Convert network byte order to host byte order
        return ntohs(serviceEntry->s_port);
    }

    // Service not found in either TCP or UDP
    return -1;
}


/**
 * @brief Resolves a hostname to its corresponding IPv4 address using system hosts files
 *
 * Attempts to resolve a hostname to an IPv4 address. First, it validates
 * whether the input string is already a valid IPv4 address. If not, it
 * searches the system hosts files in common locations to find a match
 * for the given hostname.
 *
 * @param hostname The hostname or IP address string to be resolved
 *
 * @return The resolved IPv4 address as a string if found, or an empty string if the hostname
 *         could not be resolved or if the hosts files could not be accessed.
 *
 * @note Case-insensitive comparison is used when matching hostnames
 * @note Only IPv4 addresses (not IPv6) are validated and returned
 *
 * @warning Returns an empty string if the system's hosts files are inaccessible
 * @warning Lines in the hosts file that are malformed or contain invalid entries are ignored
 */
std::string vparpc::host2ipv4addr(const std::string& hostname) {

    // IPv4 address validation regex pattern
    // Matches: 0.0.0.0 to 255.255.255.255
    std::regex ipv4_regex(R"(^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)");
    
    // Check if input is already a valid IPv4 address
    if (std::regex_match(hostname, ipv4_regex)) {
        return hostname; // Already an IP address, return as-is
    }

    // File stream for reading hosts file
    std::ifstream hosts_file;

    // Common hosts file locations across different operating systems
    const std::vector<std::string> hosts_paths = {
        "/etc/hosts",           // Linux/Unix standard location
        "C:\\Windows\\System32\\drivers\\etc\\hosts",  // Windows standard location
        "/System/Library/etc/hosts"  // macOS alternative location
    };

    // Try to open hosts file from known locations
    for (const auto& path : hosts_paths) {
        hosts_file.open(path);
        if (hosts_file.is_open()) {
            break;  // Successfully opened, exit loop
        }
    }

    if (!hosts_file.is_open()) {
        return ""; // Could not open any hosts file
    }

    std::string line;
    std::string target_hostname = hostname;

    // Convert target hostname to lowercase for case-insensitive comparison
    std::transform(target_hostname.begin(), target_hostname.end(),
                   target_hostname.begin(), ::tolower);

    // Parse hosts file line by line
    while (std::getline(hosts_file, line)) {
        // Skip empty lines and comment lines (starting with #)
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Remove leading and trailing whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.empty()) {
            continue;
        }

        // Parse line into tokens
        std::istringstream iss(line);
        std::string ip_addr;
        std::string host_entry;

        // Get the IP address (first token on the line)
        if (!(iss >> ip_addr)) {
            continue;  // Skip malformed lines
        }

        // Validate that the first token is a valid IPv4 address
        if (!std::regex_match(ip_addr, ipv4_regex)) {
            continue; // Skip IPv6 entries or invalid IP addresses
        }

        // Check all hostnames/aliases on this line
        while (iss >> host_entry) {
            // Convert hostname to lowercase for case-insensitive comparison
            std::transform(host_entry.begin(), host_entry.end(),
                          host_entry.begin(), ::tolower);

            // Check if this hostname matches our target
            if (host_entry == target_hostname) {
                hosts_file.close();
                return ip_addr;  // Found match, return corresponding IP
            }
        }
    }

    hosts_file.close();
    return ""; // Hostname not found in hosts file
}

/////////
// eof //
/////////