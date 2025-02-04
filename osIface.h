/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/osIface.h 2025/01/10   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#ifndef INDEX_CGI_OSIFACE_H
#define INDEX_CGI_OSIFACE_H

#include "std.h"

class osIface {
    char m_szFQFS[FILENAME_MAX];
    std::string m_ssFQFS;
    char m_szPath[FILENAME_MAX];
public:
    osIface();

    std::vector<std::string> allfilesindir(std::string osPath);

    std::string file2path(const char *pszFile);
    std::string file2filename(const char *pszFile);
    std::string file2filenamesansext(const char *pszFile);

    const char * genJournalFQFS(const char *, bool);
    const char * genLogFQFS(const char *, const char *, bool);

    std::string genCgiCBDPath(const char *pszCgiName,bool bDebug);
    std::string genCgiCBDUrl(const char *pszCgiName,bool bDebug);
    std::string genCgiBinUrl(const char *pszCgiName,bool bDebug);

    std::string genHtmlUrl(const char *pszPageName,bool bDebug);
    std::string genImgUrl(const char *pszImgName,bool bDebug);
    std::string genSchemaFQFS(const char * pszSchema,bool bDebug);

    //char * parseFileFunc(const char * pszFile,const char * pszFunc);
    std::string parseSchemaName(std::string ssSchemaName,bool bDebug);
    void printBinary(int,int);
};

extern osIface *pOsIface;

#endif //INDEX_CGI_OSIFACE_H

//system("curl http://daphne.goodall.com/~doug/fw/html/fw-test1.html "
//"> /tmp/fw-test1.stdout 2> /tmp/fw-test1.stderr");
