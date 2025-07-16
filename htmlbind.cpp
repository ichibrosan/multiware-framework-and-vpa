////////////////////////////////////////////////////////////////////
// ~/public_html/fw/htmlbind.cpp 2025-07-15 18:16 dwg -           //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"
//#include "htmlbind.h"

/**************************************************
 * Default constructor for the htmlbind class.
 *
 * Initializes an instance of the htmlbind class.
 *
 * @return Nothing.
 **************************************************/
htmlbind::htmlbind() = default;


/**
 * Generates an HTML anchor tag (<a>) that wraps an image specified by the
 * input parameters. The function uses the provided relative URL and image
 * source, appends the CGI root path from shared memory, and includes width
 * and height attributes for the image.
 *
 * @param szUrl A null-terminated string specifying the relative URL for the
 * anchor tag.
 * @param szImgUrl A null-terminated string specifying the URL of the image
 * to be embedded within the anchor tag.
 * @param width The width of the image to be included in the anchor tag.
 * A positive integer value.
 * @param height The height of the image to be included in the anchor tag.
 * A positive integer value.
 * @return A std::string containing the complete HTML anchor tag with the
 * image embedded inside.
 */
std::string htmlbind::hb_ahref(
    const char* szUrl,
    const char* szImgUrl,
    int width,
    int height)
{
    std::string ssBuffer;
    ssBuffer = "<a href=\"";
    ssBuffer.append(gpSh->m_pShMemng->szCgiRoot);
    ssBuffer.append(szUrl);
    ssBuffer.append("\">");
    ssBuffer.append(hb_imgsrc(szImgUrl, width, height));
    ssBuffer.append("</a>");
    return ssBuffer;
}


/*************************************************************************
 * Generates an HTML image tag string using the provided image URL, width,
 * and height.
 *
 * @param szImgUrl The relative URL of the image. It is appended to the
 * image root directory.
 * @param width The width of the image.
 * @param height The height of the image.
 * @return A string containing the constructed HTML image tag.
 *************************************************************************/
std::string htmlbind::hb_imgsrc(
    const char* szImgUrl,
    int width,
    int height)
{
    std::string ssBuffer;
    ssBuffer = "<img src=\"";
    ssBuffer.append(gpSh->m_pShMemng->szImgRoot);
    ssBuffer.append(szImgUrl);
    ssBuffer.append("\" width=\"");
    ssBuffer.append(std::to_string(width));
    ssBuffer.append("\" height=\"");
    ssBuffer.append(std::to_string(height));
    ssBuffer.append("\" />\n");
    return ssBuffer;
}

std::string htmlbind::hb_close_body()
{
    std::string ssBuffer;
    ssBuffer = "</body>\n";
    return ssBuffer;
}

std::string htmlbind::hb_close_form()
{
    std::string ssBuffer;
    ssBuffer = "</form>\n";
    return ssBuffer;
}

std::string htmlbind::hb_close_h3()
{
    std::string ssBuffer;
    ssBuffer.append("</h3>\n");
    return ssBuffer;
}

std::string htmlbind::hb_close_head()
{
    std::string ssBuffer;
    ssBuffer = "</head>\n";
    return ssBuffer;
}

std::string htmlbind::hb_close_html()
{
    std::string ssBuffer;
    ssBuffer = "</html>\n";
    return ssBuffer;
}

std::string htmlbind::hb_form_date(
    const char* pszName,
    const char* pszID,
    const char* pszValue,
    const char* pszDescr)
{
    std::string ssBuffer;
    ssBuffer = "<label";
    ssBuffer.append(" for=\"");
    ssBuffer.append(pszID);
    ssBuffer.append("\">");
    ssBuffer.append(pszDescr);
    ssBuffer.append("</label>\n");
    ssBuffer.append("<input");
    ssBuffer.append(" type=\"date\"");
    ssBuffer.append(" name=\"");
    ssBuffer.append(pszName);
    ssBuffer.append("\"");
    ssBuffer.append(" id=\"");
    ssBuffer.append(pszID);
    ssBuffer.append("\"");
    ssBuffer.append(" value=\"");
    ssBuffer.append(pszValue);
    ssBuffer.append("\" />\n");
    return ssBuffer;
}

std::string htmlbind::hb_form_datetime(
    const char* pszName,
    const char* pszID,
    const char* pszValue,
    const char* pszDescr)
{
    std::string ssBuffer;
    ssBuffer = "<label";
    ssBuffer.append(" for=\"");
    ssBuffer.append(pszID);
    ssBuffer.append("\">");
    ssBuffer.append(pszDescr);
    ssBuffer.append("</label>\n");
    ssBuffer.append("<input");
    ssBuffer.append(" type=\"datetime-local\"");
    ssBuffer.append(" name=\"");
    ssBuffer.append(pszName);
    ssBuffer.append("\"");
    ssBuffer.append(" id=\"");
    ssBuffer.append(pszID);
    ssBuffer.append("\"");
    ssBuffer.append(">\n");
    return ssBuffer;
}

