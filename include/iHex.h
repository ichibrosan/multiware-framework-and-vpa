////////////////////////////////////////////////////////////////////
// ~/public_html/fw/iHex.h 2025-07-16 08:08 dwg -                 //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#pragma once

class iHex
{
public:
    iHex();
    std::string convert_uchar_to_hex(uint8_t);
    uint8_t calculate_checksum(const std::vector<uint8_t>&);
    std::string structure_to_intel_hex(void* struct_ptr,
                                       size_t struct_size,
                                       uint16_t start_address);
};

//////////////////
// eof - iHex.h //
//////////////////
