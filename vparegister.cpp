//
// Created by doug on 5/6/25.
//

#include "mwfw2.h"

class vparegister {
    public:
        vparegister();
    private:
};

vparegister::vparegister() {

}

int main() {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);
    gpCrt->crtclr();
    window * pWin = new window();

    // WORKING DOUBLE SQUARE PREFERENCES
    // gpSemiGr->cosmetics(DSUL,   DSUR,  DSLL,
    //                     DSLR,DVSR,DVSL,
    //                     DH,  DV);

    // gpSemiGr->cosmetics(SSUL,SSUR,SSLL,SSLR,SH,SV);

    // WORKING SINGLE ROUNDED PREFERENCES
    gpSemiGr->cosmetics( SRUL,  SRUR,  SRLL,
                        SRLR,SVSR,SVSL,
                        SH,  SV);

    std::string ssCopr = "Copyright ";
    ssCopr.append("(c)");
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");

    pWin->set_title("Virtual Protocol Adapter Registration Utility    Ver 5.5.10.2");
    pWin->add_row(  ssCopr);
    pWin->add_row(  "License:      7d8f673a-2d7d-11f0-b5c9-173231e8c8c1  5/10/2025");
    pWin->render();
    pWin->show();
    return 0;

}