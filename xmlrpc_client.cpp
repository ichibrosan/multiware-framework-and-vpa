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

/**
 * @brief Array containing names of the different request functions
 *        for the Virtual Payload Application Daemon (VPAD).
 *
 * This array maps indexes to their corresponding request function
 * names, which can be used for forming or identifying requests to
 * the VPAD service. The array elements include:
 * - VERSION: Used for version requests.
 * - AUTH: Used for authentication requests.
 * - PARMS: Used for parameter management requests.
 * - STATUS: Used for status requests.
 * - TERM: Used for termination requests.
 *
 * The array should be indexed using an enum or an appropriate
 * request identifier.
 */
const char * vpad_req_names[] = {
    "VERSION","AUTH","PARMS","STATUS","TERM"
};

/**
 * @brief An array of string representations for different RPC data types.
 *
 * This array maps each numerical value of an RPC data type to its
 * corresponding string
 * representation. The indices correspond to enumerated values defined in
 * DIAGNOSE_TYPES_T
 * or REST_TYPES_T. These strings are used for logging and communication
 * within the system.
 *
 * @note The elements of this array must match the enumeration values in
 * their respective
 *       enums to ensure correct usage during lookup or mapping.
 *
 * @details The supported RPC data types and their mappings are:
 *          - NONE: Represents the absence of a value or type.
 *          - INT: Represents an integer type.
 *          - STRING: Represents a string type.
 *          - FLOAT: Represents a floating-point number type.
 *          - BOOL: Represents a boolean type.
 */
const char * rpc_type_names[] = {
    "NONE","INT","STRING","FLOAT","BOOL"
};

/**
 * @brief Array containing string representations of REST request methods.
 *
 * This array maps REST request enumerations to their corresponding string
 * names, such as "GET", "HEAD", "OPTIONS", "PUT", "DELETE", and "POST".
 *
 * Example mappings:
 * - REST_REQ_GET -> "GET"
 * - REST_REQ_POST -> "POST"
 *
 * This array is utilized in various components of the system to represent
 * or log REST request types in string format.
 */
const char * rest_req_names[] = {
    "GET","HEAD","OPTIONS","PUT","DELETE","POST"
};

/**
 * Makes an XML-RPC call to a remote VPA (Virtual Protocol Adapter) system
 * based on the provided request details and returns the response.
 *
 * This function constructs the server URL using global shared memory
 * settings and the specified VPA port. It logs the request details and
 * sends the request to the server using the `diagnose` method. The method
 * takes several parameters, including request function, parameters, and
 * authentication details.
 *
 * Error handling is performed for exceptions thrown during the XML-RPC call.
 * In case of an error, it is logged to the standard error stream.
 *
 * @param req A reference to a structure containing the VPA request details,
 *            including the remote host address, requested function,
 *            parameters, and authentication information.
 *
 * @return A string containing the response from the VPA system. If any
 *         error occurs during the RPC call, the returned value may be
 *         incomplete or invalid.
 */
std::string vpa_call(vpa_request_t& req) {
    char szLog[256];
    sprintf(szLog,
    "Client RPC: Addr= %s P1=%s,P2=%d,P3Type=%s,"
          " P3=%s,P4Type=%s,P4=%s,ssAuth=%s",
            req.szRemoteHost,
            vpad_req_names[req.eReqFunc],  req.iParm2,
            rpc_type_names[req.eParm3Type],req.szParm3,
            rpc_type_names[req.eParm4Type],req.szParm4,req.szAuth);
    char szPort[16];
    sprintf(szPort,"%d",VPA_PORT);
    std::string ssUrl;
    ssUrl.append(gpSh->m_pShMemng->szProtocol);
    ssUrl.append(gpSh->m_pShMemng->szRemoteAddr);
    ssUrl.append(":");
    ssUrl.append(szPort);
    ssUrl.append("/RPC2");
    try {
        string const serverUrl(ssUrl);
        string const methodName("diagnose");
        xmlrpc_c::clientSimple myClient;
        xmlrpc_c::value result;
        myClient.call(  serverUrl,methodName,"iiisiss",&result,
                         req.eReqFunc,  req.iParm2,
                         req.eParm3Type,req.szParm3,
                         req.eParm4Type,req.szParm4,
                         req.szAuth);
        ssValueRetcode = xmlrpc_c::value_string(result);
    } catch (exception const& e) {
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        cerr << "Client threw unexpected error." << endl;
    }
    return ssValueRetcode;
}

/**
 * Makes a remote REST call using the provided request object.
 *
 * This function constructs the request URL for the REST RPC call by
 * dynamically formatting the necessary parameters. It then utilizes the
 * `xmlrpc_c::clientSimple` library to perform the remote procedure call
 * using the provided input parameters encapsulated in the `rest_request_t`
 * structure.
 *
 * The method ensures safety by catching any exceptions that might occur
 * during the remote call and logs errors if they happen.
 *
 * @param req The `rest_request_t` object containing details such as the
 *            remote host, request function type, parameter details, and
 *            authentication information.
 *
 * @return The result of the REST call as a `std::string` containing the
 *            return value code sent back from the remote server.
 *
 * @throws std::exception and other uncaught exceptions during the call
 *            process are logged but not propagated back to the caller.
 *            Any errors encountered will result in an error message
 *            being printed to `stderr`.
 */
