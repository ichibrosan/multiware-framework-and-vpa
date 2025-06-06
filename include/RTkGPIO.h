//
// Created by doug on 6/3/25.
//

#ifndef RTKGPIO_H
#define RTKGPIO_H
#include <cstdio>
#include <unistd.h>


enum gpio_pin_types_t {
    TYPE_IO,
    TYPE_3V,
    TYPE_5V,
    TYPE_MOSI,
    TYPE_MISO,
    TYPE_SCLK,
    TYPE_CE0,
    TYPE_CE1,
    TYPE_TXD,
    TYPE_RXD,
    TYPE_SDA,
    TYPE_SCL
};

enum pinch_t {
    IO17P = 'r',
    IO18P = 's',
    IO24P = 'y',
    IO25P = 'z',
    IO5P  = 'f',
    IO6P  = 'g',
    IO16P = 'q',
    IO23P = 'x',
    IO22P = 'w',
    IO12P = 'm',
    IO20P = 'u',
    IO19P = 't',
    IO4P  = 'e',
    IO27P = '|',
    IO21P = 'v',
    IO13P = 'n',
    IO26P = '{'
};

/*
 * Led specific offsets into various vectors
 * such as szLedOn & bLedCntl
*/
enum led_ofs_t {
    IO17,
    IO18,
    IO24,
    IO25,
    IO5,
    IO6,
    IO16,
    IO23,
    IO22,
    IO12,
    IO20,
    IO19,
    IO4,
    IO27,
    IO21,
    IO13,
    IO26
};

enum {
    PIN_MODE_INPUT =  'I',
    PIN_MODE_OUTPUT = 'O'
};

enum gpio_color_indeces_t {
    LED_IGNORE,
    LED_OFF,
    LED_BLUE_OFF,
    LED_BLUE_ON,
    LED_ORANGE_ON,
    LED_PINK_ON,
    LED_RED_ON,
    NUM_LED_COLORS
};

class RTkGPIO {
    std::string m_ssDevice;
    FILE * m_pDevice;

public:
    RTkGPIO();
    std::string get_version();
    void gpio(char8_t pin, char8_t mode,char8_t state);
    void render();

};



#endif //RTKGPIO_H
