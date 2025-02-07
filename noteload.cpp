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

    gpSysLog = new CSysLog();       // 2025/02/06 18:38 dwg -
    char szTemp[128];               // 2025/02/06 18:38 dwg -

    gpLog     = new CLog(__FILE__, __FUNCTION__);
    gpSh      = new shared();
    gpEnv     = new environment();
    gpOS      = new osIface();
    gpCgi     = new Cgicc();
    gpCgiBind = new cgibind();


    std::string ssFile  = gpEnv->get_journal_root(false);

    std::string ssFilename  = gpCgiBind->get_form_variable("changefile");

    std::vector<std::vector<std::string>> journal_params;

    journal_params.push_back({"style","journal_style"});


    ssFile.append(ssFilename);

    std::cout << ssFile << std::endl;
    char szPath[256];
    strcpy(szPath,ssFile.c_str());
    FILE * fp = fopen(szPath,"r");
    if(nullptr == fp) {
        std::cout << "can't open file " << szPath << std::endl;
        return EXIT_SUCCESS;
    }

    int iFseekRetcode =             // 2025/02/06 18:40 dwg -
        fseek(fp,0,SEEK_END);
    sprintf(szTemp,"iFseekRetcode is %d",iFseekRetcode);
    gpSysLog->loginfo(szTemp);

    long l_fSize = ftell(fp);
    sprintf(szTemp,"noteload::main() says l_fSize is %ld",l_fSize);
    gpSysLog->loginfo(szTemp);

    if (0l == l_fSize)
    {
        journal_params.push_back({"loaded_text", ""});
    } else {
        void * pTempFile = malloc(l_fSize);
        if(nullptr == pTempFile) {
            std::cout << "OUT OF MEMORY " << std::endl;
            return EXIT_SUCCESS;
        }
        fseek(fp,0,SEEK_SET);
        fread(pTempFile,l_fSize,1,fp);
        journal_params.push_back(
            {"loaded_text", (const char *)pTempFile});
        fclose (fp);
        free(pTempFile);
    }

    gpSchema = new schema("journal_textarea.csv");
    gpSchema->gen_from_schema(HANDLE_NA,journal_params);

    return EXIT_SUCCESS;;
}
