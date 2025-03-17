///////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/diagnoseDefs.h 2025/02/02 11:42 //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.  //
///////////////////////////////////////////////////////////////

#ifndef DIAGNOSEDEFS_H
#define DIAGNOSEDEFS_H

/**
 * @enum DIAGNOSE_REQUESTS_T
 * @brief Enumerates the types of requests for a virtual pad (DIAGNOSE).
 *
 * This enumeration defines the various request types that can be made
 * to the virtual pad system. Each enum value corresponds to a specific
 * kind of request.
 *
 * @constant DIAGNOSE_REQ_INIT Represents a request to initialize the virtual pad system.
 * @constant DIAGNOSE_REQ_STATUS Represents a request to check the status of the virtual pad.
 * @constant DIAGNOSE_REQ_COUNT Represents the count of total request types defined.
 */
enum DIAGNOSE_REQ_FUNCS_T {
    DIAGNOSE_REQ_VERSION,
    DIAGNOSE_REQ_AUTH,
    DIAGNOSE_REQ_PARMS,
    DIAGNOSE_REQ_STATUS,
    DIAGNOSE_REQ_TERM,
    DIAGNOSE_REQ_GETSHM,
    DIAGNOSE_REQ_COUNT
};


enum DIAGNOSE_TYPES_T {
    DIAGNOSE_TYPE_NONE,
    DIAGNOSE_TYPE_INT,
    DIAGNOSE_TYPE_STRING,
    DIAGNOSE_TYPE_FLOAT,
    DIAGNOSE_TYPE_BOOL,
    DIAGNOSE_TYPE_COUNT
};


typedef struct vpa_request_t {
    char szRemoteHost[DNS_FQDN_SIZE_MAX];
    DIAGNOSE_REQ_FUNCS_T eReqFunc;
    int iParm2;
    DIAGNOSE_TYPES_T eParm3Type;
    char szParm3[BUFSIZ];
    DIAGNOSE_TYPES_T eParm4Type;
    char szParm4[BUFSIZ];
    char szAuth[FILENAME_MAX];
} vpa_req_t;

/**
 * @enum DIAGNOSE_RESP_T
 * @brief Represents the possible response states in a DIAGNOSE operation.
 *
 * @var DIAGNOSE_RESP_IDLE
 * Indicates that the DIAGNOSE operation is currently idle and no action is being performed.
 *
 * @var DIAGNOSE_RESP_SUCCESS
 * Indicates that the DIAGNOSE operation was successfully completed without errors.
 *
 * @var DIAGNOSE_RESP_FAILURE
 * Indicates that the DIAGNOSE operation failed to complete successfully.
 */
enum DIAGNOSE_RESP_T {
    DIAGNOSE_RESP_IDLE,
    DIAGNOSE_RESP_SUCCESS,
    DIAGNOSE_RESP_FAILURE
};

#endif //DIAGNOSEDEFS_H