std::string rest_call(rest_request_t& req) {
    char szLog[256];
    sprintf(szLog,
    "Client RPC: Addr= %s P1=%s,P2=%d,P3Type=%s,"
          " P3=%s,P4Type=%s,P4=%s,ssAuth=%s",
            req.szRemoteHost,
            rest_req_names[req.eReqFunc],  req.eReqSubFunc,
            rpc_type_names[req.eParm3Type],req.szParm3,
            rpc_type_names[req.eParm4Type],req.szParm4,req.szAuth);
    char szPort[16];
    sprintf(szPort,"%d",VPA_PORT);
    std::string ssUrl;
    ssUrl.append(gpSh->m_pShMemng->szProtocol);
    ssUrl.append(gpSh->m_pShMemng->szRemoteAddr);
    ssUrl.append(":");
    ssUrl.append(szPort);
    ssUrl.append("/RPC2");
    try {
        string const serverUrl(ssUrl);
        string const methodName("rest");
        xmlrpc_c::clientSimple myClient;
        xmlrpc_c::value result;
        myClient.call(  serverUrl,methodName,"iiisiss",&result,
                         req.eReqFunc,  req.eReqSubFunc,
                         req.eParm3Type,req.szParm3,
                         req.eParm4Type,req.szParm4,
                         req.szAuth);
        ssValueRetcode = xmlrpc_c::value_string(result);
    } catch (exception const& e) {
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        cerr << "Client threw unexpected error." << endl;
    }
    return ssValueRetcode;
}

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
    here;
    if (argc-1 > 0) {
        cerr << "This program has no arguments" << endl;
        exit(1);
    }

    // Set this to the desired remote VPA system
    strcpy(gpSh->m_pShMemng->szRemoteAddr,"192.168.4.17");
    strcpy(gpSh->m_pShMemng->szRemoteHost,"daphne.goodall.com");
//    strcpy(gpSh->m_pShMemng->szRemoteAddr,"192.168.4.223");

    std::cout << "Remote Addr is:       " << gpSh->m_pShMemng->szRemoteAddr
              << std::endl;

    vpa_request_t reqAuth;
    strcpy(reqAuth.szRemoteHost,gpSh->m_pShMemng->szRemoteAddr);
    reqAuth.eReqFunc = DIAGNOSE_REQ_AUTH;
    reqAuth.iParm2 = 0;
    reqAuth.eParm3Type = DIAGNOSE_TYPE_NONE;
    reqAuth.eParm4Type = DIAGNOSE_TYPE_NONE;
    strcpy(reqAuth.szAuth,VPA_RPC_PSK);
    std::string ssReturn = vpa_call(reqAuth);
    strcpy(gpSh->m_pShMemng->szRemoteAuth,ssReturn.c_str());
    std::cout << "Remote Auth Token is: " << ssReturn << std::endl;

    vpa_request_t reqVer;
    strcpy(reqVer.szRemoteHost,gpSh->m_pShMemng->szRemoteAddr);
    reqVer.eReqFunc = DIAGNOSE_REQ_VERSION;
    reqVer.iParm2 = 0;
    reqVer.eParm3Type = DIAGNOSE_TYPE_NONE;
    reqVer.eParm4Type = DIAGNOSE_TYPE_NONE;
    strcpy(reqVer.szAuth,gpSh->m_pShMemng->szRemoteAuth);
    ssReturn = vpa_call(reqVer);
    strcpy(gpSh->m_pShMemng->szRemoteVersion,ssReturn.c_str());
    std::cout << "Remote Version is:    " << ssReturn << std::endl;

    // vpa_request_t reqShm;
    // strcpy(reqShm.szRemoteHost,gpSh->m_pShMemng->szRemoteAddr);
    // reqShm.eReqFunc = DIAGNOSE_REQ_GETSHM;
    // reqShm.iParm2 = 0;
    // reqShm.eParm3Type = DIAGNOSE_TYPE_NONE;
    // reqShm.eParm4Type = DIAGNOSE_TYPE_NONE;
    // strcpy(reqShm.szAuth,gpSh->m_pShMemng->szRemoteAuth);
    // ssReturn = vpa_call(reqShm);
    // std::cout << "Remote Shared Memory is:    " << std::endl;
    // std::cout << ssReturn << std::endl;


    rest_request_t restReqAuth;
    strcpy(restReqAuth.szRemoteHost,gpSh->m_pShMemng->szRemoteAddr);
    restReqAuth.eReqFunc = REST_REQ_GET;
    restReqAuth.eReqSubFunc = REST_REQ_SUB_VER;
    restReqAuth.eParm3Type = REST_TYPE_NONE;
    restReqAuth.eParm4Type = REST_TYPE_NONE;
    strcpy(restReqAuth.szAuth,gpSh->m_pShMemng->szRemoteAuth);
    std::string ssAuthReturn = rest_call(restReqAuth);
    std::cout << "REST_REQ_GET::REST_REQ_SUB_VER returns: "
              << ssAuthReturn << std::endl;


    return 0;
}
