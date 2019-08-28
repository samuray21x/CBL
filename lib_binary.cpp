#include <cmath>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "lib_binary.h"
#include "exceptions.h"
#include <sstream>
#include <sys/stat.h>
// for windows mkdir
#ifdef _WIN32
#include <direct.h>
#endif

CBL::Address CBL::find_by_signature(const CBL::V_Byte &buffer, const CBL::V_Byte &signature, CBL::Address start_index)
{
    unsigned int offset = -1;
    bool find = false;
    for (unsigned int i = start_index; i <= buffer.size() - signature.size(); ++i)
    {
        if (buffer[i] == signature[0])
        {
            find = true;
            for (unsigned int j = 1; j < signature.size(); ++j)
            {
                if (buffer[i + j] != signature[j])
                {
                    find = false;
                    break;
                }
            }
            if (find)
            {
                offset = i;
                return offset;
            }
        }
    }
    return offset;
}
CBL::V_Address CBL::find_all_by_signature(const CBL::V_Byte &buffer, const CBL::V_Byte &signature, CBL::Address start_index)
{
    CBL::V_Address offsets;
    try
    {
        for (CBL::Address cur_offset = 0; cur_offset != (unsigned)-1;)
        {
            cur_offset = find_by_signature(buffer, signature, cur_offset + 1);
            if (cur_offset == (unsigned)-1)
                break;
            offsets.push_back(cur_offset);
        }
        return offsets;
    }
    catch (...)
    {
        std::cerr << "[ERROR] Unknown exception!" << std::endl;
        exit(-1);
    }
}

CBL::V_Byte CBL::get_buffer(const CBL::V_Byte &buffer, const CBL::Address offset, CBL::Datasize size)
{
    V_Byte result;
    if (size == 0)
    {
        if (offset == 0)
            size = buffer.size();
        else
            size = buffer.size() - offset;
    }
    else
        size = (buffer.size() - offset) < size ? (buffer.size() - offset) : size;
    for (Datasize i = offset; i < size + offset; ++i)
        result.push_back(buffer[i]);
    return result;
}

CBL::V_Byte CBL::get_reverse_buffer(const V_Byte &buffer, const Address offset, Datasize size)
{
    V_Byte temp = get_buffer(buffer, offset, size);
    reverse_buffer(temp);
    return temp;
}
CBL::V_Byte &CBL::reverse_buffer(CBL::V_Byte &buffer, const Address offset, Datasize size)
{
    if (size == 0)
    {
        if (offset == 0)
            size = buffer.size();
        else
            size = buffer.size() - offset;
    }
    else
        size = (buffer.size() - offset) < size ? (buffer.size() - offset) : size;
    Byte t = 0;
    for (int i = 0; i < (size / 2); ++i)
    {
        t = buffer[offset + i];
        buffer[offset + i] = buffer[offset + size - i - 1];
        buffer[offset + size - i - 1] = t;
    }
    return buffer;
}

CBL::V_Byte CBL::buffer_concat(V_Byte &buffer1, const V_Byte &buffer2)
{
    V_Byte result = buffer1;
    add_to_buffer(result, buffer2);
    return result;
}

CBL::V_Byte &CBL::add_to_buffer(V_Byte &buffer1, const V_Byte &buffer2)
{
    for (Datasize i = 0; i < buffer2.size(); ++i)
        buffer1.push_back(buffer2[i]);
    return buffer1;
}

uint8_t CBL::buf2u8(const CBL::V_Byte &buffer, Address offset)
{
    return buffer.size() > offset ? buffer[offset] : 0;
}

