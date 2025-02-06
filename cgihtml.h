/**
 * daphne.goodall.com:/var/www/cgihtml.h 2024/12/30 02:25 dwg -
 * Copyright (c) 2024 Douglas Wade Goodall. All Rights Reserved.
 * This file is part of the Goodall Multiware Framework.
 */

#ifndef MULTIWARE_CGIHTML_H
#define MULTIWARE_CGIHTML_H

#include "std.h"
#include "fw-limits.h"
#include "osIface.h"
extern osIface * gpOS;
#include "CLog.hpp"
extern CLog    * gpLog;
#include "shared.h"
extern shared  * gpSh;
#include "schema.h"
extern schema * gpSchema;
#include "readCsv.h"
extern readCsv * gpCsv;
#include "environment.h"
extern environment * gpEnv;
#include "cgibind.h"
extern cgibind * gpCgiBind;
#include "cgicc.h"
extern Cgicc * gpCgi;

//enum HTML_LOCATION {
//    HTML_USERDIR,
//    HTML_VARWWW
//};

class cgihtml {
    //char m_page[BUFSIZ];
public:
    cgihtml();

    void ahref(const char *,const char *,int,int);

    // TAG PRIMITIVES (closers)
    void close_body();
    void close_form();
    void close_head();
    void close_html();
    void close_script();
    void close_table();
    void close_div();

    // DEBUG DISPLAY GENERATORS
    void dump_env_vars();
    void dump_shm_vars();
    void dump_passwd();
    void dump_referrer(
        std::string ssReferrer,
        std::string ssReferrerPath,
        std::string ssReferrerFile);
    void dump_schema();

    // FORM ELEMENT HANDLERS
    void form_button(const char * pszType,
                     const char * pszForm,
                     const char * pszButtonClass,
                     const char * pszButtonDisplay);

    void form_iframe(const char * pszIframeDefaultPage,
                     const char * pszIframeTitle,
                     const char * pszIframeName,
                     const char * pszIframeClass,
                     int i_IframeWidth,
                     int i_IframeHeight);

    void form_iframe_button(const char * pszLink,
                            const char * pszImage,
                            const char * pszTarget,
                            const char * pszButtonClass,
                            const char * pszButtonDisplay);

    void form_date(         const char *,   // COL_DATE_NAME
                            const char *,   // COL_DATE_ID
                            const char *,   // COL_DATE_VALUE
                            const char *);  // COL_DATE_DESCR


    void form_datetime(     const char *,   // COL_DATETIME_NAME
                            const char *,   // COL_DATETIME_ID
                            const char *,   // COL_DATETIME_VALUE
                            const char *);  // COL_DATETIME_DESCR

    void form_label(const char *);

    void form_month(        const char *,   // COL_MONTH_NAME
                            const char *,   // COL_MONTH_ID
                            const char *,   // COL_MONTH_VALUE
                            const char *);  // COL_MONTH_DESCR

    void form_password(     const char *pszName,    // COL_PASSWORD_NAME
                            const char *pszId,      // COL_PASSWORD_ID
                            const char *pszValue,   // COL_PASSWORD_VALUE
                            const char *pszsize,    // COL_PASSWORD_SIZE
                            const char *pszVisible, // COL_PASSWORD_VISIBLE
                            const char *pszDescr);  // COL_PASSWORD_DESCR

    void form_postcheckbox( const char *,    // COL_CHECKBOX_NAME
                            const char *,    // COL_CHECKBOX_VALUE
                            const char *,    // COL_CHECKBOX_VISIBLE
                            const char *);   // COL_CHECKBOX_DESCRIPTION

    void form_precheckbox(  const char *,    // COL_CHECKBOX_NAME
                            const char *,    // COL_CHECKBOX_VALUE
                            const char *,    // COL_CHECKBOX_VISIBLE
                            const char *);   // COL_CHECKBOX_DESCRIPTION
    void form_reset();

    void form_password(const char *pszName,
                       const char *pszValue,
                       const char *pszsize,
                       const char *pszVisible,
                       const char *pszDescr);
    void form_submit();

    void form_select(const char * pszSelectName,
                     std::vector<std::string> selectValues,
                     const char *pszSelectClass);

    void form_files_select(const char * pszSelectName,
                          const char * pszSelectPath,
                          const char * pszSelectClass);

    void form_text(const char *pszName,
                   const char *pszSize,
                   const char *pszValue,
                   const char *pszVisible,
                   const char *pszReadonly,
                   const char *pszDescr,
                   const char *pszClass);

    void form_text(const char *pszName,    // COL_TEXT_NAME
                   const char *pszId,      // COL_TEXT_ID
                   const char *pszSize,    // COL_TEXT_SIZE
                   const char *pszValue,   // COL_TEXT_VALUE
                   const char *pszVisible, // COL_TEXT_VISIBLE
                   const char *pszDescr);  // COL_TEXT_DESCR

    void form_text(const char * szName,
                   const char * szID,
                   const char * szValue,
                   const char * szSize,
                   const char * szVisible,
                   const char * szReadonly,
                   const char * szDescr,
                   const char * szClass);

    void form_textarea(const char *pszName,    // COL_TEXTAREA_NAME
                       const char *pszID,      // COL_TEXTAREA_ID
                       const char *pszCols,    // COL_TEXTAREA_COLS
                       const char *pszRows,    // COL_TEXTAREA_ROWS
                       const char *pszWrap);   // COL_TEXTAREA_WRAP

    void form_textarea(const char *pszName,
                       const char * pszID,
                       const char * pszCols,
                       const char * pszRows,
                       const char * pszWrap,
                       const char * pszClass,
                       const char * pszValue);

    void form_time(    const char *pszName,    // COL_DATE_NAME
                       const char *pszId,      // COL_DATE_ID
                       const char *pszValue,   // COL_DATE_VALUE
                       const char *pszDescr);  // COL_DATE_DESCR

    void form_week(    const char *pszName,    // COL_WEEK_NAME
                       const char *pszId,      // COL_WEEK_ID
                       const char *pszValue,   // COL_WEEK_VALUE
                       const char *pszDescr);  // COL_WEEK_DESCR

    void hidden(const char *pszName,const char *pszValue);

    void imgsrc(const char *,int,int);

    // MORE TAG PRIMITIVES

    void open_body();

    void open_div(const char * pszDivClass);

    void open_form(const char * pszSchemaName,
                   const char * pszCgiFilename,
                   const char * pszProt,
                   int          handle,
                   const char * pszID,
                   const char * pszTarget = "_self");

    void open_head();

    void open_html();

    void open_script();

    void open_table(int border);


    void para();

    void print(const char *);
    void printv(const char *pszFormat,...);
    void printvar(const char *,const char *);
    void printvar(const char *,int);
    void printvar(const char *,double);
    void printvar(const char *,bool);

    void script_button(const char * pszButtonName,const char * pszVisible);

    void set_style(const char * pszStylesheet);

    void title(const char *);

    void xahref(const char * pszLink,
                const char * pszButtonClass,
                const char * pszButtonDisplay);

};


#endif //MULTIWARE_CGIHTML_H
