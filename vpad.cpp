////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/vpad.cpp 2025/01/11 05:21 //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.               //
////////////////////////////////////////////////////////////////////////////

#include "vpad.h"

int main() {

    printf("vpad Copyright (c) 2025 Douglas Wade Goodall. "
           "All Rights Reserved.\n");
    gpLog       = new CLog(__FILE__, __FUNCTION__);
    gpSh        = new shared();
    gpEnv       = new environment();
    gpOS        = new osIface();
    gpSh->m_pShMemng->vpad_pid = getpid();
    //std::cout << "From Vpad: " << getpid() << std::endl;
    strcpy(gpSh->m_pShMemng->szVpad_date,__DATE__);
    strcpy(gpSh->m_pShMemng->szVpad_time,__TIME__);

    gpSh->m_pShMemng->vpad_running = true;

    while (gpSh->m_pShMemng->vpad_running) {
         sleep(1);
    }

    return 0;
}
