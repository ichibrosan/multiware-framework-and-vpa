////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/window.h   2025/05/01 16:54 dwg -        //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#ifndef WINDOW_H
#define WINDOW_H

struct WinDesc {
    int x;
    int y;
    int width;
    int height;
    std::vector<std::string> ssData;
};

class window {
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    std::vector<std::string> m_ssData;
public:
    window(
        // WinDesc&
        );
    void add_row(std::string);
    void render();
    void show();
    ~window();
};

#endif //WINDOW_H
