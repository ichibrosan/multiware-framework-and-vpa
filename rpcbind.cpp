//
// Created by doug on 2/21/25.
//

#include "mwfw2.h"
#include "diagnoseDefs.h"

#include "rpcbind.h"

/**
 * @brief Constructor for the rpcbind class.
 *
 * Initializes an instance of the rpcbind class.
 * This constructor is used to set up any necessary internal
 * state or resources required for the object.
 */
rpcbind::rpcbind() {

}

/**
 * A global variable used to store the string result value obtained from the RPC call.
 *
 * This variable is updated within the `rpcbind::vpa_call` function after retrieving
 * the result from an XML-RPC server. It holds the string representation of the
 * XML-RPC response and is returned as the output of the function.
 */
std::string ssValue;

/**
 * \brief Makes a remote procedure call (RPC) to a specified server and retrieves the result.
 *
 * This function constructs a server URL based on the provided vpa_request_t structure
 * and invokes the XML-RPC method 'diagnose' on the remote server. Parameters for the
 * call are passed through the vpa_request_t structure, and the response is retrieved as
 * a string.
 *
 * \param req A reference to a vpa_request_t structure containing parameters required
 *            for the remote procedure call, such as the remote host, function, and
 *            authentication details.
 * \return A string representing the response from the remote procedure call.
 *
 * \throws std::exception Catches and displays exceptions if thrown while performing
 *         the RPC call.
 */
std::string rpcbind::vpa_call(vpa_request_t& req) {
    char szServerURL[1024];
    try {

        // Develop URL like http://daphne:5164/RPC2
        sprintf(szServerURL,"%s%s:%d/RPCC2",
                gpSh->m_pShMemng->szProtocol,
                req.szRemoteHost,VPA_PORT);

        std::string const serverUrl(szServerURL);
        std::string const methodName("diagnose");
        xmlrpc_c::clientSimple myClient;
        xmlrpc_c::value result;
        myClient.call(  serverUrl,
                        methodName,
                        "iiisiss",
                         &result,
                         req.eReqFunc,
                         req.iParm2,
                         req.eParm3Type,req.szParm3,
                         req.eParm4Type,req.szParm4,
                         // req.szAuth s/b szRpcUuid or
                         // VPA_RPC_PSK(for VPA_REQ_AUTH)
                         req.szAuth);

        ssValue = xmlrpc_c::value_string(result);
    } catch (std::exception const& e) {
        std::cerr << "Client threw error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Client threw unexpected error." << std::endl;
    }
    return ssValue;
}