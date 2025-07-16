////////////////////////////////////////////////////////////////////
// ~/public_html/fw/schema.h 2025-07-16 08:08 dwg -               //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#pragma once

//#include "main.h"
#include "CSysLog.h"
#include "readCsv.h"

enum
{
    ROW_META_HDR, // 0
    ROW_META_DATA, // 1
    ROW_DATA_HDR, // 2
    ROW_DATA // 3
};

/**
 * @enum SCHEMA_METADATA_T
 *
 * @brief Defines metadata keys used within a schema.
 *
 * This enumeration represents various metadata attributes associated
 * with a schema, which can be used for configuration and descriptive
 * purposes.
 *
 * Enum Values:
 * - COL_META_ACTIVE: Indicates if the schema or column is active.
 * - COL_META_VERSION: Specifies the version of the schema.
 * - COL_META_META_COLUMNS: Defines metadata about columns in the schema.
 * - COL_META_DATA_COLUMNS: Defines actual data columns in the schema.
 * - COL_META_SCHEMA: Represents the schema definition.
 * - COL_META_CGINAME: Specifies the CGI name associated with the schema.
 * - COL_META_TARGET: Indicates the target related to the schema.
 * - COL_META_PAGE_FORM: Refers to the page or form context in the schema.
 * - COL_META_STYLE: Describes the style related to the schema.
 * - COL_META_DESCRIPTION: Provides a description of the schema or column.
 */
enum SCHEMA_METADATA_T
{
    COL_META_ACTIVE,
    COL_META_VERSION,
    COL_META_META_COLUMNS,
    COL_META_DATA_COLUMNS,
    COL_META_SCHEMA,
    COL_META_CGINAME,
    COL_META_METHOD,
    COL_META_TARGET,
    COL_META_PAGE_FORM,
    COL_META_STYLE,
    COL_META_DESCRIPTION
};

/**
 * @enum SCHEMA_GENERIC_T
 * @brief Enumeration representing the identifiers for generic schema columns.
 *
 * This enumeration defines symbolic names for various generic schema column types
 * used for categorizing or specifying information in the schema.
 *
 * - COL_ACTIVE: Represents whether the schema is active.
 * - COL_PREPARA: Represents a preparatory parameter or status.
 * - COL_POSTPARA: Represents a post-parameter or status.
 * - COL_TYPE: Represents the type or category of the schema.
 * - COL_PARM1: Represents the first parameter.
 * - COL_PARM2: Represents the second parameter.
 * - COL_PARM3: Represents the third parameter.
 */
enum SCHEMA_GENERIC_T
{
    COL_ACTIVE,
    COL_PREPARA,
    COL_POSTPARA,
    COL_TYPE,
    COL_PARM1,
    COL_PARM2,
    COL_PARM3,
    COL_PARM4
};

/**
 * @enum SCHEMA_IFRAME_T
 * @brief Enumeration defining the column identifiers for the iframe schema.
 *
 * This enumeration maps to the columns related to iframe configurations.
 * It extends the SCHEMA_GENERIC_T enumeration by associating specific identifiers
 * with iframe-related properties.
 *
 * Constants:
 * - COL_IFRAME_DEF_PAGE: Represents the default page for the iframe, mapped to COL_PARM1.
 * - COL_IFRAME_TITLE: Represents the title attribute of the iframe.
 * - COL_IFRAME_NAME: Represents the name attribute used for frame identification.
 * - COL_IFRAME_CLASS: Represents the CSS class associated with the iframe.
 * - COL_IFRAME_WIDTH: Represents the width definition of the iframe.
 * - COL_IFRAME_HEIGHT: Represents the height definition of the iframe.
 */
enum SCHEMA_IFRAME_T
{
    COL_IFRAME_DEF_PAGE = COL_PARM1,
    COL_IFRAME_TITLE,
    COL_IFRAME_NAME,
    COL_IFRAME_CLASS,
    COL_IFRAME_WIDTH,
    COL_IFRAME_HEIGHT
};

