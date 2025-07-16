////////////////////////////////////////////////////////////////////
// ~/public_html/fw/RTkGPIO.cpp 2025-07-15 18:16 dwg -            //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

RTkGPIO::RTkGPIO()
{
    m_ssDevice = "/dev/ttyUSB0";

    // Open the device for read/write
    int fd = open(m_ssDevice.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
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
    options.c_cflag &= ~PARENB; // No parity
    options.c_cflag &= ~CSTOPB; // 1 stop bit
    options.c_cflag &= ~CSIZE; // Clear data size bits
    options.c_cflag |= CS8; // 8 data bits
    options.c_cflag |= CREAD | CLOCAL;
    // Enable receiver, ignore modem control lines

    // Disable hardware flow control
    options.c_cflag &= ~CRTSCTS;

    // Configure input/output flags for raw mode
    options.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control
    options.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
    options.c_oflag &= ~OPOST; // Raw output

    // Set timeout values
    options.c_cc[VMIN] = 0; // Minimum characters to read
    options.c_cc[VTIME] = 10; // Timeout in deciseconds (1 second)

    // Apply the configuration
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        std::cerr << "Failed to configure serial port" << std::endl;
        close(fd);
        exit(1);
    }

    // Convert file descriptor to FILE pointer
    m_pDevice = fdopen(fd, "r+");
    if (m_pDevice == nullptr)
    {
        std::cerr << "Failed to create FILE pointer from file descriptor" <<
            std::endl;
        close(fd);
        exit(1);
    }

    // Make sure output is unbuffered for immediate transmission
    setbuf(m_pDevice, nullptr);

    gpio(IO17P, PIN_MODE_OUTPUT, '0');
    gpio(IO18P, PIN_MODE_OUTPUT, '0');
    gpio(IO24P, PIN_MODE_OUTPUT, '0');
    gpio(IO25P, PIN_MODE_OUTPUT, '0');
    gpio(IO5P, PIN_MODE_OUTPUT, '0');
    gpio(IO6P, PIN_MODE_OUTPUT, '0');
    gpio(IO16P, PIN_MODE_OUTPUT, '0');
    gpio(IO23P, PIN_MODE_OUTPUT, '0');
    gpio(IO22P, PIN_MODE_OUTPUT, '0');
    gpio(IO12P, PIN_MODE_OUTPUT, '0');
    gpio(IO20P, PIN_MODE_OUTPUT, '0');
    gpio(IO19P, PIN_MODE_OUTPUT, '0');
    gpio(IO4P, PIN_MODE_OUTPUT, '0');
    gpio(IO4P, PIN_MODE_OUTPUT, '0');
    gpio(IO27P, PIN_MODE_OUTPUT, '0');
    gpio(IO13P, PIN_MODE_OUTPUT, '0');
    gpio(IO26P, PIN_MODE_OUTPUT, '0');

    set(IO17P, IO17);
    set(IO18P, IO18);
    set(IO24P, IO24);
    set(IO25P, IO25);
    set(IO5P, IO5);
    set(IO6P, IO6);
    set(IO16P, IO16);
    set(IO23P, IO23);
    set(IO22P, IO22);
    set(IO12P, IO12);
    set(IO20P, IO20);
    set(IO19P, IO19);
    set(IO4P, IO4);
    set(IO27P, IO27);
    set(IO21P, IO21);
    set(IO13P, IO13);
    set(IO26P, IO26);
}

