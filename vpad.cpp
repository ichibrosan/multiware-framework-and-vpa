////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/vpad.cpp 2025/02/21 20:28 dwg            //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.hpp */

#include "mwfw2.h"
#include "vpadDefs.h"
using namespace std;

#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

const char * vpad_req_names[] = {
    "VERSION",
    "AUTH",
    "PARMS",
    "STATUS",
    "TERM"
};

const char * vpad_type_names[] = {
    "NONE",
    "INT",
    "STRING",
    "FLOAT",
    "BOOL"
};

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
            xmlrpc_c::value *   const  retvalP) {
        
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
                break;
            default:
                *retvalP = xmlrpc_c::value_string("Unknown Request");
        }
    }
};


/**************************************************************************************
 * @brief Entry point of the vpad application.
 *
 * This function serves as the main entry point of the vpad application.
 * It creates an instance of the `mwfw2` class for system and process
 * initialization, prints a copyright message, and forks the process into
 * parent and child processes. Each process performs distinct operations:
 *
 * - The parent process:
 *   1. Initializes the logging system (`CLog`) and retrieves the process
 *      timestamp.
 *   2. Records process-specific information such as the process ID,
 *      compilation date, time, and uptime.
 *   3. Enters a loop to maintain the state of the `vpad` process,
 *      continuously updating its uptime until a termination signal is
 *      received.
 *
 * - The child process:
 *   1. Sets up an XML-RPC server using the `xmlrpc_c` library.
 *   2. Binds the "diagnose" RPC method to the server for XML-RPC
 *      communication.
 *   3. Starts the XML-RPC server on port 5164, allowing for XML-RPC calls.
 *
 * The primary functionality of the child process is to handle incoming
 * XML-RPC requests, while the parent process maintains the runtime state
 * of the application.
 *
 * @param argc The number of command-line arguments passed to the program.
 * @param argv An array of character pointers listing all command-line
 *              arguments.
 * @return Returns `EXIT_SUCCESS` (0) upon successful execution or an error
 * code in case of failure.
 **************************************************************************************/
int
main(int           const, 
     const char ** const) {
    mwfw2 * pMwfw = new mwfw2(__FILE__,__FUNCTION__);

    char szTimestamp[128];
    char szSine[128];

    printf("vpad Copyright (c) 2025 Douglas Wade Goodall. "
           "All Rights Reserved.\n");
    gpSh->m_pShMemng->vpad_parent_pid = getpid();
    pid_t pid = fork();
    if(pid != FORK_CHILD) {

        sprintf(szSine,"%s::%s::Parent PID: %d\n",
            __FILE__,__FUNCTION__,getpid());
        gpSysLog->loginfo(szSine);

        gpLog       = new CLog(__FILE__, __FUNCTION__);
        gpLog->getTimeDateStamp(szTimestamp);
        gpSh->m_pShMemng->vpad_parent_pid = getpid();
        //std::cout << "From Vpad: " << getpid() << std::endl;
        strcpy(gpSh->m_pShMemng->szVpad_date,__DATE__);
        strcpy(gpSh->m_pShMemng->szVpad_time,__TIME__);
        strcpy(gpSh->m_pShMemng->sz_vpad_start_time,szTimestamp);
        gpSh->m_pShMemng->vpad_running = true;
        while (gpSh->m_pShMemng->vpad_running) {
            gpSh->m_pShMemng->vpad_uptime_seconds++;
            sleep(1);
        }

        return EXIT_SUCCESS;
    } else {

        sprintf(szSine,"%s::%s::Child  PID: %d\n",
            __FILE__,__FUNCTION__,getpid());
        gpSysLog->loginfo(szSine);

        gpSh->m_pShMemng->vpad_child_pid = getpid();
        try {
            xmlrpc_c::registry myRegistry;
            xmlrpc_c::methodPtr const diagnoseMethodP(new diagnoseMethod);
            myRegistry.addMethod("diagnose", diagnoseMethodP);
            xmlrpc_c::serverAbyss myAbyssServer(
                xmlrpc_c::serverAbyss::constrOpt()
                .registryP(&myRegistry)
                .portNumber(5164));
            myAbyssServer.run();
            assert(false);
        } catch (exception const& e) {
            cerr << "Something failed.  " << e.what() << endl;
        }
        return 0;
    }
}