/**
 * @enum SCHEMA_XAHREF_T
 * @brief Enum representing specific columns for XAHREF schema.
 *
 * This enum defines column identifiers related to the XAHREF schema by reusing
 * and extending identifiers from the SCHEMA_GENERIC_T enumerator.
 *
 * @var SCHEMA_XAHREF_T::COL_XAHREF_LINK
 * Represents the link field, equivalent to COL_PARM1 in SCHEMA_GENERIC_T.
 *
 * @var SCHEMA_XAHREF_T::COL_XAHREF_CLASS
 * Represents the CSS class field for the XAHREF schema.
 *
 * @var SCHEMA_XAHREF_T::COL_XAHREF_DISPLAY
 * Represents the display field for the XAHREF schema.
 */
enum SCHEMA_XAHREF_T
{
    COL_XAHREF_LINK = COL_PARM1,
    COL_XAHREF_CLASS,
    COL_XAHREF_DISPLAY
};

/**
 * @enum SCHEMA_FORM_BUTTON_T
 * @brief Represents the column definitions for form button properties within the schema.
 *
 * Enumeration members define attributes associated with a form button in the schema.
 *
 * - COL_FORM_BUTTON_TYPE: Refers to the parameter 1 column, used to specify the button type.
 * - COL_FORM_BUTTON_FORM: Represents the column for the button's associated form.
 * - COL_FORM_BUTTON_CLASS: Indicates the column for the button's class.
 * - COL_FORM_BUTTON_DISPLAY: Represents the column controlling the display properties of the button.
 */
enum SCHEMA_FORM_BUTTON_T
{
    COL_FORM_BUTTON_TYPE = COL_PARM1,
    COL_FORM_BUTTON_FORM,
    COL_FORM_BUTTON_CLASS,
    COL_FORM_BUTTON_DISPLAY
};

/**
 * @enum SCHEMA_OPEN_FORM_T
 * @brief Enum representing column indices for the "OPEN_FORM" schema.
 *
 * This enumeration is utilized to define specific column identifiers for an
 * "OPEN_FORM" schema. The columns are assigned unique values starting from
 * `COL_PARM1` in the `SCHEMA_GENERIC_T` enumeration.
 *
 * Enumerators:
 * - COL_FORM_ACTION: Represents the column for form action, initialized from COL_PARM1.
 * - COL_FORM_PROTOCOL: Represents the column for form protocol.
 * - COL_FORM_HANDLE: Represents the column for form handle.
 * - COL_FORM_ID: Represents the column for form ID.
 * - COL_FORM_TARGET: Represents the column for form target.
 */
enum SCHEMA_OPEN_FORM_T
{
    COL_FORM_ACTION = COL_PARM1,
    COL_FORM_PROTOCOL,
    COL_FORM_HANDLE,
    COL_FORM_ID,
    COL_FORM_TARGET
};

/**
 * @enum SCHEMA_DIV_T
 * @brief Enumeration for schema division types.
 *
 * This enum is used to define specific schema division classifications
 * based on the values from SCHEMA_GENERIC_T.
 *
 * @constant COL_DIV_CLASS Represents a column identifier for division class,
 * mapped to COL_PARM1 from SCHEMA_GENERIC_T.
 */
enum SCHEMA_DIV_T
{
    COL_DIV_CLASS = COL_PARM1
};


/**
 * @enum SCHEMA_CHECKBOX_T
 * @brief Enum defining different columns related to a checkbox schema.
 *
 * This enumeration represents specific column attributes within a checkbox schema,
 * with each enumerator corresponding to a distinct property of the checkbox.
 *
 * Enumerators:
 * - COL_CHECKBOX_NAME: Represents the name of the checkbox, mapped to a generic parameter.
 * - COL_CHECKBOX_ID: Represents the unique identifier of the checkbox.
 * - COL_CHECKBOX_VALUE: Represents the value of the checkbox.
 * - COL_CHECKBOX_VISIBLE: Represents the visibility status of the checkbox.
 * - COL_CHECKBOX_DESCRIPTION: Represents the description of the checkbox.
 */
enum SCHEMA_CHECKBOX_T
{
    COL_CHECKBOX_NAME = COL_PARM1,
    COL_CHECKBOX_ID,
    COL_CHECKBOX_VALUE,
    COL_CHECKBOX_VISIBLE,
    COL_CHECKBOX_DESCRIPTION
};

