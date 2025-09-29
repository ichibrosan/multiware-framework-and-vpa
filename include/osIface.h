////////////////////////////////////////////////////////////////////
// ~/public_html/fw/osIface.h 2025-07-16 08:08 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#pragma once

#include "mwfw2.h"

/**
 * @class osIface
 * @brief Interface class for operating system-related functionalities.
 *
 * The osIface class serves as an interface to define a contract for operating system-specific operations.
 * It provides an abstraction to interact with low-level system functions, making it easier to implement
 * cross-platform solutions. The actual implementation is expected to be provided by concrete subclasses.
 *
 * This class is intended to be inherited by platform-specific implementations.
 *
 * @note Users of this class should ensure to implement all the pure virtual functions
 *       in derived classes to provide the necessary functionality.
 */
class osIface
{
	/**
	 * @brief Fully Qualified File System (FQFS) name or path.
	 *
	 * Represents the name or path of a file or directory in the system
	 * using a fully qualified format. This variable is typically used
	 * for storing absolute paths or names that are fully resolved
	 * with no ambiguity in a file system context.
	 */
	char m_szFQFS[FILENAME_MAX];
	/**
	 * @brief Represents a specific system state or configuration parameter in the application.
	 *
	 * The variable `m_ssFQFS` is used within the application to store or manipulate
	 * data relevant to a particular functionality or feature. The exact purpose of the
	 * variable depends on the surrounding context in which it is utilized. The prefix `m_`
	 * indicates that it is likely a member variable, while the remainder of the name could
	 * suggest its association with a specific internal system or process.
	 *
	 * Note: The precise definition, data type, and usage should be determined based on
	 * the context where this variable is declared or used.
	 */
	std::string m_ssFQFS;
	/**
	 * @brief Stores the full file system path utilized within the osIface class.
	 *
	 * This character array is used to represent a file path and has a size
	 * limit defined by the `FILENAME_MAX` constant, ensuring compatibility
	 * with the maximum file name length supported by the underlying
	 * file system.
	 *
	 * It is intended to be used in operations related to file handling and
	 * paths within the osIface class.
	 */
	char m_szPath[FILENAME_MAX];
	/**
	 * Retrieves the operating system interface object.
	 *
	 * This method provides access to the operating system interface,
	 * allowing interaction with OS-level functions and services.
	 *
	 * @return A pointer or reference to the operating system interface object.
	 */
public:
	osIface();

	/**
	 * Retrieves a list of all files in the specified directory.
	 *
	 * This method iterates through the files in the provided directory path
	 * and returns their full paths as a vector of strings. It utilizes
	 * `std::filesystem::directory_iterator` for traversing the directory.
	 *
	 * @param osPath The path of the directory to list files from.
	 *               It should be a valid file system path as a string.
	 * @return A vector of strings containing the full paths of the files
	 *         within the specified directory. If the directory is empty or
	 *         invalid, the returned vector will be empty.
	 */
	std::vector<std::string> allfilesindir(std::string osPath);

	/**
	 * Extracts the directory path from the given file path.
	 *
	 * @param pszFile A pointer to a null-terminated character string representing the file path.
	 * @return A string containing the directory path of the given file.
	 */
	std::string file2path(const char* pszFile);
	/**
	 * Converts a file path to its corresponding file name.
	 *
	 * @param file_path The full path of the file including directories.
	 * @return The file name extracted from the specified file path.
	 */
	std::string file2filename(const char* pszFile);
	/**
	 * Extracts the filename without its extension from a given file path.
	 * This function takes in a file path, strips the directory path and the file
	 * extension, returning only the file name without its extension.
	 *
	 * @param filePath The path of the file from which the name without extension is to be extracted.
	 * @return The file name without its extension as a string.
	 */
	std::string file2filenamesansext(const char* pszFile);

	// std::string genIniFQFS();

	/**
	 * @fn std::string genStyleFQFS(const char *pszCssName, bool bDebug)
	 * @brief Generates a fully qualified file system path for a given CSS style.
	 *
	 * This function constructs a fully qualified file system path based on the provided CSS style name.
	 * It can optionally include debugging information if the related parameter is enabled.
	 *
	 * @param pszCssName A pointer to a null-terminated C-string representing the name of the CSS style.
	 *                   This parameter must not be null.
	 * @param bDebug A boolean value that determines whether debugging information should be included.
	 *               If true, the function will generate debug-specific output.
	 *
	 * @return A std::string containing the fully qualified file system path for the specified CSS style.
	 *
	 * @note The caller must handle the validity and memory of the pszCssName parameter.
	 */
	std::string genStyleFQFS(const char* pszCssName, bool bDebug);

