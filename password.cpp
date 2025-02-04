//
// Created by doug on 1/16/25.
//
#include "password.h"

std::string gssUUID;
char gszUUID[37];


password::password()
{
    CLog log(__FILE__,__FUNCTION__);

    m_pSchema = new schema("passwd.csv");
    m_iLines  = m_pSchema->getLines();
    log.namedInt("m_iLines",m_iLines);
}


/**
 *
 * @param ssUserName
 * @param ssPasssword
 * @return Return -1 for failure or 0-n for passwd handle
 */
int lookup(std::string ssUserName,std::string ssPasssword)
{
    return -1;
}


/*****************************************************
 * Display the contents of the passwd database as HTML
 *****************************************************/
void password::dump()
{
    std::cout << "<table border=2><tr>";
    for(int iCol=0;iCol<6;iCol++) {
        std::cout << "<th>"
                  << m_pSchema->m_pReadCsv->getData(ROW_META_HDR,iCol)
                  << "</th>";
    }
    std::cout << "</tr>";
    std::cout << "</table>";
}


/***************************************************************
 * Generate a UUID abd return as a standard string
 * @return Returns a standard string containing a generated UUID
 ***************************************************************/
std::string password::get_uuid()
{
    uuid_t uuid;
    char szUUID[37 ];
    uuid_generate(uuid);
    uuid_unparse(uuid,szUUID);
    std::string gssUUID = szUUID;
    strcpy(gszUUID,gssUUID.c_str());
    return gssUUID;
}

int password::lookup_username_password( std::string ssUsername,
                                        std::string ssPassword)
{
    char szUUID[UUID_SIZE];

    int iLines = gpCsv->getLines();
    for(int iRow=3;iRow<iLines;iRow++) {
        if (0 == strcmp("true",
                        gpCsv->m_parsed_data[iRow][COL_ACTIVE].c_str())) {
            if( 0 == strcmp(
                        ssUsername.c_str(),
                        gpCsv->getData(iRow,COL_PASSWD_USERNAME).c_str())) {
                if(0 == strcmp(
                          ssPassword.c_str(),
                          gpCsv->getData(iRow,COL_PASSWD_PASSWORD).c_str())) {
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

                    // std::cout << "<H3>Welcome<i> "
                    //           << ssFirstName
                    //           << " "
                    //           << ssLastName
                    //           << " as <b>"
                    //           << ssAuthLevel
                    //           << " and "
                    //           << ssDescr
                    //           << "</b></i></h3>";

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
                    strcpy(gpSh->m_pShMemng->creds[iRow].szAuthUUID,gszUUID);
                    gpSh->m_pShMemng->creds[iRow].iAuthHandle = iRow;
                    return iRow;
                               } // if password
                            } // if(username
                        } // if(active
    } // for(iRow...
    return EXIT_FAILURE;
}
