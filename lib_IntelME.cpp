#include <iostream>
#include <fstream>
#include <assert.h>
#include <algorithm>
#include "exceptions.h"
#include "lib_binary.h"
#include "lib_IntelME.h"
#include "lib_crypto.h"

CBL::V_Address CBL::find_all_MFS_pages_by_signature(const CBL::V_Byte &buffer, const CBL::V_Byte &signature, const CBL::Address start_index)
{
    CBL::V_Address offsets;
    try
    {
        if (start_index >= buffer.size())
            throw OffsetIsOutOfBufferRange();
        for (CBL::Address cur_offset = start_index; cur_offset != (unsigned)-1; ++cur_offset)
        {
            cur_offset = find_by_signature(buffer, signature, cur_offset);
            if (cur_offset == (unsigned)-1)
                break;
            else if (offsets.size() != 0 && (cur_offset - offsets[offsets.size() - 1] != CBL::MFS_pageSize))
                throw UnexpectedAddressOfMFSPage();
            offsets.push_back(cur_offset);
        }
        return offsets;
    }
    catch (UnexpectedAddressOfMFSPage &e)
    {
        e.critical_error();
    }
    catch (OffsetIsOutOfBufferRange &e)
    {
        e.critical_error();
    }
    catch (...)
    {
        std::cerr << "[ERROR] Unknown exception!" << std::endl;
        exit(-1);
    }
}

CBL::Address CBL::find_ME_region(const V_Byte &buffer, const V_Byte &signature, const Address start_index)
{
    Address me_addr;
    try
    {
        if (start_index >= buffer.size())
            throw OffsetIsOutOfBufferRange();
        me_addr = find_by_signature(buffer, signature, start_index);
        me_addr = (me_addr < 0x10) ? -1 : me_addr - 0x10;
        return me_addr;
    }
    catch (OffsetIsOutOfBufferRange &e)
    {
        e.error();
    }
    catch (...)
    {
        std::cerr << "[ERROR] Unknown exception!" << std::endl;
        exit(-1);
    }
}

CBL::MeDescriptor CBL::read_MeDescriptor(const V_Byte &buffer, const Address start_index)
{
    MeDescriptor descriptor;
    read_MeDescriptor(descriptor, buffer, start_index);
    return descriptor;
}

void CBL::read_MeDescriptor(MeDescriptor &descriptor, const V_Byte &buffer, const Address start_index)
{
    try
    {
        if (start_index >= buffer.size())
            throw OffsetIsOutOfBufferRange();
        Address me_addr = find_ME_region(buffer);
        if (me_addr == -1)
            throw MERegionNotFound();
        Address cur_addr = me_addr;

        V_Byte sign = {'F', 'T', 'P', 'R'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.FTPR.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.FTPR.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.FTPR.name = "FTPR";
        }

        sign = {'F', 'T', 'U', 'P'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.FTUP.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.FTUP.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.FTUP.name = "FTUP";
        }

        sign = {'D', 'L', 'M', 'P'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.DLMP.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.DLMP.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.DLMP.name = "DLMP";
        }

        sign = {'P', 'S', 'V', 'N'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.PSVN.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.PSVN.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.PSVN.name = "PSVN";
        }

        sign = {'I', 'V', 'B', 'P'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.IVBP.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.IVBP.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.IVBP.name = "IVBP";
        }

        sign = {'M', 'F', 'S'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.MFS.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.MFS.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.MFS.name = "MFS";
        }

        sign = {'N', 'F', 'T', 'P'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.NFTP.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.NFTP.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.NFTP.name = "NFTP";
        }

        sign = {'R', 'O', 'M', 'B'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.ROMB.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.ROMB.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.ROMB.name = "ROMB";
        }

        sign = {'W', 'C', 'O', 'D'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.WCOD.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.WCOD.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.WCOD.name = "WCOD";
        }

        sign = {'L', 'O', 'C', 'L'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.LOCL.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.LOCL.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.LOCL.name = "LOCL";
        }

        sign = {'F', 'L', 'O', 'G'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.FLOG.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.FLOG.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.FLOG.name = "FLOG";
        }

        sign = {'U', 'T', 'O', 'K'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.UTOK.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.UTOK.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.UTOK.name = "UTOK";
        }

        sign = {'I', 'S', 'H', 'C'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.ISHC.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.ISHC.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.ISHC.name = "ISHC";
        }

        // Addition for ME12
        sign = {'U', 'E', 'P'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.UEP.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.UEP.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.UEP.name = "UEP";
        }
        
        sign = {'H', 'V', 'M', 'P'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.HVMP.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.HVMP.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.HVMP.name = "HVMP";
        }

        sign = {'R', 'B', 'E', 'P'};
        cur_addr = find_by_signature(buffer, sign, me_addr);
        if (cur_addr <= ME_descriptorMaxSize)
        {
            descriptor.RBEP.offset = buf2u32r(buffer, cur_addr + 8);
            descriptor.RBEP.size = buf2u32r(buffer, cur_addr + 0xC);
            descriptor.RBEP.name = "RBEP";
        }
    }
    catch (OffsetIsOutOfBufferRange &e)
    {
        e.error();
    }
    catch (MERegionNotFound &e)
    {
        e.error();
    }
    catch (...)
    {
        std::cerr << "[ERROR] Unknown exception!" << std::endl;
        exit(-1);
    }
}

void CBL::extract_ME_partition(MeDescriptorPartition &partition, const V_Byte &buffer, std::string directory)
{
    createDirectory(directory);
    if (partition.size != 0)
        writefile(get_buffer(buffer, partition.offset, partition.size), (directory + partition.name).c_str());
}

