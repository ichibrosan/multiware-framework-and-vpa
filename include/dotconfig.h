////////////////////////////////////////////////////////////////////
// ~/public_html/fw/dotconfig.h 2025-07-16 08:08 dwg -            //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#pragma once

class dotconfig {
    bool m_bCTOR;
public:
    dotconfig();
    bool isConfigDir();
    bool assureConfigDir();
    bool isLicenseUUID();
};

///////////////////////
// eof - dotconfig.h //
///////////////////////