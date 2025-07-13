////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/dotconfig.h   2025/04/28                 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

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