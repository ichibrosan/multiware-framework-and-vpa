//////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/fw-test4.cpp 2025/02/01 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.   //
//////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"

//#include "fw-test4.h"

// #include <cgicc/Cgicc.h>    // the cgicc headers
// #include <cgicc/CgiDefs.h>
// #include <cgicc/FormEntry.h>
// #include <cgicc/HTTPHTMLHeader.h>
// #include <cgicc/HTMLClasses.h>

// using namespace cgicc;
//
// // needed for the mwfw build
// Cgicc   * gpCgi;
// cgibind * gpCgiBind;
// environment * gpEnv;
// cgihtml * gpHtml;
// readCsv * gpCsv;
// CLog    * gpLog;
// osIface * gpOS;
// shared  * gpSh;

int main() {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    std::cout << "content-type:\ttext/html\n\n" << std::endl;
    // Cgicc *pCgi = new Cgicc();
    std::string ssServerSoftware;
    ssServerSoftware = gpCgi->getEnvironment().getServerSoftware();
    std::cout << ssServerSoftware << std::endl;
    return 0;
}
