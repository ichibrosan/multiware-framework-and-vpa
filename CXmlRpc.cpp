////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/CXmlRpc.cpp  2025/02/20                  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#include "std.h"
#include "CXmlRpc.hpp"

/////////////////////////////////////////////////////
// These is a raw class definition for the RPC system
#include "diagnoseMethod.hpp"
#ifdef SUPPORT_ADV_DIAGNOSE
//#include "advDiagnoseMethod.hpp"
#endif // SUPPORT_ADV_DIAGNOSE
/////////////////////////////////////////////////////

const char * rpcFuncNames [RPC_FUNCTIONS]  = {
    "RPC_VERSION"
  };


int
CXmlRpc::getServiceByName(const char *pszService)
{
    int port;

    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_canonname = nullptr;
    hints.ai_addr = nullptr;
    hints.ai_next = nullptr;
    getaddrinfo((const char *)nullptr,
                pszService,&hints,&result);
    while(NULL != result)
    {

        unsigned char *p;
        p = (unsigned char *)result->ai_addr;

        p = (unsigned char *)result->ai_addr;
        p += 2;
        int lsb = *p++;
        int msb = *p;
        port = htons((msb<<8)+lsb);
        result = result->ai_next;
    }

    return port;
}



///////////////////////////////////////////////////////////
// The purpose of this function is to export constants
// from the C++ application to a module that ca be imported
// in the Python code of the GUI.
///////////////////////////////////////////////////////////
// 2020/07/09 dwg - added RPC_VIEW_GSM
void
CXmlRpc::updateWebCode()
{

    /***********************************************************
     * 2021/12/07 dwg - added current timestamp to automatically
     * generated vehicle.py so we can assure it is being updated
     * appropriately. The question arose when I wasn't sure where
     * I wanted  web-iface/cgi-bin & html.
     */
    char szTimestamp[48];
    g_pAppLog->getTimeDateStamp(szTimestamp);

    FILE * fd = fopen("/usr/lib/cgi-bin/vehicle.py","w");
    fprintf(fd,"# /usr/lib/cgi-bin/vehicle.py  \n");
    fprintf(fd,"# Automatically generated %s\n",szTimestamp);

    /////////////////////////////////////////////////////
    // These RPC_ declarations come from the CXmlRpc.hpp
    fprintf(fd,"RPC_VERSION = %d\n",RPC_VERSION);
    fprintf(fd,"####################\n");
    fprintf(fd,"# eof - vehicle.py #\n");
    fprintf(fd,"####################\n");
    fclose(fd);
}


///////////////////////////////////////////////////////////////
// This member function run's in a separate thread that exists
// too support the XMLRPC interface, which waits in a blocking
// mode for requests from a peer TCP client. When this function
// is done, the thread should be terminated.
///////////////////////////////////////////////////////////////
CXmlRpc::CXmlRpc(const char *pszServiceName)
{
    char szTemp[128];
    int portNumber = CXmlRpc::getServiceByName(
            (const char *)pszServiceName);
    //updateWebCode();
    try {
        xmlrpc_c::registry myRegistry;

        xmlrpc_c::methodPtr const diagnoseMethodP(new diagnoseMethod);
        myRegistry.addMethod("gecore.diagnose",diagnoseMethodP);

//        xmlrpc_c::methodPtr const advDiagnoseMethodP(new advDiagnoseMethod);
//        myRegistry.addMethod("gecore.advDiagnose",advDiagnoseMethodP);

        xmlrpc_c::serverAbyss myAbyssServer(
                xmlrpc_c::serverAbyss::constrOpt()
                        .registryP(&myRegistry)
                        .portNumber(portNumber));
        myAbyssServer.run();
    } catch (exception const& e) {
        sprintf(szTemp,"WARNING!! CXmlRpc::run() "
                       "Failure, %s\n",e.what());
        printf("%s",szTemp);
    }
}


///////////////////////
// eof - CXmlRpc.cpp //
///////////////////////
