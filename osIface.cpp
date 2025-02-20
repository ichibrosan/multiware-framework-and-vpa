/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/osIface.cpp 2025/01/10 //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.            //
/////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

#define DEBUG_GLFQFS

/************************************************************************
 * Function: osIface::printBinary
 *
 * Description:
 * This function takes an integer and its binary digit count as inputs,
 * converts the integer into its binary representation, and prints the
 * binary digits equal to the specified count. The binary digits are
 * extracted from the most significant bits (MSB) of the number. The result
 * is formatted as a string and passed to standard output.
 *
 * Parameters:
 * - number: The integer value to be converted into its binary representation.
 * - digits: The number of significant binary digits to display, starting
 *           from the most significant bit.
 *
 * Remarks:
 * - A temporary buffer (szBuffer) is used to hold individual binary digits
 *   as strings before appending them to the full binary string.
 * - The binary string is truncated to the specified number of digits
 *   before being printed.
 ************************************************************************/
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


/**
 * @brief Global character array used to store file paths, with maximum size defined by FILENAME_MAX.
 *
 * This variable is used across various functions to store and manage fully
 * qualified file paths, ensuring a consistent and reusable path storage mechanism.
 *
 * @note The size of the array is determined by the system-defined FILENAME_MAX
 * to ensure compatibility and prevent overflows. Users of this variable must
 * ensure that the string stored does not exceed this limit.
 */
char gszPath[FILENAME_MAX];

/************************************************************************
 * Note: The global variable `gszUrl` is used to store a file path or URL
 * as a string. It is defined globally to provide persistent storage
 * for returning the generated URL from the `osIface::genImgUrl` member
 * function. This approach avoids potential issues that can arise when
 * returning stack-allocated variables from a function.
 ************************************************************************/
char gszUrl[FILENAME_MAX];

/************************************************************************
 * Constructor for the osIface class. This constructor logs a message
 * confirming the instantiation of the osIface object. It utilizes
 * a global logging object, gpLog, to log the message.
 *
 * Preconditions:
 * - gpLog must be a valid and initialized instance of the CLog class.
 *
 * Side Effects:
 * - Writes a message to the log, indicating the instantiation of the
 *   osIface object.
 ************************************************************************/
osIface::osIface() {
    gpLog->write("osIface instantiated");
}


/************************************************************************
 * Fetches the names of all files located in the provided directory path.
 *
 * This function iterates through a given directory and retrieves
 * the complete paths of all files found within it. It uses the
 * `std::filesystem::directory_iterator` to enumerate the files
 * in the specified directory and appends their paths to a vector
 * of strings, which is then returned.
 *
 * Parameters:
 * - osPath: A string containing the directory path to search for files.
 *
 * Returns:
 * - A vector of strings where each string represents the full path
 *   to a file located in the specified directory.
 *
 * Note:
 * - The function does not differentiate between files and directories.
 *   All entries in the directory are treated as files.
 ************************************************************************/
std::vector<std::string> osIface::allfilesindir(std::string osPath)
{
    std::vector<std::string> allFiles;
    here;
    for (const auto &
         osFile :
         std::filesystem::directory_iterator(osPath)) {
        allFiles.push_back(osFile.path());
         }
    return allFiles;
}

/**
 * Converts a given file path into its directory path by removing the filename.
 *
 * @param pszFile A C-style string representing the full file path.
 * @return A string containing the directory portion of the given file path.
 * This function uses the std::filesystem library to process the path and
 * extract the directory portion by removing the filename.
 */
std::string osIface::file2path(const char *pszFile)
{
    std::string ssPath = pszFile;
    ssPath = std::filesystem::path(ssPath).remove_filename();
    return ssPath;
}


/************************************************************************
 * This function, file2filename, extracts the file name, including its
 * extension, from a given file path. It first determines the directory
 * path using the file2path function, then isolates the file name portion
 * of the input by taking all characters following the directory path.
 * The resulting string is returned as the file name.
 *
 * Parameters:
 *  - pszFile: A C-style string representing the full path of the file.
 *
 * Returns:
 *  - A string containing the extracted file name, including its extension.
 ************************************************************************/