/**
 * @enum SCHEMA_DATE_T
 * @brief Enum representing columns in the DATE schema.
 *
 * This enumeration defines specific column identifiers for a data schema
 * representing DATE information. Some values are derived based on the
 * previously defined SCHEMA_GENERIC_T enumeration.
 *
 * @note COL_DATE_NAME is initialized with the value of COL_PARM1 from SCHEMA_GENERIC_T.
 *
 * Enumerators:
 *   COL_DATE_NAME   Represents the name column, inheriting its value from COL_PARM1.
 *   COL_DATE_ID     Represents the ID column for the DATE schema.
 *   COL_DATE_VALUE  Represents the value or data column for the DATE schema.
 *   COL_DATE_DESCR  Represents the description column for the DATE schema.
 */
enum SCHEMA_DATE_T
{
    COL_DATE_NAME = COL_PARM1,
    COL_DATE_ID,
    COL_DATE_VALUE,
    COL_DATE_DESCR
};

/**
 * @enum SCHEMA_DATETIME_T
 * @brief Enumerates the schema columns specific to datetime entities.
 *
 * This enum is derived and mapped to generic schema columns defined in SCHEMA_GENERIC_T.
 * Each enumerator represents a column type associated with datetime schemas.
 *
 * - COL_DATETIME_NAME: Represents the column for the name of the datetime entity, mapped to COL_PARM1.
 * - COL_DATETIME_ID: Represents the column for the ID of the datetime entity.
 * - COL_DATETIME_VALUE: Represents the column for the value of the datetime entity.
 * - COL_DATETIME_DESCR: Represents the column for the description of the datetime entity.
 */
enum SCHEMA_DATETIME_T
{
    COL_DATETIME_NAME = COL_PARM1,
    COL_DATETIME_ID,
    COL_DATETIME_VALUE,
    COL_DATETIME_DESCR
};

/**
 * @enum SCHEMA_IMAGE_T
 *
 * @brief Defines the columns specific to the IMAGE schema.
 *
 * This enumerator represents the indices of various attributes
 * related to an image in a schema. The enumerator values start
 * from COL_PARM1 defined in SCHEMA_GENERIC_T and continue sequentially.
 *
 * - COL_IMAGE_FILENAME: Refers to the filename of the image.
 * - COL_IMAGE_WIDTH: Represents the width of the image.
 * - COL_IMAGE_HEIGHT: Represents the height of the image.
 * - COL_IMAGE_ALTDESCRIPTION: Alternative description of the image.
 *
 * The values in this enum depend on the starting value of COL_PARM1
 * in SCHEMA_GENERIC_T.
 */
enum SCHEMA_IMAGE_T
{
    COL_IMAGE_FILENAME = COL_PARM1,
    COL_IMAGE_WIDTH,
    COL_IMAGE_HEIGHT,
    COL_IMAGE_ALTDESCRIPTION
};

/**
 * @enum SCHEMA_MONTH_T
 * @brief Enumeration for columns related to months in a schema.
 *
 * This enumeration defines identifiers for various month-related columns
 * used in the schema. It includes the month name, ID, value, and description.
 *
 * The first enumerator, COL_MONTH_NAME, is initialized with the value of COL_PARM1
 * from SCHEMA_GENERIC_T. Subsequent enumerators increment from that value.
 *
 * Enumerators:
 * - COL_MONTH_NAME: Represents the name of the month.
 * - COL_MONTH_ID: Represents the unique identifier for the month.
 * - COL_MONTH_VALUE: Represents the value associated with the month.
 * - COL_MONTH_DESCR: Represents the description of the month.
 */
enum SCHEMA_MONTH_T
{
    COL_MONTH_NAME = COL_PARM1,
    COL_MONTH_ID,
    COL_MONTH_VALUE,
    COL_MONTH_DESCR
};

/**
 * @enum SCHEMA_PASSWORD_T
 * @brief Enumerates the schema columns specific to password entries.
 *
 * This enum provides column identifiers for managing password-related data in
 * a schema. It extends the generic schema identifiers, using COL_PARM1 from
 * SCHEMA_GENERIC_T as the base for its entries.
 *
 * Members:
 * - COL_PASSWORD_NAME: Represents the column for the password name, starting from COL_PARM1.
 * - COL_PASSWORD_ID: Represents the column for the password identifier.
 * - COL_PASSWORD_VALUE: Represents the column for the actual value of the password.
 * - COL_PASSWORD_SIZE: Indicates the size of the password.
 * - COL_PASSWORD_VISIBLE: Specifies whether the password is visible or hidden.
 * - COL_PASSWORD_DESCR: Holds a description associated with the password.
 */
