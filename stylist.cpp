////////////////////////////////////////////////////////////////////
// ~/public_html/fw/stylist.cpp 2025-07-15 18:16 dwg -            //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * @brief Provides a CSS style definition for a default button.
 *
 * This character array defines a CSS styling class `.default_button`. The styling
 * includes various properties such as color, font, background gradient, box shadow,
 * borders, padding, and text stroke. It is intended to serve as a predefined styling
 * for UI components requiring a visually distinct and colorful button design.
 */
char sz_default_button[] = {
    "    .default_button\n"
    "    {\n"
    "        text-decoration:  none;\n"
    "        color: #ffffff;\n"
    "        font-size: 24px;\n"
    "        font-family: Arial;\n"
    "        background:linear-gradient(#ffff00, #ff0000);\n"
    "        box-shadow: 5px 5px 10px #000000, 0px 0px 0px 2px #000000;\n"
    "        border-top: #ffff00 3px groove;\n"
    "        border-left: #ffff00 3px groove;\n"
    "        border-right: #ff0000 3px groove;\n"
    "        border-bottom: #ff0000 3px groove;\n"
    "        border-radius: 10px;\n"
    "        -webkit-text-stroke-width: 1px;\n"
    "        -webkit-text-stroke-color: #000000;\n"
    "        padding-left: 10px;\n"
    "        padding-right: 10px;\n"
    "    }\n"
};

/**
 * @brief Stores CSS style rules for the .journal_container class in a C-style string.
 *
 * This char array contains the complete stylesheet definition for the
 * .journal_container class, formatted as CSS rules within a string.
 * The rules include grid-based layout, fixed positioning, and size specifications.
 */
char sz_journal_container[] = {
    "    .journal_container\n"
    "    {\n"
    "        position: fixed;\n"
    "        top: 0;\n"
    "        left: 0;\n"
    "        grid-template-columns: repeat(2, 29ch) repeat(2, 27ch);\n"
    "        grid-template-rows: repeat(4, 7cap);\n"
    "        width: 112ch;\n"
    "        height: 27.2cap;\n"
    "        display: grid;\n"
    "    }\n"
};

/**
 * @brief CSS style definition for an HTML iframe element with the class "journal_iframe".
 *
 * This character array stores the styling rules for the .journal_iframe CSS class.
 * The rules include dimensions for width and height, and the border style is set to none.
 */
char sz_journal_iframe[] = {
    "    .journal_iframe\n"
    "    {\n"
    "        width: 150ch;\n"
    "        height: 27.2cap;\n"
    "        border-style: none;\n"
    "    }\n"
};

/**
 * Defines the CSS style for the "journal_edit" class.
 *
 * This array contains the CSS rules for the "journal_edit" class,
 * specifying its styling properties. It includes details for elements
 * such as alignment and layout.
 */
char sz_journal_edit[] = {
    "    .journal_edit\n"
    "    {\n"
    "        margin: auto\n"
    "    }\n"
};

/**
 * @brief Represents a string containing the CSS style for a save button in the journal.
 *
 * This variable holds the CSS styling class `.journal_save`. The defined style includes
 * properties that determine the visual appearance of the journal save button in the user interface,
 * such as its colors, spacing, borders, and any additional decorative effects.
 */
char sz_journal_save[] = {
    "    .journal_save\n"
    "    {\n"
    "        grid-column-start: 3;\n"
    "        grid-row-start: 2;\n"
    "        margin: auto;\n"
    "        text-decoration:  none;\n"
    "        color: #%06X;\n"
    "        font-size: 24px;\n"
    "        font-family: Arial;\n"
    "        background:linear-gradient(#ffff00, #ff0000);\n"
    "        box-shadow: 5px 5px 10px #000000, 0px 0px 0px 2px #000000;\n"
    "        border-top: #ffff00 3px groove;\n"
    "        border-left: #ffff00 3px groove;\n"
    "        border-right: #ff0000 3px groove;\n"
    "        border-bottom: #ff0000 3px groove;\n"
    "        border-radius: 10px;\n"
    "        -webkit-text-stroke-width: 1px;\n"
    "        -webkit-text-stroke-color: #000000;\n"
    "        padding-left: 10px;\n"
    "        padding-right: 10px;\n"
    "    }\n"
};

