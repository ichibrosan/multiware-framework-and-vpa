//////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/noteload.cpp 2025/01/19 dwg //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.            //
//////////////////////////////////////////////////////////////////////////////

#include "noteload.h"

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


    std::string ssFile  = gpEnv->get_journal_root(false);

    std::string ssFilename  = gpCgiBind->get_form_variable("changefile");




    //ssFile.append("/");
    ssFile.append(ssFilename);


    std::cout << ssFile << std::endl;
    char szPath[256];
    strcpy(szPath,ssFile.c_str());
    FILE * fp = fopen(szPath,"r");
    if(nullptr == fp) {
        std::cout << "can't open file " << szPath << std::endl;
        return EXIT_SUCCESS;
    }

    fseek(fp,0,SEEK_END);
    long l_fSize = ftell(fp);
    //printf("%ld\n",l_fSize);
    void * pTempFile = malloc(l_fSize);

    if(nullptr == pTempFile) {
        std::cout << "OUT OF MEMORY " << std::endl;
        return EXIT_SUCCESS;
    }

    fseek(fp,0,SEEK_SET);

    //FILE * noteFile = (FILE *)malloc(i_fSize);
    //fprintf(fp,"%p",noteFile);
    //fclose(fp);
    //fopen(noteFile,"r");
    //std::cout << fread(pTempFile,l_fSize,1,fp) << std::endl;
    //std::cout << (const char *)pTempFile << std::endl;
    fread(pTempFile,l_fSize,1,fp);

    //std::string ssFileString = (const char *)pTempFile;

    std::vector<std::vector<std::string>> journal_params =
        {
        {"journal_style","journal_style"},
        {"loaded_text", (const char *)pTempFile}
        };

    gpSchema = new schema("journal_textarea.csv");
    gpSchema->gen_from_schema(0,journal_params);

    fclose (fp);
    free(pTempFile);

    //std::cout << "<p>Filename: " << szPath << " Saved!!" << std::endl;
    //std::cout << "<p>Note:<p>" << "<pre>" << ssNote << "</pre>" << std::endl;



    return EXIT_SUCCESS;;
}
