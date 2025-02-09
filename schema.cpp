//////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/schema.cpp 2025/01/10   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.   //
//////////////////////////////////////////////////////////////////////////

#include "std.h"
#include "fw-limits.h"
#include "cgicc.h"
#include "schema.h"
#include "CLog.hpp"
/**
 * @brief Global instance of a logging object used for recording and managing application logs.
 *
 * The gpLog variable serves as a centralized logging utility that enables the
 * application to log messages, warnings, errors, and debugging information.
 * It is often configured to output log messages to a console, file, or other
 * logging sinks, facilitating debugging and monitoring activities during
 * runtime.
 *
 * This variable is accessible globally within the application.
 */
extern CLog * gpLog;
#include "cgihtml.h"
#include "fw-limits.h"
#include "readCsv.h"
#include "shared.h"
#include "std.h"

#include "osIface.h"
/**
 * @brief A global pointer to the operating system interface.
 *
 * This variable serves as the global access point for the operating system
 * interface, allowing interaction with the OS functionalities. It should be
 * initialized with a valid instance of an operating system interface
 * implementation before use.
 */
extern osIface * gpOS;


using namespace std;
using namespace cgicc;
/**
 * @brief A global pointer to an instance of the `readCsv` class.
 *
 * `gpCsv` is utilized to access and operate on parsed CSV data within
 * the program. This pointer provides global access to the methods and data
 * members of the `readCsv` class, allowing various components of the software
 * to interact with the parsed CSV content.
 *
 * Primary uses:
 * - Retrieve specific data from the CSV via the `getData` method.
 * - Determine the total number of rows in the CSV using the `getLines` method.
 * - Access and iterate through the parsed data stored in the internal
 *   data structure of the `readCsv` instance.
 *
 * @note The actual object the pointer refers to must be properly initialized
 *       before use to ensure valid operations.
 */
extern readCsv * gpCsv;
/**
 * @brief Global pointer to an instance of `cgihtml`.
 *
 * This variable is used to manage or interact with HTML content
 * in CGI (Common Gateway Interface) related functionality.
 *
 * It provides a mechanism to access and manipulate dynamic HTML
 * content throughout the application. The specific use, behavior,
 * and lifecycle of this variable is determined by the implementation
 * of the `cgihtml` class or structure.
 *
 * @note Proper initialization and cleanup of this variable are
 * essential for preventing memory leaks or undefined behavior.
 *
 * @warning Accessing this variable before initialization or after
 * it has been freed may result in undefined behavior.
 */
extern cgihtml * gpHtml;
/**
 * @brief Global pointer to the `shared` class instance.
 *
 * `gpSh` is a globally accessible pointer that refers to an instance
 * of the `shared` class. It provides access to shared resources and
 * functionalities managed by the `shared` class, which may include
 * logging, system utility methods, or shared memory management.
 *
 * This variable is typically initialized during the application's
 * startup process and is used throughout the codebase to enable
 * coordinated access to shared functionalities. Proper care should
 * be taken to ensure the pointer is correctly managed to avoid
 * memory leaks or undefined behavior.
 */
extern shared * gpSh;


/**
 * Constructs a schema object and initializes it with the given schema name.
 * The constructor sets up logging, initializes a CSV reader for the schema,
 * parses the CSV data, and determines the number of rows in the data.
 *
 * @param ssSchemaName The name of the schema to initialize the object and CSV reader.
 * @return A schema object with initialized values.
 */
schema::schema(std::string ssSchemaName)
{
    m_pSysLog = new CSysLog();          // 2025/02/06 18:21 dwg -

    m_ssSchemaName = ssSchemaName;
    gpCsv = new readCsv(ssSchemaName);
    gpCsv->parseData();
    m_iRows = gpCsv->getLines();
}


/**
 * Retrieves the number of rows in the schema.
 *
 * @return The number of rows as an integer.
 */
int schema::getLines()
{
    return m_iRows;
}


/**
 * Preprocesses the row data by applying necessary transformations
 * or cleaning operations before further analysis or storage.
 *
 * @param row_data The raw data of the row that needs preprocessing.
 * @param config Configuration parameters that define how the preprocessing
 *               should be performed.
 * @param normalize A boolean flag indicating if the data should be normalized.
 * @param remove_missing A boolean flag indicating if missing values
 *                       should be removed during preprocessing.
 */
