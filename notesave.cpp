//////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/notesave.cpp 2025/01/19 dga //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.            //
//////////////////////////////////////////////////////////////////////////////

#include "notesave.h"

int main() {
    bool bCGI = false;
    char * ptr = getenv("SERVER_PORT");
    if(nullptr != ptr) {
        bCGI = true;
        std::cout << "content-type:\ttext/html\n\n" << std::endl;
    }

    gpLog     = new CLog(__FILE__, __FUNCTION__);
    gpSh      = new shared();
    gpEnv     = new environment();
    gpOS      = new osIface();
    gpCgi     = new Cgicc();
    gpCgiBind = new cgibind();


    std::string ssNote  = gpCgiBind->get_form_variable("journaltextarea");
    std::string ssFile  = gpCgiBind->get_form_variable("fileName");

    char szPath[256];
    std::string ssPath = gpEnv->get_journal_root(false);
    ssPath.append(ssFile);

    strcpy(szPath,ssPath.c_str());
    FILE * fp = fopen(szPath,"w");
    if(nullptr == fp) {
        std::cout << "can't open file " << szPath << std::endl;
        return EXIT_SUCCESS;
    }

    fprintf(fp,"%s",ssNote.c_str());
    fclose (fp);

    std::cout << "<p>Filename: " << szPath << " Saved!!" << std::endl;
    std::cout << "<p>Note:<p>" << "<pre>" << ssNote << "</pre>" << std::endl;

    return EXIT_SUCCESS;;

}
