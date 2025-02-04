////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/CLog.cpp 2025/01/14 20:25 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.     //
////////////////////////////////////////////////////////////////////////////

#include "CLog.hpp"

/************************************************************************
 * Create the fully qualified file specification based on __FILE__
 * and save result in m_szFQFS for later use.
 * @param pszFileName A pointer to a null terminated filename string
 * @param pszFuncName A pointer to a null terminated function name string
 * 2025/01/07 04:13 dwg - elegant solution
 ************************************************************************/
CLog::CLog(
        const char *pszFile,
        const char *pszFunction) {

    assert(nullptr != pszFile);
    assert(nullptr != pszFunction);

    strcpy(m_szFQFS,
           gpOS->genLogFQFS(pszFile, pszFunction,false));
    write("CLog::CLog() called");

    /*
     * Make sure the log file got created if necessary
     */
    if(0 == access(m_szFQFS,F_OK)) {
        //std::cout << "log entry was written" << std::endl;
    } else {
        std::cout << "log entry was not written" << std::endl;
    }
}


/************************************************************
 * GetTimeDateStamp Writes a time/dat stamp into the provided
 * string buffer.
 * @param szDest A pointer to a string into which is placed
 * a time/date stamp
 ************************************************************/
void CLog::getTimeDateStamp(char *pszDest) {

    // Make sure we weren't pass a bugus buffer pointer
    assert(nullptr != pszDest);

    assert(0 != strlen(m_szFQFS));

    char szTime[FILENAME_MAX];

    auto now =
            std::chrono::system_clock::now();
    std::time_t timeNow =
            std::chrono::system_clock::to_time_t(now);
    strcpy(szTime, std::ctime(&timeNow));

    // remove the training newline
    szTime[strlen(szTime) - 1] = 0;

    char szComposite[FILENAME_MAX];
    memset(szComposite, 0, sizeof(szComposite));
    szComposite[0] = szTime[20];
    szComposite[1] = szTime[21];
    szComposite[2] = szTime[22];
    szComposite[3] = szTime[23];
    szComposite[4] = '-';

    char szMon[FILENAME_MAX];
    memset(szMon,0,sizeof(szMon));

    // Extract month from the time string as "mmm"
    szMon[0] = szTime[4];
    szMon[1] = szTime[5];
    szMon[2] = szTime[6];
    szMon[3] = 0;

    // Convert ascii month abbreviation into month number
    if (strcmp("Jan", szMon) == 0) { strcat(szComposite, "01-"); }
    if (strcmp("Feb", szMon) == 0) { strcat(szComposite, "02-"); }
    if (strcmp("Mar", szMon) == 0) { strcat(szComposite, "03-"); }
    if (strcmp("Apr", szMon) == 0) { strcat(szComposite, "04-"); }
    if (strcmp("May", szMon) == 0) { strcat(szComposite, "05-"); }
    if (strcmp("Jun", szMon) == 0) { strcat(szComposite, "06-"); }
    if (strcmp("Jul", szMon) == 0) { strcat(szComposite, "07-"); }
    if (strcmp("Aug", szMon) == 0) { strcat(szComposite, "08-"); }
    if (strcmp("Sep", szMon) == 0) { strcat(szComposite, "09-"); }
    if (strcmp("Oct", szMon) == 0) { strcat(szComposite, "10-"); }
    if (strcmp("Nov", szMon) == 0) { strcat(szComposite, "11-"); }
    if (strcmp("Dec", szMon) == 0) { strcat(szComposite, "12-"); }

    // Turn leading space into zero
    if (' ' == szComposite[5])     { szComposite[5] = '0';       }

    szComposite[8] = szTime[8];
    szComposite[9] = szTime[9];
    szComposite[10] = '_';

    // Turn leading spaces into zeroes
    if (' ' == szComposite[8])     { szComposite[8] = '0';       }

    // Copy the time into the timestamp
    strncpy(&szComposite[11], &szTime[11], 8);

    // Copy to caller's buffer
    strcpy(pszDest, szComposite);
}