std::string osIface::file2filename(const char * pszFile)
{
    std::string ssPath     = file2path(pszFile);
    std::string ssFile     = pszFile;
    std::string ssFilename = ssFile.substr(ssPath.length(),ssFile.length());
    return ssFilename;
}


/************************************************************************
 * This function, file2filenamesansext, generates the file name from the
 * given file path and removes its file extension. It extracts the base
 * file name by calling the file2filename function, which retrieves the
 * name of the file. Then, it removes the last four characters, which
 * typically correspond to the file extension (e.g., ".txt"), and
 * returns the resulting file name without the extension.
 *
 * @param pszFile A C-style string representing the file path.
 * @return A std::string containing the file name without its extension.
 ************************************************************************/
std::string osIface::file2filenamesansext(const char * pszFile)
{
    std::string ssFilename =
            file2filename(pszFile);
    std::string ssFilenamesansext =
            ssFilename.substr(0,ssFilename.length()-4);
    return ssFilenamesansext;
}


/**
 * @brief Generates the file path for an image based on a given image name.
 *
 * This method constructs a file path by using the current file's directory
 * path, appending a predefined subdirectory for images, and then appending
 * the provided image name. Optionally allows for debug handling if required.
 *
 * @param pszImgName A pointer to a constant character string representing the
 *                   name of the image file.
 * @param bDebug A boolean flag that can be used for debug-specific
 *                   functionality.
 * @return The generated file path as a string.
 */
std::string osIface::genImgPath(const char *pszImgName,bool bDebug)
{
    std::string ssPath = __FILE__;
    ssPath = std::filesystem::path(ssPath).remove_filename();
    ssPath.append("/images/");
    ssPath.append(pszImgName);
    return ssPath;
}



/**
 * Generates a complete URL string for an image using protocol, IP, user, and image name.
 *
 * @param pszImgName A pointer to the image name that will be appended to form the URL.
 * @param bDebug A boolean flag to enable debug logging and output for tracing the generated URL at each step.
 * @return A complete URL string for the specified image name.
 *
 * The function constructs the URL step by step using the following components:
 * - Protocol (e.g., "http://") retrieved from `szProtocol` of a shared memory structure.
 * - IP or domain name retrieved from `szIP` of the shared memory structure.
 * - User name retrieved from `szUser` of the shared memory structure.
 * - Fixed directories and the specified image name.
 *
 * The generated URL is logged at each stage if debug mode is enabled, providing insight into how the URL is formed.
 * If critical components (e.g., `gpSh` and `m_pShMemng`) are missing, appropriate log entries are generated.
 *
 * The resulting URL is stored in a global variable `gszUrl` to allow reuse outside the function.
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


/************************************************************************
 * Function: genJournalFQFS
 *
 * Purpose:
 * Generates the fully qualified file specification (FQFS) for a journal
 * file. The FQFS is formed by concatenating a base directory path, the
 * user's specific directory path, and the provided file name. The
 * function ensures the required directories exist on the filesystem
 * before constructing the final path.
 *
 * Parameters:
 * - pszFile: A pointer to a character string representing the name
 *   of the file for which the fully qualified path is generated.
 * - bDebug: A boolean flag indicating whether debug information should
 *   be printed to the standard error stream.
 *
 * Return:
 * A const char pointer to the global variable `gszPath`, which contains
 * the generated fully qualified file specification.
 *
 * Notes:
 * - The function logs debugging information and intermediate values
 *   during its execution if `bDebug` is true.
 * - The function uses the `CLog` class to log information to a file.
 * - A `system` call is used to create the necessary directory structure
 *   if it does not already exist.
 * - The global variable `gszPath` temporarily holds the final FQFS and
 *   is returned. Be cautious of concurrent access when this global
 *   variable is shared across multiple invocations.
 ************************************************************************/
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

/************************************************************************
 * Function: osIface::genScriptFQFS
 *
 * Description:
 * This function generates the fully qualified file system path to a script
 * file within a user's web directory. The path includes the base directory,
 * user-specific subdirectory, and file name. Additionally, this function
 * optionally provides debug information through standard error outputs.
 *
 * Parameters:
 * - pszFile: Pointer to a null-terminated string containing the script file
 *            name to be appended to the constructed path.
 * - bDebug:  Boolean flag indicating whether debug information should be
 *            printed to standard error. If true, intermediate path details
 *            are output to help trace the path generation process.
 *
 * Returns:
 * - A pointer to a null-terminated string containing the fully qualified
 *   path of the requested script file. The returned string is stored in
 *   a global buffer (gszPath).
 *
 * Remarks:
 * - The function uses a global shared memory object (m_pShMemng) to obtain
 *   user-specific information for constructing the path.
 * - Debugging information is conditionally printed based on the value of
 *   the bDebug parameter.
 ************************************************************************/
