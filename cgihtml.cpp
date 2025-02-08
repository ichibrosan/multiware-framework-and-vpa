//////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/cgihtml.cpph 2025/01/27 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.   //
// This file is part of the Goodall MultiWare Framework Project.        //
//////////////////////////////////////////////////////////////////////////

#include "cgihtml.h"


/**
 *
 */
cgihtml::cgihtml()
{
}


/**
 *
 */
void cgihtml::ahref(
    const char *szURL,
    const char * szImgURL,
    int width,
    int height)
{
    std::cout << "<a href=\"" << szURL << "\">";
    imgsrc(szImgURL,width,height);
    std::cout << "</a>\n";
}


/**
 *
 */
void cgihtml::xahref(const char * pszLink,
                     const char * pszButtonClass,
                     const char * pszButtonDisplay)
{
    printf("<a href=\"%s\" class=\"%s\">%s</a>",
           pszLink,pszButtonClass,pszButtonDisplay);
}


/**
 *
 */
void cgihtml::close_body()
{
    std::cout << "</body>"  << std::endl;
}


/**
 *
 */
void cgihtml::close_form()
{
    std::cout << "</form>" << std::endl;
}


/**
 * Closes the head section of the HTML output.
 *
 * This method outputs the closing tag for the head*/
void cgihtml::close_head()
{
    std::cout << "</head>"  << std::endl;
}


/**
 * Outputs the closing HTML tag.
 *
 * This method prints the closing `</html>` tag to the standard output
 * stream to properly terminate the HTML document.
 */
void cgihtml::close_html()
{
    std::cout << "</html>" << std::endl;
}


/**
 *
 */
void cgihtml::close_table()
{
    std::cout << "</table>"  << std::endl;
}

/**
 *
 */
void cgihtml::close_div()
{
    print("</div>\n");
}


/**
 * Closes the script tag in an HTML output stream.
 *
 * This method outputs the closing </script> tag to the standard output stream,
 * ensuring proper closure of a script block in HTML documents.
 */
void cgihtml::close_script()
{
    std::cout << "</script>"  << std::endl;
}


/**
 *
 */
void cgihtml::dump_passwd()
{
    int iNumPasswdCols =
        atoi(gpCsv->getData(ROW_META_DATA,COL_META_META_COLUMNS).c_str());

    /**
     * Display the Meta section of the Password CSV
     */
    std::cout << "<h3>Password file metadata</h3>" << std::endl;

    std::cout << "<table border=2><tr>";

    /**
     * Display the Meta Headers
     */
    std::cout << "<th>Row 0</th>";
    for(int iCol=0;iCol<iNumPasswdCols;iCol++) {
        std::cout << "<th>"
                  << gpCsv->getData(ROW_META_HDR,iCol)
                  << "</th>";
    }
    std::cout << "</tr>";

    /**
     * Display the Meta data items
     */
    std::cout << "<tr><th>Row 1</th>";

    for(int iCol=0;iCol<iNumPasswdCols;iCol++) {

        std::cout << "<td>"
                  << gpCsv->getData(ROW_META_DATA,iCol)
                  << "</td>";
    }
    std::cout << "</tr>";

    std::cout << "</table>";

    /**
     * Display the Data section of the Password CSV
     */
    std::cout << "<h3>Password file data</h3>" << std::endl;

    std::cout << "<table border=2>";

    /**
     * Display the Data section headers
     */
    std::cout << "<tr>";
    std::cout << "<th>Row 2</th>";
    for(int iCol=0;iCol<iNumPasswdCols;iCol++) {
        std::cout << "<th>"
                  << gpCsv->getData(ROW_DATA_HDR,iCol)
                  << "</th>";
    }
    std::cout << "</tr>";

    /**
     * Display the Data section rows...
     */
    std::cout << "<tr>";
    int iSchemaLines = gpCsv->getLines();
    for(int iRow=3;iRow<iSchemaLines;iRow++) {
        std::cout << "<th>Row " << iRow << "</th>";
        for (int iCol = 0; iCol < iNumPasswdCols; iCol++) {
            std::cout << "<td>"
                      << gpCsv->getData(iRow, iCol)
                      << "</td>";
        }
        std::cout << "</tr>";
    }
    std::cout << "</table>";
}


