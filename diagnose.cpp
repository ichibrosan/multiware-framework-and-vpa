///////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/diagnose.cpp 2025/01/17  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.    //
///////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"


int main() {
    gpSysLog = new CSysLog();
    here;
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);
    here;

    std::cout << "Content-type:\ttext/html\n\n" << std::endl;
    std::cout << "Hello World!!" << std::endl;
    // int iHandle    =
    //    atoi(gpCgiBind->get_form_variable("handle").c_str());

    //gpTest = new test(true,pMwFw->isCGI());
    //gpSchema = new schema("login.csv");
    //gpSchema->gen_from_schema(iHandle);
    return EXIT_SUCCESS;
}
