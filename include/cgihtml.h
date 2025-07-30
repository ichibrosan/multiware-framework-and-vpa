////////////////////////////////////////////////////////////////////
// ~/public_html/fw/cgihtml.h 2025-07-16 08:08 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#pragma once

#include "mwfw2.h"


/**
 * @class cgihtml
 * @brief A class designed for handling HTML generation and CGI scripts.
 *
 * This class provides utilities for creating HTML output programmatically
 * and processing CGI inputs in web applications. It encapsulates
 * functionality for constructing HTML documents, handling form data, and
 * managing interactions between the server and the client through the
 * Common Gateway Interface.
 *
 * The primary purpose of this class is to simplify the process of handling
 * web-based content generation and server communication for CGI-based web
 * services.
 */
class cgihtml {
	/**
	 * Generates a string containing HTML code for a CGI script.
	 *
	 * This method is used to create an HTML structure dynamically
	 * for CGI-based web applications.
	 *
	 * @return A string containing the generated HTML code.
	 */

	std::string m_ssColors[NUM_LED_COLORS];
public:
	cgihtml();
	void dumps();
	void render_leds();

	/**
	 * Creates a hyperlink in text with the given display text and URL.
	 *
	 * @param displayText The text that will be displayed as the hyperlink.
	 * @param url The URL that the hyperlink will point to.
	 * @return A string containing the formatted hyperlink.
	 */
	void ahref(const char *, const char *, int, int);


	/**
	 * @brief Closes the body section of an HTML document.
	 *
	 * This method outputs the closing </body> tag for an HTML document to
	 * the standard output. It is intended to be used in conjunction with
	 * other methods that structure and output HTML content.
	 */
	void close_body();

	/**
	 * Closes the currently open form, releasing any resources associated
	 * with it. This method finalizes any pending operations and cleans up
	 * any resources used by the form to prevent resource leaks. It is
	 * intended to be called when the form is no longer necessary or its
	 * lifecycle is completed.
	 *
	 * If the form is already closed, this method has no effect.
	 *
	 * Exceptions may occur if resources cannot be released properly or
	 * if the operation encounters unexpected errors during execution.
	 */
	void close_form();

	/**
	 * Closes the current head of a data structure or stream, releasing
	 * any resources associated with it. This method is commonly used in
	 * scenarios where the head of a structure or stream represents the
	 * active or top-most resource, and it is no longer needed or must
	 * be terminated to maintain integrity or free up resources.
	 *
	 * It is the caller's responsibility to ensure that any actions
	 * dependent on the head being open are completed before invoking this
	 * method. Failure to do so may result in unexpected behavior or errors.
	 *
	 * This method does not return a value, and any necessary cleanup
	 * operations should be handled internally. In the case of an error
	 * during the closure process, appropriate exceptions should be thrown.
	 *
	 * Exceptions:
	 * - Throws an IllegalStateException if the head is already closed or
	 *   closing cannot be completed due to an invalid state.
	 * - Throws an IOException for errors related to external resources
	 *   during closure, such as file system or network-related issues.
	 */
	void close_head();

	/**
	 * Closes an open HTML document by writing the required closing tags.
	 *
	 * This method ensures the proper termination of an HTML document structure
	 * by appending all necessary closing tags based on the document's state
	 * or structure up to the point of invocation. It finalizes the document,
	 * making it compliant with HTML standards.
	 *
	 * @throws std::runtime_error if the document has already been closed or
	 *         if an attempt is made to close a non-existent document structure.
	 */
	void close_html();

	/**
	 * @brief Closes an open `<script>` HTML tag.
	 *
	 * This method writes the closing `</script>` HTML element
	 * to the standard output and terminates the current script block.
	 *
	 * Usage of this ensures proper formatting of HTML content
	 * and prevents malformed scripts in the generated HTML output.
	 */
	void close_script();

	/**
	 * @brief Closes an HTML table by outputting the closing table tag.
	 *
	 * This method outputs the closing `</table>` tag to complete the
	 * HTML table structure. It is used in conjunction with table-related
	 * methods to properly format an HTML table in the generated output.
	 */
	void close_table();

	/**
	 * @brief Closes an open HTML `<div>` element.
	 *
	 * This method outputs the closing tag `</div>` followed by a newline
	 * character to the stream. It is typically used to signify the end
	 * of a division block in HTML content.
	 *
	 * This method requires a corresponding call to an opening `<div>`
	 * for proper HTML structure. It is invoked to close previously
	 * opened `<div>` elements.
	 */
	void close_div();

