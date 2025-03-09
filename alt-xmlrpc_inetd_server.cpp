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
#include "mwfw2.h"
#include "vpadDefs.h"
using namespace std;

#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

// class sampleAddMethod : public xmlrpc_c::method {
// public:
//     sampleAddMethod() {
//         // signature and help strings are documentation -- the client
//         // can query this information with a system.methodSignature and
//         // system.methodHelp RPC.
//         this->_signature = "i:ii";  // method's arguments are two integers
//         this->_help = "This method adds two integers together";
//     }
//     void
//     execute(xmlrpc_c::paramList const& paramList,
//             xmlrpc_c::value *   const  retvalP) {
//
//         int const addend(paramList.getInt(0));
//         int const adder(paramList.getInt(1));
//
//         paramList.verifyEnd(2);
//
//         *retvalP = xmlrpc_c::value_int(addend + adder);
//     }
// };

/********************************************************************************
 * @class diagnoseMethod
 * @brief Custom implementation of an XML-RPC method for adding two integers.
 *
 * This class inherits from the xmlrpc_c::method class and implements an XML-RPC
 * method that adds two integers and returns the result. It provides a brief
 * description of the functionality and the expected parameter and return types
 * so that it can be queried via system.methodSignature and system.methodHelp.
 ********************************************************************************/
class diagnoseMethod : public xmlrpc_c::method {
    /**
     * @brief Constructor for the diagnoseMethod class.
     *
     * This method sets up the RPC method by defining its signature and help description.
     * The signature "i:ii" indicates that the method returns an integer and accepts
     * two integer arguments. The help string provides information about the functionality
     * of the method.
     *
     * @details
     * The diagnoseMethod is designed to add two integers together. The signature and help
     * strings can be queried using system.methodSignature and system.methodHelp RPC calls,
     * enabling clients to retrieve metadata about the method.
     */
public:
    diagnoseMethod() {
        // signature and help strings are documentation -- the client
        // can query this information with a system.methodSignature and
        // system.methodHelp RPC.
        this->_signature = "s:iiisiss";
            // method's result and two arguments are integers
        this->_help = "This method adds two integers together";
    }

    /************************************************************************
     * @brief Executes the method logic for adding two integers.
     *
     * This function retrieves two integer parameters from the paramList,
     * verifies that no additional parameters are supplied, and then computes
     * the sum of the two integers. The result is stored in the provided
     * xmlrpc_c::value pointer.
     *
     * @param paramList The parameter list containing the input arguments.
     *                  It expects exactly two integers.
     * @param retvalP A pointer to an xmlrpc_c::value object where the result
     *                of the addition will be stored.
     *
     * @note If the second integer parameter is 1, the method execution will
     *       be artificially delayed by 2 seconds to simulate a long-running
     *       operation.
     ************************************************************************/
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) override {

        int const iParm1(paramList.getInt(0));
        int const iParm2(paramList.getInt(1));
        int const iParm3Type(paramList.getInt(2));
        std::string ssParm3(paramList.getString(3));
        int const iParm4Type(paramList.getInt(4));
        std::string ssParm4(paramList.getString(5));
        std::string ssAuth(paramList.getString(6));
        paramList.verifyEnd(7);
        char szPayload[FILENAME_MAX];

        sprintf(szPayload,
            "RPC: P1=%s,P2=%d,P3Type=%s,"
                  "P3=%s,P4Type=%s,P4=%s,ssAuth=%s",
            vpad_req_names[iParm1],iParm2,
            vpad_type_names[iParm3Type],ssParm3.c_str(),
            vpad_type_names[iParm4Type],ssParm4.c_str(),ssAuth.c_str());
        gpSysLog->loginfo(szPayload);
        switch (iParm1) {
            case VPAD_REQ_VERSION:
                if (0 == strcmp(ssAuth.c_str(),gpSh->m_pShMemng->szRpcUuid)) {
                   *retvalP = xmlrpc_c::value_string(RVERSION_STRING_LONG);
                } else {
                    sleep(10); // make them pay a time penalty to obviate attacks
                   *retvalP = xmlrpc_c::value_string("Synchronization Error!!");
                }
                break;
            case VPAD_REQ_AUTH:
                if (0 == strcmp(ssAuth.c_str(),VPA_RPC_PSK)) {
                    *retvalP = xmlrpc_c::value_string(gpSh->m_pShMemng->szRpcUuid);
                } else {
                    sleep(10); // make them pay a time penalty to obviate attacks
                    *retvalP = xmlrpc_c::value_string("Synchronization Error!!");
                }
                break;
            case VPAD_REQ_PARMS:
                if (0 == strcmp(ssAuth.c_str(),gpSh->m_pShMemng->szRpcUuid)) {
                    *retvalP = xmlrpc_c::value_string(szPayload);
                } else {
                    sleep(10); // make them pay a time penalty to obviate attacks
                    *retvalP = xmlrpc_c::value_string("Synchronization Error!!");
                }
                break;
            case VPAD_REQ_TERM:
                here;
                *retvalP = xmlrpc_c::value_string("VPAD Shutting Down!!");
                here;
                exit(EXIT_SUCCESS);
            default:
                *retvalP = xmlrpc_c::value_string("Unknown Request");
        }
    }
};


int 
main(int           const, 
     const char ** const) {

    xmlrpc_c::registry myRegistry;

    xmlrpc_c::methodPtr const sampleAddMethodP(new sampleAddMethod);

    myRegistry.addMethod("sample.add", sampleAddMethodP);

    xmlrpc_c::serverAbyss myAbyssServer(
         xmlrpc_c::serverAbyss::constrOpt()
         .registryP(&myRegistry));

    myAbyssServer.runConn(STDIN_FILENO);
        /* This reads the HTTP POST request from Standard Input and
           executes the indicated RPC.
        */
    return 0;
}
