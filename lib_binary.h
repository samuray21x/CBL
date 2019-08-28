#ifndef LIB_BINARY_H
#define LIB_BINARY_H
#include "structs_basic.h"
#include <cstring>

namespace CBL{
    Address find_by_signature(const V_Byte &buffer, const V_Byte &signature, Address start_index = 0);
    V_Address find_all_by_signature(const V_Byte &buffer, const V_Byte &signature, Address start_index = 0);
    V_Byte get_buffer(const V_Byte &buffer, const Address offset = 0, Datasize size = 0);
    V_Byte get_reverse_buffer(const V_Byte &buffer, const Address offset = 0, Datasize size = 0);
    V_Byte& reverse_buffer(V_Byte &buffer, const Address offset = 0, Datasize size = 0);
    V_Byte buffer_concat(V_Byte &buffer1, const V_Byte &buffer2);
    V_Byte& add_to_buffer(V_Byte &buffer1, const V_Byte &buffer2);

    //Converting functions
    uint8_t buf2u8(const V_Byte &buffer, const Address offset = 0);
    uint16_t buf2u16(const V_Byte &buffer, const Address offset = 0);
    uint16_t buf2u16r(const V_Byte &buffer, const Address offset = 0);
    uint32_t buf2u32(const V_Byte &buffer, const Address offset = 0);
    uint32_t buf2u32r(const V_Byte &buffer, const Address offset = 0);
    uint64_t buf2u64(const V_Byte &buffer, const Address offset = 0);
    uint64_t buf2u64r(const V_Byte &buffer, const Address offset = 0);
    V_Byte u8buf(uint8_t value);
    V_Byte u8bufr(uint8_t value);
    V_Byte u16buf(uint16_t value);
    V_Byte u16bufr(uint16_t value);
    V_Byte u32buf(uint32_t value);
    V_Byte u32bufr(uint32_t value);
    V_Byte u64buf(uint64_t value);
    V_Byte u64bufr(uint64_t value);
    V_Byte conA2B(Byte* array, Datasize size);

    //IO functions
    Datasize read_file(V_Byte &buffer, const std::string filepath, const Datasize max_read_size = 0, const Datasize offset = 0);
    V_Byte read_file(const std::string filepath, const Datasize max_read_size = 0, const Datasize offset = 0);
    bool folder_exists(std::string foldername);
    int _mkdir(const std::string &path);
    int createDirectory(const std::string &path);
    void removeDirectory(const std::string &path); //Unix dependence
    void writefile(const V_Byte &buffer, const std::string filepath);
    void printHex(const Datasize value);
    void printHexPrefix(const Datasize value);   
    void printHex(const V_Byte &buffer, Datasize size = 0, Datasize offset = 0); 
    void printHexPrefix(const V_Byte &buffer, Datasize size = 0, Datasize offset = 0);
    std::string sprintHex(const Datasize value);
    std::string sprintHexPrefix(const Datasize value);
    std::string sprintHex(const V_Byte &buffer, Datasize size = 0, Datasize offset = 0); 
    std::string sprintHexPrefix(const V_Byte &buffer, Datasize size = 0, Datasize offset = 0);
}

#endif