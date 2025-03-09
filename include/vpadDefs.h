//////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/vpadDefs.h 2025/02/02 11:42 //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.                 //
//////////////////////////////////////////////////////////////////////////////

#ifndef VPADDEFS_H
#define VPADDEFS_H

/**
 * @enum VPAD_REQUESTS_T
 * @brief Enumerates the types of requests for a virtual pad (VPAD).
 *
 * This enumeration defines the various request types that can be made
 * to the virtual pad system. Each enum value corresponds to a specific
 * kind of request.
 *
 * @constant VPAD_REQ_INIT Represents a request to initialize the virtual pad system.
 * @constant VPAD_REQ_STATUS Represents a request to check the status of the virtual pad.
 * @constant VPAD_REQ_COUNT Represents the count of total request types defined.
 */
enum VPAD_REQ_FUNCS_T {
    VPAD_REQ_VERSION,
    VPAD_REQ_AUTH,
    VPAD_REQ_PARMS,
    VPAD_REQ_STATUS,
    VPAD_REQ_TERM,
    VPAD_REQ_COUNT
};


enum VPAD_TYPES_T {
    VPAD_TYPE_NONE,
    VPAD_TYPE_INT,
    VPAD_TYPE_STRING,
    VPAD_TYPE_FLOAT,
    VPAD_TYPE_BOOL,
    VPAD_TYPE_COUNT
};


typedef struct vpa_request_t {
    char szRemoteHost[DNS_FQDN_SIZE_MAX];
    VPAD_REQ_FUNCS_T eReqFunc;
    int iParm2;
    VPAD_TYPES_T eParm3Type;
    char szParm3[BUFSIZ];
    VPAD_TYPES_T eParm4Type;
    char szParm4[BUFSIZ];
    char szAuth[FILENAME_MAX];
} vpa_req_t;

/**
 * @enum VPAD_RESP_T
 * @brief Represents the possible response states in a VPAD operation.
 *
 * @var VPAD_RESP_IDLE
 * Indicates that the VPAD operation is currently idle and no action is being performed.
 *
 * @var VPAD_RESP_SUCCESS
 * Indicates that the VPAD operation was successfully completed without errors.
 *
 * @var VPAD_RESP_FAILURE
 * Indicates that the VPAD operation failed to complete successfully.
 */
enum VPAD_RESP_T {
    VPAD_RESP_IDLE,
    VPAD_RESP_SUCCESS,
    VPAD_RESP_FAILURE
};

#endif //VPADDEFS_H
