//
// Created by doug on 2/21/25.
//

#include "mwfw2.h"
#include "vpadDefs.h"

#include "rpcbind.h"

rpcbind::rpcbind() {

}

std::string ssValue;

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