bool CBL::mfs_page_cmp(const MfsPage &p1, const MfsPage &p2)
{
    if (p1.header.firstChunk < p2.header.firstChunk)
        return true;
    else
        return false;
}
bool CBL::mfs_sys_page_cmp(const MfsSysPage &p1, const MfsSysPage &p2)
{
    if (p1.header.USN < p2.header.USN)
        return true;
    else
        return false;
}

CBL::MfsPageHeader CBL::read_MfsPageHeader(const CBL::V_Byte &buffer, const CBL::Address addr)
{
    try
    {
        if (addr >= buffer.size())
            throw OffsetIsOutOfBufferRange();
        else if (addr + MFS_pageHeaderSize >= buffer.size())
            throw OffsetIsOutOfBufferRange();
        MfsPageHeader header;
        read_MfsPageHeader(header, buffer, addr);
        return header;
    }
    catch (OffsetIsOutOfBufferRange &e)
    {
        e.critical_error();
    }
}

void CBL::read_MfsPageHeader(MfsPageHeader &mfsPageHeader, const V_Byte &buffer, const Address addr)
{
    try
    {
        if (addr >= buffer.size())
            throw OffsetIsOutOfBufferRange();
        else if (addr + MFS_pageHeaderSize >= buffer.size())
            throw OffsetIsOutOfBufferRange();
        Address r_addr = addr;
        mfsPageHeader.signature = buf2u32r(buffer, r_addr);
        r_addr += sizeof(mfsPageHeader.signature);
        mfsPageHeader.USN = buf2u32r(buffer, r_addr);
        r_addr += sizeof(mfsPageHeader.USN);
        mfsPageHeader.nErase = buf2u32r(buffer, r_addr);
        r_addr += sizeof(mfsPageHeader.nErase);
        mfsPageHeader.nextErase = buf2u16r(buffer, r_addr);
        r_addr += sizeof(mfsPageHeader.nextErase);
        mfsPageHeader.firstChunk = buf2u16r(buffer, r_addr);
        r_addr += sizeof(mfsPageHeader.firstChunk);
        mfsPageHeader.checksum = buf2u8(buffer, r_addr);
        r_addr += sizeof(mfsPageHeader.checksum);
        mfsPageHeader.zeroByte = buf2u8(buffer, r_addr);
    }
    catch (OffsetIsOutOfBufferRange &e)
    {
        e.critical_error();
    }
}

CBL::V_MfsPageHeader CBL::read_all_MfsPageHeaders(const CBL::V_Byte &buffer, const CBL::Address addr)
{
    try
    {
        if (addr >= buffer.size())
            throw OffsetIsOutOfBufferRange();
        V_MfsPageHeader headers;
        V_Address page_addresses = find_all_MFS_pages_by_signature(buffer);
        for (Address addr : page_addresses)
            headers.push_back(read_MfsPageHeader(buffer, addr));
        return headers;
    }
    catch (OffsetIsOutOfBufferRange &e)
    {
        e.critical_error();
    }
}

CBL::MfsPage CBL::read_MFS_page(const V_Byte &buffer, Address addr)
{
    MfsPage page;
    read_MFS_page(page, buffer, addr);
    return page;
}

void CBL::read_MFS_page(MfsPage &page, const V_Byte &buffer, Address addr)
{
    try
    {
        if (addr == 0)
        {
            addr = find_by_signature(buffer, MFS_signaturePage);
        }
        if (addr >= buffer.size())
            throw OffsetIsOutOfBufferRange();
        else if (addr + MFS_pageSize >= buffer.size())
            throw OffsetIsOutOfBufferRange();
        page.addr = addr;
        read_MfsPageHeader(page.header, buffer, addr);
        if (page.header.firstChunk == 0x00)
            throw NullChunkNumberInNonSysPage();

        Address r_addr = addr + MFS_pageHeaderSize;

        for (uint16_t i = 0; i < MFS_chunksOnPage; ++i, ++r_addr)
            page.chunksMap[i] = buffer[r_addr];
        for (uint16_t i = 0; i < MFS_chunksOnPage; ++i, r_addr += MFS_chunkSizeWithCRC16)
        {
            for (uint16_t j = 0; j < MFS_chunkSize; ++j)
                page.chunks[i].data[j] = buffer[r_addr + j];
            page.chunks[i].crc16 = buf2u16(get_reverse_buffer(buffer, r_addr + MFS_chunkSize, 2));
            page.chunks[i].number = page.header.firstChunk + i;
            if (page.chunksMap[i] != 0xFF)
                page.chunks[i].correct_crc = check_chunk_data_crc(page.chunks[i]);
            else
            {
                page.chunks[i].correct_crc = true;
                page.chunks[i].crc16_calc = 0xFFFF;
            }
        }
    }
    catch (OffsetIsOutOfBufferRange &e)
    {
        e.critical_error();
    }
    catch (NullChunkNumberInNonSysPage &e)
    {
        e.error();
    }
}

