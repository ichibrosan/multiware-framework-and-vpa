////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/htmlbind.cpp  2025/03/28                 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"
#include "htmlbind.h"

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
    const char *szUrl,
    const char *szImgUrl,
    int width,
    int height)
{
    std::string ssBuffer;
    ssBuffer = "<a href=\"";
    ssBuffer.append(gpSh->m_pShMemng->szCgiRoot);
    ssBuffer.append(szUrl);
    ssBuffer.append("\">");
    ssBuffer.append(hb_imgsrc(szImgUrl,width,height));
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
    const char *szImgUrl,
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
    ssBuffer.append("\" />");
    return ssBuffer;
}
