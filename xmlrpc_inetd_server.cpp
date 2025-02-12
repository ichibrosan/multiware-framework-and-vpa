/* A simple XML-RPC server that runs under Inetd.  I.e. it lets the invoking
   program handle all the connection switching and simply processes one
   RPC on the provided connection (Standard Input) and exits.

   A typical example of where this would be useful is with an Inetd
   "super server."

   xmlrpc_sample_add_server.cpp is a server that does the same thing,
   but you give it a TCP port number and it listens for TCP connections
   and processes RPCs ad infinitum.  xmlrpc_socket_server.c is halfway
   in between those -- you give it an already bound and listening
   socket, and it listens for TCP connections and processes RPCs ad
   infinitum.

   Here is an easy way to test this program:

     socketexec --accept --local_port=8080 --stdin -- ./xmlrpc_inetd_server

   Now run the client program 'xmlrpc_sample_add_client'.  Socketexec
   will accept the connection that the client program requests and pass it
   to this program on Standard Input.  This program will perform the RPC,
   respond to the client, then exit.
*/

#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.hpp */

#ifndef _WIN32
#  include <unistd.h>
#endif
#include <cassert>

using namespace std;

#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

#include "diagnoseMethod.h"

/**
 * Main function that initializes the XML-RPC server, sets up methods, and
 * starts server execution by processing HTTP POST requests from standard input.
 *
 * @param argc The number of command-line arguments passed to the program.
 *             This parameter is unused in this implementation.
 * @param argv An array of C-style strings representing the command-line
 *             arguments. This parameter is unused in this implementation.
 *
 * @return Returns an integer value where 0 indicates successful termination
 *         of the program.
 *
 * This function registers an XML-RPC method into the server registry:
 * "diagnose" for diagnostic purposes. It configures the Abyss-based
 * XML-RPC server and runs the server to process incoming requests.
 */
int
main(int           const, 
     const char ** const) {

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

/*
 * Here is the capture of the build info for this program, used to
 * configure CMakeLists.txt:

g++
    -c
    -I.
    -I/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/include
    -I/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/include
    xmlrpc_inetd_server.cpp

g++
-o xmlrpc_inetd_server xmlrpc_inetd_server.o
/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/src/cpp/libxmlrpc_server_abyss++.a
/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/src/cpp/libxmlrpc_server++.a
/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/lib/abyss++/libxmlrpc_abyss++.a
/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/src/libxmlrpc_server_abyss.a
/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/src/libxmlrpc_server.a
/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/lib/abyss/src/libxmlrpc_abyss.a
-lssl
-lcrypto
/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/src/cpp/libxmlrpc++.a
/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/lib/libutil++/libxmlrpc_util++.a
/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/src/libxmlrpc.a
/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/lib/expat/xmlparse/libxmlrpc_xmlparse.a
/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/lib/expat/xmltok/libxmlrpc_xmltok.a
/home/doug/proj/Dougs-Networking-Prerequisites/xmlrpc-c/lib/libutil/libxmlrpc_util.a -lpthread

 *
 */
