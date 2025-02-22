////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/cgihtml.cpph 2025/02/19                  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
// This file is part of the Goodall MultiWare Framework Project.      //
////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * This is the constructor for the cgihtml class
 */
cgihtml::cgihtml()
{
}


/*******************************************************************************
 * Generates an HTML anchor tag (<a>) with an embedded image.
 *
 * This method creates an anchor tag pointing to the specified URL and includes
 * an image element inside the anchor. The image is defined with its source URL,
 * width, and height.
 *
 * @param szURL The URL to be used in the href attribute of the anchor tag.
 * @param szImgURL The URL of the image to be used within the anchor tag.
 * @param width The width of the image.
 * @param height The height of the image.
 *******************************************************************************/
void cgihtml::ahref(
    const char *szURL,
    const char * szImgURL,
    int width,
    int height)
{
    std::cout << "<a href=\"" << szURL << "\">";
    imgsrc(szImgURL,width,height);
    std::cout << "</a>" << std::endl;
}


/*****************************************************************************************************************
 * Generates an HTML anchor tag with specified attributes.
 *
 * This method creates an anchor tag (<a>) with the given hyperlink reference,
 * CSS class, and display text, and prints it to the standard output.
 *
 * @param pszLink Pointer to a null-terminated string containing the URL for the anchor tag.
 * @param pszButtonClass Pointer to a null-terminated string containing the CSS class for styling the anchor tag.
 * @param pszButtonDisplay Pointer to a null-terminated string containing the display text for the anchor tag.
 *****************************************************************************************************************/
void cgihtml::xahref(const char * pszLink,
                     const char * pszButtonClass,
                     const char * pszButtonDisplay)
{
    printf("<a href=\"%s\" class=\"%s\">%s</a>\n",
           pszLink,pszButtonClass,pszButtonDisplay);
}


/****************************************************************************
 * Closes the body tag in an HTML output stream.
 *
 * This method outputs the closing </body> tag to the standard output stream,
 * ensuring proper closure of the body section in HTML documents.
 ****************************************************************************/
void cgihtml::close_body()
{
    std::cout << "</body>"  << std::endl;
}


/***************************************************************************
 * Closes an HTML form tag in an output stream.
 *
 * This method writes the closing </form> tag to the standard output stream,
 * ensuring proper termination of an HTML form.
 ***************************************************************************/
void cgihtml::close_form()
{
    std::cout << "</form>" << std::endl;
}


/***************************************************************************
 * Closes the head tag in an HTML output stream.
 *
 * This method outputs the closing </head> tag to the standard output stream,
 * ensuring proper closure of the head section in an HTML document.
 ***************************************************************************/
void cgihtml::close_head()
{
    std::cout << "</head>"  << std::endl;
}


/*************************************************************************
 * @brief Closes an HTML document by outputting the closing `</html>` tag.
 *
 * This method is used to terminate an HTML document by writing the
 * closing HTML tag to the standard output stream.
 *************************************************************************/
void cgihtml::close_html()
{
    std::cout << "</html>" << std::endl;
}


/*************************************************************************
 * @brief Closes an HTML table by outputting the closing table
 *************************************************************************/
void cgihtml::close_table()
{
    std::cout << "</table>"  << std::endl;
}


/***************************************************************************
 * @brief Closes an open HTML div element by printing the closing div tag.
 *
 * This method outputs the closing </div> tag along with a newline character
 * to properly terminate an open HTML <div> element in the generated content.
 ***************************************************************************/
void cgihtml::close_div()
{
    print("</div>\n");
}


/**
 *
 */
void cgihtml::close_script()
{
    std::cout << "</script>"  << std::endl;
}


