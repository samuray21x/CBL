#ifndef LIB_CRYPTO_H
#define LIB_CRYPTO_H
#include "stdint.h"
#include "structs_basic.h"

namespace CBL
{
    uint16_t crc16_ccitt(V_Byte &buffer);
}

#endif