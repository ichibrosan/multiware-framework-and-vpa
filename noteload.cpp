//////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/noteload.cpp 2025/01/19 dwg //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.            //
// Originally written by Marcus Franklin, some edits by Douglas Goodall     //
//////////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * Logs and outputs an error message with context information including
 * the source file, function name, and line number where the error occurred.
 *
 * @param pszErrMsg A constant character pointer to the error message to be logged.
 * @param iLineNumber The line number where the error occurred.
 */
void process_error(const char *pszErrMsg,int iLineNumber )
{
    char szTemp[128];
    sprintf(szTemp,"%s in %s::%s line #%d",
        pszErrMsg,__FILE__,"main()",iLineNumber);
    std::cout << szTemp << std::endl;
}


/**
 * @brief The main entry point for the program execution.
 *
 * This function initializes key components of the system, determines
 * if the program is executed in a CGI environment, reads a given
 * journal file, and processes its content. It subsequently allocates
 * memory for file data, processes any read errors, and generates
 * schema from the processed data.
 *
 * The program logs errors and outputs diagnostic information regarding
 * file operations (e.g., fopen, fseek, ftell, fread, fclose).
 *
 * @return An integer value indicating the program's exit status. Typically,
 *         it returns EXIT_SUCCESS (0) upon successful completion.
 */
int main() {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    char szTemp[128];               // 2025/02/06 18:38 dwg -
    char szPath[256];
    std::vector<std::vector<std::string>> journal_params;

    journal_params.push_back({"style","journal_style"});

    std::string ssFile      = gpEnv->get_journal_root(false);
    std::string ssFilename  = gpCgiBind->get_form_variable("changefile");
    ssFile.append(ssFilename);
    std::cout << ssFile << std::endl;
    strcpy(szPath,ssFile.c_str());
    FILE * fp = fopen(szPath,"r");
    if(nullptr == fp) {
        process_error("fopen failed",__LINE__);
        return EXIT_SUCCESS;
    }

    /*
     * Seek to the end of the file in order to position the current offset
     */
    int iFseekRetcode =             // 2025/02/06 18:40 dwg -
        fseek(fp,0,SEEK_END);
    if (-1 == iFseekRetcode) {
        sprintf(szTemp,"fseek failed (errno=%d)",errno);
        process_error(szTemp,__LINE__-5);
        return EXIT_SUCCESS;
    }

    /*
     * use ftell to retrieve the current offset (happens  to be at the end)
     */
    long l_fSize = ftell(fp);
    if (-1 == l_fSize) {
        sprintf(szTemp,"ftell failed (errno=%d)",errno);
        process_error(szTemp,__LINE__-3);
        return EXIT_SUCCESS;
    }

    /*
     * Check for condition where file is empty, and do the appropriate thing
     */
    if (0l == l_fSize) {
        // File is empty
        journal_params.push_back({"loaded_text", ""});
    } else {
        // File is not empty
        /*
         * Allocate a buffer the size of the existing text file plus one
         * byte for the null terminator following the file data.
         */
        void * pTempFile = malloc(l_fSize+ZERO_TERMINATOR_SIZE);
        if(nullptr == pTempFile) {
            process_error("malloc failed (OUT OF MEMORY)",__LINE__-2);
            return EXIT_SUCCESS;
        }

        /*
         * Clear the allocated memory to zeros so that after the read, the
         * next byte will be a zero (null terminator).
         */
        memset(pTempFile,0,l_fSize+1);

        /*
         *  seek to the end of the file
         */
        int iFseekRetcode = fseek(fp,0,SEEK_SET);
        if(0 != iFseekRetcode) {
            process_error("fseek failed",__LINE__-2);
            return EXIT_SUCCESS;
        }

        /*
         * read the entire trext file as one block (lFsize)
         */
        int iFreadCount = fread(pTempFile,l_fSize,1,fp);
        if(1 != iFreadCount) {
            sprintf(szTemp,
                "fread failed (iFeadCount=%d,l_fSize=%ld)",
                iFreadCount,l_fSize);
            process_error(szTemp,__LINE__-3);
            return EXIT_SUCCESS;
        }

        journal_params.push_back(
            {"loaded_text", (const char *)pTempFile});

        int iFcloseRetcode = fclose (fp);
        if(0 != iFcloseRetcode)
        {
            sprintf(szTemp,"fclose failed (errno=%d)",errno);
            process_error(szTemp,__LINE__);
            return EXIT_SUCCESS;
        }

        free(pTempFile);    // free does not return status
    }

    gpSchema = new schema("journal_textarea.csv");
    gpSchema->gen_from_schema(HANDLE_NA,journal_params);

    return EXIT_SUCCESS;;
}
