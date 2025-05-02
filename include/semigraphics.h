////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/semigraphics.h   2025/05/01 16:54 dwg -  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#ifndef SEMIGRAPHICS_H
#define SEMIGRAPHICS_H



class semigraphics {
public:
    semigraphics();
    void singlebox(int line, int col, int width, int height);
    void topline(int line, int col, int width, int height);
    void middleline(int line, int col, int width, int height,std::string ssText);
    void endline(int line, int col, int width, int height);
};



#endif //SEMIGRAPHICS_H