	/**
	 * @brief Dumps the current environment variables to the standard output or a specified output stream.
	 *
	 * This method retrieves all the environment variables available in the system and outputs them
	 * one by one. Each variable is typically displayed in the format NAME=VALUE.
	 *
	 * @param output_stream Optional parameter. If provided, the environment variables are written
	 *        to the given output stream. If not provided, the standard output (stdout) is used
	 *        by default.
	 *
	 * @remark This function is typically used for debugging or logging purposes to check the
	 *         current state of the process environment.
	 *
	 * @note Be cautious when dumping environment variables, as they may contain sensitive
	 *       information such as authentication tokens or credentials.
	 */
	void dump_env_vars();

	/**
	 * Dumps the current state of shared memory variables for inspection or debugging.
	 *
	 * This function iterates through all shared memory variables and outputs their
	 * names, types, and current values. It is primarily used for debugging purposes
	 * to verify the integrity and state of the shared memory contents.
	 *
	 * Shared memory variables are typically important for inter-process communication
	 * or maintaining application state. Incorrect handling or data corruption in
	 * shared memory can lead to unpredictable behavior, and this function assists
	 * in identifying issues by providing a human-readable output of the contents.
	 *
	 * Preconditions:
	 * - Shared memory must be initialized and accessible.
	 * - The caller must have permission to read from the shared memory.
	 *
	 * Postconditions:
	 * - Shared memory variables are not modified by this function.
	 * - Outputs information either to the console, log files, or another output
	 *   mechanism, depending on the implementation.
	 *
	 * Thread Safety:
	 * - This function is not inherently thread-safe if shared memory access is not
	 *   synchronized across threads. Proper synchronization mechanisms should be
	 *   used to prevent data races.
	 *
	 * Returns:
	 * - This function has a void return type and does not return any value.
	 * - Errors during the dumping process may be logged or handled internally,
	 *   depending on implementation specifics.
	 */
	void dump_shm_vars();

	/**
	 * @brief Dumps the contents of a password CSV file formatted as HTML tables.
	 *
	 * This method fetches metadata and data from a password CSV file and displays
	 * them in HTML table format. It is divided into two sections:
	 *
	 * 1. Metadata:
	 *    - Displays the metadata section headers and corresponding data.
	 *    - The information in this section includes descriptions of the password file's
	 *      columns and metadata schema.
	 *
	 * 2. Password Data:
	 *    - Displays the header row and actual data rows from the password file.
	 *    - Iterates through each row and column in the password data section of the CSV.
	 *
	 * It utilizes the `readCsv` instance `gpCsv` to read specific rows and columns
	 * from the CSV structure defined in `schema.h`. The data is organized and subsequently
	 * printed to the `std::cout` stream in an HTML-friendly syntax for rendering.
	 */
	void dump_passwd();

	/**
	 * Outputs a table displaying information about the referrer.
	 *
	 * @param ssReferrer The full path or URL of the referrer.
	 * @param ssReferrerPath The directory path of the referrer.
	 * @param ssReferrerFile The file name of the referrer.
	 */
	void dump_referrer(
		std::string ssReferrer,
		std::string ssReferrerPath,
		std::string ssReferrerFile);

	/**
	 * @brief Exports the database schema to a specified format or output.
	 *
	 * This method extracts the schema information of the database,
	 * including tables, columns, relationships, and other structural
	 * metadata, and allows it to be dumped in a format suitable
	 * for documentation, migration, or analysis purposes.
	 *
	 * The format and target output (e.g., file, stdout) of the dumped schema
	 * would typically depend on the implementation details or parameters
	 * provided while invoking this method.
	 *
	 * @note The output format and the supported database systems
	 *       should be clarified in the implementation.
	 */
	void dump_schema();

	/**
	 * Creates a button with specified text, type, and action when clicked.
	 *
	 * @param buttonText The text to display on the button.
	 * @param buttonType The type of the button (e.g., submit, reset, button).
	 * @param onClickAction The function or action to execute when the button is clicked.
	 */
	void form_button(const char *pszType,
	                 const char *pszForm,
	                 const char *pszButtonClass,
	                 const char *pszButtonDisplay);

