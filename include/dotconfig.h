////////////////////////////////////////////////////////////////////
// ~/public_html/fw/dotconfig.h 2025-07-16 08:08 dwg -            //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
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