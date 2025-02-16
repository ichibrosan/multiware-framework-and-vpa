///////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/readCsv.cpp 2025/01/10   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.    //
///////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * Reads a CSV file and parses its content into a 2D vector of strings.
 *
 * @param filename The name of the CSV file to be read.
 *                 The file path is resolved to a fully-qualified filename.
 *                 Each line of the file is split into cells based on commas.
 * @return void, but the parsed CSV data is stored internally in a member variable.
 */
readCsv::readCsv(std::string filename) {
    CLog log(__FILE__,__FUNCTION__);
    log.writev("%s::%s(%s) called",__FILE__,__FUNCTION__,filename.c_str());

    gpLog->writev("%s: %s(\"%s\") called",
                __FILE__,__FUNCTION__,filename.c_str());

    std::string ssFQFS = gpOS->genSchemaFQFS(filename.c_str(),false);
    std::ifstream file(ssFQFS);

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<std::string> row;
        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        m_data.push_back(row);
    }
}

/**
 * Parses the CSV data stored in the object's internal data structures and
 * populates the parsed data member with structured information.
 *
 * The `parseData` method iterates through the rows and cells of the CSV data
 * stored in the `m_data` member of the `readCsv` object. It logs the processing
 * of each cell and stores the parsed results into the `m_parsed_data` member.
 * Each row's data is assigned a sequential index, starting from zero, to maintain
 * consistency in accessing parsed information.
 *
 * Logging is performed at various stages to provide runtime information about
 * the data parsing process and its progress. This function does not return any
 * values but modifies the class members directly.
 */
void readCsv::parseData()
{
    CLog log(__FILE__,__FUNCTION__);
    log.writev("%s::%s() called",__FILE__,__FUNCTION__);

    m_iRow=0;
    for (const auto& row: m_data) {
        int colnum=0;
        for(const auto& cell : row) {
            log.writesanstime(cell.c_str());
            log.writesanstime(",");
            m_parsed_data[m_iRow][colnum++] = cell;
        }
        log.writesanstime("\n");
        m_iRow++;
    }
}

/**
 * Retrieves data from the parsed CSV at the specified row and column.
 *
 * @param row The row index of the data to retrieve.
 * @param col The column index of the data to retrieve.
 * @return The string located at the specified row and column in the CSV data.
 */
std::string readCsv::getData(int row,int col)
{   CLog log(__FILE__,__FUNCTION__);
    log.writev("%s::%s(row=%d,col=%d) called",__FILE__,__FUNCTION__,row,col);

    log.writev("m_data[row=%d][col=%d] -> %s",
               row,col,m_data[row][col].c_str());

    return m_data[row][col];
}

/**
 * Retrieves the total number of lines (or rows) in the CSV file.
 *
 * @return The total number of lines in the CSV file as an integer.
 */
int readCsv::getLines()
{
    CLog log(__FILE__,__FUNCTION__);
    log.writev("%s::%s() called",__FILE__,__FUNCTION__);

    //pLog->writev("%s: %s() started",__FILE__,__FUNCTION__);
//    CLog log(__FILE__,__FUNCTION__);
//    log.write("instantiated");

    return m_iRow;
}