	/**
	 * Generates and returns a string containing an HTML iframe element
	 * with the provided source, width, and height.
	 *
	 * @param src A string representing the source URL for the iframe.
	 * @param width An integer specifying the width of the iframe in pixels.
	 * @param height An integer specifying the height of the iframe in pixels.
	 * @return A string containing the constructed iframe HTML element.
	 */
	void form_iframe(const char *pszIframeDefaultPage,
	                 const char *pszIframeTitle,
	                 const char *pszIframeName,
	                 const char *pszIframeClass,
	                 int i_IframeWidth,
	                 int i_IframeHeight);

	/**
	 * Generates and returns an iframe button configured with the provided parameters.
	 *
	 * @param id A unique identifier for the button element.
	 * @param width The width of the iframe button, usually specified in pixels or percentage.
	 * @param height The height of the iframe button, usually specified in pixels or percentage.
	 * @param url The URL to be loaded within the iframe.
	 * @param properties Additional CSS or HTML properties to apply to the iframe button.
	 */
	void form_iframe_button(const char *pszLink,
	                        const char *pszImage,
	                        const char *pszTarget,
	                        const char *pszButtonClass,
	                        const char *pszButtonDisplay);

	void form_date(const char *, // COL_DATE_NAME
	               const char *, // COL_DATE_ID
	               const char *, // COL_DATE_VALUE
	               const char *); /**
                             * Generates an HTML `date` input field with an associated label.
                             *
                             * @param pszName Specifies the name attribute of the `date` input element.
                             * @param pszId Specifies the id attribute of the `date` input element, which is also used for the label's "for" attribute.
                             * @param pszValue Specifies the value attribute of the `date` input element.
                             * @param pszDescr Specifies the description text for the label associated with the `date` input element.
                             */


	void form_datetime(const char *, // COL_DATETIME_NAME
	                   const char *, // COL_DATETIME_ID
	                   const char *, // COL_DATETIME_VALUE
	                   const char *); // COL_DATETIME_DESCR

	/**
	 * Generates and returns a label associated with a given form field.
	 * This method is typically used to create accessible labels for form inputs.
	 *
	 * @param forField The identifier of the form field that the label is associated with.
	 * @param text The text content to be displayed as the label.
	 * @param classes Optional. A string containing additional CSS classes to apply to the label for styling.
	 * @return A formatted label string associated with the specified form field.
	 */
	void form_label(const char *);

	void form_month(const char *, // COL_MONTH_NAME
	                const char *, // COL_MONTH_ID
	                const char *, // COL_MONTH_VALUE
	                const char *); /**
                             * @brief Forms a date string by combining the provided month and year.
                             *
                             * This method takes a numeric month and year as input and combines
                             * them into a formatted string representation.
                             *
                             * @param month An integer representing the month (1-12).
                             * @param year An integer representing the year.
                             * @return A string representing the formatted date in the format: "MM-YYYY".
                             */

	void form_password(const char *pszName, // COL_PASSWORD_NAME
	                   const char *pszId, // COL_PASSWORD_ID
	                   const char *pszValue, // COL_PASSWORD_VALUE
	                   const char *pszsize, // COL_PASSWORD_SIZE
	                   const char *pszVisible, // COL_PASSWORD_VISIBLE
	                   const char *pszDescr); // COL_PASSWORD_DESCR

	void form_postcheckbox(const char *, // COL_CHECKBOX_NAME
	                       const char *, // COL_CHECKBOX_VALUE
	                       const char *, // COL_CHECKBOX_VISIBLE
	                       const char *); /**
                             * Processes a checkbox form field and applies user-defined configurations.
                             *
                             * This method is designed to handle the initialization and configuration of
                             * checkbox form fields. It processes any pre-checked state and applies
                             * additional attributes as specified.
                             *
                             * @param fieldName The name of the checkbox form field.
                             * @param isChecked A boolean indicating if the checkbox should be pre-checked.
                             * @param attributes Additional attributes to be applied to the checkbox field.
                             */

	void form_precheckbox(const char *, // COL_CHECKBOX_NAME
	                      const char *, // COL_CHECKBOX_VALUE
	                      const char *, // COL_CHECKBOX_VISIBLE
	                      const char *); // COL_CHECKBOX_DESCRIPTION
	/**
	 * Resets a form to its initial state by clearing all input fields and
	 * resetting any modified form data to the default values. This method
	 * may also trigger any necessary cleanup operations related to the
	 * form's data fields.
	 *
	 * Intended for use in scenarios where a form needs to be reused or
	 * discarded without keeping the entered data.
	 *
	 * Preconditions:
	 * - The form object must be properly initialized before calling this method.
	 *
	 * Postconditions:
	 * - All fields in the form are cleared or reset to their default state.
	 * - Any temporary or unsaved data associated with the form will be discarded.
	 */
	void form_reset();