/**
 * @brief A CSS class definition for a `.journal_reset` styling block.
 *
 * The `sz_journal_reset` variable contains the CSS rules for styling elements with
 * the `.journal_reset` class. This styling includes grid placement, margins, text
 * properties, font settings, a gradient background, box shadow, border styling, and
 * padding definitions.
 *
 * The styling details are defined in a single character array to allow embedding
 * of CSS definitions directly within C++ code.
 *
 * @note This variable is typically used in conjunction with functions that return
 * or manipulate HTML or CSS content.
 */
char sz_journal_reset[] = {
    "    .journal_reset\n"
    "    {\n"
    "        grid-column-start: 3;\n"
    "        grid-row-start: 3;\n"
    "        margin: auto;\n"
    "        text-decoration:  none;\n"
    "        color: #ffffff;\n"
    "        font-size: 24px;\n"
    "        font-family: Arial;\n"
    "        background:linear-gradient(#ffff00, #ff0000);\n"
    "        box-shadow: 5px 5px 10px #000000, 0px 0px 0px 2px #000000;\n"
    "        border-top: #ffff00 3px groove;\n"
    "        border-left: #ffff00 3px groove;\n"
    "        border-right: #ff0000 3px groove;\n"
    "        border-bottom: #ff0000 3px groove;\n"
    "        border-radius: 10px;\n"
    "        -webkit-text-stroke-width: 1px;\n"
    "        -webkit-text-stroke-color: #000000;\n"
    "       padding-left: 10px;\n"
    "       padding-right: 10px;\n"
    "   }\n"
};

/**
 * @brief Stores the CSS styling for a textarea element identified as 'journal_textarea'.
 *
 * This variable contains a string representing CSS rules for the 'journal_textarea' class.
 * The styles define the layout, dimensions, appearance, and behavior of the textarea
 * within a grid structure, including its background color, text color, grid positions,
 * border, padding, margin, resizing behavior, and size constraints.
 */
char sz_journal_textarea[] = {
    "    .journal_textarea\n"
    "    {\n"
    "        grid-column-start: 1;\n"
    "        grid-column-end: 3;\n"
    "        grid-row-start: 1;\n"
    "        grid-row-end: 5;\n"
    "        background: #d0e7ab;\n"
    "        color: black;\n"
    "        margin: 0;\n"
    "        padding: 0;\n"
    "        resize: none;\n"
    "        box-sizing: border-box;\n"
    "        border: black;\n"
    "        width: 79ch;\n"
    "        height: 48cap;\n"
    "        max-height:100%;\n"
    "        max-width: 100%;\n"
    "    }\n"
};

/**
 * Defines a constant character array containing the CSS style rules
 * for the "table" element.
 *
 * The CSS within this array specifies the text color and background
 * color for the "table" element.
 */
char sz_table[] = {
    "   table\n"
    "   {\n"
    "       color: #%06X;\n"
    "       background: #%06X;\n"
    "   }\n"
};

/**
 * A C-style character array containing CSS styles for the body element.
 *
 * This array defines the CSS properties for the body tag, including:
 * - Text color (black).
 * - Background color (#d7e0ab).
 */
char sz_body[] = {
    "    body\n"
    "    {\n"
    "        color: #%06X;\n"
    "        background: #%06X;\n"
    "    }\n"
};

/**
 * @brief Represents the CSS style definition for the `<tr>` HTML element.
 *
 * The `sz_tr` variable contains a string with the CSS properties and
 * values applied to the `<tr>` tag. Specifically, it defines the text
 * color as `#000000` and the background color as `#7060d0`.
 */
char sz_tr[] = {
    "    tr\n"
    "    {\n"
    "        color: #%06X;\n"
    "        background: #%06X;\n"
    "    }\n"
};

/**
 * This character array defines the CSS styles for the `<th>` (table header) HTML element.
 * It specifies the default text color and background color for the table headers.
 *
 * The CSS rules include:
 * - `color`: Sets the text color of the table header to black (`#000000`).
 * - `background`: Sets the background color of the table header to a shade of grey-blue (`#405060`).
 */
char sz_th[] = {
    "    th\n"
    "    {\n"
    "        color: #%06X;\n"
    "        background: #%06X;\n"
    "    }\n"
};

/**
 * Contains a character array specifying the CSS styles for the
 * "dashboard" class.
 *
 * The "dashboard" class includes properties for text color and
 * background color:
 * - `color: #ffffff;` sets the text color.
 * - `background: #cacaac;` sets the background color.
 *
 * This array is utilized in the implementation to generate
 * and return a formatted CSS string.
 */
char sz_dot_dashboard[] = {
    "   .dashboard\n"
    "    {\n"
    "        color: #%06X;\n"
    "        background: #%06X;\n"
    "    }\n"
};