void CBL::read_MFS_sys_page(MfsSysPage &page, const V_Byte &buffer, Address addr)
{
    try
    {
        if (addr == 0)
        {
            addr = find_by_signature(buffer, MFS_signaturePage);
        }
        if (addr >= buffer.size())
            throw OffsetIsOutOfBufferRange();
        else if (addr + MFS_pageSize >= buffer.size())
            throw OffsetIsOutOfBufferRange();
        page.addr = addr;
        read_MfsPageHeader(page.header, buffer, addr);
        if (page.header.firstChunk != 0x00)
            throw NotNullChunkNumberInSysPage();

        Address r_addr = addr + MFS_pageHeaderSize;

        for (uint16_t i = 0; i < MFS_chunksOnSysPage + 1; ++i, r_addr += 2)
        {
            page.chunksMap[i] = buf2u16r(buffer, r_addr);
        }

        for (uint16_t i = 0; i < MFS_chunksOnSysPage; ++i, r_addr += MFS_chunkSizeWithCRC16)
        {
            for (uint16_t j = 0; j < MFS_chunkSize; ++j)
                page.chunks[i].data[j] = buffer[r_addr + j];
            page.chunks[i].crc16 = buf2u16r(buffer, r_addr + MFS_chunkSize);

            if (page.chunks[i].number != 0xFFFF)
                page.chunks[i].correct_crc = check_chunk_data_crc(page.chunks[i]);
            else
            {
                page.chunks[i].correct_crc = true;
                page.chunks[i].crc16_calc = 0xFFFF;
            }
        }

        bruteforce_sys_chunk_numbers(page);

        for (uint16_t i = 0; i < MFS_chunksOnSysPage; ++i, r_addr += MFS_chunkSizeWithCRC16)
        {
            if (page.chunks[i].number != 0xFFFF)
                page.chunks[i].correct_crc = check_chunk_data_crc(page.chunks[i]);
            else
            {
                page.chunks[i].correct_crc = true;
                page.chunks[i].crc16_calc = 0xFFFF;
            }
        }
    }
    catch (OffsetIsOutOfBufferRange &e)
    {
        e.critical_error();
    }
    catch (NotNullChunkNumberInSysPage &e)
    {
        e.error();
    }
}
CBL::MfsSysPage CBL::read_MFS_sys_page(const V_Byte &buffer, Address addr)
{
    MfsSysPage page;
    read_MFS_sys_page(page, buffer, addr);
    return page;
}

void CBL::read_MFS_pages(MfsPages &mfsPages, const V_Byte &buffer, Address addr)
{
    mfsPages.dataPages.clear();
    mfsPages.sysPages.clear();
    MfsSysPage t_sys_page;
    MfsPage t_page;
    V_Address pages_addrs = find_all_MFS_pages_by_signature(buffer, MFS_signaturePage, addr);
    for (int i = 0; i < pages_addrs.size(); ++i)
    {
        if (buf2u16r(buffer, pages_addrs[i] + 0xE) == 0x00)
        {
            t_sys_page = read_MFS_sys_page(buffer, pages_addrs[i]);
            t_sys_page.number_in_mfs = i + 1;
            mfsPages.sysPages.push_back(t_sys_page);
        }
        else
        {
            t_page = read_MFS_page(buffer, pages_addrs[i]);
            t_page.number_in_mfs = i + 1;
            mfsPages.dataPages.push_back(t_page);
        }
    }
    std::sort(mfsPages.sysPages.begin(), mfsPages.sysPages.end(), mfs_sys_page_cmp);
    std::sort(mfsPages.dataPages.begin(), mfsPages.dataPages.end(), mfs_page_cmp);
}
CBL::MfsPages CBL::read_MFS_pages(const V_Byte &buffer, Address addr)
{
    MfsPages mfsPages;
    read_MFS_pages(mfsPages, buffer, addr);
    return mfsPages;
}

bool CBL::check_chunk_data_crc(MfsChunk &chunk)
{
    uint16_t crc16_calculated;
    V_Byte data_and_number;
    data_and_number = conA2B(chunk.data, MFS_chunkSize);
    add_to_buffer(data_and_number, u16bufr(chunk.number));
    crc16_calculated = crc16_ccitt(data_and_number);
    chunk.crc16_calc = crc16_calculated;
    return chunk.crc16 == crc16_calculated ? true : false;
}
void CBL::bruteforce_sys_chunk_numbers(MfsSysPage &page)
{
    for (int i = 0; i < MFS_chunksOnSysPage; ++i)
        page.chunksMapDeobfuscated[i] = 0xFFFF; //initialization
    for (int i = 0; i < MFS_chunksOnSysPage; ++i)
    {
        if (page.chunksMap[i] == 0x7FFF || page.chunksMap[i] == 0xFFFF)
        {
            break;
        }
        V_Byte base_data = conA2B(page.chunks[i].data, MFS_chunkSize);
        V_Byte temp;
        uint16_t chunk_crc16 = page.chunks[i].crc16;
        for (uint16_t j = 0; j <= 0xFFFF; ++j)
        {
            temp = base_data;
            add_to_buffer(temp, u16bufr(j));
            if (crc16_ccitt(temp) == chunk_crc16)
            {
                page.chunksMapDeobfuscated[i] = j;
                page.chunks[i].number = j;
                break;
            }
        }
    }
}

void CBL::build_sys_volume(MfsSysVolume &volume, V_MfsSysPage &pages, int sys_chunks_count)
{
    //building system data buffer from chunks
    V_Byte sys_data_buf;
    for (int i = 0; i < sys_chunks_count; ++i)
        for (int j = 0; j < MFS_chunkSize; ++j)
            sys_data_buf.push_back(0x00);
    for (int i = 0; i < pages.size(); ++i)
    {
        for (int j = 0; j < MFS_chunksOnSysPage; ++j)
        {
            if (pages[i].chunksMap[j] == MFS_signatureSysChunkMapEnd || pages[i].chunksMap[j] == 0xFFFF)
                break;
            uint16_t chunk_number = pages[i].chunksMapDeobfuscated[j];
            for (int k = 0; k < MFS_chunkSize; ++k)
                sys_data_buf[chunk_number * MFS_chunkSize + k] = pages[i].chunks[j].data[k];
        }
    }
    //building volume from buffer
    Address r_addr = 0;
    volume.header.sign = buf2u32r(sys_data_buf, r_addr);
    r_addr += 4;
    volume.header.version = buf2u32r(sys_data_buf, r_addr);
    r_addr += 4;
    volume.header.totalCapacity = buf2u32r(sys_data_buf, r_addr);
    r_addr += 4;
    volume.header.nFiles = buf2u16r(sys_data_buf, r_addr);
    r_addr += 2;
    for (; r_addr < sys_data_buf.size(); r_addr += 2)
    {
        volume.FAT.push_back(buf2u16r(sys_data_buf, r_addr));
    }
}

