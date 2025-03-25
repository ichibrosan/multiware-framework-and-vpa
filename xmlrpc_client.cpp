/////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/xmlrpc_client.cpp 2025-02-24 03:56    //
// Derived from xmlrpc-c/examples/cpp/xmlrpc_sample_add_client.cpp //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////
#include "mwfw2.h"
#include "iHex.h"

using namespace std;

/**
 * @brief A global variable to store the return code as a string
 *        for both XML-RPC and REST method calls.
 *
 * This variable is used to capture and store the result of a
 * remote procedure call (RPC) or REST API call, specifically
 * the value returned by the server. It is populated after the
 * successful execution of a remote method invocation, such as
 * `vpa_call` or `rest_call`. The content of this variable is assigned
 * using the return value obtained from XML-RPC or REST methods.
 *
 * @note The variable's value is subject to change upon any invocation
 *       of the related RPC or REST functions.
 */
std::string ssValueRetcode;

// /**
//  * @brief Array containing names of the different request functions
//  *        for the Virtual Payload Application Daemon (VPAD).
//  *
//  * This array maps indexes to their corresponding request function
//  * names, which can be used for forming or identifying requests to
//  * the VPAD service. The array elements include:
//  * - VERSION: Used for version requests.
//  * - AUTH: Used for authentication requests.
//  * - PARMS: Used for parameter management requests.
//  * - STATUS: Used for status requests.
//  * - TERM: Used for termination requests.
//  *
//  * The array should be indexed using an enum or an appropriate
//  * request identifier.
//  */
// const char * vpad_req_names[] = {
//     "VERSION","AUTH","PARMS","STATUS","TERM"
// };

// /**
//  * @brief An array of string representations for different RPC data types.
//  *
//  * This array maps each numerical value of an RPC data type to its
//  * corresponding string
//  * representation. The indices correspond to enumerated values defined in
//  * DIAGNOSE_TYPES_T
//  * or REST_TYPES_T. These strings are used for logging and communication
//  * within the system.
//  *
//  * @note The elements of this array must match the enumeration values in
//  * their respective
//  *       enums to ensure correct usage during lookup or mapping.
//  *
//  * @details The supported RPC data types and their mappings are:
//  *          - NONE: Represents the absence of a value or type.
//  *          - INT: Represents an integer type.
//  *          - STRING: Represents a string type.
//  *          - FLOAT: Represents a floating-point number type.
//  *          - BOOL: Represents a boolean type.
//  */
// const char * rpc_type_names[] = {
//     "NONE","INT","STRING","FLOAT","BOOL"
// };

// /**
//  * @brief Array containing string representations of REST request methods.
//  *
//  * This array maps REST request enumerations to their corresponding string
//  * names, such as "GET", "HEAD", "OPTIONS", "PUT", "DELETE", and "POST".
//  *
//  * Example mappings:
//  * - REST_REQ_GET -> "GET"
//  * - REST_REQ_POST -> "POST"
//  *
//  * This array is utilized in various components of the system to represent
//  * or log REST request types in string format.
//  */
// const char * rest_req_names[] = {
//     "GET","HEAD","OPTIONS","PUT","DELETE","POST"
// };


/**
 * @brief Entry point of the application.
 *
 * The main function initializes the application, sets the remote address
 * of the VPA system, and performs various operations such as
 * authentication, fetching remote version, and making REST API calls.
 * It also includes mechanisms for error handling and output of operation
 * results.
 *
 * @param argc Number of arguments passed to the program.
 * @param argv Array of character pointers listing all the arguments.
 * @return int Exit status of the program.
 *
 * @details
 * This program:
 * - Ensures no command-line arguments are provided, otherwise exits with
 *      an error message.
 * - Sets a predefined remote address and host for the VPA system.
 * - Authenticates with the VPA system and retrieves the authentication
 *      token.
 * - Fetches the remote system version using the authentication token.
 * - Optionally contains commented-out functionality to retrieve shared
 *      memory details.
 * - Makes a REST API request to retrieve version information and outputs
 *      the result.
 */
int
main(int argc, char **) {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    diagnose * pDiagnose = new diagnose(gpSh->m_pShMemng->szIP);

    diagnose_request_t request;
    request.eReqFunc = DIAGNOSE_REQ_VERSION;
    std::string ssVersion = pDiagnose->call(request);

    std::cout << "Remote Version is:    " << ssVersion << std::endl;

    // std::cout << "svars: " << gpShmVars->get_string(SV_RMAC)
    //           << std::endl;

    return 0;
}
