//
// Created by doug on 3/23/25.
//

#include "std.h"
#include "include/diagnose.h"


const char * diagnose_req_names[] =
    { "NONE","VERSION", "AUTH", "PARMS", "STATUS", "TERM", "GETSHM" };

const char * diagnose_type_names[] =
    { "None","Int","String","Float","Bool" };

diagnose::diagnose(std::string ssNodeIP) {
    std::string ssValueRetcode;

    m_ssNodeIP = ssNodeIP;
    m_ssFormat = "iiisiss";
    m_ssMethod = "diagnose";
    sprintf(m_szPort,"%d",VPA_PORT);

    char szLog[256];
    sprintf(szLog,
    "vpa: Client RPC: Addr=%s Func=%s,P2=%s,P3Type=%s,"
          "P3=%s,P4Type=%s,P4=%s,Auth=%s",
            m_ssNodeIP.c_str(),
            diagnose_req_names[DIAGNOSE_REQ_AUTH],
            diagnose_req_names[DIAGNOSE_REQ_NONE],
            diagnose_type_names[DIAGNOSE_TYPE_NONE],"",
            diagnose_type_names[DIAGNOSE_TYPE_NONE],"",VPA_RPC_PSK);
    std::cout << szLog << std::endl;

    m_ssUrl = gpSh->m_pShMemng->szProtocol;
    m_ssUrl.append(gpSh->m_pShMemng->szIP);
    m_ssUrl.append(":");
    m_ssUrl.append(m_szPort);
    m_ssUrl.append("/RPC2");

    try {
        xmlrpc_c::clientSimple myClient;
        xmlrpc_c::value result;
        myClient.call(  m_ssUrl,
                        m_ssMethod,
                        m_ssFormat,
                        &result,
                         DIAGNOSE_REQ_AUTH, DIAGNOSE_REQ_NONE,
                         DIAGNOSE_TYPE_NONE,"",
                         DIAGNOSE_TYPE_NONE,"",
                         VPA_RPC_PSK);

        ssValueRetcode = xmlrpc_c::value_string(result);
        std::cout << "Auth Token: " << ssValueRetcode << std::endl;
        m_ssAuth = ssValueRetcode;
    } catch (std::exception const& e) {
        std::cerr << "Client threw error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Client threw unexpected error." << std::endl;
    }
}

std::string diagnose::call(diagnose_request_t request) {
    std::string ssValueRetcode;

    char szLog[256];
    sprintf(szLog,
    "vpa: Client RPC: Addr=%s Func=%s,P2=%d,P3Type=%s,"
          "P3=%s,P4Type=%s,P4=%s,Auth=%s",
            m_ssNodeIP.c_str(),
            diagnose_req_names[request.eReqFunc],  request.iParm2,
            diagnose_type_names[request.eParm3Type],request.szParm3,
            diagnose_type_names[request.eParm4Type],request.szParm4,
            m_ssAuth.c_str());

    try {
        xmlrpc_c::clientSimple myClient;
        xmlrpc_c::value result;
        myClient.call(  m_ssUrl,m_ssMethod,
                        m_ssFormat,
                        &result,
                         request.eReqFunc,  request.iParm2,
                         request.eParm3Type,request.szParm3,
                         request.eParm4Type,request.szParm4,
                         m_ssAuth.c_str());
        ssValueRetcode = xmlrpc_c::value_string(result);
    } catch (std::exception const& e) {
        std::cerr << "Client threw error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Client threw unexpected error." << std::endl;
    }
    return ssValueRetcode;
}