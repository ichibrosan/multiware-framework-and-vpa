////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/vparpc.h 2025/06/10 - dwg //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.     //
////////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"

#ifndef VPARPC_H
#define VPARPC_H

/**
 * @enum vparpc_version_t
 * @brief Represents the version identifiers used in vparpc.
 *
 * Enumerates the valid versions of the vparpc protocol and a count for validation purposes.
 *
 * @constant VPARPC_VERSION_NONE
 * The initial or no version state.
 *
 * @constant VPARPC_VERSION_1
 * Version 1 of the vparpc protocol.
 *
 * @constant VPARPC_VERSION_COUNT
 * The total count of available versions. Used for validation.
 */
enum vparpc_version_t {
    VPARPC_VERSION_NONE = 0,
    VPARPC_VERSION_1,
    VPARPC_VERSION_COUNT
};

/**
 * @enum vparpc_func_t
 * @brief Enumerates the available functions for the virtual process RPC.
 *
 * This enumeration defines the functions that can be invoked in the
 * virtual process RPC interface. Each function serves a specific
 * purpose in the operation of the system.
 *
 * - VPARPC_FUNC_NONE: Represents a no-operation or null function.
 * - VPARPC_FUNC_GET_AUTH: Used for authentication retrieval.
 * - VPARPC_FUNC_HOST2IPV4ADDR: Resolves a hostname to its corresponding IPv4 address.
 * - VPARPC_FUNC_VERSION: Retrieves the version information of the RPC system.
 * - VPARPC_FUNC_COUNT: Represents the total count of available functions and is used
 *   for validation purposes.
 */
enum vparpc_func_t {
    VPARPC_FUNC_NONE = 0,        ///< No operation/null function
    VPARPC_FUNC_GET_AUTH,        ///< Authentication retrieval function
    VPARPC_FUNC_HOST2IPV4ADDR,   ///< Hostname to IPv4 address resolution function
    VPARPC_FUNC_VERSION,         ///< Version information retrieval function
    VPARPC_FUNC_LOOKUP,         // using username/password , get handle
    VPARPC_FUNC_CREDS,          // using handle, get credentials
    VPARPC_FUNC_COUNT            ///< Total count of available functions (used for validation)
};

/**
 * @enum vparpc_status_t
 * @brief Enumerates the possible status codes for vparpc operations.
 *
 * The vparpc_status_t enum provides a set of status codes that indicate
 * the outcome of a vparpc operation. These codes can be used to determine
 * whether the operation was successful or if specific types of errors occurred.
 *
 * @var VPARPC_STATUS_OK
 *      Operation completed successfully.
 *      This status is equivalent to EXIT_SUCCESS.
 *
 * @var VPARPC_STATUS_ERROR
 *      Generic error occurred during the operation.
 *      This status is equivalent to EXIT_FAILURE.
 *
 * @var VPARPC_STATUS_AUTH_FAILED
 *      Authentication failure.
 *      Indicates that the authentication process did not succeed.
 *
 * @var VPARPC_STATUS_COUNT
 *      Count of all status codes defined in the vparpc_status_t enumerator.
 *      Used for validation or iteration purposes.
 */
enum vparpc_status_t {
    VPARPC_STATUS_OK    = EXIT_SUCCESS,
    VPARPC_STATUS_ERROR = EXIT_FAILURE,
    VPARPC_STATUS_AUTH_FAILED,
    VPARPC_STATUS_COUNT
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
 * @struct vparpc_request_generic_t
 * @brief Represents a generic RPC request structure in the vparpc system.
 *
 * This structure encapsulates the essential components of a generic request
 * made to the vparpc system. It includes information about the version of the
 * protocol, the size of the request data, the function being invoked, and
 * a universally unique identifier (UUID) associated with the request.
 */
struct vparpc_request_generic_t {
    vparpc_version_t    eVersion;
    size_t              nSize;
    vparpc_func_t       eFunc;
    char8_t             szUUID[UUID_SIZE];
};


/*****************************************************************************
 * @struct vparpc_request_auth_t
 * @brief Represents an authentication request in the vparpc protocol.
 *
 * This structure is used to handle and encapsulate authentication requests
 * in the vparpc communication protocol.
 *
 * @var eVersion
 * The version of the vparpc protocol being used for this request.
 *
 * @var nSize
 * The size of the request in bytes.
 *
 * @var eFunc
 * The function or operation identifier associated with the authentication
 * request.
 *
 * @var szPSK
 * The Pre-Shared Key (PSK) used for authentication. This array is sized
 * based on UUID_SIZE.
 *
 * @var eStatus
 * The status of the authentication request. Indicates any errors or success.
 *
 * @var szAuth
 * The resulting authentication token or identifier. This array is sized
 * based on UUID_SIZE.
 */
struct vparpc_request_auth_t {

    vparpc_version_t    eVersion;
    size_t              nSize;
    vparpc_func_t       eFunc;
    char8_t             szPSK[UUID_SIZE];

    vparpc_status_t     eStatus;
    char                szAuth[UUID_SIZE];
};



struct vparpc_request_version_t {

    vparpc_version_t    eVersion;
    size_t              nSize;
    vparpc_func_t       eFunc;
    char8_t             szAuth[UUID_SIZE];

    vparpc_status_t     eStatus;
    char                szVersion[VERSION_SIZE_MAX];
};


struct vparpc_request_lookup_t {

    vparpc_version_t    eVersion;
    size_t              nSize;
    vparpc_func_t       eFunc;
    char8_t             szAuth[UUID_SIZE];
    char                szUsername[UT_NAMESIZE];
    char                szPassword[UT_NAMESIZE];

    vparpc_status_t     eStatus;
    int                 iHandle;
};

struct vparpc_request_creds_t {

    vparpc_version_t    eVersion;
    size_t              nSize;
    vparpc_func_t       eFunc;
    char8_t             szAuth[UUID_SIZE];
    int                 iHandle;

    vparpc_status_t     eStatus;
    char                szAuthUserName[UT_NAMESIZE];
    char                szAuthFirstName[UT_NAMESIZE];
    char                szAuthLastName[UT_NAMESIZE];
    char                szAuthUUID[UUID_SIZE];
    char                szAuthLevel[UT_NAMESIZE];
    char                szRemoteHost[DNS_FQDN_SIZE_MAX];
    char                szRemoteAddr[DNS_FQDN_SIZE_MAX];
    char                szHttpUserAgent[128];

};

union vparpc_request_t {
    struct vparpc_request_generic_t req_generic;

    struct vparpc_request_auth_t    req_auth;

    struct vparpc_request_version_t req_version;  // Version req structure

    char filler[128];   // force the vparpc_request_t to the next 64 byte blocksize
};


class vparpc {
private:
    window * v_pWin;
    std::string v_ssVpaDestAddr;
    std::string v_ssVpaDestPort;
    int v_nListenSocket;
    int v_nSendSocket;
public:
    vparpc();
    void handle_auth_request(char *buffer, window* pWin);
    void handle_version_request(char * buffer, window* pWin);
    void handle_lookup_request(char * buffer, window* pWin);
    void handle_creds_request(char * buffer, window* pWin);
    void server(std::string ssService);
    void  process(char * pszBuffer);
    void client(std::string host,std::string service,void * pkt,size_t len);
    int svc2port(std::string ssSvcName);
    std::string host2ipv4addr(const std::string& ssHost);
    void render();
};

#endif //VPARPC_H