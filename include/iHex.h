//
// Created by doug on 3/15/25.
//

#pragma once

class iHex {
public:
    iHex();
    std::string convert_uchar_to_hex(uint8_t);
    uint8_t calculate_checksum(const std::vector<uint8_t>&);
    std::string structure_to_intel_hex(void * struct_ptr,
        size_t struct_size,uint16_t start_address);
};

//////////////////
// eof - iHex.h //
//////////////////