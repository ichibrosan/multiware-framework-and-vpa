////////////////////////////////////////////////////////////////////
// ~/public_html/fw/stylist.h 2025-07-16 08:08 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#pragma once

#include "webcolors.h"
/**
 * @class stylist
 * @brief Provides CSS styling details for various web elements.
 *
 * This class generates predefined CSS styles for several specific UI
 * components.
 * The generated CSS is written to a file during instantiation.
 */
class stylist
{
    /**
     * Constructs a `stylist` object. This constructor generates a set of
     * default CSS styles by invoking various member functions that return
     * style definitions. The generated CSS is written to a file specified
     * by the implementation.
     *
     * @return An instance of the `stylist` class, initializing any
     * necessary internal state and producing CSS for further use.
     */
public:
    stylist(int handle);

    /**
     * Generates and returns the CSS string defining the default button
     * style.
     *
     * The returned CSS string includes properties for text decoration,
     * color, font size, font family, background gradients, box shadow,
     * border styles, border radius, text-stroke, and padding.
     *
     * @return A pointer to a constant character string containing the
     * CSS definition for the default button style.
     */
    const char* default_button();

    /**
     * Generates the CSS style for the "journal_container" class.
     *
     * @return A pointer to a C-style string containing the CSS style for
     * the "journal_container" class.
     */
    const char* journal_container();

    /**
     * Generates and provides the CSS styling details for the
     * `journal_iframe` class.
     *
     * @return A pointer to a character array containing the CSS style
     * for the `journal_iframe` class.
     */
    const char* journal_iframe();

    /**
     * Generates the CSS for the "journal_edit" styling class and returns
     * it as a string.
     *
     * @return A pointer to a string containing the CSS for the
     * "journal_edit" class.
     */
    const char* journal_edit();

    /**
     * Retrieves the CSS style definition for the "journal_save" element.
     *
     * @return A C-string containing the CSS declaration for the
     * "journal_save" style.
     */
    const char* journal_save();

    /**
     * Generates and returns styling information for the journal reset
     * button.
     *
     * This method provides the CSS style specification for resetting
     * a journal element in the stylist framework. It returns the
     * style details as a character pointer.
     *
     * @return A pointer to a constant character string that contains
     * the CSS representation of the journal reset style.
     */
    const char* journal_reset();

    /**
     * Generates and returns the CSS styling for the
     * "journal_textarea" class.
     *
     * The "journal_textarea" CSS specifies the appearance and layout
     * for a textarea within a journal, including properties such as
     * grid positioning, background color, font color, and dimensions.
     *
     * @return A C-string containing the CSS styling for the
     * "journal_textarea" class.
     */
    const char* journal_textarea();

    /**
     * Generates and returns the CSS style for the "table" element.
     *
     * @return A pointer to a constant character array containing the
     * CSS styles for the "table" element.
     */
    const char* table(char* color, char* background);

    /**
     * Retrieves the CSS styling for the body element.
     *
     * @return A constant character pointer to the CSS styling string
     * for the body element.
     */
    const char* body(char* color, char* background);

    /**
     * Returns the style rules defined for the `tr` HTML element.
     *
     * @return A const char pointer to a string containing CSS rules
     *         for the `tr` HTML element.
     */
    const char* tr(char* color, char* background);

    /**
     * Provides the CSS styling for HTML table headers (`<th>` elements).
     *
     * @return A constant character pointer containing the CSS properties
     * and values for the styles applied to table header elements.
     */
    const char* th(char* color, char* background);

    /**
     * Retrieves the CSS style definition for the dashboard class.
     *
     * @return A C-string containing the CSS style definition for the
     * dashboard class.
     */
    const char* dot_dashboard(char* color, char* background);

    /**
     * Retrieves the CSS style definitions for the `<td>` element.
     *
     * @return A constant pointer to a character array containing the
     * CSS style rules for the `<td>` element.
     */
    const char* td(char* color, char* background);
};

/////////////////////
// eof - stylist.h //
/////////////////////