enum SCHEMA_PASSWORD_T
{
    COL_PASSWORD_NAME = COL_PARM1,
    COL_PASSWORD_ID,
    COL_PASSWORD_VALUE,
    COL_PASSWORD_SIZE,
    COL_PASSWORD_VISIBLE,
    COL_PASSWORD_DESCR
};

/**
 * @enum SCHEMA_RADIOBUTT_T
 * @brief Defines the schema mapping for radio button-related columns.
 *
 * This enumeration extends the generic schema enumeration and is used to define
 * specific column attributes related to radio buttons in a structured schema.
 * It starts mapping from the value of `COL_PARM1` in the `SCHEMA_GENERIC_T` enum.
 *
 * @var SCHEMA_RADIOBUTT_T::COL_RADIO_ID
 * Represents the column identifier for the radio button ID.
 *
 * @var SCHEMA_RADIOBUTT_T::COL_RADIO_NAME
 * Represents the column identifier for the radio button name.
 *
 * @var SCHEMA_RADIOBUTT_T::COL_RADIO_VALUE
 * Represents the column identifier for the assigned value of the radio button.
 *
 * @var SCHEMA_RADIOBUTT_T::COL_RADIO_LABEL
 * Represents the column identifier for the label of the radio button.
 *
 * @var SCHEMA_RADIOBUTT_T::COL_RADIO_DESCRIPTION
 * Represents the column identifier for the description of the radio button.
 */
enum SCHEMA_RADIOBUTT_T
{
    COL_RADIO_ID = COL_PARM1,
    COL_RADIO_NAME,
    COL_RADIO_VALUE,
    COL_RADIO_LABEL,
    COL_RADIO_DESCRIPTION
};

/**
 * @enum SCHEMA_RESET_T
 * @brief Represents a specific schema reset enumeration.
 *
 * This enum extends or utilizes the existing values from SCHEMA_GENERIC_T.
 * It defines constants related to schema reset properties.
 *
 * @var SCHEMA_RESET_T::COL_RESET_NAME
 * Refers to the reset name, initialized with the value of COL_PARM1
 * from SCHEMA_GENERIC_T.
 *
 * @var SCHEMA_RESET_T::COL_RESET_VALUE
 * Represents the reset value, coming after COL_RESET_NAME in sequence.
 */
enum SCHEMA_RESET_T
{
    COL_RESET_NAME = COL_PARM1,
    COL_RESET_VALUE
};

/**
 * @enum SCHEMA_TEXT_T
 * @brief Represents a schema for text attributes, defining the columns and their respective identifiers.
 *
 * This enumeration maps specific text-related attributes to column identifiers for usage in schema-based operations.
 * The column identifiers are derived starting from a predefined base value within the SCHEMA_GENERIC_T enumeration.
 *
 * @note COL_TEXT_NAME starts from the COL_PARM1 value defined in SCHEMA_GENERIC_T.
 */
enum SCHEMA_TEXT_T
{
    COL_TEXT_NAME = COL_PARM1,
    COL_TEXT_ID,
    COL_TEXT_VALUE,
    COL_TEXT_SIZE,
    COL_TEXT_VISIBLE,
    COL_TEXT_DESCR,
    COL_TEXT_READONLY,
    COL_TEXT_CLASS
};


/**
 * @enum SCHEMA_FILES_SELECT_T
 * @brief Enumeration for column selections used in the schema file context.
 *
 * This enum defines specific column indices for file selection operations
 * based on the generic schema enumeration. The values relate to generic
 * parameter indices defined in SCHEMA_GENERIC_T.
 *
 * @var COL_SELECT_NAME
 * Represents the column index for selecting the name, mapped to COL_PARM1.
 *
 * @var COL_SELECT_PATH
 * Represents the column index for selecting the path, incrementally
 * following COL_SELECT_NAME.
 *
 * @var COL_SELECT_CLASS
 * Represents the column index for selecting the class, incrementally
 * following COL_SELECT_PATH.
 */
