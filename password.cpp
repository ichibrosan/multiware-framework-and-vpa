
#include "mwfw2.h"

/**
 * @brief A globally unique identifier (UUID) used for identifying a specific GSS (Global Shared Service) instance.
 *
 * This variable is intended to store a string representation of a UUID. It is useful in contexts
 * where a unique identifier is required, such as distinguishing between different service instances
 * or ensuring uniqueness in distributed systems.
 */
std::string gssUUID;
/**
 * @brief Global character array for storing a UUID as a string.
 *
 * This variable holds the globally unique identifier (UUID) in string format
 * with a fixed length of 36 characters plus one for the null terminator,
 * adhering to the UUID standard.
 * It is used in the process of identifying credentials in the application.
 * The value is assigned when the UUID is generated and formatted as a string.
 */
char gszUUID[37];


/**
 * @brief Constructor for the password class.
 *
 * Initializes the password object by creating a schema object
 * for the file "passwd.csv" and retrieves the number of lines
 * in the schema. Logs the number of lines using the CLog class.
 *
 * @return void
 */
password::password()
{
    CLog log(__FILE__, __FUNCTION__);
    gbHere = true;
    here;
    m_pSchema = new schema("passwd.csv");
    m_iLines = m_pSchema->getLines();
    log.namedInt("m_iLines", m_iLines);
}


/**
 * Authenticates a user by validating the provided username and password.
 *
 * @param ssUserName The username to be authenticated.
 * @param ssPasssword The password corresponding to the provided username.
 * @return An integer indicating the authentication status.
 *         Returns -1 if authentication fails.
 */
int lookup(std::string ssUserName, std::string ssPasssword)
{
    return -1;
}


/**
 * @brief Outputs schema metadata as an HTML table.
 *
 * This method generates an HTML table in the console. It retrieves
 * metadata from the schema's CSV reader and outputs the first six columns
 * of the ROW_META_HDR row as table headers.
 *
 * The table structure starts with a border and includes table header
 * tags for styling. This is typically used for debugging purposes or
 * displaying schema metadata in a readable format.
 *
 * @note The method assumes there are at least six columns available
 *       in the ROW_META_HDR row of the CSV data.
 */
void password::dump()
{
    std::cout << "<table border=2><tr>";
    for (int iCol = 0; iCol < 6; iCol++)
    {
        std::cout << "<th>"
            << m_pSchema->m_pReadCsv->getData(ROW_META_HDR, iCol)
            << "</th>";
    }
    std::cout << "</tr>";
    std::cout << "</table>";
}


/**
 * Generates and returns a unique universally unique identifier (UUID).
 * The method creates a new UUID, converts it to a string representation,
 * and stores it in a global variable for further use.
 *
 * @return A string representing the generated UUID.
 */
std::string password::get_uuid()
{
    uuid_t uuid;
    char szUUID[37];
    uuid_generate(uuid);
    uuid_unparse(uuid, szUUID);
    std::string gssUUID = szUUID;
    strcpy(gszUUID, gssUUID.c_str());
    return gssUUID;
}

/**
 * Authenticates a user by verifying the provided username and password
 * against stored data. The function also sets additional session-related
 * information for the authenticated user.
 *
 * @param ssUsername The username to authenticate.
 * @param ssPassword The password to authenticate.
 * @return The row index (iRow) of the authenticated user in the stored data
 * if authentication is successful, otherwise returns EXIT_FAILURE.
 */
int password::lookup_username_password(std::string ssUsername,
                                       std::string ssPassword)
{
    gpSysLog->loginfo(__FUNCTION__);

    char szUUID[UUID_SIZE];

    int iLines = gpCsv->getLines();
    char szLogger[128];
    sprintf(szLogger, "lookup_username_password: iLines is %d", iLines);
    gpSysLog->loginfo(szLogger);

    for (int iRow = 3; iRow < iLines; iRow++)
    {
        if (0 == strcmp("true",
                        gpCsv->m_parsed_data[iRow][COL_ACTIVE].c_str()))
        {
            if (0 == strcmp(
                ssUsername.c_str(),
                gpCsv->getData(iRow, COL_PASSWD_USERNAME).c_str()))
            {
                if (0 == strcmp(
                    ssPassword.c_str(),
                    gpCsv->getData(iRow, COL_PASSWD_PASSWORD).c_str()))
                {
                    // username and password were found...
                    // fetch all passwd file values for this user
                    std::string ssActiveAcct =
                        gpCsv->m_parsed_data[iRow][COL_PASSWD_ACTIVE];
                    std::string ssUserName =
                        gpCsv->m_parsed_data[iRow][COL_PASSWD_USERNAME];
                    std::string ssFirstName =
                        gpCsv->m_parsed_data[iRow][COL_PASSWD_FIRSTNAME];
                    std::string ssLastName =
                        gpCsv->m_parsed_data[iRow][COL_PASSWD_LASTNAME];
                    std::string ssAuthLevel =
                        gpCsv->m_parsed_data[iRow][COL_PASSWD_AUTHLEVEL];
                    std::string ssDescr =
                        gpCsv->m_parsed_data[iRow][COL_PASSWD_DESCR];

                    strcpy(gpSh->m_pShMemng->creds[iRow].szHttpUserAgent,
                           gpCgi->getEnvironment().getUserAgent().c_str());

                    strcpy(gpSh->m_pShMemng->creds[iRow].szAuthUserName,
                           ssUserName.c_str());
                    strcpy(gpSh->m_pShMemng->creds[iRow].szAuthFirstName,
                           ssFirstName.c_str());
                    strcpy(gpSh->m_pShMemng->creds[iRow].szAuthLastName,
                           ssLastName.c_str());
                    strcpy(gpSh->m_pShMemng->creds[iRow].szAuthLevel,
                           ssAuthLevel.c_str());
                    std::string ssUUID = get_uuid();
                    strcpy(gpSh->m_pShMemng->creds[iRow].szAuthUUID, gszUUID);
                    gpSh->m_pShMemng->creds[iRow].iAuthHandle = iRow;
                    return iRow;
                } // if password
            } // if(username
        } // if(active
    } // for(iRow...
    return EXIT_FAILURE;
}

////////////////////////
// eof - password.cpp //
////////////////////////
