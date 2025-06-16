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
    vparpc_version_t eVersion; /**
     * Represents the version of the vparpc protocol being used, as defined by the
     * enumerated type `vparpc_version_t`.
     *
     * Possible values are:
     * - `VPARPC_VERSION_NONE`: No version specified.
     * - `VPARPC_VERSION_1`: Version 1 of the protocol.
     * - `VPARPC_VERSION_COUNT`: Represents the total count of available versions.
     *
     * This variable typically identifies the version of the protocol to ensure
     * compatibility between the communicating entities.
     */
    size_t        nSize;              //  Size of request data (in bytes)
    vparpc_func_t eFunc; /**
     * @brief A character array representing a universally unique identifier (UUID).
     *
     * This variable is used to identify a specific request or transaction uniquely
     * within the system. It ensures that requests can be tracked and managed without
     * conflicts.
     *
     * The size of the array is determined by the constant `UUID_SIZE`, ensuring
     * it accommodates a valid UUID format.
     */
    char8_t       szUUID[UUID_SIZE]; /**
     *
     */
};


/**
 * @struct vparpc_request_auth_t
 * @brief Represents the structure used for authentication requests in the VPARPC framework.
 *
 * This structure contains all required fields to specify an authentication
 * request including version, size, function, pre-shared key (PSK), status, and authentication data.
 */
struct vparpc_request_auth_t {
 /**
  * @brief Represents the version of the RPC protocol.
  *
  * This variable is of type `vparpc_version_t` and is used to specify the
  * version of the vparpc protocol being utilized. The versions are defined
  * in the `vparpc_version_t` enumeration, which includes options such as:
  * - `VPARPC_VERSION_NONE`: Represents no version specified.
  * - `VPARPC_VERSION_1`: Represents version 1 of the protocol.
  * - `VPARPC_VERSION_COUNT`: Marker for the number of versions, used for boundary checks.
  */
 vparpc_version_t    eVersion;
 /**
  * Represents the size of a data structure or memory block.
  *
  * This variable is used to define or store the size of an element
  * within the context it is being utilized, often specifying
  * the amount of data or memory required for a particular operation.
  */
 size_t              nSize;
 /**
  * @brief Represents the function type for vparpc (Virtualized Process Authentication and Remote Procedure Call) operations.
  *
  * This variable determines the specific operation or function to be executed. It can take on one of the enumerated values
  * defined in vparpc_func_t, which include:
  * - VPARPC_FUNC_NONE: Represents no operation or a null function.
  * - VPARPC_FUNC_GET_AUTH: Retrieves authentication-related details.
  * - VPARPC_FUNC_HOST2IPV4ADDR: Resolves a hostname to its corresponding IPv4 address.
  * - VPARPC_FUNC_VERSION: Retrieves version information.
  * - VPARPC_FUNC_COUNT: Used to count the total number of available functions (typically for validation purposes).
  *
  * It is important to initialize and set this variable to an appropriate value before performing vparpc-related operations.
  */
 vparpc_func_t       eFunc;
 /**
  * @brief Stores the pre-shared key (PSK) used for authentication purposes.
  *
  * This variable is a fixed-size array of characters, defined to hold a UUID-based
  * pre-shared key. The PSK is utilized in authentication protocols to ensure secure
  * communication and prevent unauthorized access.
  *
  * @note The size of the array is determined by the constant `UUID_SIZE`, which
  * represents the length of a UUID.
  */
 char8_t             szPSK[UUID_SIZE];

 /**
  * Represents the status of an entity or operation, typically used to indicate
  * different states or outcomes such as success, failure, or specific conditions.
  */
 vparpc_status_t     eStatus;
 /**
  * A character array used for storing authorization data.
  * The size of the array is defined by the macro UUID_SIZE.
  * Typically utilized in the context of authentication mechanisms
  * to store unique identifiers or related credentials.
  */
 char                szAuth[UUID_SIZE];

};

/**
 * @struct vparpc_request_version_t
 * @brief Represents a structure for RPC version request.
 *
 * This structure is used as a container for version-related request data in
 * the vparpc system.
 *
 * Members:
 * - eVersion: Specifies the version of the vparpc system or protocol.
 * - nSize: Represents the size of the request.
 * - eFunc: Identifies the function or operation being requested.
 * - szAuth: Stores authentication information, represented as a UUID.
 * - eStatus: Represents the status or result of the request.
 * - szVersion: Contains the version details in string format with a maximum
 *   size of VERSION_SIZE_MAX.
 */