enum SCHEMA_FILES_SELECT_T
{
    COL_FILES_SELECT_NAME = COL_PARM1,
    COL_FILES_SELECT_PATH,
    COL_FILES_SELECT_CLASS
};

/**
 * @enum SCHEMA_TEXTAREA_T
 *
 * An enumeration that defines the column indexes and associated properties
 * for the textarea element schema. The enumerators are used to specify
 * attributes for a textarea element in a schema definition.
 *
 * Each enumerator represents a specific property of a textarea element:
 * - `COL_TEXTAREA_NAME` : Maps to the name attribute, initialized with the value `COL_PARM1` from `SCHEMA_GENERIC_T`.
 * - `COL_TEXTAREA_ID` : Specifies the ID attribute of the textarea.
 * - `COL_TEXTAREA_COLS` : Represents the number of visible width columns of textarea.
 * - `COL_TEXTAREA_ROWS` : Represents the number of visible height rows of textarea.
 * - `COL_TEXTAREA_WRAP` : Indicates the text wrapping behavior for the textarea.
 * - `COL_TEXTAREA_CLASS` : Specifies the CSS class for styling the textarea.
 * - `COL_TEXTAREA_VALUE` : Represents the default value within the textarea.
 */
enum SCHEMA_TEXTAREA_T
{
    COL_TEXTAREA_NAME = COL_PARM1,
    COL_TEXTAREA_ID,
    COL_TEXTAREA_COLS,
    COL_TEXTAREA_ROWS,
    COL_TEXTAREA_WRAP,
    COL_TEXTAREA_CLASS,
    COL_TEXTAREA_VALUE
};

/**
 * @enum SCHEMA_TIME_T
 * @brief Enumeration for schema time-related columns.
 *
 * This enum defines specific columns used for time-based schema definitions,
 * mapping them to parameters from the generic schema type.
 *
 * The following enumerators are derived from the generic schema parameters:
 * - COL_TIME_NAME: Maps to COL_PARM1, representing the name of a time column.
 * - COL_TIME_ID: Represents the identifier for a time column.
 * - COL_TIME_VALUE: Represents the value associated with a time column.
 * - COL_TIME_DESCR: Represents the description of a time column.
 */
enum SCHEMA_TIME_T
{
    COL_TIME_NAME = COL_PARM1,
    COL_TIME_ID,
    COL_TIME_VALUE,
    COL_TIME_DESCR
};


/**
 * @enum SCHEMA_WEEK_T
 * @brief Enumeration defining columns specific to a weekly schema.
 *
 * This enum builds on the generic schema columns by providing
 * week-specific column identifiers.
 *
 * Enum members:
 * - COL_WEEK_NAME: Represents the column for the week name, initialized to COL_PARM1.
 * - COL_WEEK_ID: Represents the column for a unique week identifier.
 * - COL_WEEK_VALUE: Represents the column for the data value associated with the week.
 * - COL_WEEK_DESCR: Represents the column for a description of the week.
 */
enum SCHEMA_WEEK_T
{
    COL_WEEK_NAME = COL_PARM1,
    COL_WEEK_ID,
    COL_WEEK_VALUE,
    COL_WEEK_DESCR
};

/**
 * @enum SCHEMA_AHREF_T
 * @brief Enumeration representing specific AHREF schema columns.
 *
 * This enumeration defines the column indices used in a particular AHREF schema.
 * These indices are mapped to generic column identifiers from the SCHEMA_GENERIC_T
 * enumeration starting from the given offset.
 *
 * - COL_AHREF_CGINAME: Maps to COL_PARM1 to indicate the CGI name column.
 * - COL_AHREF_IMGNAME: Represents the image name column.
 * - COL_AHREF_WIDTH: Represents the width column.
 * - COL_AHREF_HEIGHT: Represents the height column.
 */
enum SCHEMA_AHREF_T
{
    COL_AHREF_CGINAME = COL_PARM1,
    COL_AHREF_IMGNAME,
    COL_AHREF_WIDTH,
    COL_AHREF_HEIGHT
};

