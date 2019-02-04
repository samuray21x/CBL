#include <iostream>
#include "exceptions.h"
#include "lib_binary.h"
#include "lib_IntelME.h"

CBL::V_ADDRESS CBL::find_all_MFS_pages_by_signature(const CBL::V_BYTE &buffer, CBL::ADDRESS start_index, const CBL::V_BYTE &signature){
    CBL::V_ADDRESS offsets;
    try{
        for (CBL::ADDRESS cur_offset = 0; cur_offset != (unsigned)-1; ){
            cur_offset = find_by_signature(buffer,signature, cur_offset+1);
            if (cur_offset == (unsigned)-1) break;
            else if (offsets.size() != 0 && (cur_offset - offsets[offsets.size() - 1] != CBL::MFS_pageSize) )  throw UnexpectedAddressOfMFSPage();
            offsets.push_back(cur_offset);
        }
        offsets.push_back( offsets[offsets.size() - 1] + MFS_pageSize ); // ADD OFFSET OF THE BLANK PAGE (1 in mfs, last)
        return offsets;
    }
    catch(UnexpectedAddressOfMFSPage &e)
    {
        e.debug();
        return offsets;  
    }
    catch(...){
        std::cerr<<"[ERROR] Unknown exception!"<<std::endl;
        exit(-1);
    }  
}

CBL::MFS_PAGE_HEADER CBL::read_MFS_page_header(const CBL::V_BYTE &buffer, const CBL::ADDRESS addr){
    MFS_PAGE_HEADER header;
    header.signature;
    //
    //// NO READY
    //
}
