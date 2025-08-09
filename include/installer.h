////////////////////////////////////////////////////////////////////
// ~/public_html/fw/install.h 2025-08-09 09:30 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#pragma once
#include "mwfw2.h"

class installer
{

private:
        window * m_pWin;
public:
        installer();
        bool is_devo_root();
        ~installer();
};

///////////////////////
// eof - installer.h //
///////////////////////