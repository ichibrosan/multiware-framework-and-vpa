/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/readCsv.h 2025/01/10   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#ifndef READCSV_H
#define READCSV_H

#include "mwfw2.h"

#define MAX_ROWS 42
#define MAX_COLS 20

/**
 * @class readCsv
 * @brief A class to read and parse CSV file data.
 *
 * The readCsv class provides functionality to load data from a CSV file,
 * parse it into a 2D vector of strings, and store it for further access.
 * Additionally, the class allows retrieval of specific cell data based on
 * row and column indices, as well as obtaining the number of lines in the
 * parsed CSV file.
 */
class readCsv {
	/**
	 * A two-dimensional vector containing parsed CSV data.
	 *
	 * Each inner vector represents a row in the CSV file, and each string
	 * within the inner vector corresponds to a cell within that row.
	 * This variable holds the raw data read and split from a CSV file.
	 *
	 * Usage:
	 * - Populated during the `readCsv` constructor by reading the file contents.
	 * - Accessed in methods like `parseData` and `getData` to process CSV data.
	 *
	 * Internal Details:
	 * - Outer vector size corresponds to the number of rows.
	 * - Inner vector size may vary based on the number of cells per row.
	 */
	std::vector<std::vector<std::string>> m_data;

	/**
	 * @brief A 2D array for storing parsed CSV data.
	 *
	 * This variable holds the parsed data from a CSV file, where each element
	 * corresponds to a cell value in the CSV. The array is statically sized
	 * with a maximum of `MAX_ROWS` rows and `MAX_COLS` columns.
	 *
	 * Each row represents a line in the CSV file, and each column
	 * represents a field within that line.
	 *
	 * Use it to access parsed CSV data after calling the `parseData()` function.
	 *
	 * @note The actual data is populated by the `parseData()` method derived
	 *       from the `readCsv` class, and it depends on the input passed during
	 *       object construction.
	 */
public:
    std::string m_parsed_data[MAX_ROWS][MAX_COLS];

    readCsv(std::string); /**
     * @brief Parses the CSV data and populates the internal structure with the parsed data.
     *
     * This function processes the raw CSV data stored in the `m_data` member and writes
     * each row and cell into the `m_parsed_data` structure. The rows and cells are
     * traversed in a nested loop, logging each cell content during the process.
     *
     * The function also keeps track of the current row being processed using the `m_iRow`
     * member and updates it accordingly.
     *
     * Logging is performed during the parsing process to record the content of each
     * cell and structure for debugging purposes.
     *
     * @note This function assumes that the `m_data` member is already populated with
     * valid CSV data before calling it.
     */

	/**
	 *
	 */
	void parseData();

	/**
	 * Retrieves the value from the CSV file at the specified row and column.
	 *
	 * @param row The row index of the desired data.
	 * @param col The column index of the desired data.
	 * @return A string containing the data at the specified row and column.
	 */
	std::string getData(int row,int col);
	/**
	 * Retrieves the total number of lines (rows) in the CSV file.
	 *
	 * This function returns the number of rows in the processed CSV data.
	 * It is commonly used to iterate through the rows of data or perform
	 * row-related operations.
	 *
	 * @return The number of rows in the CSV file.
	 */
	int getLines();
	/**
	 * The m_iRow member variable is an integer that represents the current number of rows
	 * parsed and stored in the `m_parsed_data` array after invoking the `parseData` method.
	 *
	 * This variable is incremented line-by-line as rows are processed and stored
	 * during the parsing of CSV data, starting from zero. It effectively serves
	 * as a counter for the number of rows processed.
	 */
	int m_iRow;
};


#endif // READCSV_H