void schema::preprocess_row_data(
        int iRow,
        std::vector<std::vector<std::string>> svvsPassedValues)
{
    // 2025/02/06 18:26 dwg - for code verification purposes
    char szTemp[256];
    sprintf(szTemp,"svvsPassedValues.size() is %ld",
        svvsPassedValues.size());
    m_pSysLog->loginfo(szTemp);
    int iMaxCols = atoi(gpCsv->m_parsed_data
        [ROW_META_DATA][COL_META_DATA_COLUMNS].c_str());

    for (int iCol = COL_PARM1; iCol < iMaxCols; iCol++)
    {
        std::string ssCurrentGrid = gpCsv->m_parsed_data[iRow][iCol];

        if (0 == std::strncmp("from:",
                 ssCurrentGrid.c_str(),
                 strlen("from:")))
        {
            ssCurrentGrid =
                gpCgiBind->get_form_variable(
                    ssCurrentGrid.substr(ssCurrentGrid.find(':') + 1));

            gpCsv->m_parsed_data[iRow][iCol] = ssCurrentGrid;
        }

        else if (0 == std::strncmp("passed:",
                 ssCurrentGrid.c_str(),
                 strlen("passed:")))
        {
            ssCurrentGrid = ssCurrentGrid.substr(
            ssCurrentGrid.find(':') + 1);

            for (int iVarName = 0;
                 iVarName < svvsPassedValues.size();
                 iVarName++) {
                if (0 == std::strncmp(ssCurrentGrid.c_str(),
                 svvsPassedValues[iVarName][VARIABLE_NAME].c_str(),
                  strlen(ssCurrentGrid.c_str())))
                {
                    gpCsv->m_parsed_data[iRow][iCol] =
                    svvsPassedValues[iVarName][VARIABLE_VALUE].c_str();
                }
            }
        }
    }
}

/**
 * Processes schema data from a given structured input and generates
 * corresponding HTML elements based on the schema's definitions.
 *
 * The function iterates over rows of data, checks activation status,
 * and processes them based on their specified type (e.g., form, div, image).
 * Depending on the type, it generates specific HTML outputs such as forms,
 * images, labels, or other elements.
 *
 * @param svvsPassedValues A 2D vector of strings representing values that can
 *                         be passed to preprocess certain rows in the schema.
 */