CBL::MfsSysVolume CBL::build_sys_volume(V_MfsSysPage &pages, int sys_chunks_count)
{
    MfsSysVolume volume;
    build_sys_volume(volume, pages, sys_chunks_count);
    return volume;
}

void CBL::build_data_volume(MfsDataVolume &volume, V_MfsPage &pages)
{
    for (MfsPage page : pages)
    {
        for (int i = 0; i < MFS_chunksOnPage; ++i)
        {
            bool exists = page.chunksMap[i] != 0xFFFF;
            for (int j = 0; j < MFS_chunkSize; ++j)
                volume.data.push_back(exists ? page.chunks[i].data[j] : 0x00);
        }
    }
}

CBL::MfsDataVolume CBL::build_data_volume(V_MfsPage &pages)
{
    MfsDataVolume volume;
    build_data_volume(volume, pages);
    return volume;
}

void CBL::build_mfs(Mfs &mfs, MfsPages &pages)
{
    mfs.sysPages = pages.sysPages;
    mfs.dataPages = pages.dataPages;
    build_sys_volume(mfs.sysVolume, pages.sysPages, pages.dataPages[0].header.firstChunk);
    build_data_volume(mfs.dataVolume, pages.dataPages);
}

CBL::Mfs CBL::build_mfs(MfsPages &pages)
{
    Mfs mfs;
    build_mfs(mfs, pages);
    return mfs;
}

void CBL::read_MFS(Mfs &mfs, const V_Byte &firmware_buffer, Address addr)
{

    mfs.sysPages.clear();
    mfs.dataPages.clear();
    mfs.sysVolume.header.sign = 0;
    mfs.sysVolume.header.version = 0;
    mfs.sysVolume.header.totalCapacity = 0;
    mfs.sysVolume.header.nFiles = 0;
    mfs.sysVolume.FAT.clear();
    mfs.dataVolume.data.clear();

    MfsPages pages = read_MFS_pages(firmware_buffer, addr);
    mfs = build_mfs(pages);
}

CBL::Mfs CBL::read_MFS(const V_Byte &firmware_buffer, Address addr)
{
    Mfs mfs;
    read_MFS(mfs, firmware_buffer, addr);
    return mfs;
}

void CBL::extract_raw_files_from_MFS(const Mfs &mfs, const std::string directory)
{
    createDirectory(directory);
    for (uint32_t i = 0; i < mfs.sysVolume.header.nFiles; ++i)
    {
        uint16_t ind = mfs.sysVolume.FAT[i];
        if (ind == 0x0000 || ind == 0xFFFE)
        {
            // FILE NOT EXIST
        }
        else if (ind == 0xFFFF)
        {
            //FILE EXIST BUT EMPTY
            writefile({}, (directory + sprintHex(i)).c_str());
        }
        else
        {
            V_Byte data;
            Address offset;
            for (;;)
            {
                uint16_t next_ind = mfs.sysVolume.FAT[ind];
                if (next_ind <= MFS_chunkSize)
                {
                    offset = (ind - mfs.sysVolume.header.nFiles) * 64;
                    add_to_buffer(data, get_buffer(mfs.dataVolume.data, offset, next_ind));
                    break;
                }
                else
                {
                    offset = (ind - mfs.sysVolume.header.nFiles) * 64;
                    add_to_buffer(data, get_buffer(mfs.dataVolume.data, offset, MFS_chunkSize));
                    ind = next_ind;
                }
            }
            writefile(data, (directory + sprintHex(i)).c_str());
        }
    }
}

CBL::V_Byte CBL::get_cfg_file(const Mfs &mfs, const int number){
    uint16_t ind = mfs.sysVolume.FAT[number];
    if (ind == 0x0000 || ind == 0xFFFE || ind == 0xFFFF) // file empty or not exist
    {
        return V_Byte();
    } else {
        V_Byte data;
        Address offset;
        for (;;)
        {
            uint16_t next_ind = mfs.sysVolume.FAT[ind];
            if (next_ind <= MFS_chunkSize)
            {
                offset = (ind - mfs.sysVolume.header.nFiles) * 64;
                add_to_buffer(data, get_buffer(mfs.dataVolume.data, offset, next_ind));
                break;
            }
            else
            {
                offset = (ind - mfs.sysVolume.header.nFiles) * 64;
                add_to_buffer(data, get_buffer(mfs.dataVolume.data, offset, MFS_chunkSize));
                ind = next_ind;
            }
        }
        return data;
    }
}

void CBL::extract_cfg(const MfsCfg &cfg, const std::string directory)
{
    std::vector<std::string> output_bases;
    for (MfsCfgRecord record : cfg.records)
    {
        if (record.mode & 0x1000) // если каталог, выходим на уровень выше или создаем его
        {
            if (std::strcmp(record.name, "..") == 0)
            {
                if (output_bases.size() != 0)
                    output_bases.pop_back();
            }
            else
            {
                std::string cur_path;
                for (std::string str : output_bases)
                    cur_path += str;
                createDirectory(directory + cur_path + record.name);
                output_bases.push_back((record.name + std::string("/")));
            }
        }
        else // если файл, то записываем его на диск
        {
            std::string cur_path;
            for (std::string str : output_bases)
                cur_path += str;
            writefile(get_buffer(cfg.data, record.offset, record.dataLength), directory + cur_path + record.name);
        }
    }
}

