////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/xmlrpc_inetd_server.cpp 2025-03-08 18:32 //
// Derived from xmlrpc-c/examples/cpp/xmlrpc_sample_add_client.cpp    //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.      //
////////////////////////////////////////////////////////////////////////


#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.hpp */

#ifndef _WIN32
#  include <unistd.h>
#endif
#include <cassert>

#include "mwfw2.h"
#include "vpadDefs.h"

using namespace std;
#include "stylist.h"
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

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
const char * vpad_req_names[] = {
    "VERSION",
    "AUTH",
    "PARMS",
    "STATUS",
    "TERM"
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
const char * vpad_type_names[] = {
    "NONE",
    "INT",
    "STRING",
    "FLOAT",
    "BOOL"
};

#include "diagnoseMethod.h"

/****************************************************************************
 * Main function, serves as the entry point of the xmlrpc_inetd_server
 * application.
 *
 * This function initializes necessary system components, sets up an XML-RPC
 * server, and begins processing incoming requests. A `diagnoseMethod`
 * instance is registered to the XML-RPC registry, allowing the server to
 * handle requests for the "diagnose" method.
 *
 * - Creates and initializes an instance of `mwfw2` for environment setup
 *      and logging.
 * - Registers a custom XML-RPC method, `diagnoseMethod`, to the
 *      `xmlrpc_c::registry`.
 * - Configures and starts an XML-RPC Abyss server using
 *      `xmlrpc_c::serverAbyss`.
 * - Listens for incoming HTTP POST requests from the standard input (STDIN).
 *
 * @param[in] const Integer placeholder, not utilized in this implementation.
 * @param[in] const char** Array of constant character pointers, not utilized
 *      in this implementation.
 *
 * @return Returns 0 on successful execution of the server.
 ***************************************************************************/
int
main(int           const, 
     const char ** const) {

    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    xmlrpc_c::registry myRegistry;

    xmlrpc_c::methodPtr const diagnoseMethodP(new diagnoseMethod);

    myRegistry.addMethod("diagnose", diagnoseMethodP);

    xmlrpc_c::serverAbyss myAbyssServer(
         xmlrpc_c::serverAbyss::constrOpt()
         .registryP(&myRegistry));

    myAbyssServer.runConn(STDIN_FILENO);
        /* This reads the HTTP POST request from Standard Input and
           executes the indicated RPC.
        */
    return 0;
}

///////////////////////////////////
// eof - xmlrpc_inetd_server.cpp //
///////////////////////////////////