/**
 *
 */
void cgihtml::dump_env_vars() {
    int iColumns = 2;
    open_table(iColumns);

    std::cout << "<tr><th>GATEWAY_INTERFACE</th><td>"
              << gpCgi->getEnvironment().getGatewayInterface();

    std::cout << "</td></tr><tr><th>SERVER_NAME</th><td>"
              << gpCgi->getEnvironment().getServerName();

    std::cout << "</td></tr><tr><th>SERVER_SOFTWARE</th><td>"
              << gpCgi->getEnvironment().getServerSoftware();

    std::cout << "</td></tr><tr><th>SERVER_PROTOCOL</th><td>"
              << gpCgi->getEnvironment().getServerProtocol();

    std::cout << "</td></tr><tr><th>SERVER_PORT</th><td>"
              << gpCgi->getEnvironment().getServerPort();

    std::cout << "</td></tr><tr><th>REQUEST_METHOD</th><td>"
              << gpCgi->getEnvironment().getRequestMethod();

    // std::cout << "</td></tr><tr><th>PATH_TRANSLATED</th><td>"
    //           << gpCgi->getEnvironment().getPathTranslated();

    std::cout << "</td></tr><tr><th>SCRIPT_NAME</th><td>"
              << gpCgi->getEnvironment().getScriptName();

    std::cout << "</td></tr><tr><th>DOCUMENT_ROOT</th><td>"
              << getenv("DOCUMENT_ROOT");

    std::cout << "</td></tr><tr><th>QUERY_STRING</th><td>"
              << gpCgi->getEnvironment().getQueryString();

    std::cout << "</td></tr><tr><th>REMOTE_HOST</th><td>"
              << gpCgi->getEnvironment().getRemoteHost();

    std::cout << "</td></tr><tr><th>REMOTE_ADDR</th><td>"
              << gpCgi->getEnvironment().getRemoteAddr();

    // std::cout << "</td></tr><tr><th>AUTH_TYPE</th><td>"
    //           << gpCgi->getEnvironment().getAuthType();

    // std::cout << "</td></tr><tr><th>REMOTE_USER</th><td>"
    //           << gpCgi->getEnvironment().getRemoteUser();

    // std::cout << "</td></tr><tr><th>REMOTE_IDENT</th><td>"
    //           << gpCgi->getEnvironment().getRemoteIdent();

    // std::cout << "</td></tr><tr><th>CONTENT_TYPE</th><td>"
    //           << gpCgi->getEnvironment().getContentType();

    // std::cout << "</td></tr><tr><th>CONTENT_LENGTH</th><td>"
    //           << gpCgi->getEnvironment().getContentLength();

    // std::cout << "</td></tr><tr><th>HTTP_FROM</th><td>"
    //           << gpCgi->getEnvironment().getHttpFrom();

    //print("</td></tr><tr><th>HTTP_ACCEPT</th><td>");
    //std::cout << gpCgi->getEnvironment().getHttpAccept();

    std::cout << "</td></tr><tr><th>HTTP_USER_AGENT</th><td>"
              << gpCgi->getEnvironment().getUserAgent();

    std::cout << "</td></tr><tr><th>HTTP_REFERER</th><td>"
              << gpCgi->getEnvironment().getReferrer();

    std::cout << "</td></tr>";
    close_table();
}


/**
 *
 */
void cgihtml::dump_referrer(
                std::string ssReferrer,
                std::string ssReferrerPath,
                std::string ssReferrerFile)
{
  std::cout << "<p><table border=2>"
            << "<tr><th>ssReferrer</th><td>"
            << ssReferrer << "</td></tr>"
            << "<tr><th>ssReferrerPath</th><td>"
            << ssReferrerPath << "</td></tr>"
            << "<tr><th>ssReferrerFile</th><td>"
            << ssReferrerFile << "</td></tr>"
            << "</table>" << std::endl;
}


/**
 *
 */
