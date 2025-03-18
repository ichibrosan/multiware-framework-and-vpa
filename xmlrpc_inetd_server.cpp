////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/xmlrpc_inetd_server.cpp 2025-03-08 19:26 //
// Derived from xmlrpc-c/examples/cpp/xmlrpc_sample_add_client.cpp    //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.      //
////////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.hpp */

#ifndef _WIN32
#  include <unistd.h>
#endif

#include "mwfw2.h"

using namespace std;
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

#include "diagnoseMethod.h"
#include "restMethod.h"

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
 * @param[in] argc Integer placeholder, not utilized in this implementation.
 * @param[in] argv char** Array of constant character pointers, not utilized
 *      in this implementation.
 *
 * @return Returns 0 on successful execution of the server.
 ***************************************************************************/
int
main(int           argc,
     char ** argv) {

    auto * pMwFw = new mwfw2(__FILE__,__FUNCTION__);
    pMwFw->sl_loginfo(__PRETTY_FUNCTION__);

    xmlrpc_c::registry myRegistry;

#include "diagnoseRegister.h"
#include "restRegister.h"

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