/**
 * @enum SCHEMA_PASSWD_T
 * @brief Enum representing columns for a password schema in a database.
 *
 * This enumeration defines the column identifiers for the fields
 * related to password management in the database. Each enumerator
 * corresponds to a specific column in the schema that stores user and
 * password-related information.
 *
 * - COL_PASSWD_ACTIVE: Represents whether the user account is active.
 * - COL_PASSWD_USERNAME: Represents the username of the user.
 * - COL_PASSWD_PASSWORD: Represents the user's password.
 * - COL_PASSWD_AUTHLEVEL: Represents the authentication level of the user.
 * - COL_PASSWD_FIRSTNAME: Represents the first name of the user.
 * - COL_PASSWD_LASTNAME: Represents the last name of the user.
 * - COL_PASSWD_DESCR: Represents a description or additional info about the user.
 */
enum SCHEMA_PASSWD_T
{
    COL_PASSWD_ACTIVE,
    COL_PASSWD_USERNAME,
    COL_PASSWD_PASSWORD,
    COL_PASSWD_AUTHLEVEL,
    COL_PASSWD_FIRSTNAME,
    COL_PASSWD_LASTNAME,
    COL_PASSWD_DESCR
};

/**
 * @enum SCHEMA_LABEL_T
 * @brief Enum defining specific schema label constants.
 *
 * This enum is used for assigning schema label values, where:
 * - `COL_LABEL_VISIBLE` is mapped to `COL_PARM1` from the `SCHEMA_GENERIC_T` enum.
 */
enum SCHEMA_LABEL_T
{
    COL_LABEL_VISIBLE = COL_PARM1
};

/**
 * @enum SCHEMA_PREPROCESS_T
 * @brief Defines the types of schema preprocessing operations.
 *
 * This enumeration is used to identify preprocessing types applied
 * to a schema. It aids in differentiating between variable names and
 * their associated values during processing.
 *
 * - VARIABLE_NAME: Represents the preprocessing operation for variable names.
 * - VARIABLE_VALUE: Represents the preprocessing operation for variable values.
 */
enum SCHEMA_PREPROCESS_T
{
    VARIABLE_NAME,
    VARIABLE_VALUE
};

/**
 * This class represents a generic schema that defines the structure or blueprint
 * for other classes or data models. It provides the necessary methods and properties
 * required for schema validation and operations on associated data.
 *
 * It can be used to define specific data models and their relationships, along
 * with performing operations such as serialization, deserialization, and validation.
 *
 * Responsibilities of this class and subclasses may include:
 * - Defining fields, their types, and constraints
 * - Ensuring data integrity based on rules specified in the schema
 * - Supporting extensibility through custom data definitions
 *
 * Thread Safety:
 * This class is not guaranteed to be thread-safe. Proper synchronization techniques
 * should be applied when used in multi-threaded environments.
 *
 * Error Handling:
 * Validation errors or schema inconsistencies should be handled gracefully,
 * providing informative error messages for debugging.
 */
