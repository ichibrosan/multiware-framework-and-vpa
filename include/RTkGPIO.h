//
// Created by doug on 6/3/25.
//

#ifndef RTKGPIO_H
#define RTKGPIO_H
#include <cstdio>
#include <unistd.h>


enum {
    IO17 = 'r',
    IO18 = 's',
    IO24 = 'y',
    IO25 = 'z',
    IO5  = 'f',
    IO6  = 'g',
    IO16 = 'q',
    IO23 = 'x',
    IO22 = 'w',
    IO12 = 'm',
    IO20 = 'u',
    IO19 = 't',
    IO4  = 'e',
    IO27 = '|',
    IO21 = 'v',
    IO13 = 'n',
    IO26 = '{'
};

enum {
    PIN_MODE_INPUT =  'I',
    PIN_MODE_OUTPUT = 'O'
};

enum LED_COLORS_T {
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
