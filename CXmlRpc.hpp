////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/CXmlRpc.hpp  2025/02/20                  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_CXMLRPC_H
#define MULTIWARE_CXMLRPC_H

enum RPC_FUNC_TAG {
    RPC_VERSION,        // 0
    RPC_FUNCTIONS       // 1
};

class CXmlRpc {
    char m_szInetBuff[16384];
public:
    CXmlRpc(const char *);
    int getServiceByName(const char *);
    void updateWebCode();
};

extern const char * rpcFuncNames[];

#endif // MULTIWARE_CXMLRPC_H

///////////////////////
// eof - CXmlRpc.hpp //
///////////////////////
