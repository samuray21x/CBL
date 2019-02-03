#ifndef ME_STRUCTS_H
#define ME_STRUCTS_H
#include <vector>
#include <stdint.h>
#include "structs_basic.h"

namespace CBL{

    /****************
          TYPEDEFS     
    ****************/
    
    
    /****************
        CONSTANTS     
    ****************/
    const DATASIZE MFS_pageSize = 0x2000;
    const DATASIZE MFS_chunkSize = 0x40;

    /*****************
        STRUCTURES     
    *****************/
    typedef struct {
        uint32_t signature;
        uint32_t USN;
        uint32_t nErase;
        uint16_t nextErase;
        uint16_t firstChunk;
        uint8_t cheksum;
        uint8_t zeroBytes = 0x00;
    } MFS_PAGE_HEADER;

    typedef struct{
        BYTE data[MFS_chunkSize];
        uint16_t crc16;
        uint16_t chunkNumber;
    } CHUNK;

    typedef struct {
        MFS_PAGE_HEADER header;
        BYTE chunksMap[122];
        CHUNK chunks[122];
    } MFS_PAGE;

    /****************
        SIGNATURES     
    ****************/
    const V_BYTE MFS_signaturePage = {0x87, 0x78, 0x55, 0xAA};
}
#endif