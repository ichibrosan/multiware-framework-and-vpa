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

std::string ssValue;

std::string vpa_call(vpa_request_t& req) {
    try {
        string const serverUrl("http://daphne:5164/RPC2");
        //string const methodName("sample.add");
        string const methodName("diagnose");

        xmlrpc_c::clientSimple myClient;
        xmlrpc_c::value result;
        here;
        myClient.call(  serverUrl,
                        methodName,
                        "iiisiss",
                         &result,
                         req.eReqFunc,
                         req.iParm2,
                         req.eParm3Type,req.szParm3,
                         req.eParm4Type,req.szParm4,
                         req.szAuth);
        here;

        //int const sum = xmlrpc_c::value_int(result);
        ssValue = xmlrpc_c::value_string(result);
        here;
        //cout << "Result of RPC (sum of 5 and 7): " << sum << endl;
        cout << "Result of diagnose: " << ssValue << endl;
        here;
    } catch (exception const& e) {
        here;
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        here;
        cerr << "Client threw unexpected error." << endl;
    }
    return ssValue;
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

    vpa_request_t req = { VPAD_REQ_PARMS,
                          0,
                          VPAD_TYPE_NONE,
                          "",
                          VPAD_TYPE_NONE,
                          "",
                          ""
    };
    strcpy(req.szAuth,gpSh->m_pShMemng->szRpcUuid);
    std::string ssValue = vpa_call(req);
    std::cout << "ssValue: " << ssValue << std::endl;
    return 0;
}
