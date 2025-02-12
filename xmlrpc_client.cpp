/////////////////////////////////////////////////////////////////////
// /home/doug/public_html/fw/xmlrpc_client.cpp 2025-02-09 04:27    //
// Derived from xmlrpc-c/examples/cpp/xmlrpc_sample_add_client.cpp //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

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

    if (argc-1 > 0) {
        cerr << "This program has no arguments" << endl;
        exit(1);
    }

    try {
        string const serverUrl("http://localhost:5164/RPC2");
        //string const methodName("sample.add");
        string const methodName("diagnose");

        xmlrpc_c::clientSimple myClient;
        xmlrpc_c::value result;
        
        myClient.call(serverUrl, methodName, "ii", &result, 5, 7);

        //int const sum = xmlrpc_c::value_int(result);
        std::string ssValue = xmlrpc_c::value_string(result);
            // Assume the method returned an integer; throws error if not

        //cout << "Result of RPC (sum of 5 and 7): " << sum << endl;
        cout << "Result of diagnose: " << ssValue << endl;

    } catch (exception const& e) {
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        cerr << "Client threw unexpected error." << endl;
    }

    return 0;
}
