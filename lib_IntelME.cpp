#include <vector>
#include <iostream>
#include "lib_binary.h"
#include "lib_IntelME.h"
#include "exceptions.h"


std::vector<CBL::ADDRESS> CBL::find_all_MFS_pages_by_signature(const std::vector<CBL::BYTE> &buffer, const std::vector<CBL::BYTE> &signature, CBL::ADDRESS start_index){
    std::vector<CBL::ADDRESS> offsets;
    try{
        for (CBL::ADDRESS cur_offset = 0; cur_offset != (unsigned)-1; ){
            cur_offset = find_by_signature(buffer,signature, cur_offset+1);
            if (cur_offset == (unsigned)-1) break;
            else if (offsets.size() != 0 && (cur_offset - offsets[offsets.size() - 1] != CBL::MFS_pageSize) )  throw unexpected_addres_of_mfs_page {};
            offsets.push_back(cur_offset);
        }
        offsets.push_back( offsets[offsets.size() - 1] + MFS_pageSize ); // ADD OFFSET OF THE BLANK PAGE (1 in mfs, last)
        return offsets;
    }
    catch(unexpected_addres_of_mfs_page)
    {
        std::cout<<"[WARNING] Unexpetced addres of MFS page!"<<std::endl;
    }
    catch(...){
        std::cerr<<"[ERROR] Unknown exception!"<<std::endl;
        exit(-1);
    }    
}

CBL::MFS_PAGE_HEADER CBL::read_MFS_page_header(const std::vector<CBL::BYTE> &buffer, const CBL::ADDRESS addr){
    MFS_PAGE_HEADER header;
    header.signature;
    //
    //// NO READY
    //
}
