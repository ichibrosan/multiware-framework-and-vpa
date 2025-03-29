////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/htmlbind.h 2025/03/28                    //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#ifndef HTMLBIND_H
#define HTMLBIND_H

class htmlbind {
public:
    htmlbind();

    std::string hb_ahref(
        const char *szUrl,
        const char *szImgUrl,
        int width,
        int height);

    std::string hb_imgsrc(
        const char *szImgUrl,
        int width,
        int height);

    std::string hb_close_body();
    std::string hb_close_form();
    std::string hb_close_head();
    std::string hb_close_html();
    std::string hb_close_table();

    std::string hb_form_date(
        const char *pszName,
        const char *pszID,
        const char *pszValue,
        const char *pszDescr);

    std::string hb_form_datetime(
            const char *pszName,
            const char *pszID,
            const char *pszValue,
            const char *pszDescr);

};

#endif //HTMLBIND_H