void cgihtml::dump_schema()
{
  std::cout << "<table border=2> <tr>";

  int iColumns =
      atoi(
        gpCsv->m_parsed_data[ROW_META_DATA][COL_META_META_COLUMNS].c_str());
  for (int iCol = 0; iCol < iColumns; iCol++) {
    std::cout << "<th>"
              << gpCsv->m_parsed_data[ROW_META_HDR][iCol]
              << "</th>";
  }
  std::cout << "</tr><tr>";
  for (int iCol = 0; iCol < iColumns; iCol++) {
    std::cout << "<td>"
              << gpCsv->m_parsed_data[ROW_META_DATA][iCol]
              << "</td>";
  }
  std::cout << "</tr> </table>";

  std::cout << "<table border=2> <tr>";

  for (int iCol = 0; iCol < iColumns; iCol++) {
    std::cout << "<th>"
              << gpCsv->m_parsed_data[ROW_DATA_HDR][iCol]
              << "</th>";
  }
  std::cout << "</tr>";
  for (int iRow = 3; iRow < gpCsv->getLines() - 1; iRow++) {
    std::cout << "<tr>";
    for (int iCol = 0; iCol < iColumns; iCol++) {
      std::cout << "<td>"
                << gpCsv->m_parsed_data[iRow][iCol]
                << "</td>";
    }
    std::cout << "</tr>";
  }
  std::cout << "</table>";
}


/**
 *
 */
void cgihtml::dump_shm_vars()
{
    char szTemp[BUFSIZ];

    int border=2;
    open_table(border);

    std::cout << "<tr><th>iSignature</th><td>";
    std::cout << gpSh->m_pShMemng->iSignature;
    std::cout << "</td></tr>";

    std::cout << "<tr><th>szHostName</th><td>";
    std::cout << gpSh->m_pShMemng->szHostname;
    std::cout << "</td></tr>";

    std::cout << "<tr><th>szIP</th><td>";
    std::cout << gpSh->m_pShMemng->szIP;
    std::cout << "</td></tr>";

    std::cout << "<tr><th>szIface</th><td>";
    std::cout << gpSh->m_pShMemng->szIface;
    std::cout << "</td></tr>";

    std::cout << "<tr><th>szProtocol</th><td>";
    std::cout << gpSh->m_pShMemng->szProtocol;
    std::cout << "</td></tr>";

    std::cout << "<tr><th>szImgRoot</th><td>";
    std::cout << gpSh->m_pShMemng->szImgRoot;
    std::cout << "</td></tr>";

    std::cout << "<tr><th>szCgiRoot</th><td>";
    std::cout << gpSh->m_pShMemng->szCgiRoot;
    std::cout << "</td></tr>";

    print("<tr><th>szStylesRoot</th><td>");
    print(gpSh->m_pShMemng->szStylesRoot);
    print("</td></tr>");

    print("<tr><th>szJournalRoot</th><td>");
    print(gpSh->m_pShMemng->szJournalRoot);
    print("</td></tr>");

    for (int iRow = ROW_DATA; iRow < ROW_DATA+MAX_USERS; iRow++) {
        if(gpSh->m_pShMemng->creds[iRow].iAuthHandle>2) {
            std::cout << "<tr><th>szAuthUserName</th><td>";
            std::cout << gpSh->m_pShMemng->creds[iRow].szAuthUserName;
            std::cout << "</td></tr>";

            std::cout << "<tr><th>szAuthFirstName</th><td>";
            std::cout << gpSh->m_pShMemng->creds[iRow].szAuthFirstName;
            std::cout << "</td></tr>";

            std::cout << "<tr><th>szAuthLastName</th><td>";
            std::cout << gpSh->m_pShMemng->creds[iRow].szAuthLastName;
            std::cout << "</td></tr>";

            std::cout << "<tr><th>szAuthUUID</th><td>";
            std::cout << gpSh->m_pShMemng->creds[iRow].szAuthUUID;
            std::cout << "</td></tr>";

            std::cout << "<tr><th>iAuthHandle</th><td>";
            std::cout << gpSh->m_pShMemng->creds[iRow].iAuthHandle;
            std::cout << "</td></tr>";
        }
    }

    std::cout << "<tr><th>vpad_running</th><td>";
    if(gpSh->m_pShMemng->vpad_running) {
        std::cout << "true";
    } else {
        std::cout << "false";
    }
    std::cout << "</td></tr>";

    if(gpSh->m_pShMemng->vpad_running) {

        // std::cout << "<tr><th>vpad_pid</th><td>";
        // std::cout << gpSh->m_pShMemng->vpad_pid;
        // std::cout << "</td></tr>";

        std::cout << "<tr><th>sz_vpad_start_time</th><td>";
        std::cout << gpSh->m_pShMemng->sz_vpad_start_time;
        std::cout << "</td></tr>";

        std::cout << "<tr><th>vpad_uptime_seconds</th><td>";
        std::cout << gpSh->m_pShMemng->vpad_uptime_seconds;
        std::cout << "</td></tr>";

        std::cout << "<tr><th>vpad_time</th><td>";
        std::cout << gpSh->m_pShMemng->szVpad_time;
        std::cout << "</td></tr>";

        std::cout << "<tr><th>vpad_date</th><td>";
        std::cout << gpSh->m_pShMemng->szVpad_date;

        std::cout << "</td></tr>";
    }

    std::cout << "<tr><th>szTimeStarted</th><td>";
    std::cout << gpSh->m_pShMemng->szTimeStarted;
    std::cout << "</td></tr>";

    std::cout << "<tr><th>test_processed_bits</th><td>";
    gpOS->printBinary(gpSh->m_pShMemng->tests_processed_bits,7);
    std::cout << "</td></tr>";

    std::cout << "<tr><th>test_passed_bits</th><td>";
    gpOS->printBinary(gpSh->m_pShMemng->tests_passed_bits,7);
    std::cout << "</td></tr>";

    std::cout << "<tr><th>test_failed_bits</th><td>";
    gpOS->printBinary(gpSh->m_pShMemng->tests_failed_bits,7);
    std::cout << "</td></tr>";

    std::cout << "<tr><th>test_skipped_bits</th><td>";
    gpOS->printBinary(gpSh->m_pShMemng->tests_skipped_bits,7);
    std::cout << "</td></tr>";

    std::cout << "<tr><th>num_tests_processed</th><td>";
    std::cout << gpSh->m_pShMemng->num_tests_processed;
    std::cout << "</td></tr>";

    std::cout << "<tr><th>num_tests_skipped</th><td>";
    std::cout << gpSh->m_pShMemng->num_tests_skipped;
    std::cout << "</td></tr>";

    std::cout << "<tr><th>num_tests_passed</th><td>";
    std::cout << gpSh->m_pShMemng->num_tests_passed;
    std::cout << "</td></tr>";;

    std::cout << "<tr><th>num_tests_failed</th><td>";
    std::cout << gpSh->m_pShMemng->num_tests_failed;
    std::cout << "</td></tr>";

    close_table();
}


