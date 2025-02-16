//////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/notesave.cpp 2025/01/19 dga //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.            //
//////////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * The main function initializes necessary objects, retrieves input values from a CGI form, writes the input to a file, and outputs success information to the client.
 *
 * @return Returns EXIT_SUCCESS (0) on successful execution.
 *         If there is an error opening the file, it still returns EXIT_SUCCESS (0) but logs a message indicating the problem.
 */
int main() {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    bool bCGI = false;
    char * ptr = getenv("SERVER_PORT");
    if(nullptr != ptr) {
        bCGI = true;
        std::cout << "content-type:\ttext/html\n\n" << std::endl;
    }

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
