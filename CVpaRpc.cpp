///////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/CVpaRpc.cpp 2025/07/02 - dwg //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.        //
///////////////////////////////////////////////////////////////////////////////


#include "include/CVpaRpc.h"

CVpaRpc::CVpaRpc(std::string ssHost,std::string ssService)
{
    m_vparpc_request_auth.eVersion = VPARPC_VERSION_1;
    m_vparpc_request_auth.nSize = sizeof(m_vparpc_request_auth);
    m_vparpc_request_auth.eFunc = VPARPC_FUNC_GET_AUTH;
    strcpy((char *)m_vparpc_request_auth.szPSK,CFG_VPA_RPC_PSK);
    gpVpaRpc->client(
        ssHost,           // daphne
        ssService,        // vparpc
        &m_vparpc_request_auth,sizeof(vparpc_request_auth_t) );  // Use struct size
    int x = 1;
}

std::string CVpaRpc::get_auth()
{
    std::string ssReturn = m_vparpc_request_auth.szAuth;
    return (ssReturn);
}

std::string CVpaRpc::get_version()
{
    m_vparpc_request_version.eVersion = VPARPC_VERSION_1;
    m_vparpc_request_version.nSize = sizeof(m_vparpc_request_version);
    m_vparpc_request_version.eFunc = VPARPC_FUNC_VERSION;
    strcpy((char *)m_vparpc_request_version.szAuth,m_vparpc_request_auth.szAuth);
    gpVpaRpc->client(
        "daphne",
        "vparpc",
        &m_vparpc_request_version,sizeof(vparpc_request_version_t) );  // Use struct size

    return(m_vparpc_request_version.szVersion);
}

int CVpaRpc::get_lookup()
{
    m_vparpc_request_lookup.eVersion = VPARPC_VERSION_1;
    m_vparpc_request_lookup.nSize = sizeof(m_vparpc_request_lookup);
    m_vparpc_request_lookup.eFunc = VPARPC_FUNC_LOOKUP;
    strcpy((char *)m_vparpc_request_lookup.szAuth,m_vparpc_request_auth.szAuth);
    strcpy(m_vparpc_request_lookup.szUsername,"doug");
    strcpy(m_vparpc_request_lookup.szPassword,"melange");
    
    // Initialize iHandle to a known value for debugging
    m_vparpc_request_lookup.iHandle = -999;
    
    // Log the request details
    char szLogger[128];
    sprintf(szLogger,"Sending lookup request - Username: %s, Password: %s, Initial Handle: %d",
                     m_vparpc_request_lookup.szUsername, 
                     m_vparpc_request_lookup.szPassword,
                     m_vparpc_request_lookup.iHandle);
    gpSysLog->loginfo(szLogger);

    gpVpaRpc->client(
        "daphne",
        "vparpc",
        &m_vparpc_request_lookup,
        sizeof(vparpc_request_lookup_t)
    );

    // Log the response
    sprintf(szLogger,"Received lookup response - Handle: %d, Status: %d",
                     m_vparpc_request_lookup.iHandle,
                     m_vparpc_request_lookup.eStatus);

    std::cout << "handle: " << m_vparpc_request_lookup.iHandle << std::endl;

    return(m_vparpc_request_lookup.iHandle);
}

void CVpaRpc::get_creds()
{
    m_vparpc_request_creds.eVersion = VPARPC_VERSION_1;
    m_vparpc_request_creds.nSize = sizeof(m_vparpc_request_creds);
    m_vparpc_request_creds.eFunc = VPARPC_FUNC_CREDS;
    strcpy((char *)m_vparpc_request_creds.szAuth,m_vparpc_request_auth.szAuth);
    m_vparpc_request_creds.iHandle = m_vparpc_request_lookup.iHandle;
    gpVpaRpc->client(
        "daphne",
        "vparpc",
        &m_vparpc_request_creds,sizeof(vparpc_request_creds_t) );  // Use struct size
}

std::string CVpaRpc::get_creds_username()
{
    std::string ssReturn = m_vparpc_request_creds.szAuthUserName;
    return (ssReturn);
}

std::string CVpaRpc::get_creds_firstname()
{
    std::string ssReturn = m_vparpc_request_creds.szAuthFirstName;
    return (ssReturn);
}

std::string CVpaRpc::get_creds_lastname()
{
    std::string ssReturn = m_vparpc_request_creds.szAuthLastName;
    return (ssReturn);
}

std::string CVpaRpc::get_creds_auth()
{
    std::string ssReturn = m_vparpc_request_creds.szAuthUUID;
    return (ssReturn);
}

std::string CVpaRpc::get_creds_level()
{
    std::string ssReturn = m_vparpc_request_creds.szAuthLevel;
    return (ssReturn);
}