//
// Created by doug on 6/10/25.
//
#include "mwfw2.h"

int main(int argc,char **argv) {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    window * pWin = new window();

    gpSemiGr->cosmetics(
        SRUL,  SRUR,  SRLL,
        SRLR,SVSR,SVSL,
         SH,  SV);
    std::string ssCopr = "Copyright ";
    ssCopr.append("(c)");
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");

    pWin->set_title("Virtual Protocol Adapter RPC Server "
                      "Ver 5.5.10.2");
    pWin->add_row(  ssCopr);

    // std::cout << gpVpaRpc->svc2port("vpa") << std::endl;
    //
    // std::string ssIPv4Addr = gpVpaRpc->host2ipv4addr("daphne");
    // pWin->add_row(" Calling gpVpaRpc->vparpc_open()");
    //
    //
    // gpVpaRpc->vparpc_open(
    //     ssIPv4Addr,"vpa",
    //     ssIPv4Addr,"vpa");
    //
    // pWin->add_row(" Calling gpVpaRpc->vparpc_open_receiver()");
    // gpVpaRpc->vparpc_open_receiver();
    // pWin->add_row(" Calling gpVpaRpc->vparpc_open_sender()");
    // gpVpaRpc->vparpc_open_sender();
    //
    // // vparpc_request_t request;
    // // request.req_version.eFunc = VPARPC_FUNC_VERSION;
    // // uuid_t uuid;
    // // uuid_generate(uuid);
    // // uuid_unparse(uuid,(char *)request.req_version.szUUID);

    pWin->render();

    delete pWin;

    // std::string ssSenderAddr;
    // int iSenderPort;
    // char buffer[1024];
    //
    // gpVpaRpc->vparpc_receive_packet(
    //     buffer,sizeof(buffer),
    //     &ssSenderAddr,&iSenderPort);
    //
    // std::cout << "Received packet from " << ssSenderAddr << std::endl;
    // std::cout << "Packet length is " << iSenderPort << std::endl;
    // std::cout << "Packet contents are " << std::endl;
    // std::cout << buffer << std::endl;

    gpVpaRpc->server("vparpc");

    return 0;

}