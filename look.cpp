////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/vpad.cpp 2025/01/11 05:21 //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.               //
////////////////////////////////////////////////////////////////////////////

#include "look.h"

struct MFW_SHMEMUSER_T {
    int  iSignature;
    char szAuthUserName[UT_NAMESIZE];
    char szAuthFirstName[UT_NAMESIZE];
    char szAuthLastName[UT_NAMESIZE];
    char szAuthUUID[UUID_SIZE];
    int  iAuthHandle;
};
struct MFW_SHMEMUSER_T * gpShUser = nullptr;

int main() {

    printf("vpad Copyright (c) 2025 Douglas Wade Goodall. "
           "All Rights Reserved.\n");
    gpLog    = new CLog(__FILE__, __FUNCTION__);
    gpSh     = new shared();
    gpEnv    = new environment();
    gpOS     = new osIface();

    printf("num_tests_processed is %d\n",
        gpSh->m_pShMemng->num_tests_processed);
    printf("num_tests_skipped is %d\n",
            gpSh->m_pShMemng->num_tests_skipped);
    printf("num_tests_passed is %d\n",
            gpSh->m_pShMemng->num_tests_passed);
    printf("num_tests_failed is %d\n\n",
            gpSh->m_pShMemng->num_tests_failed);

    printf("tests_processed_bits are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_processed_bits,NUM_TESTS);
    printf("\ntests_passed_bits    are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_passed_bits,NUM_TESTS);
    printf("\ntests_failed_bits    are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_failed_bits,NUM_TESTS);
    printf("\ntests_skipped_bits   are ");
    gpOS->printBinary(gpSh->m_pShMemng->tests_skipped_bits,NUM_TESTS);

    printf("\n\nCredentials of Authenticated Users:");
    for (int iRow=3;iRow<MAX_USERS+ROW_DATA;iRow++) {
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
    return 0;
}