class schema
{
    /**
     * Represents the number of rows in a given dataset or schema.
     *
     * This member variable is initialized in the constructor of the `schema` class
     * by retrieving the number of lines from a CSV file using the `readCsv` object.
     * It can be accessed through the `schema::getLines()` method to determine
     * the number of rows currently processed or stored in the schema.
     *
     * Usage:
     * - To store the row count after parsing CSV data.
     * - To retrieve the row count for further computations or validations.
     */
    int m_iRows;
    /**
     * @brief Stores the name of the schema being processed.
     *
     * This variable holds the schema name as a `std::string`.
     * It is initialized through the `schema` class constructor and serves as a reference
     * for identifying or processing schema-specific data throughout the lifetime
     * of a `schema` object instance.
     */
    std::string m_ssSchemaName;
    /**
     * Pointer to an instance of the CSysLog class used for system logging.
     *
     * This variable is responsible for handling logging operations within the
     * schema class. It facilitates the storage and recording of informational
     * messages, errors, or other system-level details using the CSysLog functionalities.
     * The instance is dynamically allocated during the schema initialization,
     * ensuring that the logging mechanism is available throughout the lifecycle
     * of the schema object. All logging-related tasks triggered by the schema
     * class, such as debugging or data processing logs, are routed through this pointer.
     */
    CSysLog* m_pSysLog;
    /**
     * Constructs a schema object and initializes its components using the provided schema name.
     *
     * @param ssSchemaName The name of the schema file (e.g., "journal.csv", "index.csv").
     *                     It is used to initialize the internal CSV reader and schema name variables.
     * @return A new instance of the schema class.
     */
public:
    schema(std::string);
    /**
     * Preprocesses row data from a parsed CSV structure and updates specific grid entries
     * based on contextual information. Handles dynamic data replacement based on identifiers
     * such as `from:` for form variables and `passed:` for passed values.
     *
     * @param iRow The index of the row in the parsed CSV data to be preprocessed.
     * @param svvsPassedValues A 2D vector containing key-value pairs representing
     *                         passed variables (e.g., variable name and its value).
     */
    void preprocess_row_data(int i_IRow,
                             std::vector<std::vector<std::string>>
                             svvsPassedValues);
    /**
     * Processes schema data based on the given structure and logical conditions.
     * Utilizes provided data to determine behavior related to schema activation
     * and submission requirements.
     *
     * @param svvsPassedValues A vector of vectors containing strings
     *                         representing the schema data to process.
     */
    void process_schema_data(std::vector<std::vector<std::string>>
        svvsPassedValues);
    /**
     * Generates HTML content based on the schema details and passed values.
     * Processes schema metadata to set up the HTML structure and forms.
     * Utilizes the passed values and handle for configuring the content.
     *
     * @param iHandle An integer handle used for identifying the specific schema instance.
     * @param svvsPassedValues A two-dimensional vector containing string values to be applied to the schema.
     */
    void gen_from_schema(int handle, std::vector<std::vector<std::string>>
                         svvsPassedValues = {});

    /**
     * Generates HTML content based on the schema details and passed values.
     * Processes schema metadata to set up the HTML structure and forms.
     * Utilizes the passed values and handle for configuring the content.
     *
     * @param iHandle An integer handle used for identifying the specific schema instance.
     * @param svvsPassedValues A two-dimensional vector containing string values to be applied to the schema.
     */
    void gen_from_schema(int handle,
                         int flags,
                         const char* szFile,
                         std::string ssUsername,
                         std::string ssPassword,
                         std::vector<std::vector<std::string>>
                         svvsPassedValues = {});

    /**
     * Retrieves the number of rows (or lines) associated with the current schema.
     *
     * @return The number of rows stored in the schema object.
     */
    int getLines();
    /**
     * Calculates the factorial of a given non-negative integer.
     *
     * This method uses recursion to determine the factorial, which is the product
     * of all positive integers that are less than or equal to the specified number.
     * For input values of 0 or 1, the factorial is defined as 1.
     *
     * @param number The non-negative integer for which the factorial is to be calculated.
     *               Must be 0 or greater.
     * @return The factorial of the input number as a long.
     * @throws IllegalArgumentException If the input number is negative.
     */
    ~schema();

    /**
     * @brief Pointer to an instance of the `readCsv` class used for handling CSV data.
     *
     * This member variable acts as a reference to the `readCsv` object, which is responsible
     * for parsing and storing CSV data. It enables access to various methods and functionalities
     * provided by the `readCsv` class, such as retrieving cell values, counting rows, and managing
     * parsed CSV content.
     *
     * Primary role:
     * - Provides integration of CSV reading and processing capabilities within the `schema` class.
     *
     * Usage:
     * - The `m_pReadCsv` pointer is typically set during initialization or construction of the
     *   `schema` object.
     * - Methods from the `readCsv` instance can be invoked via this pointer. For example,
     *   retrieving data from specific rows or columns by calling methods like `readCsv::getData`.
     *
     * Associated functionalities:
     * - Parsing raw CSV content into structured data.
     * - Accessing CSV rows, columns, and cell values for further processing in the schema.
     * - Ensuring compatibility with the schema data preprocessing and analysis.
     *
     * Ownership:
     * - The `schema` class assumes responsibility for interacting with the `readCsv` object
     *   through this pointer but does not necessarily manage its memory lifecycle, which must
     *   be handled externally.
     */
    readCsv* m_pReadCsv;
};

////////////////////
// eof - schema.h //
////////////////////
