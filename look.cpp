//////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/look.cpp 2025/07/05 05:45 dwg  //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved. //
//////////////////////////////////////////////////////////////
#include "mwfw2.h"
#include "cfgini.h"

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

void configini()
{
    cfgini config("/home/doug/config.ini");

    // Create a new config or load existing
    if (!config.load()) {
        config.createNew();
    }

    // Add sections and variables
    config.addSection("Database");
    config.setVariable("Database", "host", "localhost");
    config.setVariable("Database", "port", "3306");
    config.setVariable("Database", "name", "mydb");

    config.addSection("Logging");
    config.setVariable("Logging", "level", "info");
    config.setVariable("Logging", "file", "app.log");

    // Save the configuration
    config.save();

    // Read values
    std::string host = config.getVariable("Database", "host", "localhost");
    std::cout << "Database host is " << host << std::endl;
    std::string logLevel = config.getVariable("Logging", "level", "debug");
    std::cout << "Logging level is " << logLevel << std::endl;
}

void struct_diag()
{
    std::cout << "sizeof(vparpc_request_generic_t) is " << sizeof(vparpc_request_generic_t) << std::endl;
    std::cout << "sizeof(vparpc_request_auth_t) is " << sizeof(vparpc_request_auth_t) << std::endl;
    std::cout << "sizeof(vparpc_request_version_t) is " << sizeof(vparpc_request_version_t) << std::endl;
    std::cout << "sizeof(vparpc_request_lookup_t) is " << sizeof(vparpc_request_lookup_t) << std::endl;
    std::cout << "sizeof(vparpc_request_creds_t) is " << sizeof(vparpc_request_creds_t) << std::endl;
    std::cout << "sizeof(vparpc_request_urls_t) is " << sizeof(vparpc_request_urls_t) << std::endl;

    std::cout << "vparpc_request_generic_t padding is " << 1080 - sizeof(vparpc_request_generic_t) << std::endl;
    std::cout << "vparpc_request_auth_t    padding is " << 1080 - sizeof(vparpc_request_auth_t) << std::endl;
    std::cout << "vparpc_request_version_t padding is " << 1080 - sizeof(vparpc_request_version_t) << std::endl;
    std::cout << "vparpc_request_lookup_t  padding is " << 1080 - sizeof(vparpc_request_lookup_t) << std::endl;
    std::cout << "vparpc_request_creds_t   padding is " << 1080 - sizeof(vparpc_request_creds_t) << std::endl;
    std::cout << "vparpc_request_urls_t    padding is " << 1080 - sizeof(vparpc_request_urls_t) << std::endl;


}

int main() {
    auto * pMwFw = new mwfw2(__FILE__,__FUNCTION__);
    sine();
    //shmvars();
    //auth_users();
    configini();
    struct_diag();
    return EXIT_SUCCESS;
}
