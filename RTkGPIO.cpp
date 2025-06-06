//
// Created by doug on 6/3/25.
//
#include "mwfw2.h"
#include <cstdio>
#include <string>
#include "RTkGPIO.h"

#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <bits/ostream.tcc>


RTkGPIO::RTkGPIO() {
    m_ssDevice = "/dev/ttyUSB0";

    // Open the device for read/write
    int fd = open(m_ssDevice.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        std::cerr << "Failed to open device: " << m_ssDevice << std::endl;
        exit(1);
    }

    // Configure serial port settings
    struct termios options;
    tcgetattr(fd, &options);

    // Set baud rate to 230400
    cfsetispeed(&options, B230400);
    cfsetospeed(&options, B230400);

    // Configure 8N1 (8 data bits, no parity, 1 stop bit)
    options.c_cflag &= ~PARENB;   // No parity
    options.c_cflag &= ~CSTOPB;   // 1 stop bit
    options.c_cflag &= ~CSIZE;    // Clear data size bits
    options.c_cflag |= CS8;       // 8 data bits
    options.c_cflag |= CREAD | CLOCAL; // Enable receiver, ignore modem control lines

    // Disable hardware flow control
    options.c_cflag &= ~CRTSCTS;

    // Configure input/output flags for raw mode
    options.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control
    options.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
    options.c_oflag &= ~OPOST; // Raw output

    // Set timeout values
    options.c_cc[VMIN] = 0;   // Minimum characters to read
    options.c_cc[VTIME] = 10; // Timeout in deciseconds (1 second)

    // Apply the configuration
    if (tcsetattr(fd, TCSANOW, &options) != 0) {
        std::cerr << "Failed to configure serial port" << std::endl;
        close(fd);
        exit(1);
    }

    // Convert file descriptor to FILE pointer
    m_pDevice = fdopen(fd, "r+");
    if (m_pDevice == nullptr) {
        std::cerr << "Failed to create FILE pointer from file descriptor" << std::endl;
        close(fd);
        exit(1);
    }

    // Make sure output is unbuffered for immediate transmission
    setbuf(m_pDevice, nullptr);



}

std::string RTkGPIO::get_version() {
    char szTemp[128];
    usleep(100000);  // 100 milliseconds instead of 1 second
    fputs("V\r", m_pDevice);
    fflush(m_pDevice); // Ensure data is sent immediately
    usleep(100000);  // 100 milliseconds instead of 1 second

    if (fgets(szTemp, sizeof(szTemp), m_pDevice)) {
        return std::string(szTemp);
    }
    return "";
}

/*
 * GPIO Commands are two characters.
 * <pinch> <cmdch>
 *
 * pinch is the pin character (a..z) where 'a' represents pin 0.
 * cmdch is the command to perform on that pin:
 *   I: Set this pin to a digital input,        eg: aI
 *   O: Set this pin to a digital output,       eg: aO
 *   0: Write a digital low to this output,     eg: a0
 *   1: Write a digital high to this output,    eg: a1
 *   U: Write a pull input high,    eg: aU
 *   D: Write a pull input down,    eg: aD
 *   ?: Read the state of this digital input,   eg: a?
 *      State is returned as pinch + state(0|1) eg: a0
 */

void RTkGPIO::gpio(char8_t pin, char8_t mode,char8_t state) {
     int delay = 1;

    // Send pin number
    fputc(pin, m_pDevice);
    usleep(delay);  // 1 millisecond
    // Send Mode
    fputc(mode, m_pDevice);
    usleep(delay);  // 1 millisecond

    fputc(pin, m_pDevice);
    usleep(delay);  // 1 millisecond
    fputc(state, m_pDevice);
    usleep(delay);  // 1 millisecond

}

// int GPIOmap[] = {
//   TYPE_3V, IO17,     IO18,    TYPE_MOSI,TYPE_MISO,TYPE_SCLK,TYPE_CE0,TYPE_CE1,
//   TYPE_3V, TYPE_TXD, TYPE_RXD,IO24,     IO25,     IO5,      IO6,     IO16,
//   TYPE_5V, IO23,     IO22,    IDSD,     IDSC,     IO12,     IO20,    IO19,
//   TYPE_5V, TYPE_SDA, TYPE_SCL,IO4,      IO27,     IO21,     IO13,    IO26
// };


// void RTkGPIO::update_led_filenames() {
//     // szLedColorFNs[17][]
//
// }


void RTkGPIO::render() {
    // for (int index=0;index<(4*8)) {
    //     switch (index) {
    //         case TYPE_3V:
    //             break;
    //         case TYPE_5V:
    //             break;
    //         case TYPE_MOSI:
    //             break;
    //         case TYPE_MISO:
    //             break;
    //         case TYPE_SCLK:
    //             break;
    //         case TYPE_CE0:
    //             break;
    //         case TYPE_CE1:
    //             break;
    //         case TYPE_TXD:
    //             break;
    //         case TYPE_RXD:
    //             break;
    //         case TYPE_SDA:
    //             break;
    //         case TYPE_SCL:
    //             break;
    //         case IO17:
    //             gpio(IO17,PIN_MODE_OUTPUT,gpSh->m_pShMemng->bLed)
    //         case IO18:
    //         case IO24:
    //         case IO25:
    //         case IO5:
    //         case IO6:
    //         case IO16:
    //         case IO23:
    //         case IO22:
    //         case IO12:
    //         case IO20:
    //         case IO19:
    //         case IO4:
    //         case IO27:
    //         case IO21:
    //         case IO13:
    //         case IO26:
    //             gpio
    //             gpio
    //             break;
    //         default:
    //             break;
    //     }
    // }
}
