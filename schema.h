/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/schema.h 2025/01/10   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#ifndef HTML_SCHEMA_H
#define HTML_SCHEMA_H

//#include "main.h"
#include "CSysLog.hpp"
#include "readCsv.h"

enum {
    ROW_META_HDR,       // 0
    ROW_META_DATA,      // 1
    ROW_DATA_HDR,       // 2
    ROW_DATA            // 3
};

// 2025-02-06 11:56 dwg - added separate column counts
enum SCHEMA_METADATA_T {
    COL_META_ACTIVE,
    COL_META_VERSION,
    COL_META_META_COLUMNS,
    COL_META_DATA_COLUMNS,
    COL_META_SCHEMA,
    COL_META_CGINAME,
    COL_META_TARGET,
    COL_META_PAGE_FORM,
    COL_META_STYLE,
    COL_META_DESCRIPTION
};

/*
 * A Generic view of the columns in the schema file
 */
enum SCHEMA_GENERIC_T {
    COL_ACTIVE,
    COL_PREPARA,
    COL_POSTPARA,
    COL_TYPE,
    COL_PARM1,
    COL_PARM2,
    COL_PARM3
};

enum SCHEMA_IFRAME_T {
    COL_IFRAME_DEF_PAGE = COL_PARM1,
    COL_IFRAME_TITLE,
    COL_IFRAME_NAME,
    COL_IFRAME_CLASS,
    COL_IFRAME_WIDTH,
    COL_IFRAME_HEIGHT
};

enum SCHEMA_XAHREF_T {
    COL_XAHREF_LINK = COL_PARM1,
    COL_XAHREF_CLASS,
    COL_XAHREF_DISPLAY
};

enum SCHEMA_FORM_BUTTON_T {
    COL_FORM_BUTTON_TYPE = COL_PARM1,
    COL_FORM_BUTTON_FORM,
    COL_FORM_BUTTON_CLASS,
    COL_FORM_BUTTON_DISPLAY
};

enum SCHEMA_OPEN_FORM_T {
    COL_FORM_ACTION = COL_PARM1,
    COL_FORM_PROTOCOL,
    COL_FORM_HANDLE,
    COL_FORM_ID,
    COL_FORM_TARGET
};

enum SCHEMA_DIV_T {
    COL_DIV_CLASS = COL_PARM1
};

//// deprecated
//enum SCHEMA_DATA_T {
//    COL_DATA_ACTIVE,
//    COL_DATA_PREPARA,
//    COL_DATA_POSTPARA,
//    COL_DATA_TYPE,
//    COL_DATA_LABEL,
//    COL_DATA_VISIBLE,
//    COL_DATA_COMMENT
//};


enum SCHEMA_CHECKBOX_T {
    COL_CHECKBOX_NAME = COL_PARM1,
    COL_CHECKBOX_ID,
    COL_CHECKBOX_VALUE,
    COL_CHECKBOX_VISIBLE,
    COL_CHECKBOX_DESCRIPTION
};

enum SCHEMA_DATE_T {
    COL_DATE_NAME = COL_PARM1,
    COL_DATE_ID,
    COL_DATE_VALUE,
    COL_DATE_DESCR
};

enum SCHEMA_DATETIME_T {
    COL_DATETIME_NAME = COL_PARM1,
    COL_DATETIME_ID,
    COL_DATETIME_VALUE,
    COL_DATETIME_DESCR
};

enum SCHEMA_IMAGE_T {
    COL_IMAGE_FILENAME = COL_PARM1,
    COL_IMAGE_WIDTH,
    COL_IMAGE_HEIGHT,
    COL_IMAGE_ALTDESCRIPTION
};

enum SCHEMA_MONTH_T {
    COL_MONTH_NAME = COL_PARM1,
    COL_MONTH_ID,
    COL_MONTH_VALUE,
    COL_MONTH_DESCR
};

// 2025-01-30 08:07 dwg -
enum SCHEMA_PASSWORD_T {
    COL_PASSWORD_NAME = COL_PARM1,
    COL_PASSWORD_ID,
    COL_PASSWORD_VALUE,
    COL_PASSWORD_SIZE,
    COL_PASSWORD_VISIBLE,
    COL_PASSWORD_DESCR
};

enum SCHEMA_RADIOBUTT_T {
    COL_RADIO_ID = COL_PARM1,
    COL_RADIO_NAME,
    COL_RADIO_VALUE,
    COL_RADIO_LABEL,
    COL_RADIO_DESCRIPTION
};

enum SCHEMA_RESET_T {
    COL_RESET_NAME = COL_PARM1,
    COL_RESET_VALUE
};

// 2025-01-14 14:04 dwg -
enum SCHEMA_TEXT_T {
    COL_TEXT_NAME = COL_PARM1,
    COL_TEXT_ID,
    COL_TEXT_VALUE,
    COL_TEXT_SIZE,
    COL_TEXT_VISIBLE,
    COL_TEXT_DESCR,
    COL_TEXT_READONLY,
    COL_TEXT_CLASS
};


enum SCHEMA_FILES_SELECT_T {
    COL_SELECT_NAME = COL_PARM1,
    COL_SELECT_PATH,
    COL_SELECT_CLASS
};

enum SCHEMA_TEXTAREA_T {
    COL_TEXTAREA_NAME = COL_PARM1,
    COL_TEXTAREA_ID,
    COL_TEXTAREA_COLS,
    COL_TEXTAREA_ROWS,
    COL_TEXTAREA_WRAP,
    COL_TEXTAREA_CLASS,
    COL_TEXTAREA_VALUE
};

enum SCHEMA_TIME_T {
    COL_TIME_NAME = COL_PARM1,
    COL_TIME_ID,
    COL_TIME_VALUE,
    COL_TIME_DESCR
};



enum SCHEMA_WEEK_T {
    COL_WEEK_NAME = COL_PARM1,
    COL_WEEK_ID,
    COL_WEEK_VALUE,
    COL_WEEK_DESCR
};

enum SCHEMA_AHREF_T {
    COL_AHREF_CGINAME = COL_PARM1,
    COL_AHREF_IMGNAME,
    COL_AHREF_WIDTH,
    COL_AHREF_HEIGHT
};

enum SCHEMA_PASSWD_T {
    COL_PASSWD_ACTIVE,
    COL_PASSWD_USERNAME,
    COL_PASSWD_PASSWORD,
    COL_PASSWD_AUTHLEVEL,
    COL_PASSWD_FIRSTNAME,
    COL_PASSWD_LASTNAME,
    COL_PASSWD_DESCR
};

enum SCHEMA_LABEL_T {
    COL_LABEL_VISIBLE = COL_PARM1
};

enum SCHEMA_PREPROCESS_T {
    VARIABLE_NAME,
    VARIABLE_VALUE
};

class schema {

    int       m_iRows;
    std::string m_ssSchemaName;
    CSysLog * m_pSysLog;
public:
    schema(std::string);
    void preprocess_row_data(int i_IRow,
                                    std::vector<std::vector<std::string>>
                                    svvsPassedValues);
    void process_schema_data(std::vector<std::vector<std::string>>
                             svvsPassedValues);
    void gen_from_schema(int handle, std::vector<std::vector<std::string>>
                                     svvsPassedValues = {});
    int getLines();
    ~schema();

    readCsv * m_pReadCsv;
};


#endif //HTML_SCHEMA_H