void CBL::extract_cfg(const V_Byte &buffer, const std::string directory)
{
    MfsCfg cfg = read_cfg_file(buffer);
    extract_cfg(cfg, directory);
}

void CBL::extract_cfg(const std::string filepath, const std::string directory)
{
    V_Byte buffer = read_file(filepath);
    extract_cfg(buffer, directory);
}

bool CBL::find_file_in_cfg(const MfsCfg &cfg, const std::string filename)
{
    for (MfsCfgRecord record : cfg.records)
    {
        if (std::strcmp(record.name, filename.c_str()) == 0){
            return true;
        }
    }
    return false;
}

bool CBL::find_file_in_cfg(const V_Byte &buffer, const std::string filename){
    MfsCfg cfg = read_cfg_file(buffer);
    return find_file_in_cfg(cfg, filename);
}

bool CBL::find_file_in_cfg(const std::string filepath, const std::string filename){
    V_Byte buffer = read_file(filepath);
    return find_file_in_cfg(buffer, filename);
}

CBL::V_Byte CBL::get_file_from_cfg(const MfsCfg &cfg, const std::string filename){
    for (MfsCfgRecord record : cfg.records)
    {
        if (std::strcmp(record.name, filename.c_str()) == 0){
            return get_buffer(cfg.data, record.offset, record.dataLength);
        }
    }
    return V_Byte();
}

CBL::V_Byte CBL::get_file_from_cfg(const V_Byte &buffer, const std::string filename){
    MfsCfg cfg = read_cfg_file(buffer);
    return get_file_from_cfg(cfg, filename);
}

CBL::V_Byte CBL::get_file_from_cfg(const std::string filepath, const std::string filename){
    V_Byte buffer = read_file(filepath);
    return get_file_from_cfg(buffer, filename);
}

void CBL::get_cfg_record(MfsCfgRecord &record, const V_Byte &buffer, Address addr)
{
    for (int i = 0; i < 12; ++i)
    {
        record.name[i] = buffer[addr + i];
        if (record.name[i] == 0)
            break;
    }
    addr += 12;
    record.unused = buf2u16r(buffer, addr);
    addr += 2;
    record.mode = buf2u16r(buffer, addr);
    addr += 2;
    record.options = buf2u16r(buffer, addr);
    addr += 2;
    record.dataLength = buf2u16r(buffer, addr);
    addr += 2;
    record.uid = buf2u16r(buffer, addr);
    addr += 2;
    record.gid = buf2u16r(buffer, addr);
    addr += 2;
    record.offset = buf2u16r(buffer, addr);
}

CBL::MfsCfgRecord CBL::get_cfg_record(const V_Byte &buffer, Address addr)
{
    MfsCfgRecord record;
    get_cfg_record(record, buffer, addr);
    return record;
}

void CBL::read_cfg_file(MfsCfg &cfg, const V_Byte &buffer, Address addr)
{
    cfg.nRec = buf2u32r(buffer, addr);
    addr += 4;
    cfg.records.clear();
    for (uint32_t i = 0; i < cfg.nRec; ++i)
    {
        cfg.records.push_back(get_cfg_record(buffer, addr));
        addr += MFS_cfgRecordSize;
    }
    cfg.data = get_buffer(buffer, addr);
}

CBL::MfsCfg CBL::read_cfg_file(const V_Byte &buffer, Address addr)
{
    MfsCfg cfg;
    read_cfg_file(cfg, buffer, addr);
    return cfg;
}

bool CBL::check_manufacture_mode(const Mfs &mfs, const std::string tempfile){
    bool stateIntelCfg = false, stateFitcCfg = false;

    writefile(get_cfg_file(mfs, 6), tempfile); // why work only if use this
    MfsCfg tempCfg = read_cfg_file(read_file(tempfile));
    V_Byte eomFile = get_file_from_cfg(tempCfg, "manuf");

    std::cout<<"{DEBUG} intelCfg: "<<sprintHex(eomFile)<<std::endl;
    if (eomFile.size() != 1){
        stateIntelCfg = false;
    } else {
        stateIntelCfg =  (eomFile[0] == 1 ? true : false);
    }
    std::cout<<"{DEBUG} intel: "<<stateIntelCfg<<std::endl;

    writefile(get_cfg_file(mfs, 7), tempfile); // why work only if use this
    tempCfg = read_cfg_file(read_file(tempfile));
    eomFile = get_file_from_cfg(tempCfg, "eom");
    
    if (eomFile.size() != 1){
        stateFitcCfg = false;
    } else {
        stateFitcCfg =  (eomFile[0] == 1 ? true : false);
    }
    std::cout<<"{DEBUG} fitc: "<<stateFitcCfg<<std::endl;

    return stateIntelCfg || stateFitcCfg;
}

//Edit MFS

void CBL::convert_file_to_chunks(V_MfsChunk &chunks, V_Byte &buffer)
{
    chunks.clear();

    if (buffer.size() == 0) return;

    Datasize fileSize = buffer.size();
    int i;

    for(i = 0; i < fileSize/MFS_chunkSize; ++i) //обрабатываем все чанки кроме последнего
    {
        MfsChunk chunk;
        for (Address j = 0; j < MFS_chunkSize; ++j)
        {
            chunk.data[j] = buffer[i*MFS_chunkSize + j];
        }
        chunks.push_back(chunk);
    }
    
    if (fileSize == i*MFS_chunkSize) return; // если файл имеет кратный размеру чанка размер, то нечего дальше обрабатывать
    MfsChunk chunk; // иначе разбираем последний чанк, с дополнением его (0хFF) до нужного размера
    for(Address j = 0; j < MFS_chunkSize; ++j)
    {
        (i*MFS_chunkSize + j < fileSize) ? chunk.data[j] = buffer[i*MFS_chunkSize + j] : chunk.data[j] = 0xFF;
    }
    chunks.push_back(chunk);
}

