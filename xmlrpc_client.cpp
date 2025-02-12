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

/****************************************************************************
 * @brief The main entry point for the program.
 *
 * This function establishes a connection with an XML-RPC server
 * and invokes a remote method to compute the sum of two integers.
 * It also handles argument validation and error reporting. Note
 * that this program does not accept any command-line arguments,
 * and a message is displayed if arguments are provided.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments (unused in this function).
 * @return int Returns 0 on successful completion, or exits with
 *         an error status if invalid arguments are supplied or
 *         exceptions occur during execution.
 ***************************************************************************/

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
