//
// Created by doug on 3/8/25.
//

#ifndef DIAGNOSEMETHOD_H
#define DIAGNOSEMETHOD_H
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

    /*************************************************************************
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
     ***********************************************************************/
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) override {

        int const iParm1(paramList.getInt(0));
        int const iParm2(paramList.getInt(1));
        int const iParm3Type(paramList.getInt(2));
        std::string ssParm3(paramList.getString(3));
        int const iParm4Type(paramList.getInt(4));
        std::string ssParm4(paramList.getString(5));
        std::string ssAuth(paramList.getString(6));
        paramList.verifyEnd(7);
        char szPayload[FILENAME_MAX];

        sprintf(szPayload,
            "Server RPC: P1=%s,P2=%d,P3Type=%s,"
                  "P3=%s,P4Type=%s,P4=%s,ssAuth=%s",
            vpad_req_names[iParm1],iParm2,
            vpad_type_names[iParm3Type],ssParm3.c_str(),
            vpad_type_names[iParm4Type],ssParm4.c_str(),ssAuth.c_str());
        gpSysLog->loginfo(szPayload);
        switch (iParm1) {
            case VPAD_REQ_VERSION:
                if (0 == strcmp(ssAuth.c_str(),gpSh->m_pShMemng->szRpcUuid)) {
                   *retvalP = xmlrpc_c::value_string(RVERSION_STRING_LONG);
                } else {
                    sleep(10); // make them pay a time penalty to obviate attacks
                   *retvalP = xmlrpc_c::value_string("Synchronization Error!!");
                }
                break;
            case VPAD_REQ_AUTH:
                if (0 == strcmp(ssAuth.c_str(),VPA_RPC_PSK)) {
                    *retvalP = xmlrpc_c::value_string(gpSh->m_pShMemng->szRpcUuid);
                } else {
                    sleep(10); // make them pay a time penalty to obviate attacks
                    *retvalP = xmlrpc_c::value_string("Synchronization Error!!");
                }
                break;
            case VPAD_REQ_PARMS:
                if (0 == strcmp(ssAuth.c_str(),gpSh->m_pShMemng->szRpcUuid)) {
                    *retvalP = xmlrpc_c::value_string(szPayload);
                } else {
                    sleep(10); // make them pay a time penalty to obviate attacks
                    *retvalP = xmlrpc_c::value_string("Synchronization Error!!");
                }
                break;
            case VPAD_REQ_TERM:
                here;
                *retvalP = xmlrpc_c::value_string("VPAD Shutting Down!!");
                here;
                exit(EXIT_SUCCESS);
            default:
                *retvalP = xmlrpc_c::value_string("Unknown Request");
        }
    }
};

#endif //DIAGNOSEMETHOD_H
