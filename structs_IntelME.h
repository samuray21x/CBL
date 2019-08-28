#ifndef ME_STRUCTS_H
#define ME_STRUCTS_H
#include <stdint.h>
#include "structs_basic.h"
#include <string>

namespace CBL
{

/****************
    CONSTANTS     
****************/
const Datasize MFS_pageSize = {0x2000};
const Datasize MFS_pageHeaderSize = {0x12};
const Datasize MFS_chunkSize = {0x40};
const Datasize MFS_chunkSizeWithCRC16 = {MFS_chunkSize + 2};
const Datasize MFS_chunksOnPage = {0x7A};
const Datasize MFS_chunksOnSysPage = {0x78};
const Datasize MFS_cfgRecordSize = {0x1C};
const Datasize ME_partitionsCount = {0xD};
const Datasize ME_descriptorMaxSize = {0x300};

/*****************
    STRUCTURES     
*****************/

struct MeDescriptorPartition
{
    Address offset = {0};
    Datasize size = {0};
    std::string name;
};

struct MeDescriptor
{
    MeDescriptorPartition FTPR;
    MeDescriptorPartition FTUP;
    MeDescriptorPartition DLMP;
    MeDescriptorPartition PSVN;
    MeDescriptorPartition IVBP;
    MeDescriptorPartition MFS;
    MeDescriptorPartition NFTP;
    MeDescriptorPartition ROMB;
    MeDescriptorPartition WCOD;
    MeDescriptorPartition LOCL;
    MeDescriptorPartition FLOG;
    MeDescriptorPartition UTOK;
    MeDescriptorPartition ISHC;
    // Addition for ME12
    MeDescriptorPartition UEP;
    MeDescriptorPartition HVMP;
    MeDescriptorPartition RBEP;
};

struct MfsPageHeader
{
    uint32_t signature;
    uint32_t USN;
    uint32_t nErase;
    uint16_t nextErase;
    uint16_t firstChunk;
    uint8_t checksum;
    uint8_t zeroByte;
};
typedef std::vector<MfsPageHeader> V_MfsPageHeader;

struct MfsChunk
{
    Byte data[MFS_chunkSize];
    uint16_t crc16;
    uint16_t crc16_calc;
    uint16_t number = {0xFFFF};
    bool correct_crc;
};
typedef std::vector<MfsChunk> V_MfsChunk;

struct MfsPage
{
    MfsPageHeader header;
    Byte chunksMap[MFS_chunksOnPage];
    MfsChunk chunks[MFS_chunksOnPage];
    Address addr;
    uint16_t number_in_mfs = {0x00};
};
typedef std::vector<MfsPage> V_MfsPage;

struct MfsSysPage
{
    MfsPageHeader header;
    uint16_t chunksMap[MFS_chunksOnSysPage + 1];
    uint16_t chunksMapDeobfuscated[MFS_chunksOnSysPage + 1];
    MfsChunk chunks[MFS_chunksOnSysPage];
    Address addr;
    uint16_t number_in_mfs = {0x00};
};
typedef std::vector<MfsSysPage> V_MfsSysPage;

struct MfsPages
{
    V_MfsPage dataPages;
    V_MfsSysPage sysPages;
};

struct MfsSysVolumeHeader
{
    uint32_t sign;
    uint32_t version;
    uint32_t totalCapacity;
    uint16_t nFiles;
};

struct MfsSysVolume
{
    MfsSysVolumeHeader header;
    std::vector<uint16_t> FAT; // [nFiles + nDataChunks]
};

struct MfsDataVolume
{
    V_Byte data;
};

struct Mfs
{
    V_MfsPage dataPages;
    V_MfsSysPage sysPages;
    MfsSysVolume sysVolume;
    MfsDataVolume dataVolume;
};

struct MfsCfgRecord
{
    char name[12];       // File name
    uint16_t unused;     // Always 0
    uint16_t mode;       // Access mode
    uint16_t options;    // Deploy options
    uint16_t dataLength; // File data length
    uint16_t uid;        // Owner User ID
    uint16_t gid;        // Owner Group ID
    uint32_t offset;     // File data offset
};                       //28 bytes
typedef std::vector<MfsCfgRecord> V_MfsCfgRecord;

struct MfsCfg
{
    uint32_t nRec;         // Number of records
    V_MfsCfgRecord records; // Records aRec[nRec]
    V_Byte data;           // Files data
};
typedef std::vector<MfsCfg> V_MfsCfg;

/****************
    SIGNATURES     
****************/
const V_Byte ME_signatureMeRegion = {0x24, 0x46, 0x50, 0x54};   //ME region signature (0x10 offset of ME region)
const V_Byte MFS_signaturePage = {0x87, 0x78, 0x55, 0xAA};      //Mfs page signature
const V_Byte MFS_signatureSysVolume = {0x01, 0x62, 0x4F, 0x72}; //System volume signature
const uint16_t MFS_signatureSysChunkMapEnd = {0x7FFF};          //System page chunks map last element marker
} // namespace CBL
#endif