////////////////////////////////////////////////////////////////////
// ~/public_html/fw/iHex.h 2025-07-16 08:08 dwg -                 //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
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
