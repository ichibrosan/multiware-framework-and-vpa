//
// Created by doug on 6/10/25.
//

#include "mwfw2.h"


int main(int argc,char **argv) {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);
    window * pWin = new window();

    gpSemiGr->cosmetics( SRUL,  SRUR,  SRLL,
                        SRLR,SVSR,SVSL,
                        SH,  SV);
    std::string ssCopr = "Copyright ";
    ssCopr.append("(c)");
    ssCopr.append(" 2025 Douglas Wade Goodall. All Rights Reserved.");
    pWin->set_title("Virtual Protocol Adapter RPC Client "
                      "Ver 5.5.10.2");
    pWin->add_row(  ssCopr);



   // by default use my local IP
    // std::string ssTargetIP = gpSh->m_pShMemng->szIP;

    // diagnose * pDiagnose = new diagnose(ssTargetIP);

    pWin->add_row("VPA RPC Client");

// #ifdef DISPLAY_ISIGNATURE
//     muteInt * mute_iSignature =
//         new muteInt("/fw_shmem_iSignature",
//                     &gpSh->m_pShMemng->iSignature);
//     std::string ssSignature =
//         "[iSignature] is " + std::to_string(mute_iSignature->get());
//     pWin->add_row(ssSignature);
// #endif // DISPLAY_ISIGNATURE

// #ifdef DISPLAY_VPAD_UPTIME_SECONDS
//     muteInt * mute_vpad_uptime_seconds =
//         new muteInt("/fw_shmem_vpad_uptime_seconds",
//                     &gpSh->m_pShMemng->vpad_uptime_seconds);
//     std::string ssUptime =
//         "[vpad_uptime_seconds] is " +
//             std::to_string(mute_vpad_uptime_seconds->get());
//     pWin->add_row(ssUptime);
// #endif // DISPLAY_VPAD_UPTIME_SECONDS
//
//     diagnose_request_t request;
//     request.eReqFunc      = DIAGNOSE_REQ_VERSION;
//     std::string ssVersion = pDiagnose->call(request);
//     std::string ssVersion2 = "Version: " + ssVersion;
//     pWin->add_row(ssVersion2);
//
//     request.eReqFunc      = DIAGNOSE_GET_IMGROOT;
//     std::string ssImgRoot = pDiagnose->call(request);
//     std::string ssImgRoot2 = "ImgRoot: " + ssImgRoot;
//     pWin->add_row(ssImgRoot2);
//
//     request.eReqFunc = DIAGNOSE_GET_CRED;
//     strcpy(request.szParm3,CFG_USERNAME);
//     strcpy(request.szParm4,CFG_PASSWORD);
//     std::string ssHandle = pDiagnose->call(request);
//     std::string ssHandle2 = "Handle:  " + ssHandle;
//     pWin->add_row(ssHandle2);
//     int iHandle = atoi(ssHandle.c_str());
//
//     request.eReqFunc = DIAGNOSE_GET_AUTH_USER_NAME;
//     request.iParm2 = iHandle;
//     std::string ssUserName = pDiagnose->call(request);
//     std::string ssUserName2 = "User:    " + ssUserName;
//     pWin->add_row(ssUserName2);
//
//     request.eReqFunc = DIAGNOSE_GET_AUTH_FIRST_NAME;
//     request.iParm2 = iHandle;
//     std::string ssFirstName = pDiagnose->call(request);
//     std::string ssFirstName2 = "First:   " + ssFirstName;
//     pWin->add_row(ssFirstName2);
//
//     request.eReqFunc = DIAGNOSE_GET_AUTH_LAST_NAME;
//     request.iParm2 = iHandle;
//     std::string ssLastName = pDiagnose->call(request);
//     std::string ssLastName2 = "Last:    " + ssLastName;
//     pWin->add_row(ssLastName2);
//
//     request.eReqFunc = DIAGNOSE_GET_AUTH_LEVEL;
//     request.iParm2 = iHandle;
//     std::string ssUserLevel = pDiagnose->call(request);
//     std::string ssUserLevel2 = "Level:   " + ssUserLevel;
//     pWin->add_row(ssUserLevel2);

    pWin->render();

    delete pWin;


}