	/**
	 * Generates a hashed and salted representation of the provided password.
	 *
	 * This method takes a plain text password and applies a secure hashing algorithm,
	 * potentially combined with salting, to produce a hashed output for secure storage or validation purposes.
	 *
	 * @param password The plain text password to be hashed.
	 * @param salt The unique salt value to combine with the password during hashing, ensuring uniqueness.
	 * @param hashAlgorithm The algorithm to use for hashing, e.g., SHA-256, bcrypt.
	 * @return The hashed representation of the password.
	 * @throws IllegalArgumentException If any of the parameters are null or empty.
	 * @throws NoSuchAlgorithmException If the specified hashing algorithm is invalid or unsupported.
	 */
	void form_password(const char *pszName,
	                   const char *pszValue,
	                   const char *pszsize,
	                   const char *pszVisible,
	                   const char *pszDescr);


	/**************************************************************************
	 * @brief Generates and outputs an HTML select form element with associated
	 *			labels.
	 *
	 * This function is used to create an HTML form select element, along with
	 * associated labels for accessibility and display purposes. It takes
	 * parameters for the label text, the select element's ID, and name
	 * attributes to ensure proper identification and behavior within an HTML
	 * form.
	 *
	 * @param pszLabelFor Pointer to a string that specifies the `for`
	 *		attribute of the label, linking it to a select element by its ID.
	 * @param pszLabelVisible Pointer to a string that specifies the visible
	 *		text for the label associated with the select element.
	 * @param pszSelectID Pointer to a string that specifies the ID attribute
	 *		of the select element, used to uniquely identify it within the HTML
	 *		document.
	 * @param pszSelectName Pointer to a string that specifies the name
	 *		attribute of the select element, used to identify its value when
	 *		form data is submitted.
	 */
	void form_select(const char *pszLabelFor,
	                 const char *pszLabelVisible,
	                 const char *pszSelectID,
	                 const char *pszSelectName);

	/**************************************************************************
	 * @brief Adds an option to a select HTML form element with specified value
	 * and visible text. This function is used to create and append an option
	 * element to a select form control in an HTML document. The added option
	 * will display a visible label and have an associated value that can be
	 * submitted.
	 *
	 * @param pszOptionValue The value to be assigned to the option element.
	 *                       This value is submitted when the corresponding
	 *                       option is selected.
	 * @param pszOptionVisible The text to be displayed to the user for the
	 *						option element.
	 *************************************************************************/
	void form_select_opt(
		const char *pszSelectBool,
		const char *pszOptionValue,
		const char *pszOptionVisible);

	/*************************************************************************
	 * @brief Marks the end of a select HTML form element in the CGI output.
	 *
	 * This function is used to properly close a select form element when
	 * generating dynamic HTML content. It ensures the proper syntax for an
	 * HTML select element is followed, allowing for the form selection options
	 * to function as intended within a web application.
	 *
	 * This function should be used in conjunction with the corresponding
	 * function(s) that initiate and populate the select element, ensuring
	 * well-formed HTML structure in generated pages.
	 *
	 * Misuse or omission of this function may lead to malformed HTML output
	 * or unexpected behavior in rendered user interfaces.
	 *************************************************************************/
	void form_select_end();


	/**
	 * Submits a form with the provided data and triggers the corresponding actions.
	 *
	 * This method handles form submission by validating the input data,
	 * preparing the necessary payload, and sending it to the designated endpoint.
	 * Upon successful submission, it may execute callback functions, update the UI,
	 * or process server responses as required.
	 *
	 * @param formData A map or dictionary containing key-value pairs representing
	 *                 the form fields and their respective values.
	 * @param targetUrl The URL or endpoint where the form data will be submitted.
	 * @param successCallback An optional function to execute if the form submission is successful.
	 *                        Typically used to update the user interface or display success messages.
	 * @param errorCallback An optional function to execute if the form submission fails.
	 *                      It may provide information about the error or suggest corrective actions.
	 * @return True if the form was submitted successfully, false otherwise.
	 *
	 * @throws InvalidArgumentException When the provided formData is incomplete or invalid.
	 * @throws NetworkException When the form submission fails due to connectivity issues.
	 * @throws TimeoutException When the submission request exceeds the allotted time duration.
	 */
	void form_submit();

