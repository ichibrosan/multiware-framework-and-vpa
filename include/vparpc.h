////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/vparpc.h 2025/06/10 - dwg //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.     //
////////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"

#ifndef VPARPC_H
#define VPARPC_H

enum vparpc_func_t {
    VPARPC_FUNC_NONE = 0,
    VPARPC_FUNC_VERSION,
    VPARPC_FUNC_COUNT
};


/*
 * See doc/UDP-packet-size-considerations-AI.txt
 */

#define VPARPC_MAX_PAYLOAD_SIZE 512

struct vparpc_request_none_t {
    vparpc_func_t eFunc;
    char8_t       szUUID[UUID_SIZE];    // 36+1
};

struct vparpc_request_version_t {
    vparpc_func_t eFunc;
    char8_t       szUUID[UUID_SIZE];    // 36+1
};

union vparpc_request_t {
    struct vparpc_request_none_t    req_none;
    struct vparpc_request_version_t req_version;
};


class vparpc {
    window * v_pWin;
    std::string v_ssVpaSrcAddr;
    std::string v_ssVpaSrcPort;
    std::string v_ssVpaDestAddr;
    std::string v_ssVpaDestPort;
    int v_nListenSocket;  // Socket descriptor for receiving packets
    int v_nSendSocket;    // Socket descriptor for sending packets
public:

    vparpc();

    void server(std::string ssService);

    void request(std::string ssHostName,std::string ssServiceName);
    void response(std::string ssServiceName);

    // int vparpc_open( std::string ssVpaSrcAddr, std::string ssVpaSrcSvc,
    //              std::string ssVpaDstAddr, std::string ssVpaDstSvc);
    //
    // int vparpc_open_receiver();
    //
    // int vparpc_open_sender();
    //
    // int vparpc_send_packet(const void* data, size_t data_len);
    //
    // int vparpc_receive_packet(
    //     void* buffer, size_t buffer_len,
    //     std::string* sender_addr = nullptr,
    //     int* sender_port = nullptr);

    int svc2port(std::string ssSvcName);

    std::string host2ipv4addr(const std::string& ssHost);
    void render();


};



#endif //VPARPC_H