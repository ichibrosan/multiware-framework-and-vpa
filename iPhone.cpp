////////////////////////////////////////////////////////////////////
// ~/public_html/fw/iPhone.cpp 2025-07-20 03:12 dwg -             //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"
#include "include/iPhone.h"
#include <cstdlib>

int main()
{
    auto pMwFw = std::make_unique<mwfw2>(__FILE__, __FUNCTION__);
    std::cout << "Content-type: text/html\n\n" << std::endl;

    setenv("DISPLAY", ":0", 1);
    std::string command = "xterm -fullscreen -bg \"#FF0000\" &";
    int result = system(command.c_str());
    std::cout << "Message sent";

    return 0;
}