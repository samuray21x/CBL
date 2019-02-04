#include <cmath>
#include <iostream>
#include <fstream>
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
        DATASIZE size = buffer.size();
        BYTE t = 0;
        for (int i = 0; i < size/2; ++i){
            t = buffer[i];
            buffer[i] = buffer[size - i - 1];
            buffer[size - i - 1] = t;
        }
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

//IO functions

CBL::DATASIZE CBL::read_file(V_BYTE &buffer, const std::string filepath, const DATASIZE max_read_size, const OFFSET offset){
    DATASIZE count_readed = 0;
    try{
        std::ifstream file;
        file.open(filepath, std::ifstream::binary);
        if (!file) throw CBL::FileNotFoundException();

        if (offset >= 0) file.seekg(offset);
        else file.seekg(offset, file.end);
        
        CBL::BYTE t;
        while (file.read((char*)&t, 1)) {
            count_readed++;
            buffer.push_back(t);
            if (max_read_size != 0 && count_readed == max_read_size) break;
        }
        file.close();
    }
    catch(CBL::FileNotFoundException &e){
        e.error();
        count_readed = -1;
    }
    return count_readed;
}

CBL::DATASIZE CBL::read_file(V_BYTE &buffer, const char *filepath, const DATASIZE max_read_size, const OFFSET offset){
    DATASIZE count_readed = 0;
    try{
        std::ifstream file;
        file.open(filepath, std::ifstream::binary);
        if (!file) throw CBL::FileNotFoundException();

        if (offset >= 0) file.seekg(offset);
        else file.seekg(offset, file.end);
        
        CBL::BYTE t;
        while (file.read((char*)&t, 1)) {
            count_readed++;
            buffer.push_back(t);
            if (max_read_size != 0 && count_readed == max_read_size) break;
        }
        file.close();
    }
    catch(CBL::FileNotFoundException &e){
        e.error();
        count_readed = -1;
    }
    return count_readed;
}

void CBL::printHex(const DATASIZE value){
    printf("%02x", value);
}

void CBL::printHexPrefix(const DATASIZE value){
    printf("0x%02x", value);
}

void CBL::printHex(const V_BYTE &buffer, DATASIZE size, OFFSET offset){
    if (size == 0){
        size = buffer.size();
    }
    else if (size + offset > buffer.size()){
        size = buffer.size() - offset;
    }
    for (DATASIZE i = 0; i < size; ++i){
        printf("%02x", buffer[offset+i]);
        if ( i != (size - 1) ) std::cout<<' ';
    }
}

void CBL::printHexPrefix(const V_BYTE &buffer, DATASIZE size, OFFSET offset){
    if (size == 0){
        size = buffer.size();
    }
    else if (size + offset > buffer.size()){
        size = buffer.size() - offset;
    }
    for (DATASIZE i = 0; i < size; ++i){
        printf("0x%02x", buffer[offset+i]);
        if ( i != (size - 1) ) std::cout<<' ';
    }
}


//TEST
std::string CBL::sprintHex(const DATASIZE value){
    try{
        if (sizeof(value) > 8) throw UnallowableSizeOfArgument();
        char t[17];
        sprintf(t,"%02x", value);
        return std::string(t);
    }
    catch(UnallowableSizeOfArgument &e){
        e.debug();
        return std::string("");
    }
}
std::string CBL::sprintHexPrefix(const DATASIZE value){
    try{
        if (sizeof(value) > 8) throw UnallowableSizeOfArgument();
        char t[19];
        sprintf(t,"0x%02x", value);
        return std::string(t);
    }
    catch(UnallowableSizeOfArgument &e){
        e.debug();
        return std::string("");
    }
}
std::string CBL::sprintHex(const V_BYTE &buffer, DATASIZE size, OFFSET offset){
    std::string result = "";
    if (size == 0){
        size = buffer.size();
    }
    else if (size + offset > buffer.size()){
        size = buffer.size() - offset;
    }
    for (DATASIZE i = 0; i < size; ++i){
        result += sprintHex(buffer[offset+i]);
        if ( i != (size - 1) ) result += ' ';
    }
    return result;
}
std::string CBL::sprintHexPrefix(const V_BYTE &buffer, DATASIZE size, OFFSET offset){
    std::string result = "";
    if (size == 0){
        size = buffer.size();
    }
    else if (size + offset > buffer.size()){
        size = buffer.size() - offset;
    }
    for (DATASIZE i = 0; i < size; ++i){
        result += sprintHexPrefix(buffer[offset+i]);
        if ( i != (size - 1) ) result += ' ';
    }
    return result;
}
