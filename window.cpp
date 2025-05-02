////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/window.cpp 2025/05/01 16:54 dwg -        //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

window::window(
    // WinDesc& wd
    ) {
    m_x = 0; // wd.x;
    m_y = 0; // wd.y;
    m_width = 0; // wd.width;
    m_height = 0; // wd.height;
}

void window::add_row(std::string ssRow) {
    m_ssData.push_back(ssRow);
    m_height++;
    int iRowSize = ssRow.size() + 3;
    if (m_width < iRowSize) {
        m_width = iRowSize;
    }
};

void window::render() {
    gpCrt->crtstyle(MODE_BOLD,FG_GREEN,BG_BLACK);
    gpSemiGr->topline(1,1,m_width,m_height);
    for (const std::string& str : m_ssData ) {
        gpSemiGr->middleline(1,1,m_width,m_height,str);
    }
    gpSemiGr->endline(1,1,m_width,m_height);
    gpCrt->crtstyle(MODE_BOLD,FG_CYAN,BG_BLACK);
}

void window::show() {
    std::cout << "windows descriptor:" << std::endl;
    std::cout << "x: " << m_x << std::endl;
    std::cout << "y: " << m_y << std::endl;
    std::cout << "width: " << m_width << std::endl;
    std::cout << "height: " << m_height << std::endl;
    std::cout << std::endl;
}

window::~window() {

}