struct vparpc_request_version_t {
 /**
  * @brief Represents the version information for the vparpc protocol.
  *
  * This variable defines the protocol version being used in a request
  * or response. The version is represented using the `vparpc_version_t`
  * enum, which specifies the different supported versions of the protocol.
  *
  * @see vparpc_version_t
  */
 vparpc_version_t    eVersion;
 /**
  * Represents the size of the structure or data being handled.
  *
  * This variable is utilized for specifying the size in bytes,
  * ensuring proper memory allocation or data processing within
  * the context of its usage.
  */
 size_t              nSize;
 /**
  * @brief Enumerated variable representing the specific Remote Procedure Call (RPC) function to execute.
  *
  * The variable `eFunc` is of type `vparpc_func_t`, which defines a set of predefined RPC functions that
  * can be invoked. This enumerator includes options such as no operation, authentication retrieval,
  * hostname to IPv4 address resolution, version information retrieval, and a validation count for available functions.
  *
  * Possible values for `eFunc`:
  * - VPARPC_FUNC_NONE: Indicates no specific operation or a null function.
  * - VPARPC_FUNC_GET_AUTH: Used to retrieve authentication data.
  * - VPARPC_FUNC_HOST2IPV4ADDR: Converts a hostname to its associated IPv4 address.
  * - VPARPC_FUNC_VERSION: Retrieves version information.
  * - VPARPC_FUNC_COUNT: Represents the total count of available functions, mainly used for validation purposes.
  */
 vparpc_func_t       eFunc;
 /**
  * @brief Authentication identifier represented as a character array.
  *
  * szAuth is used to store a unique authentication ID, typically
  * a UUID (Universally Unique Identifier) of fixed size defined by UUID_SIZE.
  * It is employed to verify and establish secure communication or
  * to identify the requester in a system.
  */
 char8_t             szAuth[UUID_SIZE];

 /**
  * Represents the status of a specific operation or process within the application.
  * Typically used to indicate the current state or result of an executed task.
  */
 vparpc_status_t     eStatus;
 /**
  * A character array for storing version information.
  *
  * This variable holds the version string up to a maximum size defined by VERSION_SIZE_MAX.
  * It is used to represent version details in the context of the `vparpc_request_version_t` structure.
  * The value stored in this array should be null-terminated if it represents a valid string.
  */
 char                szVersion[VERSION_SIZE_MAX];

};


/**
 * @union vparpc_request_t
 * Represents a unified structure for different types of requests that the
 * vparpc module can process. This union allows access to various request
 * structures, depending on the context and functionality of the request.
 *
 * The union is used to manage request data in a type-safe manner, ensuring
 * structured processing and interpretation of request-specific fields.
 *
 * @var req_generic
 * A generic request structure. This member is used for basic request processing
 * where the fields and behaviors are general and do not belong to specific
 * categories like authentication or versioning.
 *
 * @var req_auth
 * An authentication-specific request structure. This member is used for requests
 * related to authentication functionalities, providing the necessary fields for
 * authentication processing.
 *
 * @var req_version
 * A version-specific request structure. This member is used for requests related
 * to versioning, carrying details necessary for version-specific functionalities.
 */
union vparpc_request_t {
    struct vparpc_request_generic_t req_generic; /**
     * @struct vparpc_request_auth_t
     * Represents a request structure used within the vparpc framework for
     * authenticating a connection or user.
     *
     * This structure is part of a union within `vparpc_request_t` and is
     * specifically designed to facilitate authentication requests involving
     * pre-shared keys (PSK) and other related fields.
     *
     * @var req_auth
     * A structure of type `vparpc_request_auth_t` embedded within the `vparpc_request_t` union,
     * used to handle authentication requests in the framework.
     *
     * The structure contains:
     * - `eVersion`: Specifies which version of the protocol is being requested.
     * - `nSize`: Represents the size of the request data in bytes.
     * - `eFunc`: Identifies the function type for processing within the system.
     * - `szPSK`: Stores the pre-shared key for authentication.
     * - `eStatus`: Represents the status of the request, defined by `vparpc_status_t`.
     * - `szAuth`: Contains the generated authentication token or credentials.
     */
    struct vparpc_request_auth_t    req_auth; /**
     * @brief Data structure representing a version request in the vparpc system.
     *
     * This structure is specifically designed to handle version-related requests
     * in the vparpc system, allowing a client to request and handle version
     * information from a remote service. The structure contains fields for
     * version negotiation, request metadata, authentication, and the retrieved
     * version data.
     *
     * Fields:
     * - eVersion: Specifies the protocol version being used for the request.
     * - nSize: Specifies the size of the request data in bytes.
     * - eFunc: Identifies the function being executed for this request.
     * - szAuth: Authentication string used for secure interaction.
     * - eStatus: Indicates the success or failure status of the request.
     * - szVersion: Buffer to store the version data returned by the service.
     *
     * The `req_version` variable is an instance of this structure and represents
     * a specific version request.
     */
    struct vparpc_request_version_t req_version;  // Version req structure
};

/**
 * @class vparpc
 * @brief Represents the vparpc class handling specific functionalities.
 */