/**
 *
 */
void cgihtml::form_date(const char *pszName,   // COL_DATE_NAME
                        const char *pszId,     // COL_DATE_ID
                        const char *pszValue,  // COL_DATE_VALUE
                        const char *pszDescr)  // COL_DATE_DESCR
{
    std::cout << "<label"
              << " for=\""   << pszId      << "\"> "
                             << pszDescr
              << "</label>";
    std::cout << "<input"
              << " type=\"date\""
              << " name=\""  << pszName   << "\""
              << " value=\"" << pszId     << "\""
              << " size=\""  << pszValue  << "\">";
}


/**
 * Generates*/
void cgihtml::form_datetime(
        const char *pszName,   // COL_DATETIME_NAME
        const char *pszId,     // COL_DATETIME_ID
        const char *pszValue,  // COL_DATETIME_VALUE
        const char *pszDescr)  // COL_DATETIME_DESCR
{
    std::cout << "<label"
              << " for=\""  << pszId      << "\"> "
                             << pszDescr
              << "</label>";
    std::cout << "<input"
              << " type=\"datetime-local\""
              << " name=\""  << pszName   << "\""
              << " value=\"" << pszId     << "\""
              << " size=\""  << pszValue  << "\">";
}


/**
 *
 */
void cgihtml::form_label(const char *pszVisible)
{
    std::cout << pszVisible << std::endl;
}


