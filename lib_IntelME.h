#ifndef LIB_INTELME_H
#define LIB_INTELME_H
#include "structs_basic.h"
#include "structs_IntelME.h"
#include <string>

namespace CBL
{
Address find_ME_region(const V_Byte &buffer, const V_Byte &signature = ME_signatureMeRegion, const Address start_index = 0);
MeDescriptor read_MeDescriptor(const V_Byte &buffer, const Address start_index = 0);
void read_MeDescriptor(MeDescriptor &descriptor, const V_Byte &buffer, const Address start_index = 0);
void extract_ME_partition(MeDescriptorPartition &partition, const V_Byte &buffer, std::string directory = "_partitions/");
bool mfs_page_cmp(const MfsPage &p1, const MfsPage &p2);
bool mfs_sys_page_cmp(const MfsSysPage &p1, const MfsSysPage &p2);

//MFS
V_Address find_all_MFS_pages_by_signature(const V_Byte &buffer, const V_Byte &signature = MFS_signaturePage, const Address start_index = 0);

void read_MfsPageHeader(MfsPageHeader &mfsPageHeader, const V_Byte &buffer, Address addr = 0);
MfsPageHeader read_MfsPageHeader(const V_Byte &buffer, const Address addr = 0);

V_MfsPageHeader read_all_MfsPageHeaders(const V_Byte &buffer, const Address addr = 0);

void read_MFS_page(MfsPage &page, const V_Byte &buffer, Address addr = 0);
MfsPage read_MFS_page(const V_Byte &buffer, Address addr = 0);

void read_MFS_sys_page(MfsSysPage &page, const V_Byte &buffer, Address addr = 0);
MfsSysPage read_MFS_sys_page(const V_Byte &buffer, Address addr = 0);

void read_MFS_pages(MfsPages &mfsPages, const V_Byte &buffer, Address addr = 0);
MfsPages read_MFS_pages(const V_Byte &buffer, Address addr = 0);

bool check_chunk_data_crc(MfsChunk &chunk);
void bruteforce_sys_chunk_numbers(MfsSysPage &page);

void build_sys_volume(MfsSysVolume &volume, V_MfsSysPage &pages, int sys_chunks_count);
MfsSysVolume build_sys_volume(V_MfsSysPage &pages, int sys_chunks_count);

void build_data_volume(MfsDataVolume &volume, V_MfsPage &pages);
MfsDataVolume build_data_volume(V_MfsPage &pages);

void build_mfs(Mfs &mfs, MfsPages &pages);
Mfs build_mfs(MfsPages &pages);

void read_MFS(Mfs &mfs, const V_Byte &firmware_buffer, Address addr = 0);
Mfs read_MFS(const V_Byte &firmware_buffer, Address addr = 0);

void extract_raw_files_from_MFS(const Mfs &mfs, const std::string directory = "_mfs/raw/");

V_Byte get_cfg_file(const Mfs &mfs, const int number);

void extract_cfg(const MfsCfg &cfg, const std::string directory = "_mfs/");
void extract_cfg(const V_Byte &buffer, const std::string directory = "_mfs/"); 
void extract_cfg(const std::string filepath, const std::string directory = "_mfs/");

bool find_file_in_cfg(const MfsCfg &cfg, const std::string filename);
bool find_file_in_cfg(const V_Byte &buffer, const std::string filename); 
bool find_file_in_cfg(const std::string filepath, const std::string filename);

V_Byte get_file_from_cfg(const MfsCfg &cfg, const std::string filename);
V_Byte get_file_from_cfg(const V_Byte &buffer, const std::string filename); 
V_Byte get_file_from_cfg(const std::string filepath, const std::string filename);

void get_cfg_record(MfsCfgRecord &record, const V_Byte &buffer, Address addr);
MfsCfgRecord get_cfg_record(const V_Byte &buffer, Address addr);
void read_cfg_file(MfsCfg &cfg, const V_Byte &buffer, Address addr = 0);
MfsCfg read_cfg_file(const V_Byte &buffer, Address addr = 0);

bool check_manufacture_mode(const Mfs &mfs, const std::string tempfile = "mnf.tmp"); // not ready, why work only if write and read file???

//Edit MFS
void convert_file_to_chunks(V_MfsChunk &chunks, V_Byte &buffer); //test on real system
void convert_file_to_chunks(V_MfsChunk &chunks, const std::string file);
V_MfsChunk convert_file_to_chunks(V_Byte &buffer); //test on real system
V_MfsChunk convert_file_to_chunks(const std::string file);
int find_sysVolume_free_file(MfsSysVolume &sysVolume);
int find_sysVolume_FAT_write_position(MfsSysVolume &sysVolume);
int find_last_used_chunk(MfsDataVolume &dataVolume); //test
void create_FAT_record(Mfs &mfs, V_MfsChunk &chunks); //not


//IO
void print_ME_decriptor(MeDescriptor &descriptor);

//MFS IO
void print_page_base_info(MfsPage &page);
void print_sys_page_base_info(MfsSysPage &page);
void print_page_chunks_map(MfsPage &page);
void print_sys_page_chunks_map(MfsSysPage &page);
void print_page_chunks_data(MfsPage &page);
void print_sys_page_chunks_data(MfsSysPage &page); 
void print_page_info(MfsPage &page);               
void print_sys_page_info(MfsSysPage &page);        
void print_cfg_files(const MfsCfg &cfg, std::string cfg_filename = "");
void print_mfs_cfgs_info(const Mfs mfs);
std::string sprint_cfg_file_permissions(const MfsCfgRecord &record);
void write_MFS_FAT_to_disk(std::vector<uint16_t> &FAT, std::string filename = "_aFAT (system volume).bin");

} // namespace CBL
#endif