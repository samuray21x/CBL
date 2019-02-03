#ifndef LIB_BINARY_H
#define LIB_BINARY_H
#include <vector>
#include "structs_basic.h"

namespace CBL{

    ADDRESS find_by_signature(const V_BYTE &buffer, const V_BYTE &signature, ADDRESS start_index = 0);
    V_ADDRESS find_all_by_signature(const V_BYTE &buffer, const V_BYTE &signature, ADDRESS start_index = 0);
    V_BYTE get_reverse_buffer(const V_BYTE &buffer, const ADDRESS offset = 0, const DATASIZE size = 0); // rewrite
    void reverse_buffer(V_BYTE &buffer);  // rewrite algorithm
    uint8_t buf2u8(const V_BYTE &buffer, const ADDRESS offset = 0);
    uint16_t buf2u16(const V_BYTE &buffer, const ADDRESS offset = 0);
    uint32_t buf2u32(const V_BYTE &buffer, const ADDRESS offset = 0);
    uint64_t buf2u64(const V_BYTE &buffer, const ADDRESS offset = 0);   
}

// FOR DEBUG
void printHex(const std::vector<CBL::BYTE> &buffer, const CBL::DATASIZE size);
void printHex(const CBL::DATASIZE value);
#endif