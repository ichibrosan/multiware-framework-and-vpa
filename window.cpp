////////////////////////////////////////////////////////////////////
// ~/public_html/fw/window.cpp 2025-07-15 18:16 dwg -             //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

window::window(
    // WinDesc& wd
)
{
    m_x = 0; // wd.x;
    m_y = 0; // wd.y;
    m_width = 0; // wd.width;
    m_height = 0; // wd.height;
}

void window::add_row(std::string ssRow)
{
    m_ssData.push_back(ssRow);
    m_height++;
    int iRowSize = ssRow.size() + 3;
    if (m_width < iRowSize)
    {
        m_width = iRowSize;
    }
};

void window::set_title(std::string ssTitle)
{
    m_ssTitle = ssTitle;
    int iTitleSize = ssTitle.size() + 3;
    if (m_width < iTitleSize)
    {
        m_width = iTitleSize;
    }
}

int window::get_height()
{
    return m_height;
}

int window::get_width()
{
    return m_width;
}

int window::get_x()
{
    return m_x;
}

int window::get_y()
{
    return m_y;
}


void window::render()
{
    gpCrt->crtstyle(MODE_BOLD, FG_GREEN, BG_BLACK);
    gpSemiGr->topline(1, 1, m_width, m_height);
    gpSemiGr->middleline(1, 1, m_width, m_height, m_ssTitle);
    gpSemiGr->vert_splitter(1, 1, m_width, m_height);
    for (const std::string& str : m_ssData)
    {
        gpSemiGr->middleline(1, 1, m_width, m_height, str);
    }
    gpSemiGr->endline(1, 1, m_width, m_height);
    gpCrt->crtstyle(MODE_BOLD, FG_CYAN, BG_BLACK);
}

void window::render_frames()
{
    gpCrt->crtstyle(MODE_BOLD, FG_GREEN, BG_BLACK);
    gpSemiGr->topline(1, 1, m_width, m_height);
    for (const std::string& str : m_ssData)
    {
        gpSemiGr->middleline(1, 1, m_width, m_height, str);
    }
    gpSemiGr->endline(1, 1, m_width, m_height);
    gpCrt->crtstyle(MODE_BOLD, FG_CYAN, BG_BLACK);
}

void window::render_text()
{
}

void window::show()
{
    std::cout << "windows descriptor:" << std::endl;
    if (m_ssTitle.size() > 0)
    {
        std::cout << "title: " << m_ssTitle << std::endl;
    }
    std::cout << "x: " << m_x << std::endl;
    std::cout << "y: " << m_y << std::endl;
    std::cout << "width: " << m_width << std::endl;
    std::cout << "height: " << m_height << std::endl;
    std::cout << std::endl;
}

window::~window()
{
}
