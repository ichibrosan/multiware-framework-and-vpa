////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/vpad.cpp 2025/02/21 20:28 dwg            //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.hpp */

#include "mwfw2.h"
#include "vpadDefs.h"
using namespace std;
#include "stylist.h"
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

#include "diagnoseMethod.h"

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
main(int argc,char ** argv) {
    auto * pMwfw = new mwfw2(__FILE__,__FUNCTION__);
    char szTimestamp[128];
    char szSine[128];

    printf("vpad Copyright (c) 2025 "
            "Douglas Wade Goodall. "
            "All Rights Reserved.\n");

    stylist * pStylist = new stylist();

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
            return EXIT_FAILURE;
        }
    }
}