void schema::process_schema_data(std::vector<std::vector<std::string>>
                                 svvsPassedValues)
{
    gpLog->writev("%s: %s() started",__FILE__,__FUNCTION__);
    CLog log(__FILE__,__FUNCTION__);
    log.write("instantiated");

    bool bSubmitRequired = false;
    bool bPageForm = false;

    if (0 == strcmp("true",
    gpCsv->m_parsed_data[ROW_META_DATA][COL_META_PAGE_FORM].c_str())) {
        bPageForm = true;
    }
    else
    {
        bPageForm = false;
    }



    int iCol;
    int iRow = ROW_DATA;
    int iDataRows = gpCsv->getLines()-3;
#ifdef DEBUG_PROCESS_SCHEMA_DATA
    gpHtml->para(); gpHtml->printvar("Schema Data Rows",iDataRows);
#endif //  DEBUG_PROCESS_SCHEMA_DATA
    while(0 < iDataRows) {
        // If this line of the schema is active
        iCol= COL_ACTIVE;
        if(0 == strcmp("true",
                       gpCsv->m_parsed_data[iRow][iCol].c_str())) {

            preprocess_row_data(iRow,svvsPassedValues);

            // If prepara is yes
            if(0 == strcmp("yes",
                           gpCsv->m_parsed_data[iRow][COL_PREPARA].c_str())) {
                gpHtml->para();
            }

            // if type is xahref
            if (0 == strcmp("xahref",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->xahref(
                    gpCsv->m_parsed_data[iRow][COL_XAHREF_LINK].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_XAHREF_CLASS].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_XAHREF_DISPLAY].c_str()
                    );
            }


            // If type is openform
            if(0 == strcmp("openform",
                           gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->open_form(
                "UNUSED",
                gpCsv->m_parsed_data[iRow][COL_FORM_ACTION].c_str(),
                gpCsv->m_parsed_data[iRow][COL_FORM_PROTOCOL].c_str(),
                atoi(gpCsv->m_parsed_data[iRow][COL_FORM_HANDLE].c_str()),
                gpCsv->m_parsed_data[iRow][COL_FORM_ID].c_str(),
                gpCsv->m_parsed_data[iRow][COL_FORM_TARGET].c_str()
                    );
            }

            // If type is opendiv
            if(0 == strcmp("opendiv",
                           gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->open_div(
                    gpCsv->m_parsed_data[iRow][COL_DIV_CLASS].c_str()
                    );
            }

            // If type is closediv
            if(0 == strcmp("closediv",
                           gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->close_div();
            }

            // If type is closeform
            if(0 == strcmp("closeform",
                           gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->close_form();
            }

            // if type is iframe
            if (0 == strcmp("iframe",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_iframe(
                    gpCsv->m_parsed_data[iRow][COL_IFRAME_DEF_PAGE].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_IFRAME_TITLE].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_IFRAME_NAME].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_IFRAME_CLASS].c_str(),
                    atoi(gpCsv->m_parsed_data[iRow][COL_IFRAME_WIDTH].c_str()),
                    atoi(gpCsv->m_parsed_data[iRow][COL_IFRAME_HEIGHT].c_str())
                    );
            }

            // if type is formbutton
            if (0 == strcmp("formbutton",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_button(
                    gpCsv->m_parsed_data[iRow][COL_FORM_BUTTON_TYPE].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_FORM_BUTTON_FORM].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_FORM_BUTTON_CLASS].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_FORM_BUTTON_DISPLAY].c_str()
                    );
            }

            if (0 == strcmp("select",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_select(
                    gpCsv->m_parsed_data[iRow][COL_PARM1].c_str(),  // labelfor
                    gpCsv->m_parsed_data[iRow][COL_PARM2].c_str(),  // labelvis
                    gpCsv->m_parsed_data[iRow][COL_PARM3].c_str(),  // selid
                    gpCsv->m_parsed_data[iRow][COL_PARM4].c_str()); // selname
            }

            if (0 == strcmp("selectopt",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_select_opt(
                    gpCsv->m_parsed_data[iRow][COL_PARM1].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_PARM2].c_str());
            }

            if (0 == strcmp("selectend",
                           gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_select_end();
            }

            // if type is select_files
            if (0 == strcmp("select_files",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_select_files(
                    gpCsv->m_parsed_data[iRow][COL_FILES_SELECT_NAME].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_FILES_SELECT_PATH].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_FILES_SELECT_CLASS].c_str()
                    );
            }

            // if type is date
            // 2025/01/29 18:13 dwg - implemented & tested
            if(0 == strcmp("date",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_date(
                    gpCsv->m_parsed_data[iRow][COL_DATE_NAME].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_DATE_ID].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_DATE_VALUE].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_DATE_DESCR].c_str());
                bSubmitRequired = true;
                            }

            // if type is datetime-local
            // 2025/01/29 18:13 dwg - implemented & tested
            if(0 == strcmp("datetime-local",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_datetime(
                    gpCsv->m_parsed_data[iRow][COL_DATETIME_NAME].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_DATETIME_ID].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_DATETIME_VALUE].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_DATETIME_DESCR].c_str());
                bSubmitRequired = true;
                            }

            // if type is image
            if (0 == strcmp("image",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpLog->write("doing image element");
                gpHtml->imgsrc(
                        gpCsv->m_parsed_data[iRow][COL_IMAGE_FILENAME].c_str(),
                        atoi(gpCsv->m_parsed_data[iRow][COL_IMAGE_WIDTH].c_str()),
                        atoi(gpCsv->m_parsed_data[iRow][COL_IMAGE_HEIGHT].c_str())
                );
                //bSubmitRequired = true;
            }

            // if type is imglink
            if (0 == strcmp("imagelink",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->ahref(
                        gpCsv->m_parsed_data[iRow][COL_AHREF_CGINAME].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_AHREF_IMGNAME].c_str(),
                        atoi(gpCsv->m_parsed_data[iRow][COL_AHREF_WIDTH].c_str()),
                        atoi(gpCsv->m_parsed_data[iRow][COL_AHREF_HEIGHT].c_str())
                );
                //bSubmitRequired = true;
            }

            /**
             * label is not a form type, but a synthetic I made to allow
             * text to be inserted ad-hoc. 2024/12/31/dwg -
             */
            // if type is label
            if(0 == strcmp("label",
                           gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_label(
                        gpCsv->m_parsed_data[iRow][COL_LABEL_VISIBLE].c_str());
            }

            // if type is month
            // 2025/01/29 18:13 dwg - implemented & tested
            if(0 == strcmp("month",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_month(
                    gpCsv->m_parsed_data[iRow][COL_MONTH_NAME].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_MONTH_ID].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_MONTH_VALUE].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_MONTH_DESCR].c_str());
                bSubmitRequired = true;
            }

            // if type is password
            // 2025-01-14 14:03 dwg -
            if (0 == strcmp("password",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_password(
                    gpCsv->m_parsed_data[iRow][COL_PASSWORD_NAME].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_PASSWORD_ID].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_PASSWORD_VALUE].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_PASSWORD_SIZE].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_PASSWORD_VISIBLE].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_PASSWORD_DESCR].c_str());
                bSubmitRequired = true;
            }

            // if type is checkbox
            if(0 == strcmp("postcheckbox",
                           gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_postcheckbox(
                     gpCsv->m_parsed_data[iRow][COL_CHECKBOX_NAME].c_str(),
                     gpCsv->m_parsed_data[iRow][COL_CHECKBOX_ID].c_str(),
                     gpCsv->m_parsed_data[iRow][COL_CHECKBOX_VALUE].c_str(),
                     gpCsv->m_parsed_data[iRow][COL_CHECKBOX_VISIBLE].c_str()
                 );
                bSubmitRequired = true;
            }

            // if type is checkbox
            if(0 == strcmp("precheckbox",
                           gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_precheckbox(
                     gpCsv->m_parsed_data[iRow][COL_CHECKBOX_NAME].c_str(),
                     gpCsv->m_parsed_data[iRow][COL_CHECKBOX_ID].c_str(),
                     gpCsv->m_parsed_data[iRow][COL_CHECKBOX_VALUE].c_str(),
                     gpCsv->m_parsed_data[iRow][COL_CHECKBOX_VISIBLE].c_str()
                 );
                bSubmitRequired = true;
            }

            // if type is reset
            if (0 == strcmp("reset",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_reset();
                bSubmitRequired = true;
            }

            if (0 == strcmp("text",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_text(
                        gpCsv->m_parsed_data[iRow][COL_TEXT_NAME].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_TEXT_ID].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_TEXT_VALUE].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_TEXT_SIZE].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_TEXT_VISIBLE].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_TEXT_READONLY].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_TEXT_CLASS].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_TEXT_DESCR].c_str());
                bSubmitRequired = true;
            }

            // if type is textarea
            if(0 == strcmp("textarea",
                           gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_textarea(
                        gpCsv->m_parsed_data[iRow][COL_TEXTAREA_NAME].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_TEXTAREA_ID].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_TEXTAREA_COLS].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_TEXTAREA_ROWS].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_TEXTAREA_WRAP].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_TEXTAREA_CLASS].c_str(),
                        gpCsv->m_parsed_data[iRow][COL_TEXTAREA_VALUE].c_str()
                );
                //bSubmitRequired = true;
            }

            // if type is time
            // 2025/01/29 18:13 dwg - implemented & tested
            if(0 == strcmp("time",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_time(
                    gpCsv->m_parsed_data[iRow][COL_TIME_NAME].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_TIME_ID].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_TIME_VALUE].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_TIME_DESCR].c_str());
                bSubmitRequired = true;
                            }


            // if type is week
            // 2025/01/29 18:13 dwg - implemented & tested
            if(0 == strcmp("week",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_week(
                    gpCsv->m_parsed_data[iRow][COL_WEEK_NAME].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_WEEK_ID].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_WEEK_VALUE].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_WEEK_DESCR].c_str());
                bSubmitRequired = true;
            }

            // If postpara is yes
            if(0 == strcmp("yes",
                           gpCsv->m_parsed_data[iRow][COL_POSTPARA].c_str())) {
                gpHtml->para();
            }

            // end of schema line processing

        }

        //        else {