/**
 * The sz_td array defines the CSS styling rules for the `<td>` HTML element.
 *
 * This C-style string includes properties such as:
 * - `color`: Sets the text color using the hexadecimal value `#4040404`.
 * - `background`: Defines the background color using the hexadecimal value `#4050d0`.
 */
char sz_td[] = {
    "   td\n"
    "    {\n"
    "        color: #%06X;\n"
    "        background: #%06X;\n"
    "    }\n"
};

/**
 * @brief A global character buffer used for returning style strings in stylist methods.
 *
 * This buffer is declared with a size `BUFSIZ` which provides enough space
 * to store CSS style definitions used by the stylist class methods. It is used
 * by functions like `stylist::default_button()`, `stylist::journal_container()`,
 * and `stylist::journal_iframe()` to format and return the corresponding
 * CSS style strings.
 *
 * @note This buffer is shared among the stylist class methods. Each method
 * overwrites its content before returning. Therefore, if multiple calls
 * to these methods are made in succession, the caller must handle the
 * returned string immediately before making another call.
 *
 * @attention This global buffer is not thread-safe, and concurrent access
 * to the stylist methods might lead to undefined behavior.
 */
char szReturn[BUFSIZ];

/**
 * @brief Constructor for the `stylist` class. This constructor generates
 * a CSS file containing styling information by writing the result of
 * various style-related methods into a specified file.
 *
 * The generated CSS file is stored at "/home/devo/public_html/fw/styles/exp.css".
 * Each line in the file corresponds to the output of a specific styling method.
 *
 * @return void
 */
stylist::stylist(int handle)
{
    // std::string ssCssFQFS =
    //     "/home/devo/public_html/fw/styles/doug.css";

    std::string ssUser = gpSh->m_pShMemng->szUser;
    std::string ssCssFQFS = gpOS->genStyleFQFS(
        (const char*)ssUser.append(".css").c_str(), false);
    gpSysLog->loginfo(ssCssFQFS.c_str());

    FILE* fp = fopen(ssCssFQFS.c_str(), "w");
    fprintf(fp, "%s\n", default_button());
    fprintf(fp, "%s\n", journal_container());
    fprintf(fp, "%s\n", journal_iframe());
    fprintf(fp, "%s\n", journal_edit());
    fprintf(fp, "%s\n", journal_save());
    fprintf(fp, "%s\n", journal_reset());
    fprintf(fp, "%s\n", journal_textarea());

    fprintf(fp, "%s\n", table(
                gpSh->m_pShMemng->prefs[handle].szTableFGcolor,
                gpSh->m_pShMemng->prefs[handle].szTableFGcolor)
    );

    fprintf(fp, "%s\n", body(
                gpSh->m_pShMemng->prefs[handle].szBodyFGcolor,
                gpSh->m_pShMemng->prefs[handle].szBodyBGcolor)
    );

    fprintf(fp, "%s\n", tr(
                gpSh->m_pShMemng->prefs[handle].szTrFGcolor,
                gpSh->m_pShMemng->prefs[handle].szTrBGcolor)
    );

    fprintf(fp, "%s\n", th(
                gpSh->m_pShMemng->prefs[handle].szThFGcolor,
                gpSh->m_pShMemng->prefs[handle].szThBGcolor)
    );

    fprintf(fp, "%s\n", dot_dashboard(
                gpSh->m_pShMemng->prefs[handle].szDbFGcolor,
                gpSh->m_pShMemng->prefs[handle].szDbBGcolor)
    );

    fprintf(fp, "%s\n", td(
                gpSh->m_pShMemng->prefs[handle].szTdFGcolor,
                gpSh->m_pShMemng->prefs[handle].szTdBGcolor)
    );

    fclose(fp);
}

/**
 * Generates and returns the CSS style for the default button.
 *
 * This method composes a CSS string representing the default style
 * properties of a button, including various visual aspects like
 * background, font, color, and more.
 *
 * @return A pointer to a constant character array containing
 * the CSS string defining the default button style.
 */
const char* stylist::default_button()
{
    sprintf(szReturn, "%s", sz_default_button);
    return szReturn;
}

/**
 * Retrieves the CSS styling for the "journal_container" class.
 *
 * This function returns a pointer to a C-style string containing the
 * CSS rules specifically designed for styling elements with the
 * "journal_container" class.
 *
 * @return A pointer to a constant character string containing the CSS
 *         rules for the "journal_container" class.
 */
const char* stylist::journal_container()
{
    sprintf(szReturn, "%s", sz_journal_container);
    return szReturn;
}

