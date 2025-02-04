/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/osIface.cpp 2025/01/10 //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.            //
/////////////////////////////////////////////////////////////////////////

#include <fcntl.h>
#include <unistd.h>

#include "CLog.hpp"
#include "fw-limits.h"
#include "osIface.h"
#include "shared.h"
#include "test.h"
#define DEBUG_GLFQFS

extern shared *gpSh;
extern CLog   *gpLog;

void osIface::printBinary(int number,int digits) {
    char szBuffer[4];
    std::string ssNumber = "";
    for (int i = sizeof(number) * 8 - 1; i >= 0; i--) {
        sprintf(szBuffer,"%d", (number >> i) & 1);
        ssNumber.append(szBuffer);
    }
    ssNumber = ssNumber.substr(32-digits, ssNumber.size() - 1);
    printf("%s", ssNumber.c_str());
}


/************************************************************************
 * Note: This variable, gszPath, is used to store a string that is being
 * returned from a member function. It is unhealthy to return a variable
 * that is on the stack because it may not exist after you return from
 * the function. So I use this global variable, not on the stack, to hold
 * the return value while I perform the return.
 ************************************************************************/
char gszPath[FILENAME_MAX];
char gszUrl[FILENAME_MAX];

osIface::osIface() {
    gpLog->write("osIface instantiated");
}


std::vector<std::string> osIface::allfilesindir(std::string osPath)
{
    std::vector<std::string> allFiles;
    for (const auto &
         osFile :
         std::filesystem::directory_iterator(osPath)) {
        allFiles.push_back(osFile.path());
         }
    return allFiles;
}

/************************************************************
 * Convert __FILE__ into a fully qualified file specification
 * @param pszFile
 * @return Return a standard string with the FQFS
 ************************************************************/
std::string osIface::file2path(const char *pszFile)
{
    std::string ssPath = pszFile;
    ssPath = std::filesystem::path(ssPath).remove_filename();
    return ssPath;
}


/**************************************************************************
 * Convert __FILE__ into just the filename portion
 * @param pszFile
 * @return
 **************************************************************************/
std::string osIface::file2filename(const char * pszFile)
{
    std::string ssPath     = file2path(pszFile);
    std::string ssFile     = pszFile;
    std::string ssFilename = ssFile.substr(ssPath.length(),ssFile.length());
    return ssFilename;
}


/**
 *
 * @param pszFile
 * @return
 */
std::string osIface::file2filenamesansext(const char * pszFile)
{
    std::string ssFilename =
            file2filename(pszFile);
    std::string ssFilenamesansext =
            ssFilename.substr(0,ssFilename.length()-4);
    return ssFilenamesansext;
}


/**
 * Create URL for image file
 * @param pszImgName
 * @param bDebug
 * @return
 */

/**
 * TODO Replace occurences of function genImgUrl with get_img_root
*  TODO where applicable
*/

std::string osIface::genImgUrl(const char *pszImgName,bool bDebug)
{
    CLog log(__FILE__,__FUNCTION__);
    log.namedString("pszImageName",pszImgName);
    if(bDebug) {
        std::cout << __FUNCTION__ << " called" << std::endl;
    }

// system("http://daphne.goodall.com/~doug/fw/images/fsilver-me-logo.png"

    std::string ssUrl;


    // fetch the appropriate protocol based on host (kludge)
    if(nullptr == gpSh) {
        log.write("gpSh was null");
    }
    if(nullptr == gpSh->m_pShMemng) {
        log.write("gpSh-<m_pShMemng was null");
    }
    ssUrl.append(gpSh->m_pShMemng->szProtocol);  // http://
    log.namedString("ssUrl",ssUrl.c_str());

    ssUrl.append(gpSh->m_pShMemng->szIP);        // daphne.goodall.com
    log.namedString("ssUrl",ssUrl.c_str());
    if(bDebug) {
        log.namedString("ssUrl",ssUrl.c_str());
        std::cout << ssUrl << std::endl;
    }

    ssUrl.append("/~");                         // /~
    log.namedString("ssUrl",ssUrl.c_str());
    if(bDebug) {
        log.namedString("ssUrl",ssUrl.c_str());
        std::cout << ssUrl << std::endl;
    }

    //ssUrl.append(getenv("LOGNAME"));           // doug
    ssUrl.append(gpSh->m_pShMemng->szUser);
    log.namedString("ssUrl",ssUrl.c_str());
    if(bDebug) {
        log.namedString("ssUrl",ssUrl.c_str());
        std::cout << ssUrl << std::endl;
    }

    ssUrl.append("/fw/images/");              // /fw/cgi-bin/
    log.namedString("ssUrl",ssUrl.c_str());
    if(bDebug) {
        log.namedString("ssUrl",ssUrl.c_str());
        std::cout << ssUrl << std::endl;
    }

    ssUrl.append(pszImgName);                  // fw-test3.py
    log.namedString("ssUrl",ssUrl.c_str());
    if(bDebug) {
        log.namedString("ssUrl",ssUrl.c_str());
        std::cout << ssUrl << std::endl;
    }

    strcpy(gszUrl,ssUrl.c_str());
    log.namedString("ssUrl",ssUrl.c_str());
    return gszUrl;
}


