////////////////////////////////////////////////////////////////////
// ~/public_html/fw/htmlbind.h 2025-07-16 08:08 dwg -             //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#pragma once

class htmlbind
{
public:
    htmlbind();

    std::string hb_ahref(
        const char* szUrl,
        const char* szImgUrl,
        int width,
        int height);

    std::string hb_imgsrc(
        const char* szImgUrl,
        int width,
        int height);

    std::string hb_close_body();
    std::string hb_close_form();
    std::string hb_close_h3();
    std::string hb_close_head();
    std::string hb_close_html();
    std::string hb_close_table();
    std::string hb_close_td();
    std::string hb_close_th();
    std::string hb_close_tr();

    std::string hb_dashboard(int iHandle, int iButtons);

    std::string hb_form_date(
        const char* pszName,
        const char* pszID,
        const char* pszValue,
        const char* pszDescr);

    std::string hb_form_datetime(
        const char* pszName,
        const char* pszID,
        const char* pszValue,
        const char* pszDescr);

    std::string hb_form_label(
        const char* pszVisible);


    std::string hb_form_month(
        const char* pszName,
        const char* pszId,
        const char* pszValue,
        const char* pszDescr);

    std::string hb_form_select(
        const char* pszLabelFor,
        const char* pszLabelVisible,
        const char* pszSelectID,
        const char* pszSelectName);

    std::string hb_form_select_opt(
        const char* pszDefaultBoolean,
        const char* pszOptionValue,
        const char* pszOptionVisible);

    std::string hb_form_select_end();

    std::string hb_form_text(
        const char* szName,
        const char* szValue,
        const char* szSize,
        const char* szVisible,
        const char* szDescr);

    std::string hb_form_password(
        const char* pszName,
        const char* pszId,
        const char* pszValue,
        const char* pszSize,
        const char* pszVisible,
        const char* pszDescr);

    std::string hb_open_h3();
    std::string hb_open_table(int iBorder);
    std::string hb_open_tr();
    std::string hb_open_td();
    std::string hb_open_th();
};

//////////////////////
// eof - htmlbind.h //
//////////////////////
