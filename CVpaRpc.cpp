///////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/CVpaRpc.cpp 2025/07/02 - dwg //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.        //
///////////////////////////////////////////////////////////////////////////////


#include "include/CVpaRpc.h"

CVpaRpc::CVpaRpc()
{
    m_vparpc_request_auth.eVersion = VPARPC_VERSION_1;
    m_vparpc_request_auth.nSize = sizeof(m_vparpc_request_auth);
    m_vparpc_request_auth.eFunc = VPARPC_FUNC_GET_AUTH;
    strcpy((char *)m_vparpc_request_auth.szPSK,CFG_VPA_RPC_PSK);
    gpVpaRpc->client(
        "daphne",
        "vparpc",
        &m_vparpc_request_auth,sizeof(m_vparpc_request_auth) );
    //strcpy(m_szAuth,m_vparpc_request_auth.szAuth);

    std::cout << "auth: " << m_vparpc_request_auth.szAuth << std::endl;

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
        &m_vparpc_request_version,sizeof(m_vparpc_request_version) );

    std::cout << "version: " << m_vparpc_request_version.szVersion << std::endl;

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
    gpVpaRpc->client(
        "daphne",
        "vparpc",
        &m_vparpc_request_lookup,sizeof(m_vparpc_request_lookup) );

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
        &m_vparpc_request_creds,sizeof(m_vparpc_request_creds) );

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