void CBL::convert_file_to_chunks(V_MfsChunk &chunks, const std::string file)
{
    V_Byte buffer = read_file(file);
    convert_file_to_chunks(chunks, buffer);
}

CBL::V_MfsChunk CBL::convert_file_to_chunks(V_Byte &buffer)
{
    V_MfsChunk chunks;
    convert_file_to_chunks(chunks, buffer);
    return chunks;
}

CBL::V_MfsChunk CBL::convert_file_to_chunks(const std::string file)
{
    V_Byte buffer = read_file(file);
    return convert_file_to_chunks(buffer);
}

int CBL::find_sysVolume_free_file(MfsSysVolume &sysVolume)
{   
    for (int i = 9; i < sysVolume.header.nFiles; ++i)
    {
        if (sysVolume.FAT[i] == 0x0000) return i;
    }
    return -1;
}

int CBL::find_sysVolume_FAT_write_position(MfsSysVolume &sysVolume)
{
    int i;
    for(i = sysVolume.FAT.size() - 1; i >= sysVolume.header.nFiles; --i)
    {
        if (sysVolume.FAT[i] != 0x0000) break;
    }
    return i+1;
}

int CBL::find_last_used_chunk(MfsDataVolume &dataVolume)
{
    for(int i = 0; i < dataVolume.data.size(); i += MFS_chunkSize)
    {
        if (dataVolume.data[i] != 0xFF) continue;
        else
        {
            int j;
            for (int j = 0; j < MFS_chunkSize; ++j)
                if (dataVolume.data[i+j] != 0xFF) break; 
            if (j == MFS_chunkSize) return i;
        }
    }
    return -1;
}

void CBL::create_FAT_record(Mfs &mfs, V_MfsChunk &chunks)
{
    int file_ind = find_sysVolume_free_file(mfs.sysVolume);
    if ( !chunks.size() ) //если массив чанков пуст, т.е. файл пустой, то просто создаем запись в FAT
    {
        mfs.sysVolume.FAT[file_ind] = 0xFFFF;
    }
    else 
    {
        int FAT_write_position = find_sysVolume_FAT_write_position(mfs.sysVolume);
        // mfs.sysVolume.FAT[file_ind] = 
    }
}

//IO

void CBL::print_ME_decriptor(MeDescriptor &descriptor)
{
    std::cout << "[DESCRIPTOR]: [Datasize : SIZE]" << std::endl;
    (descriptor.FTPR.offset) ? std::cout << "[FTPR]: " << sprintHexPrefix(descriptor.FTPR.offset) << " : " << sprintHexPrefix(descriptor.FTPR.size) << std::endl : std::cout << "[FTPR]: ----- EMPTY -----" << std::endl;
    (descriptor.FTUP.offset) ? std::cout << "[FTUP]: " << sprintHexPrefix(descriptor.FTUP.offset) << " : " << sprintHexPrefix(descriptor.FTUP.size) << std::endl : std::cout << "[FTUP]: ----- EMPTY -----" << std::endl;
    (descriptor.DLMP.offset) ? std::cout << "[DLMP]: " << sprintHexPrefix(descriptor.DLMP.offset) << " : " << sprintHexPrefix(descriptor.DLMP.size) << std::endl : std::cout << "[DLMP]: ----- EMPTY -----" << std::endl;
    (descriptor.PSVN.offset) ? std::cout << "[PSVN]: " << sprintHexPrefix(descriptor.PSVN.offset) << " : " << sprintHexPrefix(descriptor.PSVN.size) << std::endl : std::cout << "[PSVN]: ----- EMPTY -----" << std::endl;
    (descriptor.IVBP.offset) ? std::cout << "[IVBP]: " << sprintHexPrefix(descriptor.IVBP.offset) << " : " << sprintHexPrefix(descriptor.IVBP.size) << std::endl : std::cout << "[IVBP]: ----- EMPTY -----" << std::endl;
    (descriptor.MFS.offset) ? std::cout << " [MFS]: " << sprintHexPrefix(descriptor.MFS.offset) << " : " << sprintHexPrefix(descriptor.MFS.size) << std::endl : std::cout << " [MFS]: ----- EMPTY -----" << std::endl;
    (descriptor.NFTP.offset) ? std::cout << "[NFTP]: " << sprintHexPrefix(descriptor.NFTP.offset) << " : " << sprintHexPrefix(descriptor.NFTP.size) << std::endl : std::cout << "[NFTP]: ----- EMPTY -----" << std::endl;
    (descriptor.ROMB.offset) ? std::cout << "[ROMB]: " << sprintHexPrefix(descriptor.ROMB.offset) << " : " << sprintHexPrefix(descriptor.ROMB.size) << std::endl : std::cout << "[ROMB]: ----- EMPTY -----" << std::endl;
    (descriptor.WCOD.offset) ? std::cout << "[WCOD]: " << sprintHexPrefix(descriptor.WCOD.offset) << " : " << sprintHexPrefix(descriptor.WCOD.size) << std::endl : std::cout << "[WCOD]: ----- EMPTY -----" << std::endl;
    (descriptor.LOCL.offset) ? std::cout << "[LOCL]: " << sprintHexPrefix(descriptor.LOCL.offset) << " : " << sprintHexPrefix(descriptor.LOCL.size) << std::endl : std::cout << "[LOCL]: ----- EMPTY -----" << std::endl;
    (descriptor.FLOG.offset) ? std::cout << "[FLOG]: " << sprintHexPrefix(descriptor.FLOG.offset) << " : " << sprintHexPrefix(descriptor.FLOG.size) << std::endl : std::cout << "[FLOG]: ----- EMPTY -----" << std::endl;
    (descriptor.UTOK.offset) ? std::cout << "[UTOK]: " << sprintHexPrefix(descriptor.UTOK.offset) << " : " << sprintHexPrefix(descriptor.UTOK.size) << std::endl : std::cout << "[UTOK]: ----- EMPTY -----" << std::endl;
    (descriptor.ISHC.offset) ? std::cout << "[ISHC]: " << sprintHexPrefix(descriptor.ISHC.offset) << " : " << sprintHexPrefix(descriptor.ISHC.size) << std::endl : std::cout << "[ISHC]: ----- EMPTY -----" << std::endl;
    std::cout << std::endl;
}

