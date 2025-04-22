/////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/diagnoseMethod.h 2025-03-148 12:28    //
// Derived from xmlrpc-c/examples/cpp/xmlrpc_sample_add_client.cpp //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////

#ifndef DIAGNOSEMETHOD_H
#define DIAGNOSEMETHOD_H

/**
 * @brief Array of request names for the Virtual Protocol Adapter.
 *
 * This array contains string constants representing various request
 * types that the VPAD system can handle. These names are typically
 * used for logging or identifying a specific request type in the
 * system's request handling logic.
 *
 * The available request types are:
 * - "VERSION" : Request related to system version.
 * - "AUTH"    : Request for authentication.
 * - "PARMS"   : Request for parameters.
 * - "STATUS"  : Request for system status.
 * - "TERM"    : Request to terminate the system.
 */
const char * diagnose_req_names[] = {
    "NONE","VERSION","AUTH","PARMS","STATUS","TERM","GETSHM",
    "GETIMGROOT",
    "GETCRED","GETUSERNAME","GETFIRSTNAME","GETLASTNAME","GETLEVEL",
    "GETDASHBOARD"
};


/**
 * @brief Array of strings representing the names of variable parameter types.
 *
 * This array is used to map integer type identifiers to their corresponding
 * string representations, providing a way to handle and log different types
 * of variable parameters (e.g., NONE, INT, STRING, FLOAT, BOOL) within the
 * system.
 *
 * @note The order of elements in the array should correspond to the
 * enumerated values or integer representations of the types used in the
 * application.
 */
const char * diagnose_type_names[] = {
    "NONE","INT","STRING","FLOAT","BOOL"
};

/***************************************************************************
 * @class diagnoseMethod
 * @brief A class implementing an XML-RPC method to handle various server
 *        diagnostic and operational requests.
 *
 * This class inherits from `xmlrpc_c::method` and serves as a handler for
 * XML-RPC requests. It processes specific diagnostic requests such as
 * obtaining the server version, authentication handling, retrieving
 * parameters, and terminating the server.
 *
 * The method provides detailed logging of requests and applies security
 * measures, including authentication verification and intentional delays
 * to mitigate attacks.
 */
class diagnoseMethod : public xmlrpc_c::method {
    /**
     * A method implementing the "diagnose" functionality for an XML-RPC
     * server. This class encapsulates the behavior needed to perform
     * operations related to the "diagnose" method, providing both the
     * signature and help metadata for XML-RPC clients to query.
     *
     * The class is derived from `xmlrpc_c::method`, making it suitable
     * to be integrated into an XML-RPC server. The signature describes
     * the method's input and return types, while the help string provides
     * context about its operation for client-side documentation.
     */
public:
    diagnoseMethod() {
        // signature and help strings are documentation -- the client
        // can query this information with a system.methodSignature and
        // system.methodHelp RPC.
        this->_signature = "s:iiisiss";
            // method's result and two arguments are integers
        this->_help = "This method adds two integers together";
    }

