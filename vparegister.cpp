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
    window * pWin = new window();
    pWin->add_row(__PRETTY_FUNCTION__);
    gpSemiGr->cosmetics(DSUL,  DSUR,
                        DSLL,  DSLR,
                        DHL,DVL);
    pWin->render();
    return 0;

}