/**************************************************************************
 * Create FQFS for journal file in doc folder
 * @param pszFile
 * @return A fully qualified file specification for a journal file
 * This function is a modern c++ solution to a long standing thorny problem
 * naming log files in a variety of situations, without having to write
 * environment specific code. What a relief to be past this...
 * 2025/01/21 dwg - Marcus & Doug decided to move the journal files out
 * of the project directories and into the user's Documents folder so notes
 * don't get lost when we blow off development source trees. This code is
 * tested and working now and will be used henceforth. :-)
 **************************************************************************/
const char * osIface::genJournalFQFS(const char *pszFile,bool bDebug)
{
    CLog log(__FILE__,__FUNCTION__);
    log.truncate();
    std::string ssFile = pszFile;
    log.namedString("ssFile",ssFile.c_str());
    if(bDebug) { std::cerr << "ssFile      is " << ssFile << std::endl; }
    std::string ssPath = "/home/";
    log.namedString("ssPath",ssPath.c_str());
    if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    ssPath.append(gpSh->m_pShMemng->szUser);
    log.namedString("ssPath",ssPath.c_str());
    if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    ssPath.append("/Documents/Fw_Notes/");
    log.namedString("ssPath",ssPath.c_str());
    /**
     * Make sure the Documents/Fw_Notes folders are present.
     */
    char szCommand[FILENAME_MAX];
    sprintf(szCommand,"mkdir -p %s",ssPath.c_str());
    log.namedString("ssCommand",szCommand);
    system(szCommand);

    if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    ssPath.append(pszFile);
    log.namedString("ssPath",ssPath.c_str());
    if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    strcpy(gszPath,ssPath.c_str());
    return gszPath;

    // if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    // ssPath.append("doc/");
    // if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    // ssPath.append(ssFile);
    // if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    // strcpy(gszPath,ssPath.c_str());
    // return gszPath;
}


/**************************************************************************
 * Create FQFS for log file using __FILE__ and __FUNCTION__ passed as parms
 * @param pszFile
 * @param pszFunction
 * @return A fully qualified file specification for a log file
 * This function is a modern c++ solution to a long standing thorny problem
 * naming log files in a variety of situations, without having to write
 * environment specific code. What a relief to be past this...
 **************************************************************************/
const char * osIface::genLogFQFS(const char *pszFile,
                           const char *pszFunction,
                           bool bDebug) {
    if(bDebug) { std::cerr << std::endl << "genLogFQFS:" << std::endl; }
    if(bDebug) { std::cerr << "pszFile     is " << pszFile << std::endl; }
    if(bDebug) { std::cerr << "pszFunction is " << pszFunction << std::endl; }

    std::string ssFile = pszFile;
    std::string ssFunction = pszFunction;
    std::string ssPath = file2path(pszFile);
    if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    ssPath.append("log/");
    if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    ssPath.append(file2filenamesansext(pszFile));
    if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    ssPath.append("::");
    if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    ssPath.append(ssFunction);
    if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    ssPath.append(".log");
    if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }

    //char szPath[FILENAME_MAX];
    strcpy(gszPath,ssPath.c_str());
    return gszPath;
}

/**
 * Generate curl command to fetch web page with http:// protocol
 * @param pszPageName
 * @param bDebug
 * @return
 */
std::string osIface::genCgiBinUrl(const char *pszCgiName,
                                bool bDebug)
{
    if(bDebug) {
        std::cout << __FUNCTION__ << " called" << std::endl;
    }

// system("curl http://daphne.goodall.com/~doug/fw/cgi-bin/fw-test3.py"
//        "> /tmp/fw-test3.stdout 2> /tmp/fw-test3.stderr");

    std::string ssCommand;

    ssCommand.append("curl ");                      // curl
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    // fetch the appropriate protocol based on host (kludge)
    ssCommand.append(gpSh->m_pShMemng->szProtocol);  // http://
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append(gpSh->m_pShMemng->szIP);        // daphne.goodall.com
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append("/~");                         // /~
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    //ssCommand.append(getenv("LOGNAME"));           // doug
    ssCommand.append(gpSh->m_pShMemng->szUser);
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append("/fw/cgi-bin/");              // /fw/cgi-bin/
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append(pszCgiName);                  // fw-test3.py
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append(" > /tmp/");                   // > /tmp/
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append(pszCgiName);                   // fw-test3.py
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand = std::filesystem::path(ssCommand)
            .replace_extension(".stdout");          // fw-test3.stdout
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append(" 2> /tmp/");                  // 2> /tmp/
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append(pszCgiName);                  // fw-test3.py
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand = std::filesystem::path(ssCommand)
            .replace_extension(".stderr");          // fw-test3.stderr
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    return ssCommand;
}



