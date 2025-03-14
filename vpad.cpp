////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/vpad.cpp 2025/03/14 12:21 dwg            //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
// 2025-03-14 12:22 dwg - #include Method/Register components         //
////////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.hpp */

#include "mwfw2.h"
using namespace std;
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

#include "diagnoseMethod.h"

/**
 * Entry point of the application.
 *
 * This function initializes essential components, logs initial system state,
 * and manages process forking to establish a parent and child process.
 * The parent process updates uptime information and runtime metadata,
 * while the child process sets up an XML-RPC server for remote procedure
 * call handling.
 *
 * @param argc The number of command-line arguments passed.
 * @param argv Array of command-line arguments.
 * @return An integer status code. Returns 0 (EXIT_SUCCESS) if the program
 * completes successfully in the parent process. The child process may \
 * return different codes based on server operation.
 */
int
main(int argc,char ** argv) {
    auto * pMwfw = new mwfw2(__FILE__,__FUNCTION__);
    pMwfw->sl_loginfo(__PRETTY_FUNCTION__);

    char szTimestamp[128];
    char szSine[128];

    printf("vpad Copyright (c) 2025 "
            "Douglas Wade Goodall. "
            "All Rights Reserved.\n");

    gpSh->m_pShMemng->vpad_parent_pid = getpid();
    pid_t pid = fork();
    if(pid != FORK_CHILD) {

        sprintf(szSine,"%s::%s::Parent PID: %d\n",
            __FILE__,__FUNCTION__,getpid());
        gpSysLog->loginfo(szSine);

        gpLog = new CLog(__FILE__, __FUNCTION__);
        gpLog->getTimeDateStamp(szTimestamp);
        gpSh->m_pShMemng->vpad_parent_pid = getpid();
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

#include "diagnoseRegister.h"

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

////////////////////
// eof - vpad.cpp //
////////////////////