/**
 * Outputs the password file metadata and data in HTML table format.
 *
 * This method is responsible for displaying the metadata and data content
 * of a password CSV file. It generates HTML tables with proper headers and rows
 * for both the metadata and data sections of the file. The method extracts the
 * information from a predefined CSV object `gpCsv` and formats it accordingly.
 *
 * - The metadata section contains two rows:
 *   - The header row showing column names from the metadata header.
 *   - The data row showing corresponding metadata values.
 *
 * - The data section contains:
 *   - A header row that displays the column names of the data.
 *   - Multiple data rows where each cell contains data values extracted from the CSV.
 *
 * The output is generated using standard output streams and includes
 * HTML elements such as table tags, headers, and data cells to create structured
 * tables for visualization.
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
 * Outputs a table of CGI environment variables to the standard output stream.
 *
 * This method generates an HTML table displaying various CGI environment
 * variables and their values. These include server details, request
 * information, and other relevant data retrieved from the CGI environment.
 *
 * Only the selected environment variables are included in the output.
 * Unused variables are commented out within the implementation.
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
 * Outputs detailed information about the referrer in an HTML table format.
 *
 * This method displays the provided referrer details, including the referrer,
 * its path, and its filename, in an organized HTML table structure
 * to the standard output stream.
 *
 * @param ssReferrer The full referrer string to be displayed.
 * @param ssReferrerPath The path portion of the referrer.
 * @param ssReferrerFile The file portion of the referrer.
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
 * Generates HTML tables representing the schema and data from a CSV file.
 *
 * This method outputs two distinct HTML tables to the standard output stream:
 * 1. A table displaying the metadata and schema definition, including column headers
 *    and associated metadata values.
 * 2. A table displaying the actual data rows from the CSV file, including
 *    headers and row-wise data values.
 *
 * Each table is formatted with a border for readability. The method processes
 * the parsed CSV data, extracting metadata, headers, and row data to
 * construct the respective tables.
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
 * Outputs shared memory variables and associated metadata as an HTML table.
 *
 * This method retrieves various shared memory variables from the global shared
 * memory structure and outputs them to the standard output stream wrapped in
 * an HTML table format. Data includes configurations, user credentials, state
 * information, testing statistics, and other related variables. The method
 * follows a structured format with headings and corresponding data for
 * readability.
 *
 * The method dynamically iterates through specific arrays within the shared
 * memory to output user credential details conditionally if their authentication
 * handle value is greater than a defined threshold. Additionally, it provides
 * structured output of test statistics and optional state values based on the
 * runtime state of specific flags.
 *
 * Assumes the presence of globally accessible shared memory (`gpSh`) and
 * supporting utility functions like `open_table`, `close_table`, and `print`.
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

    std::cout << "<tr><th>szPublicIP</th><td>";
    std::cout << gpSh->m_pShMemng->szPublicIP;
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

    print("<tr><th>szTmpRoot</th><td>");
    print(gpSh->m_pShMemng->szTmpRoot);
    print("</td></tr>");

    print("<tr><th>szJournalRoot</th><td>");
    print(gpSh->m_pShMemng->szJournalRoot);
    print("</td></tr>");

    print("<tr><th>szUser</th><td>");
    print(gpSh->m_pShMemng->szUser);
    print("</td></tr>");

    print("<tr><th>szRpcUuid</th><td>");
    print(gpSh->m_pShMemng->szRpcUuid);
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
    printf(" 0x%02x",gpSh->m_pShMemng->tests_processed_bits);
    std::cout << "</td></tr>";

    std::cout << "<tr><th>test_passed_bits</th><td>";
    gpOS->printBinary(gpSh->m_pShMemng->tests_passed_bits,7);
    printf(" 0x%02x",gpSh->m_pShMemng->tests_passed_bits);
    std::cout << "</td></tr>";

    std::cout << "<tr><th>test_failed_bits</th><td>";
    gpOS->printBinary(gpSh->m_pShMemng->tests_failed_bits,7);
    printf(" 0x%02x",gpSh->m_pShMemng->tests_failed_bits);
    std::cout << "</td></tr>";

    std::cout << "<tr><th>test_skipped_bits</th><td>";
    gpOS->printBinary(gpSh->m_pShMemng->tests_skipped_bits,7);
    printf(" 0x%02x",gpSh->m_pShMemng->tests_skipped_bits);
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
 * Generates an HTML form field for selecting a date.
 *
 * This method outputs the HTML markup for a `<label>` element and a `<input>`
 * element of type "date", used to allow date selection in an HTML form.
 *
 * @param pszName The name attribute of the date input element.
 * @param pszId The id attribute of the date input element, also referenced by the label element.
 * @param pszValue The value attribute of the date input element.
 * @param pszDescr The description used as the content of the label element.
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
 * Generates an HTML datetime input field with an associated label.
 *
 * This method creates a label and a datetime-local input field. The label is
 * bound to the input field via the `for` attribute, and the input field is
 * customized with the provided parameters.
 *
 * @param pszName The name attribute of the input field.
 * @param pszId The id attribute of the input field and the value used in the `for` attribute of the label.
 * @param pszValue The value attribute of the input field.
 * @param pszDescr The descriptive text for the label.
 */
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
 * Emit a form tag
 */