	/**
	 * Generates a Fully Qualified File System (FQFS) path for a given journal.
	 *
	 * This method constructs a valid, fully qualified file system path
	 * for accessing or storing journal-related resources. It ensures the
	 * path is formatted properly according to the application's requirements.
	 *
	 * @param journalName The name of the journal for which the FQFS path is generated.
	 * @param basePath The base directory path where the journal is stored.
	 * @param includeTimestamp A boolean flag indicating whether to include a timestamp in the generated path.
	 *        If true, the current timestamp will be appended to the path.
	 * @param fileExtension The file extension to be appended to the path (e.g., ".txt", ".json").
	 * @return The constructed FQFS path as a string.
	 */
	const char* genJournalFQFS(const char*, bool);


	/**
	 * Generates a CGI (Common Gateway Interface) path for CBD (Component-Based Development).
	 *
	 * This method constructs a CGI-compatible path based on provided parameters
	 * and configurations. The resulting path is typically used to execute CGI scripts
	 * associated with the specified CBD module and function.
	 *
	 * @param moduleName The name of the CBD module for which the CGI path is being generated.
	 * @param functionName The name of the function within the module to be invoked via CGI.
	 * @param basePath The base directory or URL from which the CGI script will be executed.
	 * @return A string representing the complete CGI path constructed for the given module, function, and base path.
	 */
	std::string genCgiCBDPath(const char* pszCgiName, bool bDebug);
	/**
	 * Generates the complete URL for a CGI script hosted in the "cmake-build-debug" directory.
	 *
	 * This method constructs a URL using protocol, IP, user information, and the
	 * provided CGI script name, which is fetched from shared memory.
	 *
	 * @param pszCgiName The name of the CGI script (e.g., "fw-test4.cgi").
	 * @param bDebug If true, debug information will be printed to the standard output.
	 * @return A std::string containing the fully formed URL for the specified CGI script.
	 */
	std::string genCgiCBDUrl(const char* pszCgiName, bool bDebug);
	/**
	 * Generates a CGI bin URL string based on the provided CGI script name.
	 *
	 * @param pszCgiName A pointer to a null-terminated string containing the name of the CGI script.
	 * @param bDebug A boolean flag indicating whether to output debug information.
	 * @return A string representing the full URL to the CGI script.
	 */
	std::string genCurlCgiBinUrl(const char* pszCgiName, bool bDebug);

	/**
	 * @brief Generates a URL pointing to a CGI script in the server's cgi-bin directory.
	 *
	 * This function constructs the URL by appending the necessary components such as
	 * protocol, hostname, user directory path, and CGI script name. These components
	 * are retrieved from shared memory or passed as arguments to the function.
	 *
	 * @param pszCgiName The name of the CGI script to include in the URL.
	 * @param bDebug A flag indicating whether debug output should be enabled. If true,
	 *        the function will print each step of the URL construction process to the console.
	 *
	 * @return A string representing the fully constructed URL for the specified CGI script.
	 */
	std::string genCgiBinUrl(const char* pszCgiName, bool bDebug);

	/**
	 * Generates a URL for an HTML page based on the provided page name
	 * and configuration from shared memory. Optionally outputs debug
	 * information during execution.
	 *
	 * @param pszPageName The name of the HTML page.
	 * @param bDebug A boolean flag indicating whether debug information should be output.
	 * @return A fully constructed URL as a string.
	 */
	std::string genHtmlUrl(const char* pszPageName, bool bDebug);
	/**
	 * Generates a URL for an image based on the input parameters.
	 *
	 * @param baseUrl The base URL of the image hosting service.
	 * @param imgPath The path to the specific image in the hosting service.
	 * @param params Additional query parameters to customize the image URL, such as size or format.
	 * @return A fully constructed URL string pointing to the specified image.
	 */
	std::string genImgUrl(const char* pszImgName);