const char * osIface::genScriptFQFS(const char *pszFile,bool bDebug) {
    CLog log(__FILE__,__FUNCTION__);
    log.truncate();
    std::string ssFile = pszFile;
    if(bDebug) { std::cerr << "ssFile      is " << ssFile << std::endl; }
    std::string ssPath = "/home/";
    if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    ssPath.append(gpSh->m_pShMemng->szUser);
    if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    ssPath.append("/public_html/fw/scripts/");
    if(bDebug) { std::cerr << "ssPath      is " << ssPath << std::endl; }
    ssPath.append(pszFile);
    strcpy(gszPath,ssPath.c_str());
    return gszPath;
}

/************************************************************************
 * Generates a fully qualified file system path for a log file based on
 * the input source file and function name. The resulting path includes
 * a "log/" directory and appends the source file's base name (excluding
 * its extension) concatenated with the function name, followed by the
 * extension ".log".
 *
 * The generated path is stored in the global variable `gszPath` for
 * returning a persistent reference. This avoids returning a local
 * variable reference which may go out of scope.
 *
 * Debugging information can be printed to the standard error output
 * when the `bDebug` flag is set to true.
 *
 * @param pszFile The name of the source file.
 * @param pszFunction The name of the function.
 * @param bDebug Flag to enable debug output to standard error.
 * @return A pointer to the global character array containing the path.
 ************************************************************************/
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

/************************************************************************
 * This function generates a CGI-bin URL for executing a CGI script.
 *
 * @param pszCgiName The name of the CGI script to be executed.
 * @param bDebug A boolean flag indicating whether debugging messages
 *               should be printed to standard output.
 *
 * @return A string containing the constructed command for executing the
 *         CGI script using curl. It includes the protocol, host, user,
 *         script path, and directs output to associated log files.
 *
 * The generated URL is constructed step by step by appending various
 * components such as protocol, host, user name, and CGI script path.
 * If debugging is enabled, each step is logged to standard output.
 * The command execution output is redirected to log files (.stdout and
 * .stderr) located in the /tmp directory.
 ************************************************************************/
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
 * Generates a cURL command string to retrieve an HTML page, save its
 * standard output to a temporary file, and save its error output to a
 * separate temporary file.
 *
 * The generated command fetches the page using the protocol, IP address,
 * user directory, and other path components specified in the shared memory
 * structure. The command redirects the downloaded content to a temporary
 * file and any error output to another file with appropriate extensions.
 *
 * If debug mode is enabled, the constructed command segments and the final
 * command are printed to the standard output for debugging purposes.
 *
 * @param pszPageName Pointer to a C-string specifying the name of the page to fetch.
 * @param bDebug Boolean value to indicate whether debug statements should be printed.
 * @return A string containing the fully constructed cURL command.
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


/************************************************************************
 * The function `genCgiCBDPath` constructs the complete file system path
 * to a specified CGI executable located in the "cmake-build-debug"
 * directory.
 *
 * It takes the name of the CGI script and a debug flag as input.
 *
 * If the debug flag is enabled, the function outputs debug information
 * about each step of path construction through the console.
 *
 * The function starts by determining the current file's path (`__FILE__`),
 * then removes the filename to get the directory path, appends
 * "cmake-build-debug/" to it, and finally appends the CGI script name.
 *
 * The resulting path is returned as a string.
 *
 * @param pszCgiName The name of the CGI script for which the path is to
 *                   be constructed.
 * @param bDebug A boolean flag that enables debug output when set to true.
 * @return A string containing the full file system path for the CGI script.
 ************************************************************************/
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