void cgihtml::form_label(const char *pszVisible)
{
    std::cout << pszVisible << std::endl;
}


/**
 * Generates HTML for a form input of type "month" including a label.
 *
 * @param pszName The name attribute for the input element.
 * @param pszId The id attribute for the input element and for the label's "for" attribute.
 * @param pszValue The value attribute for the input element.
 * @param pszDescr The text content for the label element.
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
 * Generates a label and a select HTML element with specified attributes.
 *
 * @param pszLabelFor The value for the "for" attribute of the label.
 *                      This links the label to the select element.
 * @param pszLabelVisible The text content to display for the label.
 * @param pszSelectID The value for the "id" attribute of the select element.
 * @param pszSelectName The value for the "name" attribute of the select
 *                      element.
 */
void cgihtml::form_select(		const char * pszLabelFor,
                         const char * pszLabelVisible,
                         const char * pszSelectID,
                         const char * pszSelectName)
{

    /*  <label for="fruits">Choose a fruit:</label>       <<<<<
        <select id="fruits" name="fruits">                <<<<<
            <option value="apple">Apple</option>
            <option value="banana">Banana</option>
            <option value="cherry">Cherry</option>
        </select>
     */

    std::cout << "<label for=\""
              << pszLabelFor
              << "\">"
              << pszLabelVisible
              << "</label>"
              << std::endl;

    std::cout << "<select id=\""
              << pszSelectID
              << "\""
              << " name=\""
              << pszSelectName
              << "\">"
              << std::endl;
}

/**
 * Generates an HTML `<option>` tag with the specified value and visible text.
 *
 * @param pszOptionValue The value attribute of the `<option>` element.
 * @param pszOptionVisible The visible text to display for the `<option>` element.
 */
void cgihtml::form_select_opt(	const char * pszOptionValue,
                         const char * pszOptionVisible)
{

    /*
        <label for="fruits">Choose a fruit:</label>
        <select id="fruits" name="fruits">
            <option value="apple">Apple</option>        <<<<<
            <option value="banana">Banana</option>
            <option value="cherry">Cherry</option>
        </select>
    */

    std::cout << "<option value=\""
              << pszOptionValue
              << "\">"
              << pszOptionVisible
              << "</option>"
              << std::endl;
}

/**
 * Completes an HTML select element by adding the closing tag.
 */
void cgihtml::form_select_end()
{
    /*
        <label for="fruits">Choose a fruit:</label>
        <select id="fruits" name="fruits">
            <option value="apple">Apple</option>
            <option value="banana">Banana</option>
            <option value="cherry">Cherry</option>
        </select>                                       <<<<<
    */

    std::cout << "</select>"
              << std::endl;
}

/**
 * @brief Generates an HTML input text field with specified attributes.
 *
 * This function creates an HTML input element of type "text" with the given
 * attributes and writes it to the standard output.
 * If the value starts with "from:", it is resolved by retrieving the form
 * variable value using the bound CGI object.
 *
 * @param szName The name attribute of the input field.
 * @param szValue The value attribute for the field. If it starts with "from:",
 * the actual value is retrieved dynamically.
 * @param szSize The size attribute defining the visible width of the input field.
 * @param szVisible Determines the visibility or additional presentation of the
 * input field.
 * @param szReadonly The readonly attribute specifies if the field is read-only.
 * @param szDescr A description or additional commentary related to the field.
 * @param szClass Specifies the CSS class attribute for styling the input field.
 */
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
 * Generates an HTML text input element.
 *
 * This method creates an HTML text input field with the specified attributes
 * and outputs it to the standard output stream. If the value starts with
 * "from:", it retrieves the actual value from a form variable binding.
 *
 * @param szName The name attribute of the input field.
 * @param szID The id attribute of the input field.
 * @param szValue The initial value of the input field, or a form variable reference if prefixed with "from:".
 * @param szSize The size attribute of the input field.
 * @param szVisible Additional visibility control for the input field's HTML output.
 * @param szReadonly Specifies if the input field is readonly.
 * @param szDescr A description or additional information for the input field.
 * @param szClass The CSS class attribute of the input field.
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
 * Generates and outputs an HTML password input field.
 *
 * This function constructs an HTML password input element with an associated label
 * based on the specified parameters. It will output the generated HTML structure
 * to the standard output.
 *
 * @param pszName The 'name' attribute of the HTML input element.
 * @param pszId The 'id' attribute of the HTML input element and the value of the 'for' attribute in the label element.
 * @param pszValue The default value for the input field. Currently, it is unused in this implementation.
 * @param pszSize The 'size' attribute of the HTML input element, which controls the width of the input field.
 * @param pszVisible The text for the label associated with the password input field.
 * @param pszDescr The placeholder text for the input field, describing the expected input.
 */
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
 * Generates an HTML select element with the provided name, options, and class.
 *
 * @param pszSelectName Name attribute for the select HTML element.
 * @param selectValues Vector containing the option values for the select element.
 * @param pszSelectClass Class attribute for the select HTML element.
 */