    /***********************************************************************
     * Executes a server-side XML-RPC method to handle specific client
     *    requests.
     *
     * This override processes a list of parameters sent via XML-RPC,
     * performs the necessary actions based on the specified request
     * type, and sets the result appropriately. The following requests
     * are supported:
     *
     * - VPAD_REQ_VERSION: Returns the version string if the client provides
     *      valid authentication.
     * - VPAD_REQ_AUTH: Returns an authentication token upon correct
     *      pre-shared key verification.
     * - VPAD_REQ_PARMS: Returns request parameters as a serialized payload
     *      if authentication is valid.
     * - VPAD_REQ_TERM: Terminates the server after returning a shutdown
     *      message.
     * - Default: Returns an "Unknown Request" error for unrecognized
     *      requests.
     *
     * Security measures are implemented to delay responses for invalid
     * authentication, mitigating potential brute force attacks.
     *
     * @param paramList A const reference to the parameter list passed by
     *                  the client. It includes various arguments relevant
     *                  to the specific request.
     * @param retvalP A pointer to an XML-RPC value object where the
     *                  response is stored.
     *********************************************************************/
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) override {

        std::string ssBuffer;
        int iHandle;

        int const iFunc(paramList.getInt(0));
        int const iParm2(paramList.getInt(1));
        int const iParm3Type(paramList.getInt(2));
        std::string ssParm3(paramList.getString(3));
        int const iParm4Type(paramList.getInt(4));
        std::string ssParm4(paramList.getString(5));
        std::string ssAuth(paramList.getString(6));
        paramList.verifyEnd(7);
        char szPayload[FILENAME_MAX];

        sprintf(szPayload,
            "vpad Server RPC: Func=%s,P2=%d,P3Type=%s,"
                  "P3=%s,P4Type=%s,P4=%s,Auth=%s",
            diagnose_req_names[iFunc],iParm2,
            diagnose_type_names[iParm3Type],ssParm3.c_str(),
            diagnose_type_names[iParm4Type],ssParm4.c_str(),ssAuth.c_str());
        gpSysLog->loginfo(szPayload);
        switch (iFunc) {
            case DIAGNOSE_REQ_VERSION:
                if (0 == strcmp(ssAuth.c_str(),
                    gpSh->m_pShMemng->szRpcUuid)) {
                   *retvalP = xmlrpc_c::value_string(
                       RLONG);
                } else {
                    sleep(10); // make them pay a time penalty
                    *retvalP = xmlrpc_c::value_string(
                        "Synchronization Error!!");
                }
                break;
            case DIAGNOSE_REQ_AUTH:
                if (0 == strcmp(ssAuth.c_str(),CFG_VPA_RPC_PSK)) {
                    *retvalP =
                        xmlrpc_c::value_string(
                            gpSh->m_pShMemng->szRpcUuid);
                } else {
                    sleep(10); // make them pay a time penalty
                    *retvalP = xmlrpc_c::value_string(
                        "Synchronization Error!!");
                }
                break;
            case DIAGNOSE_REQ_PARMS:
                if (0 == strcmp(ssAuth.c_str(),
                    gpSh->m_pShMemng->szRpcUuid)) {
                    *retvalP = xmlrpc_c::value_string(szPayload);
                } else {
                    sleep(10); // make them pay a time penalty
                    *retvalP = xmlrpc_c::value_string(
                        "Synchronization Error!!");
                }
                break;
            case DIAGNOSE_REQ_TERM:
                here;
                *retvalP = xmlrpc_c::value_string(
                    "VPAD Shutting Down!!");
                here;
                exit(EXIT_SUCCESS);
            case DIAGNOSE_REQ_GETSHM:
                here;
                ssBuffer =
                    gpHex->structure_to_intel_hex(gpSh->m_pShMemng,
                        gpSh->m_pShMemng->stShMemSize,0);
                here;
                *retvalP = xmlrpc_c::value_string(ssBuffer);
                here;
                break;

            case DIAGNOSE_GET_IMGROOT:
                *retvalP = xmlrpc_c::value_string(
                         gpSh->m_pShMemng->szImgRoot);
                break;

            case DIAGNOSE_GET_CRED:
                // Tested OK 2025-04-01 17:32 dwg -
                gpCsv = new readCsv("passwd.csv");
                gpCsv->parseData();
                iHandle = gpPassword->lookup_username_password(
                            ssParm3,ssParm4);
                sprintf(szPayload,"%d",iHandle);
                *retvalP = xmlrpc_c::value_string(szPayload);
                break;

            case DIAGNOSE_GET_AUTH_USER_NAME:
                *retvalP = xmlrpc_c::value_string(
                    gpSh->m_pShMemng->creds[iParm2].szAuthUserName);
            break;

            case DIAGNOSE_GET_AUTH_FIRST_NAME:
                *retvalP = xmlrpc_c::value_string(
                    gpSh->m_pShMemng->creds[iParm2].szAuthFirstName);
            break;

            case DIAGNOSE_GET_AUTH_LAST_NAME:
                *retvalP = xmlrpc_c::value_string(
                    gpSh->m_pShMemng->creds[iParm2].szAuthLastName);
            break;

            case DIAGNOSE_GET_AUTH_LEVEL:
                *retvalP = xmlrpc_c::value_string(
                    gpSh->m_pShMemng->creds[iParm2].szAuthLevel);
            break;

            case DIAGNOSE_GET_IP:
                *retvalP = xmlrpc_c::value_string(gpSh->m_pShMemng->szIP);
                break;

            default:
                *retvalP = xmlrpc_c::value_string(
                    "Unknown Request");
        }
    }
};

#endif //DIAGNOSEMETHOD_H
