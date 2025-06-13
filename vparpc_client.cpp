// vparpc_client.cpp

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

    pWin->set_title("Virtual Protocol Adapter RPC Client "
                      "Ver 5.5.10.2");
    pWin->add_row(  ssCopr);

    pWin->render();

    delete pWin;

    gpVpaRpc->request("daphne","http");


    return 0;
}