std::string htmlbind::hb_form_label(const char* pszVisible)
{
    return pszVisible;
}

std::string htmlbind::hb_form_month(
    const char* pszName,
    const char* pszId,
    const char* pszValue,
    const char* pszDescr)
{
    std::string ssBuffer;
    ssBuffer = "<label";
    ssBuffer.append(" for=\"");
    ssBuffer.append(pszId);
    ssBuffer.append("\">");
    ssBuffer.append(pszDescr);
    ssBuffer.append("</label>\n");
    ssBuffer.append("<input");
    ssBuffer.append(" type=\"month\"");
    ssBuffer.append(" name=\"");
    ssBuffer.append(pszName);
    ssBuffer.append("\"");
    ssBuffer.append(" value=\"");
    ssBuffer.append(pszId);
    ssBuffer.append("\"");
    ssBuffer.append(" size=\"");
    ssBuffer.append(pszValue);
    ssBuffer.append("\?>");
    return ssBuffer;
}

std::string htmlbind::hb_form_select(
    const char* pszLabelFor,
    const char* pszLabelVisible,
    const char* pszSelectID,
    const char* pszSelectName)
{
    std::string ssBuffer;
    ssBuffer = "<label";
    ssBuffer.append(" for=\"");
    ssBuffer.append(pszLabelFor);
    ssBuffer.append("\">");
    ssBuffer.append(pszLabelVisible);
    ssBuffer.append("</label>\n");
    ssBuffer.append("<select");
    ssBuffer.append(" id=\"");
    ssBuffer.append(pszSelectID);
    ssBuffer.append("\"");
    ssBuffer.append(" name=\"");
    ssBuffer.append(pszSelectName);
    ssBuffer.append("\">\n");
    return ssBuffer;
}

std::string htmlbind::hb_form_select_opt(
    const char* pszDefaultBoolean,
    const char* pszOptionValue,
    const char* pszOptionVisible)
{
    std::string ssBuffer;
    if (0 == strcmp("true", pszDefaultBoolean))
    {
        ssBuffer = "<option";
        ssBuffer.append(" value=\"");
        ssBuffer.append(pszOptionValue);
        ssBuffer.append("\"");
        ssBuffer.append(" selected=\"selected\"");
        ssBuffer.append(">");
        ssBuffer.append(pszOptionVisible);
        ssBuffer.append("</option>\n");
    }
    else
    {
        ssBuffer = "<option";
        ssBuffer.append(" value=\"");
        ssBuffer.append(pszOptionValue);
        ssBuffer.append("\"");
        ssBuffer.append(pszOptionVisible);
        ssBuffer.append("</option>\n");
    }
    return ssBuffer;
}

std::string htmlbind::hb_form_select_end()
{
    std::string ssBuffer;
    ssBuffer = "</select>\n";
    return ssBuffer;
}

std::string htmlbind::hb_form_text(
    const char* szName,
    const char* szValue,
    const char* szSize,
    const char* szVisible,
    const char* szDescr)
{
    std::string ssBuffer;
    ssBuffer.append("<input");
    ssBuffer.append(" type=\"text\"");
    ssBuffer.append(" name=\"");
    ssBuffer.append(szName);
    ssBuffer.append("\"");
    ssBuffer.append(" value=\"");
    ssBuffer.append(szValue);
    ssBuffer.append("\"");
    ssBuffer.append(" size=\"");
    ssBuffer.append(szSize);
    ssBuffer.append("\">\n");
    return ssBuffer;
}


std::string htmlbind::hb_form_password(
    const char* pszName,
    const char* pszId,
    const char* pszValue,
    const char* pszSize,
    const char* pszVisible,
    const char* pszDescr)
{
    std::string ssBuffer;
    ssBuffer.append("<label for=\"");
    ssBuffer.append(pszId);
    ssBuffer.append("\">");
    ssBuffer.append(pszVisible);
    ssBuffer.append("</label>\n");
    ssBuffer.append("<input");
    ssBuffer.append(" type=\"password\"");
    ssBuffer.append(" id=\"");
    ssBuffer.append(pszId);
    ssBuffer.append("\"");
    ssBuffer.append(" name=\"");
    ssBuffer.append(pszName);
    ssBuffer.append("\"");
    ssBuffer.append(" size=\"");
    ssBuffer.append(pszSize);
    ssBuffer.append("\" required>\n");
    return ssBuffer;
};