/*********************************************
 * Truncate logfile or create if necessary
 * @return [ RETURN_SUCCESS | RETURN_FAILURE ]
 *********************************************/
int CLog::truncate() {

    // Assure wee have a valid log filename saved.
    assert(0 != strlen(m_szFQFS));

    FILE *fd = fopen(m_szFQFS, "w");
    if (nullptr == fd) {
        printf("CLog::write(open %s failed at line %d)",
               m_szFQFS,__LINE__);
        return RETURN_FAILURE;
    } else {
        int int_truncate_retcode =
                fprintf(fd, "\n--------------------------------"
                              "--------------------------------\n");
        if(0 == int_truncate_retcode) {
            printf("fprintf failed at line %d\n",__LINE__);
        }

        fclose(fd);
        return RETURN_SUCCESS;
    }
}



/***************************************************
 * Write a message to the log with a time/date stamp
 * @param szMessage
 * @return
 ***************************************************/
int CLog::write(const char *szMessage) {

    // Assure we weren't passed a bugus msg pointer
    assert(nullptr != szMessage);

    // Assure we have a non-empty log filespec
    assert(0 != strlen(m_szFQFS));

    char szTime[FILENAME_MAX];
    getTimeDateStamp(szTime);

    FILE *fd = fopen(m_szFQFS, "a");
    if (nullptr == fd) {
        printf("CLog::write(open %s failed at line %d)",
               m_szFQFS,__LINE__);
        return RETURN_FAILURE;
    }

    int count = fprintf(fd, "%s %s\n", szTime, szMessage);
    if(count == 0) {
        printf("fprintf failed at line %d\n",__LINE__);
        return RETURN_FAILURE;
    }

    int iCloseRetcode = fclose(fd);
    if(0 != iCloseRetcode) {
        printf("%d = fclose failed at line %d\n",
               iCloseRetcode,__LINE__);
        printf("errno was %d\n",errno);
    }
    return RETURN_SUCCESS;
}


/*********************************************************************
 * Write a log entry without a timestamp
 * @param szMessage
 * @return
 *********************************************************************/
