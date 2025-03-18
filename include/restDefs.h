//
// Created by doug on 3/17/25.
//

#ifndef RESTDEFS_H
#define RESTDEFS_H

enum RESTFUL_REQ_FUNCS_T {
    RESTFUL_REQ_GET,
    RESTFUL_REQ_HEAD,
    RESTFUL_REQ_OPTIONS,
    RESTFUL_REQ_PUT,
    RESTFUL_REQ_DELETE,
    RESTFUL_REQ_POST,
    RESTFUL_REQ_COUNT
};


enum RESTFUL_TYPES_T {
    RESTFUL_TYPE_NONE,
    RESTFUL_TYPE_INT,
    RESTFUL_TYPE_STRING,
    RESTFUL_TYPE_FLOAT,
    RESTFUL_TYPE_BOOL,
    RESTFUL_TYPE_COUNT
};


typedef struct rest_request_t {
    char szRemoteHost[DNS_FQDN_SIZE_MAX];
    RESTFUL_REQ_FUNCS_T eReqFunc;
    int iParm2;
    RESTFUL_TYPES_T eParm3Type;
    char szParm3[BUFSIZ];
    RESTFUL_TYPES_T eParm4Type;
    char szParm4[BUFSIZ];
    char szAuth[FILENAME_MAX];
} rest_req_t;

/**
 * @enum RESTFUL_RESP_T
 * @brief Represents the possible response states in a RESTFUL operation.
 *
 * @var RESTFUL_RESP_IDLE
 * Indicates that the RESTFUL operation is currently idle and no action is being performed.
 *
 * @var RESTFUL_RESP_SUCCESS
 * Indicates that the RESTFUL operation was successfully completed without errors.
 *
 * @var RESTFUL_RESP_FAILURE
 * Indicates that the RESTFUL operation failed to complete successfully.
 */
enum RESTFUL_RESP_T {
    RESTFUL_RESP_IDLE,
    RESTFUL_RESP_SUCCESS,
    RESTFUL_RESP_FAILURE
};


#endif //RESTDEFS_H
