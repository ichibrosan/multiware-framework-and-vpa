////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/vparpc.h 2025/06/10 - dwg //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.     //
////////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"

#ifndef VPARPC_H
#define VPARPC_H



class vparpc {
    std::string v_ssVpaSrcAddr;
    std::string v_ssVpaSrcPort;
    std::string v_ssVpaDestAddr;
    std::string v_ssVpaDestPort;
public:
    vparpc();
    int vparpc_open( std::string ssVpaSrcAddr, std::string ssVpaSrcSvc,
                 std::string ssVpaDstAddr, std::string ssVpaDstSvc);
    int svc2port(std::string ssSvcName);
};



#endif //VPARPC_H