//MFS IO
void CBL::print_page_base_info(MfsPage &page)
{
    if (page.number_in_mfs != 0)
        std::cout << "---------------------  Page: #" << (page.number_in_mfs) << "  ---------------------" << std::endl;
    else
        std::cout << "---------------------  Page  ---------------------" << std::endl;
    std::cout << "Page offset: " << sprintHexPrefix(page.addr) << std::endl;
    std::cout << "[HEADER]:" << std::endl;
    std::cout << "Signature: " << sprintHexPrefix(page.header.signature).c_str() << std::endl;
    std::cout << "USN: " << sprintHexPrefix(page.header.USN).c_str() << std::endl;
    std::cout << "Number of erase: " << sprintHexPrefix(page.header.nErase).c_str() << std::endl;
    std::cout << "Next erase: " << sprintHexPrefix(page.header.nextErase).c_str() << std::endl;
    std::cout << "First chunk: " << sprintHexPrefix(page.header.firstChunk).c_str() << std::endl;
    std::cout << "Checksum (header): " << sprintHexPrefix(page.header.checksum).c_str() << std::endl;
    std::cout << "Zero byte:" << sprintHexPrefix(page.header.zeroByte).c_str() << std::endl;
    unsigned int usedChunksCount = {0};
    for (Byte b : page.chunksMap)
    {
        if (b != 0xFF)
            usedChunksCount++;
        else if (b == 0xff)
            break;
    }
    std::cout << "Number of used chunks: " << usedChunksCount << std::endl;
    bool crc_correct = true;
    for (MfsChunk i : page.chunks)
        crc_correct = i.correct_crc;
    if (crc_correct)
        std::cout << "CRC16 correct for all chunks." << std::endl;
    else
        std::cout << "CRC16 INCORRECT for one (some) chunk(s)." << std::endl;
    std::cout << std::endl;
}

void CBL::print_sys_page_base_info(MfsSysPage &page)
{
    if (page.number_in_mfs != 0)
        std::cout << "---------------------  Page (SYSTEM): #" << (page.number_in_mfs);
    else
        std::cout << "---------------------  Page (SYSTEM)";
    std::cout << "  ---------------------" << std::endl;
    std::cout << "Page offset: " << sprintHexPrefix(page.addr) << std::endl;

    std::cout << "[HEADER]:" << std::endl;
    std::cout << "Signature: " << sprintHexPrefix(page.header.signature).c_str() << std::endl;
    std::cout << "USN: " << sprintHexPrefix(page.header.USN).c_str() << std::endl;
    std::cout << "Number of erase: " << sprintHexPrefix(page.header.nErase).c_str() << std::endl;
    std::cout << "Next erase: " << sprintHexPrefix(page.header.nextErase).c_str() << std::endl;
    std::cout << "Checksum (header): " << sprintHexPrefix(page.header.checksum).c_str() << std::endl;
    std::cout << "Zero byte:" << sprintHexPrefix(page.header.zeroByte).c_str() << std::endl;
    bool crc_correct = true;
    for (MfsChunk i : page.chunks)
        crc_correct = i.correct_crc;
    if (crc_correct)
        std::cout << "CRC16 correct for all chunks." << std::endl;
    else
        std::cout << "CRC16 INCORRECT for one (some) chunk(s)." << std::endl;
    std::cout << std::endl;
}

void CBL::print_page_chunks_map(MfsPage &page)
{
    std::cout << "[CHUNKS USE MAP] (0xFF --> not used chunk):" << std::endl;

    unsigned int usedChunksCount = {0};
    for (Byte b : page.chunksMap)
    {
        if (b != 0xFF)
            usedChunksCount++;
        else if (b == 0xff)
            break;
    }
    for (int i = 0; i < MFS_chunksOnPage; ++i)
    {
        if (i % 8 == 0 && i != 0)
            std::cout << std::endl;
        printHexPrefix(page.chunksMap[i]);
        std::cout << ' ';
    }
    std::cout << std::endl
              << std::endl;
}

void CBL::print_sys_page_chunks_map(MfsSysPage &page)
{
}

void CBL::print_page_chunks_data(MfsPage &page)
{
    unsigned int usedChunksCount = {0};
    for (Byte b : page.chunksMap)
    {
        if (b != 0xFF)
            usedChunksCount++;
        else if (b == 0xff)
            break;
    }
    std::cout << "[BODY]:" << std::endl;
    for (int i = 0; i < MFS_chunksOnPage; ++i)
    {
        std::cout << "Chunk " << sprintHexPrefix(page.chunks[i].number).c_str() << std::endl;
        if (i < usedChunksCount)
        {
            for (int j = 0; j < MFS_chunkSize; ++j)
            {
                if (j % 8 == 0 && j != 0)
                    std::cout << std::endl;
                printHexPrefix(page.chunks[i].data[j]);
                std::cout << ' ';
            }
            std::cout << std::endl
                      << "Chunk CRC16: " << sprintHexPrefix(page.chunks[i].crc16).c_str();
            if (page.chunks[i].correct_crc)
                std::cout << " (CORRECT)" << std::endl
                          << std::endl;
            else
                std::cout << " (INCORRECT must be --> " << sprintHexPrefix(page.chunks[i].crc16_calc).c_str() << ") " << std::endl
                          << std::endl;
        }
        else
        {
            std::cout << "--- EMPTY ---" << std::endl
                      << std::endl;
        }
    }
}