/**
 * Generates a URL string for executing a specific CGI binary script.
 *
 * This function composes a URL by combining components obtained from a global
 * shared object, such as protocol, IP, user information, and a specific path.
 * The name of the CGI script is passed as an argument and appended at the end
 * of the URL. If debug mode is enabled, it outputs the function call to the
 * console for logging purposes.
 *
 * @param pszCgiName The name of the CGI script whose URL is to be generated.
 * @param bDebug A boolean flag to enable or disable debug logging.
 * @return A string representing the fully constructed URL for the specified
 *         CGI script.
 */
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


std::string osIface::genTempFQFS(std::string ssFilename, bool bDebug) {
    here;

    if(bDebug) {
        std::cout << __FUNCTION__ << " called" << std::endl;
    }

    std::string ssPath = __FILE__;
    if (bDebug) {
        std::cout << "ssPath is " << ssPath << std::endl;
    }

    ssPath = std::filesystem::path(ssPath).remove_filename();
    if (bDebug) {
        std::cout << "ssPath is " << ssPath << std::endl;
    }

    ssPath.append("tmp/");
    if (bDebug) {
        std::cout << "ssPath is " << ssPath << std::endl;
    }

    ssPath.append(ssFilename);
    if (bDebug) {
        std::cout << "ssPath is " << ssPath << std::endl;
    }

    return ssPath;
}


/************************************************************************
 * Generates the fully qualified file system path for a given schema file.
 *
 * This function constructs the full path for a schema file, appending the
 * relative path "schemas/" and the provided schema name to the directory
 * of the current source file. Optionally, debug information can be printed
 * to indicate the function's execution and the final computed path.
 *
 * Parameters:
 * - pszSchema: A pointer to a null-terminated string representing the
 *   name of the schema file.
 * - bDebug: A boolean flag indicating whether debug output should be
 *   printed during the execution of this function.
 *
 * Returns:
 * - A string containing the fully qualified path to the schema file.
 *
 * Note:
 * The function leverages std::filesystem to manipulate file paths and
 * uses preprocessing macros (__FUNCTION__, __FILE__) to determine the
 * source file location.
 ************************************************************************/
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
 * Retrieves the last modified date of the style in the filename.
 *
 * @param ssStyle The name of the stylesheet sans .css or date modified.
 * @return A string containing the date in the filename.
 */
std::string osIface::getStyleModDate(std::string ssStyle)
{
    // Retrieving all the FQFS of the files in the style file root directory.
    std::vector<std::string> vsStylesheets =
        gpOS->allfilesindir(gpEnv->get_styles_file_root(false));

    // Instantiating this value here for later use in the for loop.
    std::string sscheckedStyle;

    // lmd = Last Modified Date.
    std::string sstrueStyleName = ssStyle + "-lmd-";

    // Setting the default value in the case that we can't find the name
    // of the style.
    std::string sslastModified = "Style not found";

    // We loop over vsStylesheets.
    for (std::string& style :  vsStylesheets)
    {
        // We strip down the FQFS just to the filenames.
        sscheckedStyle = gpOS->file2filename(style.c_str());

        // If we find a match for the full filename including "-lmd-".
        if (std::string::npos != sscheckedStyle.find(sstrueStyleName))
        {
            // We set the return value to the date following "-lmd-".
            sslastModified = sscheckedStyle.substr(
                sstrueStyleName.length(),
                DATE_LENGTH);
            // Since we've found a match, we leave the for loop.
            break;
        }
    }
    // We return the string, whether we found a match or not.
    return sslastModified;
}

/**
 * Modifies the date in the filename of the style if it's not the same
 * as the last modified date of the file itself.
 *
 * @param ssStyle The name of the stylesheet to modify the date.
 */
void osIface::setStyleModDate(std::string ssStyle)
{
    std::string ssPath = gpEnv->get_styles_file_root(false)
                       + ssStyle
                       + "-lmd-"
                       + gpOS->getStyleModDate(ssStyle)
                       + ".css";

    //auto fileDate = std::filesystem::last_write_time(ssPath);
    //std::time_t convtime = std::chrono::system_clock::to_time_t(fileDate);
    //std::cout << "fileDate" << fileDate;
}

/**
 * @brief Parses a given schema name string and separates it into its components.
 *
 * @param schemaName The input string containing the schema name to parse.
 * @return A structured representation or components of the schema name.
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