uint16_t CBL::buf2u16(const CBL::V_Byte &buffer, Address offset)
{
    uint16_t result = {0};
    unsigned int size = buffer.size() - offset <= 2 ? buffer.size() - offset : 2;
    for (unsigned int i = 0; i < size; ++i)
        result += buffer[offset + size - i - 1] * std::pow(0x100, i);
    return result;
}
uint16_t CBL::buf2u16r(const CBL::V_Byte &buffer, Address offset)
{
    uint16_t result = {0};
    unsigned int size = buffer.size() - offset <= 2 ? buffer.size() - offset : 2;
    for (unsigned int i = 0; i < size; ++i)
        result += buffer[offset + i] * std::pow(0x100, i);
    return result;
}
uint32_t CBL::buf2u32(const CBL::V_Byte &buffer, Address offset)
{
    uint32_t result = {0};
    unsigned int size = buffer.size() - offset <= 4 ? buffer.size() - offset : 4;
    for (unsigned int i = 0; i < size; ++i)
        result += buffer[offset + size - i - 1] * std::pow(0x100, i);
    return result;
}
uint32_t CBL::buf2u32r(const CBL::V_Byte &buffer, Address offset)
{
    uint32_t result = {0};
    unsigned int size = buffer.size() - offset <= 4 ? buffer.size() - offset : 4;
    for (unsigned int i = 0; i < size; ++i)
        result += buffer[offset + i] * std::pow(0x100, i);
    return result;
}
uint64_t CBL::buf2u64(const CBL::V_Byte &buffer, Address offset)
{
    uint64_t result = {0};
    unsigned int size = buffer.size() - offset <= 8 ? buffer.size() - offset : 8;
    for (unsigned int i = 0; i < size; ++i)
        result += buffer[offset + size - i - 1] * std::pow(0x100, i);
    return result;
}
uint64_t CBL::buf2u64r(const CBL::V_Byte &buffer, Address offset)
{
    uint64_t result = {0};
    unsigned int size = buffer.size() - offset <= 8 ? buffer.size() - offset : 8;
    for (unsigned int i = 0; i < size; ++i)
        result += buffer[offset + i] * std::pow(0x100, i);
    return result;
}

CBL::V_Byte CBL::u8buf(uint8_t value)
{
    V_Byte result;
    result.push_back(value);
    return result;
}

CBL::V_Byte CBL::u16buf(uint16_t value)
{
    V_Byte result;
    int size = sizeof(uint16_t);
    for (int i = 0; i < size; ++i)
    {
        result.push_back(value % 0x100);
        value /= 0x100;
    }
    return reverse_buffer(result);
}
CBL::V_Byte CBL::u16bufr(uint16_t value)
{
    V_Byte result;
    int size = sizeof(uint16_t);
    for (int i = 0; i < size; ++i)
    {
        result.push_back(value % 0x100);
        value /= 0x100;
    }
    return result;
}
CBL::V_Byte CBL::u32buf(uint32_t value)
{
    V_Byte result;
    int size = sizeof(uint32_t);
    for (int i = 0; i < size; ++i)
    {
        result.push_back(value % 0x100);
        value /= 0x100;
    }
    return reverse_buffer(result);
}
CBL::V_Byte CBL::u32bufr(uint32_t value)
{
    V_Byte result;
    int size = sizeof(uint32_t);
    for (int i = 0; i < size; ++i)
    {
        result.push_back(value % 0x100);
        value /= 0x100;
    }
    return result;
}
CBL::V_Byte CBL::u64buf(uint64_t value)
{
    V_Byte result;
    int size = sizeof(uint64_t);
    for (int i = 0; i < size; ++i)
    {
        result.push_back(value % 0x100);
        value /= 0x100;
    }
    return reverse_buffer(result);
}
CBL::V_Byte CBL::u64bufr(uint64_t value)
{
    V_Byte result;
    int size = sizeof(uint64_t);
    for (int i = 0; i < size; ++i)
    {
        result.push_back(value % 0x100);
        value /= 0x100;
    }
    return result;
}

CBL::V_Byte CBL::conA2B(Byte *array, Datasize size)
{
    V_Byte buffer;
    for (Datasize i = 0; i < size; ++i)
        buffer.push_back(array[i]);
    return buffer;
}

//IO functions

CBL::Datasize CBL::read_file(V_Byte &buffer, const std::string filepath, const Datasize max_read_size, const Datasize offset)
{
    Datasize count_readed = 0;
    try
    {
        std::ifstream file;
        file.open(filepath, std::ifstream::binary);
        if (!file)
            throw CBL::FileNotFoundException();

        if (offset >= 0)
            file.seekg(offset);
        else
            file.seekg(offset, file.end);

        CBL::Byte t;
        while (file.read((char *)&t, 1))
        {
            count_readed++;
            buffer.push_back(t);
            if (max_read_size != 0 && count_readed == max_read_size)
                break;
        }
        file.close();
    }
    catch (CBL::FileNotFoundException &e)
    {
        e.error();
        count_readed = -1;
    }
    return count_readed;
}

CBL::V_Byte CBL::read_file(const std::string filepath, const Datasize max_read_size, const Datasize offset)
{
    V_Byte file_buffer;
    read_file(file_buffer, filepath, max_read_size, offset);
    return file_buffer;
}

void CBL::writefile(const V_Byte &buffer, const std::string filepath)
{
    try
    {
        std::ofstream file(filepath);
        if (!file)
            throw CantCreateFileToWrite();
        file.clear();
        for (Byte b : buffer)
            file << b;
        file.close();
    }
    catch (CantCreateFileToWrite &e)
    {
        e.debug();
    }
}