//            gpHtml->para(); gpHtml->print("Data row is not active");
//            gpHtml->para(); gpHtml->print(
//                    gpCsv->m_parsed_data[iRow][COL_DATA_ACTIVE].c_str());
//
//        } // data active

        iRow++;
        iDataRows--;
    } // while


    if(bSubmitRequired && bPageForm) {
        gpHtml->form_submit();
    }
}

/**
 * @brief Generates HTML content and applies schema-specific configuration based on parsed data and passed values.
 *
 * The function creates an HTML webpage using information from the associated schema data.
 * It evaluates schema status, adjusts styles, and performs conditional logic based on schema metadata.
 * If the schema is active and valid, it processes further schema data and dynamically generates
 * HTML elements. The function supports the merging of external passed values into the schema metadata.
 *
 * @param iHandle An integer handle that is used for the schema form and other metadata identification during processing.
 * @param svvsPassedValues A 2D vector containing pairs of variable names and corresponding values to be used for dynamic schema updates.
 */
void schema::gen_from_schema(int iHandle,
                             std::vector<std::vector<std::string>>
                             svvsPassedValues)
{
    char szHandle[4];

    int iRow  = 0;
    int iCol  = 0;

    std::string ssStyleGrid = gpCsv->m_parsed_data[ROW_META_DATA]
                     [COL_META_STYLE];

    if (0 == std::strncmp("passed:",
                 ssStyleGrid.c_str(),
                 strlen("passed:")))
    {
        ssStyleGrid = ssStyleGrid.substr(
            ssStyleGrid.find(':') + 1);


        for (int i_VarName = 0;
             i_VarName <= svvsPassedValues.size() - 1;
             i_VarName++)
        {
            if (0 == std::strncmp(ssStyleGrid.c_str(),
             svvsPassedValues[i_VarName][VARIABLE_NAME].c_str(),
              strlen(ssStyleGrid.c_str())))
            {
                gpCsv->m_parsed_data[ROW_META_DATA][COL_META_STYLE] =
                svvsPassedValues[i_VarName][VARIABLE_VALUE];
            }
        }
    }



    char szTemp[BUFSIZ];
    memset(szTemp,0,sizeof(szTemp));
    gpHtml->open_html();
    gpHtml->open_head();
    sprintf(szTemp,"%s%s%s",
            gpSh->m_pShMemng->szProtocol,
            gpSh->m_pShMemng->szIP,
            "/action.py");
    gpHtml->title(szTemp);


    gpHtml->set_style(
        gpCsv->m_parsed_data
        [ROW_META_DATA]
        [COL_META_STYLE].c_str());

    gpHtml->close_head();
    gpHtml->open_body();
    gpHtml->open_script();
    gpHtml->script_button("TryIt","Click Me");
    gpHtml->close_script();
    //gpHtml->imgsrc("our-office.png",896/3,676/3);

    // Experimental 2025/01/15 03:47 dwg -
    char szCGIPath[FILENAME_MAX];
    strcpy(szCGIPath,gpCsv->m_parsed_data
                    [ROW_META_DATA][COL_META_CGINAME].c_str());
    gpHtml->open_form(
            gpCsv->m_parsed_data[ROW_META_DATA][COL_META_SCHEMA].c_str(),
            gpCsv->m_parsed_data[ROW_META_DATA][COL_META_CGINAME].c_str(),
          //"GET",iHandle);
          "POST",
          iHandle,
          "default",
          gpCsv->m_parsed_data[ROW_META_DATA][COL_META_TARGET].c_str());

    sprintf(szHandle,"%d",iHandle);
    gpHtml->hidden("handle",szHandle);
    // If the Schema is Active (line 1 element 1)
    iRow = ROW_META_DATA;
    iCol = COL_META_ACTIVE;
    if(0 ==
       strcmp("true",
              gpCsv->m_parsed_data[iRow][iCol].c_str())) {
        iCol = COL_META_VERSION;
        if(0 == strcmp("1",
                       gpCsv->m_parsed_data[iRow][iCol].c_str())) {
            //iCol = COL_META_COLUMNS;
            // Process Schema Data
            process_schema_data(svvsPassedValues);

        } else {
            gpHtml->para(); gpHtml->print("Schema Version Check Failed!!");
        }

    } else {
        gpHtml->para(); gpHtml->print("Schema is not active");
    }

    //gpHtml->close_form();
    gpHtml->close_body();
    gpHtml->close_html();
}


/**
 * @brief Destructor for the schema class.
 *
 * This method is invoked when an instance of the schema class
 * is destroyed. It performs cleanup operations, releasing any
 * resources or memory allocated during the object's lifetime.
 */
schema::~schema()
{
}