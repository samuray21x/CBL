#ifndef LIB_BINARY_H
#define LIB_BINARY_H
#include "structs_basic.h"
#include <cstring>

namespace CBL{
    ADDRESS find_by_signature(const V_BYTE &buffer, const V_BYTE &signature, ADDRESS start_index = 0);
    V_ADDRESS find_all_by_signature(const V_BYTE &buffer, const V_BYTE &signature, ADDRESS start_index = 0);
    V_BYTE get_reverse_buffer(const V_BYTE &buffer, const ADDRESS offset = 0, const DATASIZE size = 0); // rewrite
    void reverse_buffer(V_BYTE &buffer);  // rewrite algorithm
    uint8_t buf2u8(const V_BYTE &buffer, const ADDRESS offset = 0);
    uint16_t buf2u16(const V_BYTE &buffer, const ADDRESS offset = 0);
    uint32_t buf2u32(const V_BYTE &buffer, const ADDRESS offset = 0);
    uint64_t buf2u64(const V_BYTE &buffer, const ADDRESS offset = 0);

    //IO functions
    DATASIZE read_file(V_BYTE &buffer, const std::string filepath, const DATASIZE max_read_size = 0, const OFFSET offset = 0);
    DATASIZE read_file(V_BYTE &buffer, const char *filepath, const DATASIZE max_read_size = 0, const OFFSET offset = 0);
    void printHex(const DATASIZE value);
    void printHexPrefix(const DATASIZE value);   
    void printHex(const V_BYTE &buffer, DATASIZE size = 0, OFFSET offset = 0);
    void printHexPrefix(const V_BYTE &buffer, DATASIZE size = 0, OFFSET offset = 0);
    std::string sprintHex(const DATASIZE value);
    std::string sprintHexPrefix(const DATASIZE value);
    std::string sprintHex(const V_BYTE &buffer, DATASIZE size = 0, OFFSET offset = 0);
    std::string sprintHexPrefix(const V_BYTE &buffer, DATASIZE size = 0, OFFSET offset = 0);
}
#endif