int CLog::writesanstime(const char *szMessage) {

    // Assure we weren't pass a bugus msg pointer
    assert(nullptr != szMessage);

    /// Assure we don't have an empty log filename string
    assert(0 != strlen(m_szFQFS));

    FILE *fd = fopen(m_szFQFS, "a");
    if (nullptr == fd) {
        printf("CLog::write(open %s failed at line %d)",
               m_szFQFS,__LINE__);
        return RETURN_FAILURE;
    }

    int count = fprintf(fd, "%s", szMessage);
    if (count == 0) {
        return RETURN_FAILURE;
    }

    int closeRetcode = fclose(fd);
    if (0 != closeRetcode) {
        printf("fclose failed at line %d\n",__LINE__);
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}


/*********************************************
 * Write to logfile (uses varargs like printf)
 * @param pszFormat
 * @param ...
 * @return
 *********************************************/
int CLog::writev(const char *pszFormat, ...) {

    // Assure we weren't pass a bogus format string
    assert(nullptr != pszFormat);

    // Assure we don't have an empty log filename
    assert(0 != strlen(m_szFQFS));

    char szTime[FILENAME_MAX];
    getTimeDateStamp(szTime);

    char szFormat[FILENAME_MAX];
    strcpy(szFormat, szTime);
    strcat(szFormat, " ");
    strcat(szFormat, pszFormat);
    assert(nullptr != pszFormat);
    assert(0 != strlen(m_szFQFS));

    char szFinal[FILENAME_MAX];
    va_list args;
    va_start (args, pszFormat);
    vsprintf(szFinal, szFormat, args);
    va_end (args);

    FILE *fd = fopen(m_szFQFS, "a");
    if (nullptr == fd) {
        printf("fopen failed during call to "
               "writev opening %s for append\n",
               m_szFQFS);
        printf("data was %s\n", szFinal);
        return RETURN_FAILURE;
    }
    int count = fprintf(fd, "%s\n", szFinal);
    if (count == 0) {
        printf("fprintf failed at line %d\n",__LINE__);
        return RETURN_FAILURE;
    }
    int closeRetcode = fclose(fd);
    if (0 != closeRetcode) {
        printf("fclose failed\n");
        return RETURN_FAILURE;
    }
    return RETURN_SUCCESS;
}


/**
 * Log a named string
 * @param szName
 * @param value
 * @return
 */
int CLog::namedString(const char *szName, const char *value) {
    char szMessage[BUFSIZ];

    sprintf(szMessage, "%s %s", szName, value);
    char szTime[FILENAME_MAX];
    getTimeDateStamp(szTime);

    FILE *fd = fopen(m_szFQFS, "a");
    if (nullptr == fd) {
        printf("CLog::write(open %s failed at line %d)",
               m_szFQFS,__LINE__);
        return RETURN_FAILURE;
    }

    int count = fprintf(fd, "%s %s\n", szTime, szMessage);
    if (count == 0) {
        return RETURN_FAILURE;
    }
    int closeRetcode = fclose(fd);
    if (0 != closeRetcode) {
        printf("fclose failed\n");
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}


/*****************************************************
 * Log a named boolean
 * @param szName
 * @return
 *****************************************************/
int CLog::namedBool(const char *pszName, bool bBool) {

    assert(nullptr != pszName);

    char szMessage[FILENAME_MAX];

    if (bBool) {
        sprintf(szMessage, "%s true", pszName);
    } else {
        sprintf(szMessage, "%s false", pszName);
    }

    char szTime[FILENAME_MAX];
    getTimeDateStamp(szTime);

    FILE *fd = fopen(m_szFQFS, "a");
    if (nullptr == fd) {
        printf("CLog::write(open %s failed at line %d)",
               m_szFQFS,__LINE__);
        return RETURN_FAILURE;
    }

    int count = fprintf(fd, "%s %s\n", szTime, szMessage);
    if (count < 0) {
        return RETURN_FAILURE;
    }
    int closeRetcode = fclose(fd);
    if (0 != closeRetcode) {
        printf("fclose failed at line %d\n",__LINE__);
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}


/*****************************************************
 * Log a named double
 * @param szName
 * @param value
 * @return Returns RETURN_SUCCESS or RETURN_FAILURE
 *****************************************************/
int CLog::namedDouble(const char *pszName, double value) {

    // Assure we didn't get passed a null variable name string
    assert(nullptr != pszName);

    char szMessage[FILENAME_MAX];
    sprintf(szMessage, "%s %8.3f", pszName, value);

    char szTime[FILENAME_MAX];
    getTimeDateStamp(szTime);

    FILE *fd = fopen(m_szFQFS, "a");
    if (nullptr == fd) {
        printf("CLog::write(open %s failed at line %d)",
               m_szFQFS,__LINE__);
        return RETURN_FAILURE;
    }

    int count = fprintf(fd, "%s %s\n", szTime, szMessage);
    assert(0 != count);
    if (0 == count) {
        return RETURN_FAILURE;
    }
    int closeRetcode = fclose(fd);
    if (0 != closeRetcode) {
        printf("fclose failed\n");
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}


/***************************************************
 * Log a named int
 * @param szName
 * @param value
 * @return
 ***************************************************/
int CLog::namedInt(const char *szName, int value) {
    assert(nullptr != szName);
    assert(0 != strlen(m_szFQFS));

    char szMessage[FILENAME_MAX];
    sprintf(szMessage, "%s %d", szName, value);

    char szTime[FILENAME_MAX];
    getTimeDateStamp(szTime);

    FILE *fd = fopen(m_szFQFS, "a");
    if (nullptr == fd) {
        printf("CLog::write(open %s failed at line %d)",
               m_szFQFS,__LINE__);
        return RETURN_FAILURE;
    }

    int count = fprintf(fd, "%s %s\n", szTime, szMessage);
    if (count < 0) {
        return RETURN_FAILURE;
    }
    int closeRetcode = fclose(fd);
    if (0 != closeRetcode) {
        printf("fclose failed at line %d\n",__LINE__);
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}

////////////////////
// eof - CLog.cpp //
////////////////////
