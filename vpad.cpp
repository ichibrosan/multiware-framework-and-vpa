////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/vpad.cpp 2025/01/11 05:21 //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.               //
////////////////////////////////////////////////////////////////////////////

#include "vpad.h"

/**
 * Main function for the vpad application, responsible for initializing system components,
 * configuring shared memory, and maintaining application runtime operations.
 *
 * @return Returns 0 upon successful execution.
 */
int main() {
    char szTimestamp[128];

    printf("vpad Copyright (c) 2025 Douglas Wade Goodall. "
           "All Rights Reserved.\n");
    gpLog       = new CLog(__FILE__, __FUNCTION__);
    gpLog->getTimeDateStamp(szTimestamp);
    gpSh        = new shared();
    gpEnv       = new environment();
    gpOS        = new osIface();
    gpSh->m_pShMemng->vpad_pid = getpid();
    //std::cout << "From Vpad: " << getpid() << std::endl;
    strcpy(gpSh->m_pShMemng->szVpad_date,__DATE__);
    strcpy(gpSh->m_pShMemng->szVpad_time,__TIME__);
    strcpy(gpSh->m_pShMemng->sz_vpad_start_time,szTimestamp);
    gpSh->m_pShMemng->vpad_running = true;

    while (gpSh->m_pShMemng->vpad_running) {
         gpSh->m_pShMemng->vpad_uptime_seconds++;
         sleep(1);
    }

    return 0;
}
