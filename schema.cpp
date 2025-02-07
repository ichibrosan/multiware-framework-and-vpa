//////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/schema.cpp 2025/01/10   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.   //
//////////////////////////////////////////////////////////////////////////

#include "std.h"
#include "fw-limits.h"
#include "cgicc.h"
#include "schema.h"
#include "CLog.hpp"
extern CLog * gpLog;
#include "cgihtml.h"
#include "fw-limits.h"
#include "readCsv.h"
#include "shared.h"
#include "std.h"

#include "osIface.h"
extern osIface * gpOS;


using namespace std;
using namespace cgicc;
extern readCsv * gpCsv;
extern cgihtml * gpHtml;
extern shared * gpSh;


/**********************************************
 * This is the constructor for the schema class
 * @param ssSchemaName
 **********************************************/
schema::schema(std::string ssSchemaName)
{
    m_pSysLog = new CSysLog();          // 2025/02/06 18:21 dwg -

    m_ssSchemaName = ssSchemaName;
    gpCsv = new readCsv(ssSchemaName);
    gpCsv->parseData();
    m_iRows = gpCsv->getLines();
}


/********************************************
 * Return the number of lines in the CSV file
 * @return
 ********************************************/
int schema::getLines()
{
    return m_iRows;
}


/******************************************************************
 * Pre-process Row Data by checking for specific hooks in the
 * argument columns of the schema.
 * Currently: from: and passed:
 * @param iRow
 * @param svvsPassedValues
 ******************************************************************/
void schema::preprocess_row_data(
        int iRow,
        std::vector<std::vector<std::string>> svvsPassedValues)
{
    // 2025/02/06 18:26 dwg - for code verification purposes
    char szTemp[256];
    sprintf(szTemp,"svvsPassedValues.size() is %d",
        svvsPassedValues.size());
    m_pSysLog->loginfo(szTemp);
    int iMaxCols = atoi(gpCsv->m_parsed_data
        [ROW_META_HDR][COL_META_DATA_COLUMNS].c_str());

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

/*************************************************************
 * Generate HTML Form using Open Schema Data
 * @param pSchema Pointer to active instance of Schema Class
 * @param pReadCsv Pointer to active instance of readCsv class
 *************************************************************/
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

            // if type is select
            if (0 == strcmp("select",
                            gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
                gpHtml->form_files_select(
                    gpCsv->m_parsed_data[iRow][COL_SELECT_NAME].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_SELECT_PATH].c_str(),
                    gpCsv->m_parsed_data[iRow][COL_SELECT_CLASS].c_str()
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


schema::~schema()
{
}