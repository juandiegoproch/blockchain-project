#pragma once

#include <string>
#include <cstdint>

struct uint512_t
{
    unsigned char data[64];

    uint512_t() = default;

    uint512_t& operator=(const uint512_t&& other)
    {
        for (int i = 0; i<64;i++)
        {
            data[i] = other.data[i];
        }
        return *this;
    }

    uint512_t& operator=(const uint512_t& other)
    {
        for (int i = 0; i<64;i++)
        {
            data[i] = other.data[i];
        }
        return *this;
    }

    uint512_t& operator=(unsigned int other)
    {
        char* other_data = (char*)&other;
        // 64 - sizeof(uint) must be 0
        // sizeof(uint) must copy data exactly
        for (int i = 0; i<64; i++)
        {
            data[i] = 0;
        }

        for (int i = 0; i<sizeof(unsigned int); i++)
        {
            data[i] = *other_data;
            other_data++;
        }
        return *this;
    }

    uint512_t(uint512_t&& other)
    {
        for (int i = 0; i<64;i++)
        {
            data[i] = other.data[i];
        }
    }

    uint512_t(const uint512_t& other)
    {
        for (int i = 0; i<64;i++)
        {
            data[i] = other.data[i];
        }
    }
};

int getValueFromHexDigit(char digit)
{
    switch(digit)
    {
        case '0':
        return 0;
        break;
    
        case '1':
        return 1;
        break;

        case '2':
        return 2;
        break;

        case '3':
        return 3;
        break;

        case '4':
        return 4;
        break;

        case '5':
        return 5;
        break;

        case '6':
        return 6;
        break;

        case '7':
        return 7;
        break;

        case '8':
        return 8;
        break;

        case '9':
        return 9;
        break;

        case 'A':
        return 10;
        break;

        case 'a':
        return 10;
        break;

        case 'B':
        return 11;
        break;

        case 'b':
        return 11;
        break;

        case 'C':
        return 12;
        break;

        case 'c':
        return 12;
        break;

        case 'D':
        return 13;
        break;

        case 'd':
        return 13;
        break;

        case 'E':
        return 14;
        break;

        case 'e':
        return 14;
        break;

        case 'F':
        return 15;
        break;

        case 'f':
        return 15;
        break;

        default:
        return -1;
        break;
    }
}

uint512_t getui512fromstr(std::string num_string)
{
    if (num_string[1] = 'x') // 0x formatted hex value. discard
    {
        num_string = num_string.substr(2);
    }
    
    uint512_t to_ret;
    unsigned char byte;
    for (int i = 0; i<128;i+=2) // avanzar de 2 en 2, (byte en byte)
    {
        unsigned char msn = getValueFromHexDigit(num_string[i]);
        unsigned char lsn = getValueFromHexDigit(num_string[i+1]);
        byte = msn*16 + lsn;
        
        to_ret.data[i/2] = byte;
    }
    return to_ret;
}

std::string to_string(uint512_t dat)
{
    char hdigits[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    std::string to_ret = "0x";

    for (int i=0;i<64;i++) // for byte in 64-byte-long-field
    {
        unsigned int lsn = dat.data[i]%16;
        unsigned int msn = dat.data[i]/16;

        to_ret += hdigits[msn];
        to_ret += hdigits[lsn];
    }

    return to_ret;
}