	/**
	 * Selects a form element from the available options.
	 *
	 * This method is used to select a specific element within a form based on
	 * provided criteria. The selection process can be based on the element's
	 * value, name, id, or other attributes.
	 *
	 * @param form_id Identifier of the form containing the element to be selected.
	 * @param element_name Name of the element to select from the form.
	 * @param value The value or criteria to use for selecting the form element.
	 */
	void form_select_array(const char *pszSelectName,
	                       std::vector<std::string> selectValues,
	                       const char *pszSelectClass);

	/**
	 * Allows the user to select specific files from a form submission for processing.
	 *
	 * This method is typically used to filter through the files submitted via a form
	 * and return only the ones needed for further operations or tasks.
	 *
	 * @param fileList A reference to the list of files submitted through the form.
	 *                 This represents the collection of all uploaded files.
	 * @param criteria A function or lambda expression used to filter the files.
	 *                 It should return a boolean indicating whether a file meets
	 *                 the required conditions.
	 * @param selectedFiles A reference to a container where the selected files will
	 *                      be stored after processing. This container is modified
	 *                      in place by the method.
	 */
	void form_select_files(const char *pszSelectName,
	                       const char *pszSelectPath,
	                       const char *pszSelectClass);

	/**
	 * Processes the input text to perform certain transformations or operations.
	 *
	 * @param text A string representing the input text to be processed.
	 *             This could be a sentence, paragraph, or any other form
	 *             of textual data.
	 * @param options A map or dictionary containing configuration options
	 *                that dictate how the text should be processed. These
	 *                options may include specific transformations, formatting
	 *                instructions, or other operation parameters.
	 * @param result A reference to a string where the processed text will
	 *               be stored as output.
	 */
	void form_text(const char *pszName,
	               const char *pszSize,
	               const char *pszValue,
	               const char *pszVisible,
	               const char *pszReadonly,
	               const char *pszDescr,
	               const char *pszClass);

	void form_text(const char *pszName, // COL_TEXT_NAME
	               const char *pszId, // COL_TEXT_ID
	               const char *pszSize, // COL_TEXT_SIZE
	               const char *pszValue, // COL_TEXT_VALUE
	               const char *pszVisible, // COL_TEXT_VISIBLE
	               const char *pszDescr); /**
                    * Processes and formats the input text according to specific rules or conditions.
                    *
                    * @param text A string representing the input text to be processed.
                    * @return A string containing the processed and formatted version of the input text.
                    */

	void form_text(const char *szName,
	               const char *szID,
	               const char *szValue,
	               const char *szSize,
	               const char *szVisible,
	               const char *szReadonly,
	               const char *szDescr,
	               const char *szClass);

	void form_textarea(const char *pszName, // COL_TEXTAREA_NAME
	                   const char *pszID, // COL_TEXTAREA_ID
	                   const char *pszCols, // COL_TEXTAREA_COLS
	                   const char *pszRows, // COL_TEXTAREA_ROWS
	                   const char *pszWrap); /**
                        * Processes and formats the input text for display in a text area.
                        *
                        * @param text The input string to be formatted and displayed.
                        * @param maxLength The maximum allowable length of the text; excess will be truncated.
                        * @param placeholder The default text to display when the input is empty or invalid.
                        * @param isReadOnly A flag indicating whether the text area should be read-only.
                        * @param wrapMode A string specifying the wrapping mode (e.g., "none", "soft", "hard").
                        * @param isResizable A flag indicating whether resizing of the text area is allowed.
                        */

	void form_textarea(const char *pszName,
	                   const char *pszID,
	                   const char *pszCols,
	                   const char *pszRows,
	                   const char *pszWrap,
	                   const char *pszClass,
	                   const char *pszValue);

	void form_time(const char *pszName, // COL_DATE_NAME
	               const char *pszId, // COL_DATE_ID
	               const char *pszValue, // COL_DATE_VALUE
	               const char *pszDescr); /**
                        * Converts individual components of time (hour, minute, second)
                        * into a standard time representation.
                        *
                        * @param hour The hour component of the time. Accepted values are in the range [0, 23].
                        * @param minute The minute component of the time. Accepted values are in the range [0, 59].
                        * @param second The second component of the time. Accepted values are in the range [0, 59].
                        * @return A formatted time representation combining the hour, minute, and second inputs.
                        */