std::string RTkGPIO::get_version()
{
    char szTemp[128];
    usleep(100000); // 100 milliseconds instead of 1 second
    fputs("V\r", m_pDevice);
    fflush(m_pDevice); // Ensure data is sent immediately
    usleep(100000); // 100 milliseconds instead of 1 second

    if (fgets(szTemp, sizeof(szTemp), m_pDevice))
    {
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

void RTkGPIO::gpio(char8_t pin, char8_t mode, char8_t state)
{
    int delay = 1;

    // Send pin number
    fputc(pin, m_pDevice);
    usleep(delay); // 1 millisecond
    // Send Mode
    fputc(mode, m_pDevice);
    usleep(delay); // 1 millisecond

    fputc(pin, m_pDevice);
    usleep(delay); // 1 millisecond
    fputc(state, m_pDevice);
    usleep(delay); // 1 millisecond

    // switch (pin) {
    //     case IO17P:
    //         gpSh->m_pShMemng->bLedCntl[IO17] = true;
    //         break;
    //     case IO18P:
    //         gpSh->m_pShMemng->bLedCntl[IO18] = true;
    //         break;
    //     default:
    //         break;
    // }
}

void RTkGPIO::set(pinch_t pin, led_ofs_t index)
{
    int delay = 1;

    fputc(pin, m_pDevice);
    usleep(delay); // 1 millisecond
    fputc('1', m_pDevice);
    usleep(delay); // 1 millisecond
    gpSh->m_pShMemng->bLedCntl[index] = true;
}

void RTkGPIO::reset(pinch_t pin, led_ofs_t index)
{
    int delay = 1;

    fputc(pin, m_pDevice);
    usleep(delay); // 1 millisecond
    fputc('0', m_pDevice);
    usleep(delay); // 1 millisecond
    gpSh->m_pShMemng->bLedCntl[index] = false;
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


void RTkGPIO::render()
{
    for (int index = 0; index < 17; index++)
    {
        switch (index)
        {
        case IO17:
            if (gpSh->m_pShMemng->bLedCntl[IO17])
            {
                set(IO17P, IO17);
            }
            else
            {
                reset(IO17P, IO17);
            }
            break;

        case IO18:
            if (gpSh->m_pShMemng->bLedCntl[IO18])
            {
                set(IO18P, IO18);
            }
            else
            {
                reset(IO18P, IO18);
            }
            break;

        case IO24:
            if (gpSh->m_pShMemng->bLedCntl[IO24])
            {
                set(IO24P, IO24);
            }
            else
            {
                reset(IO24P, IO24);
            }
            break;

        case IO25:
            if (gpSh->m_pShMemng->bLedCntl[IO25])
            {
                set(IO25P, IO25);
            }
            else
            {
                reset(IO25P, IO25);
            }
            break;

        case IO5:
            if (gpSh->m_pShMemng->bLedCntl[IO5])
            {
                set(IO5P, IO5);
            }
            else
            {
                reset(IO5P, IO5);
            }
            break;

        case IO6:
            if (gpSh->m_pShMemng->bLedCntl[IO5])
            {
                set(IO5P, IO5);
            }
            else
            {
                reset(IO6P, IO6);
            }
            break;

        case IO16:
            if (gpSh->m_pShMemng->bLedCntl[IO16])
            {
                set(IO16P, IO16);
            }
            else
            {
                reset(IO16P, IO16);
            }
            break;

        case IO23:
            if (gpSh->m_pShMemng->bLedCntl[IO23])
            {
                set(IO23P, IO23);
            }
            else
            {
                reset(IO23P, IO23);
            }
            break;

        case IO22:
            if (gpSh->m_pShMemng->bLedCntl[IO22])
            {
                set(IO22P, IO22);
            }
            else
            {
                reset(IO22P, IO22);
            }
            break;

        case IO12:
            if (gpSh->m_pShMemng->bLedCntl[IO12])
            {
                set(IO12P, IO12);
            }
            else
            {
                reset(IO12P, IO12);
            }
            break;

        case IO20:
            if (gpSh->m_pShMemng->bLedCntl[IO20])
            {
                set(IO20P, IO20);
            }
            else
            {
                reset(IO20P, IO20);
            }
            break;

        case IO19:
            if (gpSh->m_pShMemng->bLedCntl[IO19])
            {
                set(IO19P, IO19);
            }
            else
            {
                reset(IO19P, IO19);
            }
            break;

        case IO4:
            if (gpSh->m_pShMemng->bLedCntl[IO4])
            {
                set(IO4P, IO4);
            }
            else
            {
                reset(IO4P, IO4);
            }
            break;

        case IO27:
            if (gpSh->m_pShMemng->bLedCntl[IO27])
            {
                set(IO27P, IO27);
            }
            else
            {
                reset(IO27P, IO27);
            }
            break;

        case IO21:
            if (gpSh->m_pShMemng->bLedCntl[IO21])
            {
                set(IO21P, IO21);
            }
            else
            {
                reset(IO21P, IO21);
            }
            break;

        case IO13:
            if (gpSh->m_pShMemng->bLedCntl[IO13])
            {
                set(IO13P, IO13);
            }
            else
            {
                reset(IO13P, IO13);
            }
            break;

        case IO26:
            if (gpSh->m_pShMemng->bLedCntl[IO26])
            {
                set(IO26P, IO26);
            }
            else
            {
                reset(IO26P, IO26);
            }
            break;

        default:
            break;
        }
    }
}
