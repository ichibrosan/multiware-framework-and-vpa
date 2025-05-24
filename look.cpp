//////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/look.cpp 2025/02/19 05:21      //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved. //
//////////////////////////////////////////////////////////////
#include "mwfw2.h"

/****************************************************************************
 * @brief Main function that initializes core components, logs system
 * information, and outputs processed statistical data and authenticated user
 * credentials.
 *
 * This function initializes the logging mechanism, shared memory, environment
 * services, and operating system interface modules. It retrieves and displays
 * statistics related to processed, passed, failed, and skipped tests along
 * with their respective binary representations. Additionally, it outputs the
 * details of authenticated users, including their usernames, names, UUIDs,
 * and handles.
 *
 * @return int Returns 0 upon successful execution.
 ****************************************************************************/
int main() {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    // shared::SharedMemoryManager manager;
    // manager.lockSharedMemory();
    // gpSh->m_pShMemng->iSignature++;
    // manager.releaseSharedMemory();

    gpShMemMgr->lockSharedMemory();
    gpSh->m_pShMemng->iSignature++;
    gpShMemMgr->releaseSharedMemory();

    printf("vpad Copyright (c) 2025 Douglas Wade Goodall. "
           "All Rights Reserved.\n");

    if (gpSh->m_pShMemng->iMwfwFeatures & (1<<FEATURE_CRTBIND)) {
        printf("Mwfw CRTBIND is enabled.\n");
    } else {
        printf("Mwfw CRTBIND is disabled.\n");
    }

    if (gpSh->m_pShMemng->iMwfwFeatures & (1<<FEATURE_CGICC)) {
        printf("Mwfw CGI/CC is enabled.\n");
    } else {
        printf("Mwfw CGI/CC is disabled.\n");
    }


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

    printf("\n\nCredentials of Authenticated Users:");
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
    return EXIT_SUCCESS;
}