/**
 *
 */
void cgihtml::form_month(
        const char *pszName,   // COL_MONTH_NAME
        const char *pszId,     // COL_MONTH_ID
        const char *pszValue,  // COL_MONTH_VALUE
        const char *pszDescr)  // COL_MONTH_DESCR
{
    std::cout << "<label"
              << " for=\""   << pszId      << "\"> "
                             << pszDescr
              << "</label>";
    std::cout << "<input"
              << " type=\"month\""
              << " name=\""  << pszName   << "\""
              << " value=\"" << pszId     << "\""
              << " size=\""  << pszValue  << "\">";
}


/**
 * Generates an HTML text input form field*/
void cgihtml::form_text(const char * szName,
                        const char * szValue,
                        const char * szSize,
                        const char * szVisible,
                        const char * szReadonly,
                        const char * szDescr,
                        const char * szClass)
{
    std::string ssValue = szValue;

    if (0 == std::strncmp("from:", szValue, strlen("from:")))
    {
        ssValue = gpCgiBind->get_form_variable(
                ssValue.substr(ssValue.find(':') + 1));
    }
    std::cout << szVisible
              << "<input type=\"text\""
              << " name=\""  << szName  << "\""
              << " value=\"" << ssValue << "\""
              << " size=\""  << szSize  << "\""
              << " class=\""  << szClass  << "\""
              << szReadonly << ">";
}


/**
 *
 */
void cgihtml::form_text(const char * szName,
                        const char * szID,
                        const char * szValue,
                        const char * szSize,
                        const char * szVisible,
                        const char * szReadonly,
                        const char * szDescr,
                        const char * szClass)
{
    std::string ssValue = szValue;
    if (0 == std::strncmp("from:", szValue, strlen("from:")))
    {
        ssValue = gpCgiBind->get_form_variable(
                ssValue.substr(ssValue.find(':') + 1));
    }
    std::cout << szVisible
              << "<input type=\"text\""
              << " name=\""  << szName  << "\""
              << " id=\""  << szID  << "\""
              << " value=\"" << ssValue << "\""
              << " size=\""  << szSize  << "\""
              << " class=\""  << szClass  << "\""
              << szReadonly << ">";
}


/**
 * Renders a password input form element with an*/
void cgihtml::form_password(
        const char *pszName,        // COL_PASSWORD_NAME
        const char *pszId,          // COL_PASSWORD_ID
        const char *pszValue,       // COL_PASSWORD_VALUE
        const char *pszSize,        // COL_PASSWORD_SIZE
        const char *pszVisible,     // COL_PASSWORD_VISIBLE
        const char *pszDescr)       // COL_PASSWORD_DESCR
{
    char szTemp[BUFSIZ];
    sprintf(szTemp,
            "<label for=\"%s\">%s</label>"
            "<input type=\"password\" id=\"%s\" name=\"%s\""
            " size=\"%s\""
            "placeholder=\"%s\" required>",
            pszId,pszVisible,pszId,pszName,pszSize,pszDescr);
    std::cout << szTemp << std::endl;
}


/**
 *
 */
void cgihtml::form_select(
        const char * pszSelectName,
        std::vector<std::string> selectValues,
        const char * pszSelectClass)
{
    std::cout << "<select name=\"" << pszSelectName << "\""
              << "class =\"" << pszSelectClass << "\">";;
    for (const auto & option : selectValues)
    {
        std::string ssPureOption = gpOS->file2filename(option.c_str());

        std::cout << "<option value=\"" << ssPureOption << "\""
                  << ">" << ssPureOption << "</option>";
    }
    std::cout << "</select>";
}


/**
 *
 */
void cgihtml::form_files_select(
        const char * pszSelectName,
        const char * pszSelectPath,
        const char * pszSelectClass)
{
    std::vector<std::string> selectValues;

    if (0 == strcmp("default",pszSelectPath)) {
        selectValues =
            gpOS->allfilesindir(gpEnv->get_journal_root(false));
    } else {
        selectValues =
            gpOS->allfilesindir(pszSelectPath);
    }

    form_select(pszSelectName,selectValues,pszSelectClass);
}


