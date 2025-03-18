/////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/xmlrpc_client.cpp 2025-02-24 03:56    //
// Derived from xmlrpc-c/examples/cpp/xmlrpc_sample_add_client.cpp //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////
#include "mwfw2.h"
#include "iHex.h"

using namespace std;

/**
 * @brief A global string variable used to store the return code
 *        result from an XML-RPC call in the `vpa_call` function.
 */
std::string ssValueRetcode;

const char * vpad_req_names[] = {
    "VERSION",
    "AUTH",
    "PARMS",
    "STATUS",
    "TERM"
};

const char * rpc_type_names[] = {
    "NONE",
    "INT",
    "STRING",
    "FLOAT",
    "BOOL"
};

const char * rest_req_names[] = {
    "GET",
    "HEAD",
    "OPTIONS",
    "PUT",
    "DELETE",
    "POST"
};

std::string vpa_call(vpa_request_t& req) {

    char szLog[256];
    sprintf(szLog,
    "Client RPC: Addr= %s P1=%s,P2=%d,P3Type=%s,"
          " P3=%s,P4Type=%s,P4=%s,ssAuth=%s",
            req.szRemoteHost,
            vpad_req_names[req.eReqFunc],
            req.iParm2,
            rpc_type_names[req.eParm3Type],
            req.szParm3,
            rpc_type_names[req.eParm4Type],
            req.szParm4,
            req.szAuth);
    gpSysLog->loginfo(szLog);

    // s/b like "http://127.0.0.1:5164/RPC2"
    char szPort[16];
    sprintf(szPort,"%d",VPA_PORT);
    std::string ssUrl;
    ssUrl.append(gpSh->m_pShMemng->szProtocol);
    //ssUrl.append(OCULAR_ADDR);
    ssUrl.append(gpSh->m_pShMemng->szRemoteAddr);
    ssUrl.append(":");
    ssUrl.append(szPort);
    ssUrl.append("/RPC2");

    try {
        string const serverUrl(ssUrl);
        string const methodName("diagnose");
        xmlrpc_c::clientSimple myClient;
        xmlrpc_c::value result;
        myClient.call(  serverUrl,
                        methodName,
                        "iiisiss",
                         &result,
                         req.eReqFunc,      // integer (enum)
                         req.iParm2,        // integer
                         req.eParm3Type,    // integer (enum)
                         req.szParm3,       // string
                         req.eParm4Type,    // integer (enum)
                         req.szParm4,       // string
                         req.szAuth);       // string

        ssValueRetcode = xmlrpc_c::value_string(result);

    } catch (exception const& e) {
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        cerr << "Client threw unexpected error." << endl;
    }

    return ssValueRetcode;
}

/**
 * @brief The main function for executing the program.
 *
 * This function initializes the application, verifies that no command-line arguments are passed,
 * and performs operations to interact with a remote VPA (Virtual Process Automation) system.
 * It makes two remote procedure calls (RPCs):
 *
 * 1. Requests an authentication token using a private shared key.
 * 2. Requests the remote system version using the acquired authentication token.
 *
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return Returns 0 upon successful execution.
 */

int
main(int argc, char **) {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);
    here;
    if (argc-1 > 0) {
        cerr << "This program has no arguments" << endl;
        exit(1);
    }

    // std::string buffer =
    //     gpHex->structure_to_intel_hex(gpSh->m_pShMemng,
    //         gpSh->m_pShMemng->stShMemSize,0);

    // Set this to the desired remote VPA system
    strcpy(gpSh->m_pShMemng->szRemoteAddr,"192.168.4.17");
    strcpy(gpSh->m_pShMemng->szRemoteHost,"daphne.goodall.com");

//    strcpy(gpSh->m_pShMemng->szRemoteAddr,"192.168.4.223");

    std::cout << "Remote Addr is:       " << gpSh->m_pShMemng->szRemoteAddr
              << std::endl;

    /**
     * Call the remote system and request auth token using Private Shared Key
     */
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

    /**
     * Call the remote system and request version using auth token
     */
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

    // /**
    //  * Call the remote system and request shm using auth token
    //  */
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


    return 0;
}
