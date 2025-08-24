////////////////////////////////////////////////////////////////////
// ~/public_html/fw/iHex.cpp 2025-07-15 18:16 dwg -               //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

iHex::iHex()
{
}

std::string iHex::convert_uchar_to_hex(uint8_t byte)
{
    std::ostringstream hex_stream;
    hex_stream << std::hex
        << std::setfill('0')
        << std::setw(2)
        << static_cast<int>(byte);
    return hex_stream.str();
}

// Function to calculate checksum for Intel Hex record
uint8_t iHex::calculate_checksum(const std::vector<uint8_t>& record)
{
    uint8_t sum = 0;
    for (const auto& byte : record)
    {
        sum += byte;
    }
    return static_cast<uint8_t>(-sum);
}

// Function to convert structure to Intel Hex format
std::string iHex::structure_to_intel_hex(void* struct_ptr,
                                         size_t struct_size,
                                         uint16_t start_address)
{
    const uint8_t* data = reinterpret_cast<uint8_t*>(struct_ptr);

    constexpr size_t bytes_per_line = 16; // 16 bytes per line in Intel Hex
    std::ostringstream hex_stream;

    for (size_t offset = 0; offset < struct_size; offset += bytes_per_line)
    {
        // Number of bytes for the current line
        size_t len = std::min(bytes_per_line, struct_size - offset);

        // Record in Intel Hex: BYTE COUNT (1) + ADDRESS (2) + RECORD TYPE (1) + DATA (len) + CHECKSUM (1)
        std::vector<uint8_t> record;

        // Byte count
        record.push_back(static_cast<uint8_t>(len));

        // Address (2 bytes, high byte first)
        uint16_t address = start_address + static_cast<uint16_t>(offset);
        record.push_back(static_cast<uint8_t>((address >> 8) & 0xFF));
        // High byte
        record.push_back(static_cast<uint8_t>(address & 0xFF)); // Low byte

        // Record type (0x00 for data)
        record.push_back(0x00);

        // Data
        for (size_t i = 0; i < len; ++i)
        {
            record.push_back(data[offset + i]);
        }

        // Checksum
        uint8_t checksum = calculate_checksum(record);

        // Convert record data to hex string
        hex_stream << ":";
        for (const auto& byte : record)
        {
            hex_stream << convert_uchar_to_hex(byte);
        }

        // Append checksum
        hex_stream << convert_uchar_to_hex(checksum);
        hex_stream << "\n";
    }

    // End-of-file record
    hex_stream << ":00000001FF\n";

    return hex_stream.str();
}