std::string ssBuffer;

std::string htmlbind::hb_dashboard(int iHandle, int iButtons)
{
    bool bAuthenticated = true;
    bool bAvatarExists = false;
    int iBorder = 2;

    int iEffectiveButtons = iButtons;
    if (ROW_DATA_HDR < iHandle)
    {
        bAuthenticated = false;
        iEffectiveButtons = 0;
    }
    else
    {
        gpSh->m_pShMemng->bDisplaySchema = false;
        gpSh->m_pShMemng->bDisplayShmVars = false;
        gpSh->m_pShMemng->bDisplayEnvVars = false;
    }

    std::string ssAvatar = gpSh->m_pShMemng->creds[iHandle].szAuthUserName;
    ssAvatar.append("_avatar.jpg");
    //    std::string ssBuffer;

    if (std::filesystem::is_regular_file(
        gpOS->genImgPath(ssAvatar.c_str(),F_OK)))
    {
        bAvatarExists = true;
        hb_open_table(4);
        ssBuffer.append("<tr><td class=\"dashboard\">");
        hb_imgsrc(ssAvatar.c_str(), 110, 110);
        ssBuffer.append("</td><td class=\"dashboard\">");
    }
    //
    ssBuffer.append(hb_open_table(iBorder));

    ssBuffer.append(hb_open_tr());
    // ssBuffer.append(hb_open_h3());
    // ssBuffer.append(hb_open_th());
    // ssBuffer.append("Goodall MultiWare Framework Dashboard");
    // ssBuffer.append(hb_close_th());
    // ssBuffer.append(hb_close_h3());
    // ssBuffer.append(hb_close_tr());
    // ssBuffer.append(hb_close_table());
    //
    // ssBuffer.append(hb_open_table(1));
    // ssBuffer.append(hb_open_tr());
    // ssBuffer.append(hb_open_th());
    // ssBuffer.append("Authenticated Username");
    // ssBuffer.append(hb_close_th());
    // ssBuffer.append(hb_open_td());
    // ssBuffer.append(gpSh->m_pShMemng->creds[iHandle].szAuthUserName);
    // ssBuffer.append(hb_close_td());
    // ssBuffer.append(hb_open_th());
    // ssBuffer.append("Semantic Version");
    // ssBuffer.append(hb_close_th());
    // ssBuffer.append(hb_open_td());
    // ssBuffer.append(RLONG);
    // ssBuffer.append(" (");
    // ssBuffer.append(RTYPE);
    // ssBuffer.append(")");
    // ssBuffer.append(hb_close_td());
    // ssBuffer.append(hb_close_tr());
    //
    // ssBuffer.append(hb_open_tr());
    // ssBuffer.append(hb_open_th());
    // ssBuffer.append("Authenticated User");
    // ssBuffer.append(hb_close_th());
    // ssBuffer.append(hb_open_td());
    // ssBuffer.append(gpSh->m_pShMemng->creds[iHandle].szAuthFirstName);
    // ssBuffer.append(" ");
    // ssBuffer.append(gpSh->m_pShMemng->creds[iHandle].szAuthLastName);
    // ssBuffer.append(hb_close_td());
    // ssBuffer.append(hb_open_th());
    // ssBuffer.append("Current Build");
    // ssBuffer.append(hb_close_th());
    // ssBuffer.append(hb_open_td());
    // ssBuffer.append(RDATE);
    // ssBuffer.append(" ");
    // ssBuffer.append(RTIME);
    // ssBuffer.append(hb_close_td());
    // ssBuffer.append(hb_close_tr());
    //
    // ssBuffer.append(hb_open_tr());
    // ssBuffer.append(hb_open_th());
    // ssBuffer.append("Privilege Level");
    // ssBuffer.append(hb_close_th());
    // ssBuffer.append(hb_open_td());
    // ssBuffer.append(gpSh->m_pShMemng->creds[iHandle].szAuthLevel);
    // ssBuffer.append(hb_close_td());
    // ssBuffer.append(hb_close_tr());
    //
    // ssBuffer.append(hb_close_table());
}

std::string htmlbind::hb_open_h3()
{
    std::string ssBuffer;
    ssBuffer.append("<h3>\n");
    return ssBuffer;
}

std::string htmlbind::hb_open_table(int iBorder)
{
    std::string ssBuffer;
    ssBuffer.append("<table");
    ssBuffer.append(" border=\"");
    ssBuffer.append(std::to_string(iBorder));
    ssBuffer.append("\">\n");
    return ssBuffer;
}