	std::string genImgPath(const char* pszImgName, bool bDebug);

	/**
	 * Generates a fully qualified schema based on the provided parameters.
	 *
	 * @param schemaName The name of the schema to generate.
	 * @param namespace The namespace to use when constructing the schema.
	 * @param options Additional options or configurations for generating the schema.
	 * @return A fully qualified schema string created based on the provided inputs.
	 */
	std::string genSchemaFQFS(const char* pszSchema, bool bDebug);

	/**
	 * @brief Generates a fully qualified file system path to the script folder.
	 *
	 * The genScriptFQFS function constructs or generates a specific fully qualified output
	 * based on the provided script and debug flag. The actual behavior, such as returning
	 * a file path or processed script output, depends on the context of implementation.
	 *
	 * @param pszScript A constant character pointer representing the input script or script path.
	 *                  Its validity and format should be ensured by the caller.
	 * @param bDebug A boolean flag indicating whether to enable debug-specific functionality
	 *               or output during script generation.
	 *
	 * @return A std::string containing the generated output, which may vary based
	 *         on the parameters provided and the overall implementation.
	 */
	const char* genScriptFQFS(const char* pszScript, bool bDebug);

	/**
	 * @fn std::string genTempFQFS(const char * pszFilename, bool bDebug)
	 * @brief Generates a fully qualified temporary file system path.
	 *
	 * This function creates a temporary path based on the provided filename and additional debug settings.
	 * It ensures that the returned path is properly formatted and ready for use in a file system operation.
	 *
	 * @param pszFilename A pointer to a null-terminated character array representing the base filename.
	 * @param bDebug A boolean flag indicating whether the function should include additional debug information in the path.
	 * @return A string containing the generated temporary fully qualified file system path.
	 *
	 * @warning The caller must ensure that pszFilename is not a null or invalid pointer before passing it to this function.
	 */
	std::string genTempFQFS(std::string ssFilename, bool bDebug);

	/**
	 * Modifies the date in the filename of the style if it's not the same
	 * as the last modified date of the file itself.
	 *
	 * @param ssStyle The name of the stylesheet to modify the date.
	 */
	void setStyleModDate(std::string ssStyle);

	/**
	 * Constructs the complete file path for a given schema name by appending it
	 * to the directory path derived from the current file location, and optionally
	 * logs debugging information.
	 *
	 * @param ssSchemaName The name of the schema whose path needs to be constructed.
	 * @param bDebug If true, enables debug mode to output debugging information.
	 * @return The full path to the schema as a string.
	 */
	std::string parseSchemaName(std::string ssSchemaName, bool bDebug);

	/**
	 * Retrieves the last modified date of the style in the filename.
	 *
	 * @param ssStyle The name of the stylesheet sans .css or date modified.
	 * @return A string containing the date in the filename.
	 */
	std::string getStyleModDate(std::string ssStyle);

	/**
	 * Converts an integer number into its binary representation and prints it as a string with a specified number of digits.
	 *
	 * @param number The integer value to be converted to binary.
	 * @param digits The number of binary digits to be displayed in the output. The output is truncated to match this count.
	 */
	void printBinary(int, int);


	/**
	 * @brief Gets the handle of the current user, and returns the stylesheet
	 * to use for the webpage based on their username.
	 * \n\n
	 * Defaults to the "default.css" stylesheet if the handle isn't
	 * associated with an authenticated user.
	 *
	 * @param iHandle The handle of the user.
	 * @return Returns the stylesheet to use for the passed handle.
	 */
	std::string get_handle_style(int iHandle);
};

/**
 * @brief Pointer to the OS interface structure.
 *
 * This variable holds a reference to an operating system-specific interface
 * structure. It is intended to provide an abstraction layer for OS-dependent
 * operations and functionalities, ensuring compatibility and ease of use
 * across different platforms.
 *
 * The structure that `pOsIface` points to typically contains function pointers
 * or methods relevant to OS-level tasks such as threading, memory management,
 * timing, and other platform-dependent operations. This allows the application
 * to interact with the operating system in a modular and portable manner.
 *
 * It is important to ensure that this pointer is properly initialized before
 * its use to avoid undefined behavior or runtime errors.
 */
extern osIface* pOsIface;

/////////////////////
// eof - osIface.h //
/////////////////////