/**
 * Generate curl command to fetch web page with http:// protocol
 * @param pszPageName
 * @param bDebug
 * @return
 */
std::string osIface::genHtmlUrl(const char *pszPageName,
                                bool bDebug)
{
    if(bDebug) {
        std::cout << __FUNCTION__ << " called" << std::endl;
    }

    //system("curl http://daphne.goodall.com/~doug/fw/html/fw-test1.html "
    //"> /tmp/fw-test1.stdout 2> /tmp/fw-test1.stderr");


    std::string ssCommand;

    ssCommand.append("curl ");                      // curl
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    // fetch the appropriate protocol based on host (kludge)
    ssCommand.append(gpSh->m_pShMemng->szProtocol);  // http://
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append(gpSh->m_pShMemng->szIP);        // daphne.goodall.com
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append("/~");                         // /~
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    //ssCommand.append(getenv("LOGNAME"));            // doug
    ssCommand.append(gpSh->m_pShMemng->szUser);
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append("/fw/html/");                  // /fw/html/
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append(pszPageName);                  // fw-test1.html
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append(" > /tmp/");                   // > /tmp/
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append(pszPageName);                  // fw-test1.html
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand = std::filesystem::path(ssCommand)
                .replace_extension(".stdout");      // fw-test1.stdout
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append(" 2> /tmp/");                  // 2> /tmp/
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand.append(pszPageName);                  // fw-test1.html
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    ssCommand = std::filesystem::path(ssCommand)
            .replace_extension(".stderr");          // fw-test1.stderr
    if(bDebug) {
        std::cout << ssCommand << std::endl;
    }

    return ssCommand;
}


std::string osIface::genCgiCBDPath(const char *pszCgiName, bool bDebug) {
    if(bDebug) {
        std::cout << __FUNCTION__ << " called" << std::endl;
    }

    //    system("curl http://daphne.goodall.com/~doug/fw/cmake-build-debug/"
    //           "fw-test4.cgi > /tmp/fw-test4.stdout 2> /tmp/fw-test4.stderr");

    std::string ssPath = __FILE__;
    if (bDebug) {
        std::cout << "ssPath is " << ssPath << std::endl;
    }

    ssPath = std::filesystem::path(ssPath).remove_filename();
    if (bDebug) {
        std::cout << "ssPath is " << ssPath << std::endl;
    }

    ssPath.append("cmake-build-debug/");
    if (bDebug) {
        std::cout << "ssPath is " << ssPath << std::endl;
    }

    ssPath.append(pszCgiName);
    if (bDebug) {
        std::cout << "ssPath is " << ssPath << std::endl;
    }

    return ssPath;
}


std::string osIface::genCgiCBDUrl(const char * pszCgiName,bool bDebug)
{
    if(bDebug) {
        std::cout << __FUNCTION__ << " called" << std::endl;
    }

    std::string ssUrl = gpSh->m_pShMemng->szProtocol;
    ssUrl.append(gpSh->m_pShMemng->szIP);
    ssUrl.append("/~");
    //ssUrl.append(getenv("LOGNAME"));
    ssUrl.append(gpSh->m_pShMemng->szUser);
    ssUrl.append("/fw/cmake-build-debug/");
    ssUrl.append(pszCgiName);
    return ssUrl;
}


std::string osIface::genSchemaFQFS(const char * pszSchema,bool bDebug)
{
    if(bDebug) {
        std::cout << __FUNCTION__ << " called" << std::endl;
    }

    std::string ssFile = __FILE__;
    ssFile = std::filesystem::path(ssFile.c_str()).remove_filename();
    ssFile.append("schemas/");
    ssFile.append(pszSchema);
    if(bDebug) {
        std::cout << "genSchemaFQFS says ssFile is " << ssFile << std::endl;
    }
    return ssFile;
}


/**
 *
 * @param ssSchemaName
 * @return
 */
std::string osIface::parseSchemaName(std::string ssSchemaName,bool bDebug) {
    if(bDebug) {
        std::cout << __FUNCTION__ << " called" << std::endl;
    }

    std::string ssFile = __FILE__;
    std::size_t offset = ssFile.find_last_of("/");
    std::string ssPath = ssFile.substr(0, offset);
    std::string ssFileName = ssFile.substr(offset + 1);
    ssPath.append("/schemas/");
    ssPath.append(ssSchemaName);
    return ssPath;
}

///////////////////////
// eof - osIface.cpp //
///////////////////////
