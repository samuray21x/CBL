#include "cmath"
#include <iostream>
#include <stdio.h> // debug
#include "lib_binary.h"
#include "exceptions.h"

CBL::ADDRESS CBL::find_by_signature(const CBL::V_BYTE &buffer, const CBL::V_BYTE &signature, CBL::ADDRESS start_index){
    unsigned int offset = -1;
    bool find = false;
    for(unsigned int i = start_index; i <= buffer.size() - signature.size(); ++i){
        if (buffer[i] == signature[0]) {
            find = true;
            for (unsigned int j = 1; j < signature.size(); ++j){
                if (buffer[i+j] != signature[j]){ find = false;  break; }
            }
            if (find) {
                offset = i;
                return offset;
            }
        }
    }
    return offset;
}
CBL::V_ADDRESS CBL::find_all_by_signature(const CBL::V_BYTE &buffer, const CBL::V_BYTE &signature, CBL::ADDRESS start_index){
    CBL::V_ADDRESS offsets;
    try{
        for (CBL::ADDRESS cur_offset = 0; cur_offset != (unsigned)-1; ){
            cur_offset = find_by_signature(buffer,signature, cur_offset+1);
            if (cur_offset == (unsigned)-1) break;
            offsets.push_back(cur_offset);
        }
        return offsets;
    }
    catch(...){
        std::cerr<<"[ERROR] Unknown exception!"<<std::endl;
        exit(-1);
    }    
}

CBL::V_BYTE CBL::get_reverse_buffer(const V_BYTE &buffer, const ADDRESS offset, const DATASIZE size){
    //
    //get buffer func then write

    V_BYTE temp;
    for (int i = buffer.size() - 1; i >= 0; --i) temp.push_back(buffer[i]);
    return temp;
}
void CBL::reverse_buffer(CBL::V_BYTE &buffer){  // rewrite algorithm
        V_BYTE temp;
        for (int i = buffer.size() - 1; i >= 0; --i) temp.push_back(buffer[i]);
        buffer = temp;
}




uint8_t CBL::buf2u8(const CBL::V_BYTE &buffer, ADDRESS offset){
    return buffer.size() > offset ? buffer[offset] : 0;   
}
uint16_t CBL::buf2u16(const CBL::V_BYTE &buffer, ADDRESS offset){
    uint16_t result = {0};
    char size = buffer.size()-offset <= 2 ? buffer.size()-offset : 2;
    for (unsigned int i = 0; i < size ; ++i) result += buffer[offset+size-i-1]*std::pow(0x100, i);
    return result;
}
uint32_t CBL::buf2u32(const CBL::V_BYTE &buffer, ADDRESS offset){
    uint32_t result = {0};
    char size = buffer.size()-offset <= 4 ? buffer.size()-offset : 4;
    for (unsigned int i = 0; i < size ; ++i) result += buffer[offset+size-i-1]*std::pow(0x100, i);
    return result;
}
uint64_t CBL::buf2u64(const CBL::V_BYTE &buffer, ADDRESS offset){
    uint64_t result = {0};
    char size = buffer.size()-offset <= 8 ? buffer.size()-offset : 8;
    for (unsigned int i = 0; i < size ; ++i) result += buffer[offset+size-i-1]*std::pow(0x100, i);
    return result;
}

//for debug
void printHex(const CBL::V_BYTE &buffer, const CBL::DATASIZE size){
    for (CBL::DATASIZE i = 0; i < size; ++i){
        printf("0x%02x", buffer[i]);
        if ( i != (size - 1) ) std::cout<<' ';
    }
}

void printHex(const CBL::DATASIZE value){
    printf("0x%02x", value);
}