class vparpc {
private:
    window * v_pWin; /**
     * @brief Pointer to a window object, used for managing and manipulating
     * graphical window components within the associated system.
     *
     * This variable is utilized within the `vparpc` class to reference and
     * interact with a `window` object. It may handle operations such as
     * rendering, displaying, and maintaining the state of the window during
     * various processes.
     */
    std::string v_ssVpaSrcAddr;     ///< Source IP address for network operations
    std::string v_ssVpaSrcPort; /**
     * Represents the destination IP address used for client operations in network communication.
     *
     * This variable is utilized to specify the IP address of the target server or endpoint
     * in client-side processes. It is part of the vparpc class and plays a key role in
     * configuring the destination for outgoing network requests.
     */
    std::string v_ssVpaDestAddr;    ///< Destination IP address for client operations
    std::string v_ssVpaDestPort; /**
     * Socket descriptor for receiving incoming packets.
     *
     * This variable is used to hold the file descriptor associated with
     * the listening socket. It is responsible for accepting incoming
     * network connections and facilitating data exchange. Typically,
     * it is initialized when a server binds to a specific port and
     * begins listening for incoming connections.
     */
    int v_nListenSocket;            ///< Socket descriptor for receiving incoming packets
    int v_nSendSocket; /**
     * Handles an authentication request by processing the provided buffer and updating the authentication status.
     *
     * This method validates the pre-shared key (PSK) from the provided buffer. If the PSK matches
     * the configured value, the method initializes the authentication data in the buffer and sets
     * the status to `VPARPC_STATUS_OK`. Otherwise, it sets the status to `VPARPC_STATUS_AUTH_FAILED`.
     * Log messages are recorded in the provided window object to indicate the result of the authentication process.
     *
     * @param buffer A pointer to the buffer containing the incoming authentication request. The buffer must
     *               follow the structure of `vparpc_request_auth_t` and will be modified to include
     *               the authentication result on success or failure.
     * @param pWin A pointer to the window object used for logging messages during the authentication process.
     * @return The size of the authentication request structure (`sizeof(vparpc_request_auth_t)`).
     */
public:
    size_t handle_auth_request(char *buffer, window* pWin);

    /**
     * Handles the processing of a version request in the vparpc system.
     *
     * This method validates the authentication provided in the request buffer,
     * compares it with the system's expected authentication token, and sets the
     * appropriate version information or authentication status based on this
     * validation. It also logs the status of the operation in the provided
     * `window` instance.
     *
     * @param buffer A pointer to the buffer containing the version request
     *               information. This should be properly formatted according
     *               to the structure `vparpc_request_version_t`.
     * @param pWin A pointer to the `window` object for logging the steps and
     *             status of the operation.
     * @return The size of the request structure (`nSize`), as stored within
     *         the buffer.
     */
    size_t handle_version_request(char * buffer, window* pWin);

    /**
     * Represents a type or function related to vparpc functionality.
     *
     * @return The result or specific behavior based on the vparpc implementation.
     */
    vparpc();

    /**
     * Represents the server functionality or component.
     */
    void server(std::string ssService);

    /**
     * Processes the given data or executes the designated operation.
     *
     * @param input The input data or object to be processed.
     * @param mode The mode in which the process function operates.
     * @return The result or outcome of the process function.
     */
    size_t process(char * pszBuffer);

    /**
     * Represents a client entity for communication or operations.
     */
    void client(std::string ssHostName,
                std::string ssServiceName,
                void * reqpkt,
                size_t pktlen);

    /**
     * Resolves a given service name to its corresponding port number.
     * Attempts to resolve the port number using the TCP protocol first,
     * and if unsuccessful, tries the UDP protocol. If the service name
     * is not found in either, returns -1.
     *
     * @param ssSvcName The name of the service to be resolved (e.g., "http", "ftp").
     * @return The port number corresponding to the specified service name,
     *         or -1 if the service name cannot be resolved.
     */
    int svc2port(std::string ssSvcName);

    /**
     * Resolves a given hostname to its corresponding IPv4 address. If the hostname
     * is already a valid IPv4 address, it is returned as-is. Otherwise, the method
     * attempts to resolve the IPv4 address by reading the system's hosts file.
     * If the hostname cannot be resolved, an empty string is returned.
     *
     * @param hostname The hostname to resolve. It can be a domain name or an IPv4 address.
     * @return The corresponding IPv4 address as a string if the resolution is successful,
     *         or an empty string if the resolution fails.
     */
    std::string host2ipv4addr(const std::string& ssHost);

    /**
     * Renders the content to the current context.
     *
     * This method is responsible for rendering elements or components
     * associated with the class. The implementation of the render function
     * is class-dependent and may include drawing graphical elements, displaying
     * text, or invoking other rendering-related operations.
     */
    void render();
};

#endif //VPARPC_H