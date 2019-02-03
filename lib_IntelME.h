#ifndef LIB_INTELME_H
#define LIB_INTELME_H
#include <vector>
#include "structs_basic.h"
#include "structs_IntelME.h"

namespace CBL{
    std::vector<ADDRESS> find_all_MFS_pages_by_signature(const std::vector<BYTE> &buffer, const std::vector<BYTE> &signature, ADDRESS start_index = 0);
    MFS_PAGE_HEADER read_MFS_page_header(const std::vector<BYTE> &buffer, const ADDRESS addr = 0); // not
    void read_MFS_page_header(MFS_PAGE_HEADER &mfsPageHeader, const std::vector<BYTE> &buffer, const ADDRESS addr = 0);// not
    MFS_PAGE read_MFS_page(const std::vector<BYTE> &buffer, const ADDRESS addr = 0);// not
    void read_MFS_page(MFS_PAGE &mfsPage, const std::vector<BYTE> &buffer, const ADDRESS addr = 0);// not
}
#endif