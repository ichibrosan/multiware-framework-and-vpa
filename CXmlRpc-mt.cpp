// CXmlRpc.cpp 2020/06/10 dwg -
// Copyright (c) 2020 RMD Systems
// Written by Douglas Goodall

#include "gecore.hpp"

extern CModel      * g_pModel;
extern CView       * g_pView;
extern CController * g_pController;

////////////////////////////////////////////////////
// This is a raw class definition for the RPC system
#include "diagnoseMethod.hpp"
////////////////////////////////////////////////////


/////////////////////////////////////////////////////
CXmlRpc::CXmlRpc(int portNumber)
{
    g_pLog->write("CXmlRpc::CXmlRpc() called");
    m_iPortNumber = portNumber;

#ifdef DEBUG
    printf("\nListner Created\n");
#endif // DEBUG

    pid_t pid = fork();
    if(0<pid) {
        // This return is for the parent thread
        //printf("CXmlRpc parent thread returning\n");
        return;
    }
    else {
        run();
    }
}


///////////////////////////////////////////////////////////////
// This member function run's in a separate thread that exists
// too support the XMLRPC interface, which waits in a blocking
// mode for requests from a peer TCP client. When this function
// is done, the thread should be terminated.
///////////////////////////////////////////////////////////////
int
CXmlRpc::run()
{
    char szTemp[128];
    g_pLog->write("CXmlRpc::run() called");

#ifdef DEBUG
    printf("CXmlRpc::run() called\n");
#endif // DEBUG

    try {
        xmlrpc_c::registry myRegistry;

        xmlrpc_c::methodPtr const
            diagnoseMethodP(new diagnoseMethod);

        myRegistry.addMethod("gecore.diagnose",
                diagnoseMethodP);

        xmlrpc_c::serverAbyss myAbyssServer(
                xmlrpc_c::serverAbyss::constrOpt()
                        .registryP(&myRegistry)
                        .portNumber(m_iPortNumber));

        myAbyssServer.run();
        assert(false);
    } catch (exception const& e) {
        sprintf(szTemp,"WARNING!! CXmlRpc::run() "
                       "Something failed, %s\n",e.what());
        g_pLog->write(szTemp);
        g_pLog->write("WARNING!! CXmlRpc::run() "
                      "returning Failure");

        return EXIT_FAILURE;
    }

#ifdef DEBUG
    printf("CXmlRpc::run() returning EXIT_SUCCESS\n");
#endif // DEBUG

    g_pLog->write("WARNING!! CXmlRpc::run() returning Success");
    return EXIT_SUCCESS;
}
//////////////////////////////////////////////////////


///////////////////
CXmlRpc::~CXmlRpc()
{
    g_pLog->write("CXmlRpc::~CXmlRpc() called");

}
///////////////////