void CBL::print_sys_page_chunks_data(MfsSysPage &page)
{
}

void CBL::print_page_info(MfsPage &page)
{
    print_page_base_info(page);
    print_page_chunks_map(page);
    print_page_chunks_data(page);
    std::cout << "---------------------  End of page  ---------------------" << std::endl;
}

void CBL::print_sys_page_info(MfsSysPage &page)
{
    print_sys_page_base_info(page);
    std::cout << "---------------------  End of page  ---------------------" << std::endl;
}

void CBL::print_cfg_files(const MfsCfg &cfg, std::string cfg_filename)
{
    if (std::strcmp(cfg_filename.c_str(), "") != 0)
    {
        std::cout << "Print files from .cfg file: " << cfg_filename << std::endl;
    }
    std::vector<std::string> output_bases;
    output_bases.push_back("");
    output_bases.push_back("     ");
    int cur_base_ind = 0;
    for (MfsCfgRecord record : cfg.records)
    {
        if (record.mode & 0x1000) // если каталог
        {
            if (std::strcmp(record.name, "..") == 0)
            {
                cur_base_ind = cur_base_ind - 1 > 0 ? cur_base_ind - 1 : 0;
            }
            else
            {
                std::cout << sprint_cfg_file_permissions(record) << "     " << output_bases[cur_base_ind] << record.name << ": " << std::endl;
                cur_base_ind++;
                if (cur_base_ind == output_bases.size())
                    output_bases.push_back(output_bases[output_bases.size() - 1] + "     ");
            }
        }
        else
        {
            std::cout << sprint_cfg_file_permissions(record) << "     " << output_bases[cur_base_ind] << record.name << " ( " << record.dataLength << " B)" << std::endl;
        }
    }
    std::cout << std::endl;
}

void CBL::print_mfs_cfgs_info(const Mfs mfs)
{
    V_MfsCfg cfgs;
    std::cout << "MFS files:" << std::endl;
    for (uint32_t i = 0; i < mfs.sysVolume.header.nFiles; ++i)
    {
        uint16_t ind = mfs.sysVolume.FAT[i];
        if (ind == 0x0000 || ind == 0xFFFE)
        {
            // FILE NOT EXIST
        }
        else if (ind == 0xFFFF)
        {
            //FILE EXIST BUT EMPTY
            std::cout << "File: " << i << " (EMPTY)" << std::endl;
        }
        else
        {
            V_Byte data;
            Address offset;
            for (;;)
            {
                uint16_t next_ind = mfs.sysVolume.FAT[ind];
                if (next_ind <= MFS_chunkSize)
                {
                    offset = (ind - mfs.sysVolume.header.nFiles) * 64;
                    add_to_buffer(data, get_buffer(mfs.dataVolume.data, offset, next_ind));
                    break;
                }
                else
                {
                    offset = (ind - mfs.sysVolume.header.nFiles) * 64;
                    add_to_buffer(data, get_buffer(mfs.dataVolume.data, offset, MFS_chunkSize));
                    ind = next_ind;
                }
            }
            std::cout << "File: " << i << " (Size: " << data.size() << " B)" << std::endl;
        }
    }
}

std::string CBL::sprint_cfg_file_permissions(const MfsCfgRecord &record)
{
    std::string result;

    result.push_back((record.mode & 0x8000) ? '-' : '-'); //Unknown bit
    result.push_back((record.mode & 0x4000) ? '-' : '-'); //Unknown bit
    result.push_back((record.mode & 0x2000) ? '-' : '-'); //Unknown bit
    result.push_back((record.mode & 0x1000) ? 'D' : '-'); //Direcroty bit (1 - dir, 0 - file)
    result.push_back((record.mode & 0x800) ? 'A' : '-');  //Anti-replay using bit (1 - used, 0 - not used)
    result.push_back((record.mode & 0x400) ? 'E' : '-');  //Encryption enabled bit (1 - enable, 0 - not enable)
    result.push_back((record.mode & 0x200) ? 'I' : '-');  //Integrity enabled bit (1 - enable, 0 - not enable)
    result.push_back((record.mode & 0x100) ? 'r' : '-');  //Owner read access bit
    result.push_back((record.mode & 0x80) ? 'w' : '-');   //Owner write access bit
    result.push_back((record.mode & 0x40) ? 'x' : '-');   //Owner execute access bit
    result.push_back((record.mode & 0x20) ? 'r' : '-');   //Group read access bit
    result.push_back((record.mode & 0x10) ? 'w' : '-');   //Group write access bit
    result.push_back((record.mode & 0x8) ? 'x' : '-');    //Group execute access bit
    result.push_back((record.mode & 0x4) ? 'r' : '-');    //Other's read access bit
    result.push_back((record.mode & 0x2) ? 'w' : '-');    //Other's write access bit
    result.push_back((record.mode & 0x1) ? 'x' : '-');    //Other's execute access bit

    return result;
}

void CBL::write_MFS_FAT_to_disk(std::vector<uint16_t> &FAT, std::string filename)
{
    V_Byte sysBuffer;
    for (uint16_t v : FAT)
        add_to_buffer(sysBuffer, u16buf(v));
    writefile(sysBuffer, filename);
}
