#ifndef LIB_INTELME_H
#define LIB_INTELME_H
#include <vector>
#include "structs_basic.h"
#include "structs_IntelME.h"

namespace CBL{
    V_ADDRESS find_all_MFS_pages_by_signature(const V_BYTE &buffer, const V_BYTE &signature, ADDRESS start_index = 0);
    MFS_PAGE_HEADER read_MFS_page_header(const V_BYTE &buffer, const ADDRESS addr = 0); // not
    void read_MFS_page_header(MFS_PAGE_HEADER &mfsPageHeader, const V_BYTE &buffer, const ADDRESS addr = 0);// not
    MFS_PAGE read_MFS_page(const V_BYTE &buffer, const ADDRESS addr = 0);// not
    void read_MFS_page(MFS_PAGE &mfsPage, const V_BYTE &buffer, const ADDRESS addr = 0);// not
}
#endif