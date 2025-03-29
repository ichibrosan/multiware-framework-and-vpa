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

};

#endif //HTMLBIND_H