void cgihtml::form_select_array(
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
                  << ">" << ssPureOption << "</option>" << std::endl;
    }
    std::cout << "</select>";
}


/**
 * Generates and populates a dropdown (select) input element with file options.
 *
 * This method retrieves a list of files from the specified directory path
 * or from the default journal directory if "default" is specified, and
 * populates a dropdown menu with these files.
 *
 * @param pszSelectName The name attribute for the select element.
 * @param pszSelectPath The path from which to load the list of files. If "default"
 *                      is provided, files from the default journal directory will be used.
 * @param pszSelectClass The class attribute for the select element, defining its styling.
 */
void cgihtml::form_select_files(
        const char * pszSelectName,
        const char * pszSelectPath,
        const char * pszSelectClass)
{
    here;
    std::vector<std::string> selectValues;
here;
    if (0 == strcmp("default",pszSelectPath)) {
here;
        selectValues =
            gpOS->allfilesindir(gpEnv->get_journal_root(false));
    } else {
        here;
        selectValues =
            gpOS->allfilesindir(pszSelectPath);
    }
here;
    form_select_array(pszSelectName,selectValues,pszSelectClass);
    here;
}


/**
 * Generates an HTML checkbox input element with specified attributes and writes it to the standard output.
 *
 * @param pszName The name attribute of the checkbox input element.
 * @param pszId The id attribute of the checkbox input element.
 * @param pszValue A string indicating whether the checkbox should be checked. If the value is "true", the checkbox is marked as checked.
 * @param pszVisible The visible text displayed alongside the checkbox element.
 */
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
 * Generates and outputs an HTML checkbox element with specified attributes.
 *
 * @param pszName The name attribute of the checkbox.
 * @param pszId The id attribute of the checkbox.
 * @param pszValue The value indicating whether the checkbox should be checked. If "true", the checkbox will be checked, otherwise it will be unchecked.
 * @param pszVisible The visible label displayed next to the checkbox.
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
 * Outputs a reset button as an HTML input element.
 *
 * This method writes an HTML `<input type="reset">` element to standard output,
 * allowing users to reset form fields to their initial values.
 */
void cgihtml::form_reset()
{
    std::cout << "<input type=\"reset\" value=\"Reset\">";
}


/**
 */
void cgihtml::form_submit()
{
    gpLog->writev("%s: %s() started",__FILE__,__FUNCTION__);
    print("      <input type=\"submit\" value=\"Submit\">");
}


