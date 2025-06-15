////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/vparpc.h 2025/06/10 - dwg //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.     //
////////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"

#ifndef VPARPC_H
#define VPARPC_H

enum vparpc_version_t {
    VPARPC_VERSION_NONE = 0,
    VPARPC_VERSION_1,
    VPARPC_VERSION_COUNT
};

/**
 * @brief Enumeration of supported VPA RPC function types
 * 
 * Defines the various remote procedure call functions available in the VPA RPC system.
 * Each function represents a specific operation that can be invoked remotely.
 */
enum vparpc_func_t {
    VPARPC_FUNC_NONE = 0,        ///< No operation/null function
    VPARPC_FUNC_GET_AUTH,        ///< Authentication retrieval function
    VPARPC_FUNC_HOST2IPV4ADDR,   ///< Hostname to IPv4 address resolution function
    VPARPC_FUNC_VERSION,         ///< Version information retrieval function
    VPARPC_FUNC_COUNT            ///< Total count of available functions (used for validation)
};

/**
 * @brief Maximum payload size for VPA RPC packets
 * 
 * Defines the maximum size in bytes for RPC packet payloads to ensure compatibility
 * with UDP packet size limitations and network infrastructure constraints.
 * 
 * @note See doc/UDP-packet-size-considerations-AI.txt for detailed rationale
 */
#define VPARPC_MAX_PAYLOAD_SIZE 512

/**
 * @brief Basic RPC request structure for functions requiring no additional parameters
 * 
 * Used for simple RPC calls that only need function identification and request tracking.
 */
struct vparpc_request_generic_t {
    vparpc_version_t eVersion;        // Function type identifier
    size_t        nSize;              //  Size of request data (in bytes)
    vparpc_func_t eFunc;              //  Function type identifier
    char8_t       szUUID[UUID_SIZE];  //  Unique request identifier (36 chars + null terminator)
};


struct vparpc_request_auth_t {
    vparpc_version_t eVersion;        // Function type identifier
    size_t        nSize;              //  Size of request data (in bytes)
    vparpc_func_t eFunc;              ///< Function type identifier
    char8_t       szPSK[UUID_SIZE];  ///< Unique request identifier (36 chars + null terminator)
    char       szAuth[UUID_SIZE];  ///< Unique request identifier (36 chars + null terminator)
};


/**
 * @brief RPC request structure for version information requests
 * 
 * Specialized request structure for version queries, currently identical to the basic
 * request but maintained separately for potential future extensions.
 */
struct vparpc_request_version_t {
    vparpc_version_t eVersion;        // Function type identifier
    size_t        nSize;              //  Size of request data (in bytes)
    vparpc_func_t eFunc;              ///< Function type identifier (should be VPARPC_FUNC_VERSION)
    char8_t       szUUID[UUID_SIZE];  ///< Unique request identifier (36 chars + null terminator)
};

/**
 * @brief Union of all possible RPC request structures
 * 
 * Provides a unified interface for handling different types of RPC requests
 * while maintaining type safety and memory efficiency.
 */
union vparpc_request_t {
    struct vparpc_request_generic_t req_generic;  // Generic req structure
    struct vparpc_request_auth_t    req_auth;     // Auth    req structure
    struct vparpc_request_version_t req_version;  // Version req structure
};

/**
 * @brief VPA Remote Procedure Call handler class
 * 
 * Implements both client and server functionality for VPA RPC communications.
 * Handles UDP-based network communication, request processing, and response generation.
 * Supports both synchronous client calls and asynchronous server operation.
 */
class vparpc {
private:
    window * v_pWin;                ///< Pointer to associated window for UI operations
    std::string v_ssVpaSrcAddr;     ///< Source IP address for network operations
    std::string v_ssVpaSrcPort;     ///< Source port for network operations
    std::string v_ssVpaDestAddr;    ///< Destination IP address for client operations
    std::string v_ssVpaDestPort;    ///< Destination port for client operations
    int v_nListenSocket;            ///< Socket descriptor for receiving incoming packets
    int v_nSendSocket;              ///< Socket descriptor for sending outgoing packets
public:
    std::string handle_none_request(const vparpc_request_generic_t& request, window* pWin);
//    std::string handle_auth_request(const vparpc_request_generic_t& request, window* pWin);
    size_t handle_auth_request(char *buffer, window* pWin);
//    std::string handle_host_resolution_request(const vparpc_request_generic_t& request, window* pWin);
//    std::string handle_version_request(const vparpc_request_version_t& request, window* pWin);


    /**
     * @brief Default constructor
     * 
     * Initializes the VPA RPC instance with default values.
     * Sets up internal state but does not establish network connections.
     */
    vparpc();

    /**
     * @brief Start RPC server on specified service
     * 
     * Initializes and starts the RPC server to listen for incoming requests
     * on the specified service name/port.
     * 
     * @param ssService Service name or port number to bind to
     * 
     * @note This method blocks and continuously processes incoming requests
     */
    void server(std::string ssService);

    /**
     * @brief Process incoming RPC request buffer
     * 
     * Parses and processes an incoming RPC request, generating an appropriate response.
     * Handles function dispatch and parameter validation.
     * 
     * @param pszBuffer Pointer to buffer containing the RPC request data
     * @return std::string Response data to be sent back to the client
     * 
     * @note Buffer must contain a valid RPC request structure
     */
    size_t process(char * pszBuffer);

    /**
     * @brief Send RPC request to remote server
     * 
     * Establishes connection to remote RPC server and sends the specified packet.
     * Handles client-side communication including connection setup and data transmission.
     * 
     * @param ssHostName Target hostname or IP address
     * @param ssServiceName Target service name or port number
     * @param packet RPC request packet data to send
     * 
     * @note This method handles synchronous communication with the remote server
     */
    void client(std::string ssHostName,
        std::string ssServiceName,
        void * reqpkt,
        size_t pktlen);

    /**
     * @brief Convert service name to port number
     * 
     * Resolves a service name to its corresponding port number using system
     * service resolution mechanisms (e.g., /etc/services, DNS SRV records).
     * 
     * @param ssSvcName Service name to resolve
     * @return int Port number corresponding to the service, or -1 if resolution fails
     */
    int svc2port(std::string ssSvcName);

    /**
     * @brief Resolve hostname to IPv4 address
     * 
     * Performs DNS resolution to convert a hostname to its corresponding IPv4 address.
     * Supports both hostname resolution and validation of IP address strings.
     * 
     * @param ssHost Hostname or IP address string to resolve
     * @return std::string IPv4 address in dotted decimal notation, or empty string on failure
     * 
     * @note This function may block during DNS resolution
     */
    std::string host2ipv4addr(const std::string& ssHost);

    /**
     * @brief Render RPC status and statistics
     * 
     * Updates the associated window with current RPC status information,
     * connection statistics, and operational state for monitoring purposes.
     * 
     * @note Requires valid v_pWin pointer for display operations
     */
    void render();
};

#endif //VPARPC_H