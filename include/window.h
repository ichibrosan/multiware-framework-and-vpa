////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/window.h   2025/05/01 16:54 dwg -        //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#pragma once

struct WinDesc
{
    int x;
    int y;
    int width;
    int height;
    std::vector<std::string> ssData;
};

class window
{
    int m_x; // zero relative column number of left corner edge
    int m_y; // zero relative line number of top edge
    int m_width; // width of window  (dynamic)
    int m_height; // height of window (dynamic)
    std::string m_ssTitle;
    std::vector<std::string> m_ssData;

public:
    window(
        // WinDesc&
    );
    int get_height();
    int get_width();
    int get_x();
    int get_y();
    void add_row(std::string);
    void render_frames();
    void render_text();
    void render();
    void set_title(std::string ssTitle);
    void show();
    ~window();
};

////////////////////
// eof - window.h //
////////////////////