bool CBL::folder_exists(std::string foldername)
{
    struct stat st;
    stat(foldername.c_str(), &st);
    return st.st_mode & S_IFDIR;
}

int CBL::_mkdir(const std::string &path)
{
#ifdef _WIN32
    return ::_mkdir(path.c_str());
#else
#if _POSIX_C_SOURCE
    return ::mkdir(path.c_str(), 0777);
#else
    return ::mkdir(path.c_str(), 0777); // not sure if this works on mac
#endif
#endif
}

int CBL::createDirectory(const std::string &path)
{
    std::string current_level = "";
    std::string level;
    std::stringstream ss(path);

    while (std::getline(ss, level, '/'))
    {
        current_level += level;

        if (!folder_exists(current_level) && _mkdir(current_level.c_str()) != 0)
            return -1;

        current_level += "/";
    }

    return 0;
}

void CBL::removeDirectory(const std::string &path)
{
    system(("rm -rf " + path).c_str());
}

void CBL::printHex(const Datasize value)
{
    printf("%02X", value);
}

void CBL::printHexPrefix(const Datasize value)
{
    printf("0x%02X", value);
}

void CBL::printHex(const V_Byte &buffer, Datasize size, Datasize offset)
{
    try
    {
        if (offset > buffer.size())
            throw OffsetIsOutOfBufferRange();
    }
    catch (OffsetIsOutOfBufferRange &e)
    {
        offset = 0;
        e.error();
    }
    if (size == 0)
    {
        size = buffer.size();
    }
    else if (size + offset > buffer.size())
    {
        size = buffer.size() - offset;
    }
    for (Datasize i = 0; i < size; ++i)
    {
        printf("%02X", buffer[offset + i]);
        if (i != (size - 1))
            std::cout << ' ';
    }
}

void CBL::printHexPrefix(const V_Byte &buffer, Datasize size, Datasize offset)
{
    try
    {
        if (offset > buffer.size())
            throw OffsetIsOutOfBufferRange();
    }
    catch (OffsetIsOutOfBufferRange &e)
    {
        offset = 0;
        e.error();
    }
    if (size == 0)
    {
        size = buffer.size();
    }
    else if (size + offset > buffer.size())
    {
        size = buffer.size() - offset;
    }
    for (Datasize i = 0; i < size; ++i)
    {
        printf("0x%02X", buffer[offset + i]);
        if (i != (size - 1))
            std::cout << ' ';
    }
}

std::string CBL::sprintHex(const Datasize value)
{
    try
    {
        if (sizeof(value) > 8)
            throw UnallowableSizeOfArgument();
        char t[17];
        sprintf(t, "%02X", value);
        return std::string(t);
    }
    catch (UnallowableSizeOfArgument &e)
    {
        e.debug();
        return std::string("");
    }
}
std::string CBL::sprintHexPrefix(const Datasize value)
{
    try
    {
        if (sizeof(value) > 8)
            throw UnallowableSizeOfArgument();
        char t[19];
        sprintf(t, "0x%02X", value);
        return std::string(t);
    }
    catch (UnallowableSizeOfArgument &e)
    {
        e.debug();
        return std::string("");
    }
}
std::string CBL::sprintHex(const V_Byte &buffer, Datasize size, Datasize offset)
{
    std::string result = "";
    try
    {
        if (offset > buffer.size())
            throw OffsetIsOutOfBufferRange();
    }
    catch (OffsetIsOutOfBufferRange &e)
    {
        offset = 0;
        e.error();
    }
    if (size == 0)
    {
        size = buffer.size();
    }
    else if (size + offset > buffer.size())
    {
        size = buffer.size() - offset;
    }
    for (Datasize i = 0; i < size; ++i)
    {
        result += sprintHex(buffer[offset + i]);
        if (i != (size - 1))
            result += ' ';
    }
    return result;
}
std::string CBL::sprintHexPrefix(const V_Byte &buffer, Datasize size, Datasize offset)
{
    std::string result = "";
    try
    {
        if (offset > buffer.size())
            throw OffsetIsOutOfBufferRange();
    }
    catch (OffsetIsOutOfBufferRange &e)
    {
        offset = 0;
        e.error();
    }
    if (size == 0)
    {
        size = buffer.size();
    }
    else if (size + offset > buffer.size())
    {
        size = buffer.size() - offset;
    }
    for (Datasize i = 0; i < size; ++i)
    {
        result += sprintHexPrefix(buffer[offset + i]);
        if (i != (size - 1))
            result += ' ';
    }
    return result;
}