/**
 * Generates an HTML text input element along with a label and outputs it to the standard output stream.
 *
 * The method creates an HTML form element consisting of a label and a text input field.
 * The label is associated with the input field through the "for" attribute, and the input
 * field contains several customizable attributes such as id, name, size, placeholder, and visibility.
 *
 * @param szName The name attribute for the input field.
 * @param szId The id attribute for the input field and the "for" attribute for the label.
 * @param szValue The value attribute for the input field (currently unused).
 * @param szSize The size attribute specifying the width of the input field.
 * @param szVisible The text to display in the label for the input field.
 * @param szDescr The placeholder text that gives input guidance in the input field.
 */
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
 * Generates and outputs an HTML `<textarea>` element with the provided attributes.
 * It dynamically resolves the value of the `<textarea>` if the `pszValue`
 * string starts with "from:", by using the `gpCgiBind` object to fetch the associated variable.
 *
 * @param*/
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
 * @brief Generates an HTML form field for a time input.
 *
 * This function creates and outputs an HTML label and input element with type="time".
 * It uses the provided parameters for the input field's name, ID, value, and label description.
 *
 * @param pszName The name attribute of the time input element.
 * @param pszId The ID attribute to associate the input element with its label.
 * @param pszValue The value attribute of the time input field.
 * @param pszDescr The description for the input element, displayed as a label.
 */
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
 * Generates an HTML iframe element with specified attributes and outputs it to the standard output.
 *
 * @param pszIframeDefaultPage The default URL or page that the iframe will load as its source.
 * @param pszIframeTitle       The title attribute of the iframe, which provides additional information about the iframe's content.
 * @param pszIframeName        The name attribute of the iframe, used for targeting in forms or scripts.
 * @param pszIframeClass       The class attribute of the iframe, used for styling purposes.
 * @param i_IframeWidth        The width of the iframe in pixels.
 * @param i_IframeHeight       The height of the iframe in pixels.
 */
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
 * @brief Generates an HTML week input field with an associated label element.
 *
 * This function creates a `<label>` element associated with the given input
 * field, followed by an `<input>` element of type "week". The label uses the
 * `pszDescr` parameter as its display text, and the input field is configured
 * with the specified attributes.
 *
 * @param pszName The name attribute for the HTML input element.
 * @param pszId The id attribute for the HTML input element, also used by the label's for attribute.
 * @param pszValue The value attribute for the HTML input element.
 * @param pszDescr The descriptive text for the HTML label element.
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
 * Generates an HTML button element with the specified attributes and displays it.
 *
 * @param pszType The type attribute of the button element (e.g., "submit", "reset", "button").
 * @param pszForm The ID of the form to which the button is associated.
 * @param pszButtonClass The class attribute for styling the button.
 * @param pszButtonDisplay The display text or content of the button.
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
 * Generates and outputs an HTML `<img>` tag with the specified image file name, width, and height.
 *
 * @param pszImageFN The file name of the image to be included in the `<img>` tag.
 * @param width The width of the image as it should appear in the HTML.
 * @param height The height of the image as it should appear in the HTML.
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
                  "height=\"%d\">",
            ssImgFQFS.c_str(),
            width,height);
    print(szTag);
}


/**
 * Opens the HTML body section.
 *
 * This method outputs the opening `<body*/
void cgihtml::open_body()
{
    std::cout << "<body>";
}


/**
 * Opens and initializes an HTML form by generating and printing the associated HTML form tag.
 *
 * @param pszSchemaName Specifies the schema name. This parameter is currently unused in the method.
 * @param pszCgiFilename Defines the CGI filename to be included in the "action" attribute of the form.
 * @param pszProt Specifies the protocol (e.g., "GET" or "POST") to be used in the "method" attribute of the form.
 * @param handle An integer handle, currently unused in the function.
 * @param pszID The unique identifier for the form, assigned to the "id" attribute of the form.
 * @param pszTarget Indicates the target for the form, assigned to the "target" attribute of the form.
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
 * @*/
//void cgihtml::open_head(std::string ssCssName)
void cgihtml::open_head()
{
    std::cout << "<head>";
              //<< "<link rel=\"stylesheet\" "
              // << "href=\""
              // << ssCssName
              // << "\">"
              // << std::endl;
}


/**
 * @brief Outputs the opening HTML tag to the standard output stream*/
void cgihtml::open_html()
{
    std::cout << "<html>";
}

/**
 * Generates an HTML meta tag using a list as its argument.
 *
 * @param metaData Takes in a list of arbitrary length to be parsed into an
 * html meta line. Every pair of elements are to be in the next array position.
 * Example: {"class", "button",
 *           "id", "button1",
 *           ...}
 */
void cgihtml::gen_meta_line(std::initializer_list<std::string> metaData)
{
    std::string metaHeader = "<meta ";
    int iArgCount = 0;
    for (auto data : metaData)
    {
        // If iArgCount is even, then it takes the current data element and
        // inserts it into the line.
//        if (0 == iArgCount++%2)
        if (0 == (1 & iArgCount++))
        {
            metaHeader.append(data + "=");
        }
        else
        {
            // If iArgCount is odd, then we take the current data element and
            // insert it after the equal sign with quotes.
            metaHeader.append("\"" + data + "\" ");
        }
    }
    // Erases the last character of the string, which should be a " ".
    metaHeader.pop_back();
    std::cout << metaHeader << ">" << std::endl;
}


