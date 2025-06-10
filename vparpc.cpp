//////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/vparpc.cpp 2025/01/17 - dwg //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.       //
//////////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

#include "vparpc.h"

#include <netdb.h>
#include <arpa/inet.h>

vparpc::vparpc() {

}

int vparpc::vparpc_open(std::string ssVpaSrcAddr, std::string ssVpaSrcSvc,
                    std::string ssVpaDstAddr, std::string ssVpaDstSvc) {
    std::cout << "vparpc::vparpc()" << std::endl;
    return EXIT_SUCCESS;
}

int vparpc::svc2port(std::string ssSvcName) {
    struct servent *serviceEntry;
    
    // Look up the service by name for TCP protocol
    serviceEntry = getservbyname(ssSvcName.c_str(), "tcp");
    
    if (serviceEntry != nullptr) {
        // Convert network byte order to host byte order
        return ntohs(serviceEntry->s_port);
    }
    
    // If TCP lookup failed, try UDP
    serviceEntry = getservbyname(ssSvcName.c_str(), "udp");
    
    if (serviceEntry != nullptr) {
        // Convert network byte order to host byte order
        return ntohs(serviceEntry->s_port);
    }
    
    // Service not found
    return -1;
}