////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/structures.cpp 2025/07/13 02:32 dwg  //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.       //
////////////////////////////////////////////////////////////////////
#include "mwfw2.h"
#include "cfgini.h"
#include "xinetdcfg.h"

/**************************************************************
 * Display Retro Header Information IBM 5150 Monochrome style *
 **************************************************************/
void sine()
{
    auto* pWin = new window();

    gpSemiGr->cosmetics(
        SRUL, SRUR, SRLL,
        // Corner characters: ┌ ┐ └ ┘
        SRLR, SVSR, SVSL,
        // Right corner and separators
        SH, SV);
    // Horizontal ─ and vertical │ lines

    char szVersion[64];
    sprintf(szVersion, "Virtual Protocol Adapter Structures Utility "
            "Ver %d.%d.%d.%d",RMAJ,RMIN,RREV,RBLD);
    pWin->set_title(szVersion);
    std::string ssCopr = "  Copyright ";
    ssCopr.append("(c)"); // Append copyright symbol for compatibility
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");
    pWin->add_row(ssCopr);
    pWin->render();
}


void struct_diag()
{
    std::cout << "sizeof(vparpc_request_generic_t) is " << sizeof(
        vparpc_request_generic_t) << std::endl;

    std::cout << "vparpc_request_generic_t padding is " << 1080 - sizeof(
        vparpc_request_generic_t) << std::endl;
    std::cout << "vparpc_request_auth_t    padding is " << 1080 - sizeof(
        vparpc_request_auth_t) << std::endl;
    std::cout << "vparpc_request_version_t padding is " << 1080 - sizeof(
        vparpc_request_version_t) << std::endl;
    std::cout << "vparpc_request_lookup_t  padding is " << 1080 - sizeof(
        vparpc_request_lookup_t) << std::endl;
    std::cout << "vparpc_request_creds_t   padding is " << 1080 - sizeof(
        vparpc_request_creds_t) << std::endl;
    std::cout << "vparpc_request_urls_t    padding is " << 1080 - sizeof(
        vparpc_request_urls_t) << std::endl;
}

int main()
{
    auto* pMwFw = new mwfw2(__FILE__, __FUNCTION__);
    sine();
    struct_diag();
    return EXIT_SUCCESS;
}
