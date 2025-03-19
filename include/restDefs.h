//
// Created by doug on 3/17/25.
//

#ifndef RESTDEFS_H
#define RESTDEFS_H

enum REST_REQ_FUNCS_T {
    REST_REQ_GET,
    REST_REQ_HEAD,
    REST_REQ_OPTIONS,
    REST_REQ_PUT,
    REST_REQ_DELETE,
    REST_REQ_POST,
    REST_REQ_COUNT
};

enum REST_REQ_SUBFNS_T {
    REST_REQ_SUB_VER,
    REST_REQ_SUB_COUNT
};

enum REST_TYPES_T {
    REST_TYPE_NONE,
    REST_TYPE_INT,
    REST_TYPE_STRING,
    REST_TYPE_FLOAT,
    REST_TYPE_BOOL,
    REST_TYPE_COUNT
};


typedef struct rest_request_t {
    char szRemoteHost[DNS_FQDN_SIZE_MAX];
    REST_REQ_FUNCS_T eReqFunc;
    REST_REQ_SUBFNS_T eReqSubFunc;
    REST_TYPES_T eParm3Type;
    char szParm3[BUFSIZ];
    REST_TYPES_T eParm4Type;
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
enum REST_RESP_T {
    REST_RESP_IDLE,
    REST_RESP_SUCCESS,
    REST_RESP_FAILURE
};


#endif //RESTDEFS_H
