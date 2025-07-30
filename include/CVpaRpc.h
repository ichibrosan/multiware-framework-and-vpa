////////////////////////////////////////////////////////////////////
// ~/public_html/fw/CVpaRpc.h 2025-07-16 08:08 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#pragma once

#include "mwfw2.h"

class CVpaRpc
{
    std::string m_ssSvr; // set by CVpaRpc::CVpaRpc()
    std::string m_ssSvc; // set by CVpaRpc::CVpaRpc()
public:
    CVpaRpc(std::string ssHost, std::string ssService);
    std::string get_auth();

    std::string get_version();
    std::string get_version_version();

    int get_lookup();

    void get_creds();
    std::string get_creds_username();
    std::string get_creds_firstname();
    std::string get_creds_lastname();
    std::string get_creds_auth();
    std::string get_creds_level();

    void get_urls();
    std::string get_urls_ip();
    std::string get_urls_cgiroot();
    std::string get_urls_stylesroot();

    vparpc_request_auth_t m_vparpc_request_auth;
    //    char                        m_szAuth[UUID_SIZE];
    vparpc_request_version_t m_vparpc_request_version;
    vparpc_request_lookup_t m_vparpc_request_lookup;
    vparpc_request_creds_t m_vparpc_request_creds;
    vparpc_request_urls_t m_vparpc_request_urls;
};

/////////////////////
// eof - CVpaRpc.h //
/////////////////////