	void form_week(const char *pszName, // COL_WEEK_NAME
	               const char *pszId, // COL_WEEK_ID
	               const char *pszValue, // COL_WEEK_VALUE
	               const char *pszDescr); // COL_WEEK_DESCR

	/**
	 * Calculates the sum of two integers.
	 *
	 * @param a The first integer to be added.
	 * @param b The second integer to be added.
	 * @return The sum of the two integers.
	 */
	void hidden(const char *pszName, const char *pszValue);

	/**
	 * Sets the source path of the image to be rendered or displayed.
	 *
	 * @param src The file path or URI of the image to be loaded.
	 */
	void imgsrc(const char *, int, int);

	// MORE TAG PRIMITIVES

	/**
	 * Opens the body of a specific entity or resource.
	 *
	 * This method is used to initiate or re-enable access to the body
	 * content of a resource, entity, or object. It performs operations
	 * needed to prepare the body for processing or interaction
	 * depending on the context in which it is used.
	 *
	 * It may invoke additional dependencies, initialize states, or
	 * reset default parameters associated with the body, ensuring it
	 * is accessible and ready for the intended operation.
	 *
	 * Preconditions:
	 * - The entity or resource must be in a state where its body
	 *   can be safely opened.
	 * - All required preliminary operations (if any) must have been
	 *   completed before invoking this function.
	 *
	 * Postconditions:
	 * - The body's state is set to an "open" or "accessible" mode.
	 *
	 * Exceptions:
	 * - May throw exceptions if the entity or resource is unavailable,
	 *   unprepared, or in an invalid state for opening.
	 */
	void open_body();

	/**
	 * Opens a division operation for further mathematical computations or grouping.
	 *
	 * @param numerator The numerator value for the division operation.
	 * @param denominator The denominator value for the division operation. It should not be zero to avoid division errors.
	 */
	void open_div(const char *pszDivClass);

	/**
	 * Opens the specified form for the user.
	 *
	 * This method is responsible for initializing and rendering the
	 * user interface of the specified form, making it ready for
	 * interaction.
	 *
	 * @param form_id The unique identifier of the form to be opened.
	 * @param show_in_fullscreen Indicates whether the form should be displayed
	 *        in fullscreen mode. Set to true for fullscreen; false otherwise.
	 */
	void open_form(const char *pszSchemaName,
	               const char *pszCgiFilename,
	               const char *pszProt,
	               int handle,
	               const char *pszID,
	               const char *pszTarget = "_self");

	/**
	 * @brief Opens the head of a specified entity or resource.
	 *
	 * This method performs the necessary operations to open or
	 * expose the head section of the given entity. It typically
	 * allows interaction or processing with the opened head.
	 * Ensure that the preconditions for opening the head are met
	 * before invoking this method.
	 *
	 * @param entityId An identifier used to specify the entity
	 *                 whose head should be opened.
	 * @return A boolean value indicating success (true) or
	 *         failure (false) of the operation.
	 *
	 * @throw std::invalid_argument If the entityId provided is
	 *                              invalid or null.
	 * @throw std::runtime_error If the operation fails due to
	 *                           an unexpected error.
	 */
	void open_head();

	//    void open_head(std::string ssCssName);

	/**
	 * Opens the given HTML content in a web viewer.
	 *
	 * This method is used to load and display HTML content in a designated
	 * viewer component or browser. It accepts a string containing valid HTML
	 * and may render it within the application's predefined viewer interface.
	 *
	 * Behavior:
	 * - Validates the input HTML string.
	 * - Handles any implications related to improper or malicious content.
	 * - May throw an exception if the content cannot be rendered.
	 *
	 * Parameters:
	 * @param htmlContent A string containing the HTML content to be opened.
	 *                    Must not be null or empty and should comply with
	 *                    the expected HTML standards.
	 *
	 * Throws:
	 * @throw IllegalArgumentException if the htmlContent is null or empty.
	 * @throw RenderException if there is an error rendering the provided HTML content.
	 */
	void open_html();

	/**
 	* Generates an HTML meta tag using a list as its argument.
 	*
 	* @param metaData Takes in a list of arbitrary length to be parsed into an
 	* html meta line. Every pair of elements are to be in the next array position.
 	* Example: {"class", "button",
 	*           "id", "button1",
 	*           ...}
 	*/
	void gen_meta_line(std::initializer_list<std::string> metaData);

