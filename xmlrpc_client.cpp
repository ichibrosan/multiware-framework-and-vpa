/////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/xmlrpc_client.cpp 2025-02-24 03:56    //
// Derived from xmlrpc-c/examples/cpp/xmlrpc_sample_add_client.cpp //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////
#include "mwfw2.h"
#include "iHex.h"

using namespace std;

#define DISPLAY_ISIGNATURE
//#define DISPLAY_VPAD_UPTIME_SECONDS

/**
 * A global string variable used to store the return code or response value for
 * XML-RPC client communications. The value of this variable is typically
 * populated after making a remote procedure call using the XML-RPC protocol.
 *
 * This variable is used across different parts of the application to access
 * the result or status value returned from the remote server.
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
 * Main entry point of the application.
 *
 * This function initializes required components, processes diagnostic
 * requests, and displays the output on a user interface window. Various
 * diagnostic functions are executed to retrieve and display system
 * information and credentials.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv An array of argument strings passed to the program.
 * @return Returns 0 on successful execution.
 */
int
main(int argc, char **) {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    window * pWin = new window();

    // by default use my local IP
    std::string ssTargetIP = gpSh->m_pShMemng->szIP;

    diagnose * pDiagnose = new diagnose(ssTargetIP);

#ifdef DISPLAY_ISIGNATURE
    muteInt * mute_iSignature =
        new muteInt("/fw_shmem_iSignature",
                    &gpSh->m_pShMemng->iSignature);
    std::string ssSignature =
        "[iSignature] is " + std::to_string(mute_iSignature->get());
    pWin->add_row(ssSignature);
#endif // DISPLAY_ISIGNATURE

#ifdef DISPLAY_VPAD_UPTIME_SECONDS
    muteInt * mute_vpad_uptime_seconds =
        new muteInt("/fw_shmem_vpad_uptime_seconds",
                    &gpSh->m_pShMemng->vpad_uptime_seconds);
    std::string ssUptime =
        "[vpad_uptime_seconds] is " +
            std::to_string(mute_vpad_uptime_seconds->get());
    pWin->add_row(ssUptime);
#endif // DISPLAY_VPAD_UPTIME_SECONDS

    diagnose_request_t request;
    request.eReqFunc      = DIAGNOSE_REQ_VERSION;
    std::string ssVersion = pDiagnose->call(request);
    std::string ssVersion2 = "Version: " + ssVersion;
    pWin->add_row(ssVersion2);

    request.eReqFunc      = DIAGNOSE_GET_IMGROOT;
    std::string ssImgRoot = pDiagnose->call(request);
    std::string ssImgRoot2 = "ImgRoot: " + ssImgRoot;
    pWin->add_row(ssImgRoot2);

    request.eReqFunc = DIAGNOSE_GET_CRED;
    strcpy(request.szParm3,CFG_USERNAME);
    strcpy(request.szParm4,CFG_PASSWORD);
    std::string ssHandle = pDiagnose->call(request);
    std::string ssHandle2 = "Handle:  " + ssHandle;
    pWin->add_row(ssHandle2);
    int iHandle = atoi(ssHandle.c_str());

    request.eReqFunc = DIAGNOSE_GET_AUTH_USER_NAME;
    request.iParm2 = iHandle;
    std::string ssUserName = pDiagnose->call(request);
    std::string ssUserName2 = "User:    " + ssUserName;
    pWin->add_row(ssUserName2);

    request.eReqFunc = DIAGNOSE_GET_AUTH_FIRST_NAME;
    request.iParm2 = iHandle;
    std::string ssFirstName = pDiagnose->call(request);
    std::string ssFirstName2 = "First:   " + ssFirstName;
    pWin->add_row(ssFirstName2);

    request.eReqFunc = DIAGNOSE_GET_AUTH_LAST_NAME;
    request.iParm2 = iHandle;
    std::string ssLastName = pDiagnose->call(request);
    std::string ssLastName2 = "Last:    " + ssLastName;
    pWin->add_row(ssLastName2);

    request.eReqFunc = DIAGNOSE_GET_AUTH_LEVEL;
    request.iParm2 = iHandle;
    std::string ssUserLevel = pDiagnose->call(request);
    std::string ssUserLevel2 = "Level:   " + ssUserLevel;
    pWin->add_row(ssUserLevel2);

    pWin->render();

    delete pWin;
    return 0;
}
