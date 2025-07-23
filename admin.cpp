////////////////////////////////////////////////////////////////////
// ~/public_html/fw/admin.cpp 2025-07-22 02:16 dwg -              //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.hpp */

#include "mwfw2.h"
using namespace std;

int
main(int argc, char** argv)
{
    auto* pMwfw = new mwfw2(__FILE__, __FUNCTION__);

    int handle = atoi(gpCgiBind->get_form_variable("handle").c_str());
    std::string ssUsername = gpSh->m_pShMemng->creds[handle].szAuthUserName;

    std::string ssSchema = gpOS->file2filenamesansext(__FILE__);
    ssSchema.append(".csv");
    gpSchema = new schema(ssSchema.c_str());
    gpSchema->gen_from_schema(handle,
                              LOGOUT,__FILE__, ssUsername,
                              ssPassword);

    if (pMwfw->isCGI()) { gpHtml->dumps(); }

    return EXIT_SUCCESS;
}