/**
 * Creates and outputs an HTML checkbox input element.
 *
 * This method generates a checkbox with the specified properties and renders it
 * along with its associated visible label. The checkbox will be marked as checked
 **/
void cgihtml::form_postcheckbox(
        const char *pszName,
        const char *pszId,
        const char *pszValue,
        const char *pszVisible)
{
    char szBuffer[BUFSIZ];
    char szChecked[16];
    if(0 == strcmp("true",pszValue)) {
        strcpy(szChecked,"Checked");
    } else {
        strcpy(szChecked,"");
    }
    std::cout << pszVisible << " "
              << "<input type=\"checkbox\""
              << " name=\"" << pszName << "\""
              << " id=\""   << pszId   << "\""
              << " "        << szChecked
              << "> "       << std::endl;
}


/**
 *
 */
void cgihtml::form_precheckbox(
        const char *pszName,
        const char *pszId,
        const char *pszValue,
        const char *pszVisible)
{
    char szBuffer[BUFSIZ];
    char szChecked[16];
    if(0 == strcmp("true",pszValue)) {
        strcpy(szChecked,"Checked");
    } else {
        strcpy(szChecked,"");
    }
    std::cout << "<input type=\"checkbox\""
              << " name=\"" << pszName << "\""
              << " id=\""   << pszId   << "\""
              << " "        << szChecked
              << "> "       << pszVisible
              << std::endl;
}


/**
 *
 */
void cgihtml::form_reset()
{
    std::cout << "<input type=\"reset\" value=\"Reset\">";
}


/**
 *
 */
void cgihtml::form_submit()
{
    gpLog->writev("%s: %s() started",__FILE__,__FUNCTION__);
    print("      <input type=\"submit\" value=\"Submit\">");
}


/**
 * Generates and outputs an HTML text input field with an associated label.
 *
 * This method creates an HTML text input field along with a visible label
 * and writes the generated HTML to the standard output.
 *
 * @param szName The name attribute of the input field.
 * @param szId The id attribute of the input field and the label's "for" attribute.
 * @param szValue Placeholder*/
void cgihtml::form_text(const char * szName,
                        const char * szId,
                        const char * szValue,
                        const char * szSize,
                        const char * szVisible,
                        const char * szDescr)
{
    char szTemp[BUFSIZ];
    sprintf(szTemp,
            "<label for=\"%s\">%s</label>"
            "<input type=\"text\" id=\"%s\" name=\"%s\""
            " size=\"%s\""
            "placeholder=\"%s\" required>",
            szId,szVisible,szId,szName,szSize,szDescr);
    std::cout << szTemp << std::endl;
}


/**
 * Generates and outputs an HTML <textarea> element with the specified attributes.
 *
 * The function constructs a <textarea> element using the provided parameters for
 * attributes such as name, ID, dimensions, wrapping behavior, CSS class, and initial value.
 * If the initial value starts with "from:", it retrieves the variable's value
 * using cgi binding.
 *
 * @param pszName The name attribute of the*/
void cgihtml::form_textarea(const char *pszName,
                            const char *pszID,
                            const char *pszCols,
                            const char *pszRows,
                            const char *pszWrap,
                            const char *pszClass,
                            const char * pszValue)
{
    gpLog->writev("%s: %s() started",__FILE__,__FUNCTION__);

    std::string ssValue = pszValue;
    if (0 == std::strncmp("from:", pszValue, strlen("from:")))
    {
        ssValue = gpCgiBind->get_form_variable(
                ssValue.substr(ssValue.find(':') + 1));
    }

    std::cout << "<textarea "
              << "name=\"" << pszName << "\" "
              << "id=\"" << pszID << "\" "
              << "cols=\"" << pszCols << "\" "
              << "rows=\"" << pszRows << "\" "
              << "wrap=\"" << pszWrap << "\""
              << "class=\""<< pszClass << "\""
              << ">" << ssValue << "</textarea>"
              << std::endl;
}


/**
 * Generates an HTML form input element of type "*/
