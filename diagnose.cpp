///////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/diagnose.cpp 2025/01/17  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.    //
///////////////////////////////////////////////////////////////////////////

#include "diagnose.h"


int main() {
    char *ptr = getenv("SERVER_PORT");
    bool bCGI = false;
    if (nullptr != ptr) {
        bCGI = true;
        std::cout << "content-type:\ttext/html\n\n" << std::endl;
    }

    gpLog = new CLog(__FILE__, __FUNCTION__);
    gpLog->truncate();

    gpSh = new shared();


    gpCgi = new Cgicc();
    gpCgiBind = new cgibind();

    int iHandle    =
       atoi(gpCgiBind->get_form_variable("handle").c_str());
    //std::cout << "handle is " << iHandle << std::endl;

    std::string ssHttpReferrer = gpCgi->getEnvironment().getReferrer();
    std::string ssReferrerPath =
        std::filesystem::path(ssHttpReferrer).remove_filename();
    std::string ssReferrerFile =
        ssHttpReferrer.substr(ssReferrerPath.length(), ssHttpReferrer.length());

    gpEnv = new environment();

    gpSchema = new schema("journal.csv");
    gpSchema->gen_from_schema(iHandle);
    return EXIT_SUCCESS;
}