/**
 * Retrieves the CSS style definition for the "journal_iframe" element.
 *
 * @return A constant character pointer containing the CSS style rules
 * for the "journal_iframe" element.
 */
const char* stylist::journal_iframe()
{
    sprintf(szReturn, "%s", sz_journal_iframe);
    return szReturn;
}

/**
 * Provides the CSS style details for the "journal_edit" class.
 *
 * This method generates and returns the style definition for the
 * CSS class "journal_edit" as a C-string.
 *
 * @return A pointer to a constant character array containing the
 * CSS definition for the "journal_edit" class.
 */
const char* stylist::journal_edit()
{
    sprintf(szReturn, "%s", sz_journal_edit);
    return szReturn;
}

/**
 * Retrieves the CSS style definition for the "journal_save" element.
 *
 * This function returns a pointer to a C-style string containing the
 * CSS rules associated with the "journal_save" style. The string
 * includes declarations specifying how the "journal_save" element
 * should be styled in the application's context.
 *
 * @return A constant character pointer to the CSS style string for
 * the "journal_save" element.
 */
const char* stylist::journal_save()
{
    sprintf(szReturn, "%s", sz_journal_save);
    return szReturn;
}

/**
 * Retrieves the CSS styling information for the "journal_reset"
 * element.
 *
 * This function generates the style string for resetting a journal
 * element and returns it as a constant character pointer.
 *
 * @return A pointer to a constant character string containing the
 * CSS styling for the "journal_reset" element.
 */
const char* stylist::journal_reset()
{
    sprintf(szReturn, "%s", sz_journal_reset);
    return szReturn;
}

/**
 * Retrieves the CSS style definition for the "journal_textarea" element.
 *
 * This method provides the styling properties for the "journal_textarea"
 * class, which is used to define the appearance and behavior of a textarea
 * within a journal framework.
 *
 * @return A constant character pointer to a string containing the
 * CSS style rules for the "journal_textarea" element.
 */
const char* stylist::journal_textarea()
{
    sprintf(szReturn, "%s", sz_journal_textarea);
    return szReturn;
}

/**
 * Generates and returns the CSS style for the "table" element.
 *
 * This method creates a CSS definition for the "table" style, stores it
 * internally, and returns a pointer to the generated CSS string.
 *
 * @return A pointer to a constant character array containing the CSS
 * style rules for the "table" element.
 */
const char* stylist::table(char* color, char* background)
{
    sprintf(szReturn, sz_table, color, background);
    return szReturn;
}

/**
 * Retrieves the CSS style definition for the body element in the stylesheet.
 *
 * This method constructs and returns a string containing the CSS rules
 * defined for the `body` element.
 *
 * @return A constant character pointer to the string containing the
 * CSS representation of the body element's style.
 */
const char* stylist::body(char* color, char* background)
{
    sprintf(szReturn, sz_body, color, background);
    return szReturn;
}

/**
 * Retrieves the CSS style rules for the "tr" (table row) HTML element.
 *
 * This method provides the styling information defined for the table row
 * element, and returns it as a constant character pointer.
 *
 * @return A constant pointer to a character string containing the CSS
 *         definition for the "tr" element.
 */
const char* stylist::tr(char* color, char* background)
{
    sprintf(szReturn, sz_tr, color, background);
    return szReturn;
}

/**
 * Provides the CSS styling for HTML table headers (`<th>` elements).
 *
 * This method retrieves the style rules for table header elements and
 * returns them as a constant character string.
 *
 * @return A pointer to a constant character string containing the
 * CSS properties and values for the styles applied to table header elements.
 */
const char* stylist::th(char* color, char* background)
{
    sprintf(szReturn, sz_th, color, background);
    return szReturn;
}

/**
 * Retrieves the CSS style definition for the "dot_dashboard" element.
 *
 * This method generates the CSS string associated with the
 * "dot_dashboard" element, utilizing internal implementation details
 * to format the output.
 *
 * @return A constant character pointer containing the CSS style
 * definition for the "dot_dashboard" element.
 */
const char* stylist::dot_dashboard(char* color, char* background)
{
    sprintf(szReturn, sz_dot_dashboard, color, background);
    return szReturn;
}

/**
 * Retrieves the CSS style definitions for the `<td>` element.
 *
 * @return A constant pointer to a character array containing the
 * CSS style rules for the `<td>` element.
 */
const char* stylist::td(char* color, char* background)
{
    sprintf(szReturn, sz_td, color, background);
    return szReturn;
}