void cgihtml::form_time(const char *pszName,   // COL_TIME_NAME
                        const char *pszId,     // COL_TIME_ID
                        const char *pszValue,  // COL_TIME_VALUE
                        const char *pszDescr)  // COL_TIME_DESCR
{
    std::cout << "<label"
              << " for=\""   << pszId      << "\"> "
                             << pszDescr
              << "</label>";
    std::cout << "<input"
              << " type=\"time\""
              << " name=\""  << pszName   << "\""
              << " value=\"" << pszId     << "\""
              << " size=\""  << pszValue  << "\">";
}

// Marcus Franklin 15:02 1-26-2025
/**
 * Generates and outputs an HTML iframe element with the specified attributes.
 *
 * @param pszIframeDefaultPage The*/
void cgihtml::form_iframe(const char * pszIframeDefaultPage,
                          const char * pszIframeTitle,
                          const char * pszIframeName,
                          const char * pszIframeClass,
                          int          i_IframeWidth,
                          int          i_IframeHeight)
{
    gpLog->writev("%s: %s() started",__FILE__,__FUNCTION__);
    printf("<iframe src=\"%s\" title=\"%s\" name=\"%s\" class=\"%s\" "
                 "width=%d height=%d></iframe>",
                 pszIframeDefaultPage,
                 pszIframeTitle,
                 pszIframeName,
                 pszIframeClass,
                 i_IframeWidth,
                 i_IframeHeight);
}

/**
 *
 */
void cgihtml::form_week(const char *pszName,   // COL_WEEK_NAME
                        const char *pszId,     // COL_WEEK_ID
                        const char *pszValue,  // COL_WEEK_VALUE
                        const char *pszDescr)  // COL_WEEK_DESCR
{
    std::cout << "<label"
              << " for=\""   << pszId      << "\"> "
                             << pszDescr
              << "</label>";
    std::cout << "<input"
              << " type=\"week\""
              << " name=\""  << pszName   << "\""
              << " value=\"" << pszId     << "\""
              << " size=\""  << pszValue  << "\">";
}


/**
 *
 */
void cgihtml::form_button(const char * pszType,
                          const char * pszForm,
                          const char * pszButtonClass,
                          const char * pszButtonDisplay)
{
    printf("<button type=\"%s\" form=\"%s\" class=\"%s\">%s</button>",
                 pszType,pszForm,pszButtonClass,pszButtonDisplay);
}


/**
 *
 */
void cgihtml::hidden(const char * pszName,const char *pszValue)
{
    // char szBuffer[BUFSIZ];
    // sprintf(szBuffer,"<input type=hidden name=\"%s\" value=\"%s\">\n",
    //         pszName,pszValue);
    // print(szBuffer);

    std::cout << "<input type=\"hidden\" name=\"";
    std::cout << pszName << "\" value=\"";
    std::cout << pszValue << "\" />";
}


/**
 *
 */
void cgihtml::imgsrc(const char *pszImageFN,int width,int height)
{
    std::string ssImgFQFS = gpSh->m_pShMemng->szImgRoot;
    ssImgFQFS.append(pszImageFN);

    CLog log(__FILE__,__FUNCTION__);
    log.writev("%s: %s() started",__FILE__,__FUNCTION__);
    char szTag[FILENAME_MAX];
    log.namedString("std::string ssImgFQFS = gpSh->m_pShMemng->szImgRoot;\n"
                    "ssImgFQFS.append(pszImageFN);",
                       ssImgFQFS.c_str());

    sprintf(szTag,"    <img "
                  "src=\"%s\" "
                  "width=\"%d\" "
                  "height=\"%d\">\n",
            ssImgFQFS.c_str(),
            width,height);
    print(szTag);
}


/**
 *
 */
void cgihtml::open_body()
{
    std::cout << "<body>";
}


/**
 *
 */
void cgihtml::open_form(    const char * pszSchemaName,
                            const char * pszCgiFilename,
                            const char * pszProt,
                            int          handle,
                            const char * pszID,
                            const char * pszTarget)
{

    char szTag[FILENAME_MAX];
    sprintf(szTag,"    <form action=\"%s\" method=\"%s\""
                        "id=\"%s\" target=\"%s\">\n",
            pszCgiFilename,pszProt,pszID,pszTarget);
    print(szTag);
    char szValue[8];
}


/**
 *
 */
