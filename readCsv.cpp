///////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/readCsv.cpp 2025/01/10   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.    //
///////////////////////////////////////////////////////////////////////////

#include "readCsv.h"
#include "CLog.hpp"
#include "fw-limits.h"
#include "osIface.h"
#include "shared.h"
#include "std.h"

extern CLog * gpLog;
extern osIface * gpOS;

/***********************************************
 * This is the constructor for the readCsv class
 * Read a CSV file for parsing
 * @param filename in a standard string
 ***********************************************/
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
 *
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

std::string readCsv::getData(int row,int col)
{   CLog log(__FILE__,__FUNCTION__);
    log.writev("%s::%s(row=%d,col=%d) called",__FILE__,__FUNCTION__,row,col);

    log.writev("m_data[row=%d][col=%d] -> %s",
               row,col,m_data[row][col].c_str());

    return m_data[row][col];
}

int readCsv::getLines()
{
    CLog log(__FILE__,__FUNCTION__);
    log.writev("%s::%s() called",__FILE__,__FUNCTION__);

    //pLog->writev("%s: %s() started",__FILE__,__FUNCTION__);
//    CLog log(__FILE__,__FUNCTION__);
//    log.write("instantiated");

    return m_iRow;
}