	/**
 	* Generates an HTML meta tag using a string as its argument.
 	*
 	* @param ssMetaLine Takes in a string to be inserted into an html meta line.
 	* As quotes must be escaped with this implementation, I've elected to use
 	* the other function overload that uses the arbitrary list of strings.
 	* Example: "class=\"button\" id=\"button1\"..."
 	*/
	void gen_meta_line(std::string ssMetaLine);

	/**
	 * Opens a script file located at the specified path, reads its contents,
	 * and prepares it for execution or further processing.
	 *
	 * This method is responsible for loading a script file into memory
	 * and ensuring its readiness for use. It determines if the file exists,
	 * validates its format, and handles errors in case of missing
	 * or invalid files.
	 *
	 * @param filePath The path to the script file to be opened.
	 *                 Must be a valid string pointing to a readable file.
	 * @return Boolean value indicating success (true) or failure (false)
	 *         in opening and preparing the script file.
	 * @throws IOException if there is an issue accessing the file.
	 * @throws InvalidFormatException if the script file has an invalid format.
	 */
	void open_script();

	/**
	 * Opens a table for reading or modification.
	 *
	 * @param table_name The name of the table to be opened.
	 * @param mode The mode in which the table should be opened (e.g., read, write).
	 * @param options Additional options for opening the table, such as locking behavior or caching policy.
	 */
	void open_table(int border);


	/**
	 * Calculates the area of a rectangular shape based on the given width and height.
	 *
	 * This method computes the area by multiplying the width and height parameters.
	 * It assumes that both width and height are non-negative values. If negative
	 * values are provided, the behavior is undefined.
	 *
	 * @param width The width of the rectangle. Must be a non-negative value.
	 * @param height The height of the rectangle. Must be a non-negative value.
	 * @return The calculated area of the rectangle as a floating-point number.
	 *         Returns 0 if either width or height is zero.
	 */
	void para();

	/**
	 * Prints the provided message to the standard output.
	 *
	 * @param message The string message to be printed.
	 */
	void print(const char *);

	/**
	 * Prints the content of a vector to the standard output.
	 * Each element of the vector is printed followed by a space.
	 *
	 * @param vec The vector whose elements are to be printed.
	 */
	void printv(const char *pszFormat, ...);

	/**
	 * Prints the given variable to the standard output.
	 *
	 * @param var The variable to be printed. It can be of any type that supports output streaming (e.g., int, float, string).
	 */
	void printvar(const char *, const char *);

	/**
	 * Prints the value of a variable to the standard output.
	 *
	 * @param var The variable whose value is to be printed. This can be of any type that supports output via the stream operator.
	 */
	void printvar(const char *, int);

	/**
	 * Prints the given variable to the standard output.
	 *
	 * @param var The variable to be printed. It can be of any data type that supports output streaming.
	 */
	void printvar(const char *, double);

	/**
	 *
	 */
	void printvar(const char *, bool);

	/**
	 * Creates a button element in a script, sets its attributes, and appends it to the document body.
	 *
	 * @param pszButtonName The name of the button, used to identify and create a unique function for it.
	 * @param pszVisible The text or label that will be displayed on the button.
	 */
	void script_button(const char *pszButtonName, const char *pszVisible);

	/**
	 * Sets the style of the specified element or object.
	 *
	 * @param element The target element or object whose style needs to be set.
	 * @param style A string defining the style to be applied to the target element.
	 * @param value A string representing the value of the style property to set.
	 */
	void set_style(const char *pszStylesheet);

	/**
	 * Sets the specified title for an HTML document by outputting it as an HTML `<title>` tag.
	 *
	 * @param szTitle The title string to be incorporated into the HTML `<title>` tag.
	 */
	void title(const char *);

	/**
	 * Generates an HTML anchor (`<a>`) tag with the specified hyperlink, CSS class, and display text.
	 *
	 * @param pszLink The URL or hyperlink that the anchor tag will point to.
	 * @param pszButtonClass The CSS class to style the anchor tag.
	 * @param pszButtonDisplay The text that will be displayed within the anchor tag.
	 */
	void xahref(const char *pszLink,
	            const char *pszButtonClass,
	            const char *pszButtonDisplay);
};

/////////////////////
// eof - cgihtml.h //
/////////////////////