void cgihtml::open_head()
{
    std::cout << "<head>";
}


/**
 * @brief Outputs the opening <html> tag*/
void cgihtml::open_html()
{
    std::cout << "<html>";
}


/**
 * Opens a script block in HTML output.
 *
 * This method writes the opening `<script>` tag to the standard output.
 */
void cgihtml::open_script()
{
    std::cout << "<script>";
}


/**
 *
 */
void cgihtml::open_div(const char * pszDivClass)
{
    gpLog->writev("%s: %s() started",__FILE__,__FUNCTION__);
    printf("<div class=\"%s\">",pszDivClass);
}


/**
 * @brief*/
void cgihtml::para()
{
    std::cout << "<p>";
}


/**
 * Outputs the provided text to the*/
void cgihtml::print(const char *szText)
{
    std::cout << szText;
}


/**
 *
 */
void cgihtml::printv(const char *pszFormat,...)
{
    char szFormat[BUFSIZ];
    strcat(szFormat,pszFormat);

    char szFinal[BUFSIZ];
    va_list args;
    va_start (args, pszFormat);
    vsprintf(szFinal, szFormat,args);
    va_end (args);

    std::cout << szFinal;
}


/**
 * Prints the specified variable name along with its boolean value as a message.
 *
 * Formats a message indicating whether the given variable is true or false
 * and outputs it using the print method.
 *
 * @param pszName The name of the variable to be printed.
 * @param bValue The boolean value of the variable. If true, the message indicates the variable is true; otherwise, false.
 */
void cgihtml::printvar(const char *pszName,bool bValue)
{
    gpLog->writev("%s: %s() started",__FILE__,__FUNCTION__);
    char szBuffer[BUFSIZ];
    if(bValue) {
        sprintf(szBuffer,"%s is true",pszName);
    } else {
        sprintf(szBuffer,"%s is false",pszName);
    }
    print(szBuffer);
}


/**
 * Prints a variable name and its corresponding value to the standard output.
 *
 * This method outputs the given name and value pair in the format "name = value".
 *
 * @param pszName The name of the variable to be printed.
 * @param pszValue The value of the variable to be printed.
 */
void cgihtml::printvar(const char *pszName,const char *pszValue)
{
    std::cout << pszName << " = " << pszValue << std::endl;
}


/**
 * Outputs a variable name and its integer value in the format "name = value*/
void cgihtml::printvar(const char *pszName,int iValue)
{
    std::cout << pszName << " = " << iValue << std::endl;
}


/**
 * Prints the name and corresponding double value to the output stream.
 *
 * @param pszName The name or label to be displayed.
 * @param dValue The double value to be printed alongside the name.
 */
void cgihtml::printvar(const char *pszName,double dValue)
{
    std::cout << pszName << " = " << dValue << std::endl;
}


/**
 * Opens an HTML table with the specified border size.
 *
 * @param border The size of the border for the HTML table.
 */
void cgihtml::open_table(int border)
{
    std::cout << "<table "
              << "border=\"" << border << "\""
              << ">";
}


/**
 *
 */
void cgihtml::script_button(const char * pszButtonName,
                            const char * pszVisible)
{
    printf("      function my%sButton() {\n",pszButtonName);
    print("        var x = document.createElement(\"INPUT\");\n");
    print("        x.setAttribute(\"type\",\"button\");\n");
    printf("        x.setAttribute(\"value\",\"%s\");\n",pszVisible);
    print("        document.body.appendChild(x);\n");
    print("      }\n");
}


/**
 * Sets the stylesheet for the cgihtml object.
 *
 * This method generates a link to the specified stylesheet and outputs it in*/
void cgihtml::set_style(const char * pszStylesheet)
{
    gpLog->writev("%s: %s() started",__FILE__,__FUNCTION__);
    printf("<link rel=\"stylesheet\" href=\"%s%s.css\"/>",
           gpEnv->get_styles_root(false).c_str(),
           pszStylesheet);
}


/**
 */
void cgihtml::title(const char * szTitle)
{
    std::cout << "<title>" << szTitle << "</title>" << std::endl;
}

///////////////////////
// eof - cgihtml.cpp //
///////////////////////