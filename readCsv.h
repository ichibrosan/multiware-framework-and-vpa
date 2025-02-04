/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/readCsv.h 2025/01/10   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#ifndef READCSV_H
#define READCSV_H

#include "std.h"

#define MAX_ROWS 42
#define MAX_COLS 20

class readCsv {

    std::vector<std::vector<std::string>> m_data;

public:
    std::string m_parsed_data[MAX_ROWS][MAX_COLS];

    readCsv(std::string); // NOLINT(*-explicit-constructor)

    void parseData();

    std::string getData(int row,int col);
    int getLines();
    int m_iRow;
};


#endif // READCSV_H