/**
 * Generates an HTML meta tag using a string as its argument.
 *
 * @param ssMetaLine Takes in a string to be inserted into an html meta line.
 * As quotes must be escaped with this implementation, I've elected to use
 * the other function overload that uses the arbitrary list of strings.
 * Example: "class=\"button\" id=\"button1\"..."
 */
void cgihtml::gen_meta_line(std::string ssMetaLine)
{
    std::cout << "<meta " << ssMetaLine << ">" << std::endl;
}


/**
 * Opens a script tag by outputting the HTML `<script>` element.
 */
void cgihtml::open_script()
{
    std::cout << "<script>";
}


/**
 * Opens a new HTML div element with the specified class attribute.
 *
 * @param pszDivClass The class name to be assigned to the div element.
 */
void cgihtml::open_div(const char * pszDivClass)
{
    gpLog->writev("%s: %s() started",__FILE__,__FUNCTION__);
    printf("<div class=\"%s\">",pszDivClass);
}


/**
 * Outputs the opening HTML paragraph tag.
 */
void cgihtml::para()
{
    std::cout << "<p>";
}


/**
 * Prints the provided text to the standard output.
 *
 * @param sz*/
void cgihtml::print(const char *szText)
{
    std::cout << szText;
}


/**
 * Prints formatted output to the standard output stream.
 *
 * This method takes a format string and a variable number of arguments
 * to construct and print the output string.
 *
 * @param pszFormat A C-style format string specifying how subsequent
 *                  arguments are formatted and output.
 * @param ...       Variable arguments used in the formatting of the
 *                  output string, based on the format*/
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
 * Prints the provided variable name alongside its boolean value as a string.
 * If the boolean value is true, appends "is true" to the name.
 * If the boolean value is false, appends "is false" to the name.
 *
 * @param pszName The name of the variable to be printed.
 * @param bValue The boolean value of the variable.
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
 * Prints a variable name and its value in the format "name = value".
 *
 * @param pszName The name of the variable to be printed.
 * @param pszValue The value of the variable to be printed.
 */
void cgihtml::printvar(const char *pszName,const char *pszValue)
{
    std::cout << pszName << " = " << pszValue << std::endl;
}


/**
 * Prints a variable name and its value in the format: <name> = <value>.
 *
 * @param pszName The name of the variable to be printed.
 * @param iValue The integer value of the variable to be printed.
 */
void cgihtml::printvar(const char *pszName,int iValue)
{
    std::cout << pszName << " = " << iValue << std::endl;
}


/**
 * Prints a variable name and its associated double value to the standard output.
 *
 * The function outputs the given variable name and value in the format:
 * `name = value`, followed by a new line.
 *
 * @param pszName The name of the variable to be printed. Must be a null-terminated string.
 * @param dValue The double value associated with the variable name to be printed.
 */
void cgihtml::printvar(const char *pszName,double dValue)
{
    std::cout << pszName << " = " << dValue << std::endl;
}


/**
 * Opens an HTML table with a specified border width.
 *
 * @param border The width of the border for the HTML table.
 */
void cgihtml::open_table(int border)
{
    std::cout << "<table "
              << "border=\"" << border << "\""
              << ">"
              << std::endl;
}


/**
 * @brief Generates a JavaScript function to create a button dynamically in HTML.
 *
 * This method writes a JavaScript function that creates an HTML button with a specific name
 * and visible label, and appends it to the document body.
 *
 * @param pszButtonName The name to be associated with the button in the generated JavaScript function.
 **/
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
 * Sets the style for the specified element or component.
 *
 * @param styleName The name of the style to be applied.
 *                  It should correspond to a defined style key.
 * @param value The value of the style to be applied.
 *              This typically represents the properties and formatting for the style.
 */
void cgihtml::set_style(const char * pszStylesheet)
{
    gpLog->writev("%s: %s() started",__FILE__,__FUNCTION__);
    printf("<link rel=\"stylesheet\" href=\"%s%s.css\"/>",
           gpEnv->get_styles_root(false).c_str(),
           pszStylesheet);
}


/**
 * Sets the title for the HTML page by outputting it within <title> tags.
 *
 * @param szTitle The title to be displayed in the HTML document.
 */
void cgihtml::title(const char * szTitle)
{
    std::cout << "<title>" << szTitle << "</title>" << std::endl;
}

///////////////////////
// eof - cgihtml.cpp //
///////////////////////
