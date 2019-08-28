#include "lib_crypto.h"

uint16_t CBL::crc16_ccitt(V_Byte &buffer){
    uint16_t crc = 0xFFFF;
    Byte i;
    for (Datasize i = 0; i < buffer.size(); ++i)
    {
        crc ^= buffer[i] << 8;

        for (uint8_t j = 0; j < 8; j++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}