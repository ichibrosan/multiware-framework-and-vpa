/////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/xmlrpc_client.cpp 2025-02-09 04:27    //
// Derived from xmlrpc-c/examples/cpp/xmlrpc_sample_add_client.cpp //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////
#include "mwfw2.h"
#include "vpadDefs.h"

// #include <cstdlib>
// #include <string>
// #include <iostream>

using namespace std;

#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

std::string ssValueRetcode;

std::string vpa_call(vpa_request_t& req) {
    try {
        string const serverUrl("http://127.0.0.1:5164/RPC2");
        string const methodName("diagnose");
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

        ssValueRetcode = xmlrpc_c::value_string(result);
        } catch (exception const& e) {
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        cerr << "Client threw unexpected error." << endl;
    }
    return ssValueRetcode;
}

/**
 * @brief Main entry point for the application. This program makes a client
 *        call to a remote server using XML-RPC to invoke a method and fetches
 *        its result.
 *
 * @param argc The count of command-line arguments passed to the program.
 * @param argv Array of command-line arguments. In this program, command-line
 * arguments are not used.
 * @return int Returns 0 on successful execution, and exits with 1 if there
 *             are command-line arguments or an error occurs.
 */

int
main(int argc, char **) {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);
    here;
    if (argc-1 > 0) {
        cerr << "This program has no arguments" << endl;
        exit(1);
    }


    vpa_request_t req;
    strcpy(req.szRemoteHost,"127.0.0.1");
    req.eReqFunc = VPAD_REQ_VERSION;
    req.iParm2 = 0;
    req.eParm3Type = VPAD_TYPE_NONE;
    req.eParm4Type = VPAD_TYPE_NONE;
    strcpy(req.szAuth,gpSh->m_pShMemng->szRpcUuid);
    std::string ssReturn = vpa_call(req);
    std::cout << "Return value: " << ssReturn << std::endl;

    return 0;
}
