//////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/look.cpp 2025/07/05 05:45 dwg  //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved. //
//////////////////////////////////////////////////////////////
#include "mwfw2.h"

/**************************************************************
 * Display Retro Header Information IBM 5150 Monochrome style *
 **************************************************************/
void sine()
{
    auto * pWin = new window();
    gpSemiGr->cosmetics(
        SRUL,  SRUR,  SRLL,    // Corner characters: ┌ ┐ └ ┘
        SRLR,  SVSR,  SVSL,    // Right corner and separators
        SH,    SV);             // Horizontal ─ and vertical │ lines
    char szVersion[64];
    sprintf(szVersion,"Virtual Protocol Adapter Look Utility "
                            "Ver %d.%d.%d.%d",RMAJ,RMIN,RREV,RBLD);
    pWin->set_title(szVersion);
    std::string ssCopr = "  Copyright ";
    ssCopr.append("(c)");  // Append copyright symbol for compatibility
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");
    pWin->add_row(ssCopr);
    pWin->render();
}

/****************************************
 * Display Some Shared Memory Variables *
 ****************************************/
void shmvars()
{
    shared::SharedMemoryManager manager;
    manager.lockSharedMemory();
    gpSh->m_pShMemng->iSignature++;
    manager.releaseSharedMemory();

    gpShMemMgr->lockSharedMemory();
    gpSh->m_pShMemng->iSignature++;
    gpShMemMgr->releaseSharedMemory();

    printf("num_tests_processed is %d\n",
           gpSh->m_pShMemng->num_tests_processed);
    printf("num_tests_skipped is %d\n",
            gpSh->m_pShMemng->num_tests_skipped);
    printf("num_tests_passed is %d\n",
            gpSh->m_pShMemng->num_tests_passed);
    printf("num_tests_failed is %d\n\n",
            gpSh->m_pShMemng->num_tests_failed);
    gpSh->m_pShMemng->num_tests_processed = 0;
    int iNumTests = 7;
    printf("tests_processed_bits are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_processed_bits,iNumTests);
    printf("\ntests_passed_bits    are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_passed_bits,iNumTests);
    printf("\ntests_failed_bits    are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_failed_bits,iNumTests);
    printf("\ntests_skipped_bits   are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_skipped_bits,iNumTests);
}

void auth_users()
{
    printf("Credentials of Authenticated Users:");
    for (int iRow=3;iRow<CFG_MAX_USERS+ROW_DATA;iRow++) {
        if (0 < gpSh->m_pShMemng->creds[iRow].iAuthHandle) {
            printf("\n-------------------------------------------\n");
            printf(    "szAuthUserName  is %s\n",
                gpSh->m_pShMemng->creds[iRow].szAuthUserName);
            printf(    "szAuthFirstname is %s\n",
                gpSh->m_pShMemng->creds[iRow].szAuthFirstName);
            printf(    "szAuthLastName  is %s\n",
                gpSh->m_pShMemng->creds[iRow].szAuthLastName);
            printf(    "szAuthUUID      is %s\n",
                gpSh->m_pShMemng->creds[iRow].szAuthUUID);
            printf(    "iAuthHandle     is %d\n",
                gpSh->m_pShMemng->creds[iRow].iAuthHandle);
            printf(    "iHttpUserAgent  is %s\n",
         gpSh->m_pShMemng->creds[iRow].szHttpUserAgent);
        }
    }
}

int main() {
    auto * pMwFw = new mwfw2(__FILE__,__FUNCTION__);
    sine();
    //shmvars();
    auth_users();
    return EXIT_SUCCESS;
}
