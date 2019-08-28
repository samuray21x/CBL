#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <cstring>
#include <iostream>

// Soon it will be base class Exception and other classes will be rewrite methods:
// debug(), error() and critical_error(), and although class constuctor for message update

namespace CBL{
    class FileNotFoundException {
        protected:
        std::string msg;
        public:
            FileNotFoundException(){ msg = "File not found!"; }
            ~FileNotFoundException(){}
            void debug(){
                std::cout<<"[DEBUG] "<<msg.c_str()<<std::endl;
            }
            void error(){
                std::cerr<<"[ERROR] "<<msg.c_str()<<std::endl;
           }
          void critical_error(){
              std::cerr<<"[CRITICAL ERROR] "<<msg.c_str()<<" --> Programm collapse!"<<std::endl;
              exit(-1);
            }
    };
    class UnexpectedAddressOfMFSPage {
        protected:
        std::string msg;
        public:
            UnexpectedAddressOfMFSPage(){ msg = "Unexpected address of MFS page!"; }
            ~UnexpectedAddressOfMFSPage(){}
            void debug(){
                std::cout<<"[DEBUG] "<<msg.c_str()<<std::endl;
            }
            void error(){
                std::cerr<<"[ERROR] "<<msg.c_str()<<std::endl;
           }
          void critical_error(){
              std::cerr<<"[CRITICAL ERROR] "<<msg.c_str()<<" --> Programm collapse!"<<std::endl;
              exit(-1);
            }
    };
    class OffsetIsOutOfBufferRange {
        protected:
        std::string msg;
        public:
            OffsetIsOutOfBufferRange(){ msg = "Offset is out of buffer range!"; }
            ~OffsetIsOutOfBufferRange(){}
            void debug(){
                std::cout<<"[DEBUG] "<<msg.c_str()<<std::endl;
            }
            void error(){
                std::cerr<<"[ERROR] "<<msg.c_str()<<std::endl;
           }
          void critical_error(){
              std::cerr<<"[CRITICAL ERROR] "<<msg.c_str()<<" --> Programm collapse!"<<std::endl;
              exit(-1);
            }
    };
    class SizeIsOutOfBufferRange {
        protected:
        std::string msg;
        public:
            SizeIsOutOfBufferRange(){ msg = "Size is out of buffer range!"; }
            ~SizeIsOutOfBufferRange(){}
            void debug(){
                std::cout<<"[DEBUG] "<<msg.c_str()<<std::endl;
            }
            void error(){
                std::cerr<<"[ERROR] "<<msg.c_str()<<std::endl;
           }
          void critical_error(){
              std::cerr<<"[CRITICAL ERROR] "<<msg.c_str()<<" --> Programm collapse!"<<std::endl;
              exit(-1);
            }
    };
    class UnallowableSizeOfArgument {
        protected:
        std::string msg;
        public:
            UnallowableSizeOfArgument(){ msg = "Size is out of buffer range!"; }
            ~UnallowableSizeOfArgument(){}
            void debug(){
                std::cout<<"[DEBUG] "<<msg.c_str()<<std::endl;
            }
            void error(){
                std::cerr<<"[ERROR] "<<msg.c_str()<<std::endl;
           }
          void critical_error(){
              std::cerr<<"[CRITICAL ERROR] "<<msg.c_str()<<" --> Programm collapse!"<<std::endl;
              exit(-1);
            }
    };
    class MERegionNotFound {
        protected:
        std::string msg;
        public:
            MERegionNotFound(){ msg = "ME Region is not found in firmware!"; }
            ~MERegionNotFound(){}
            void debug(){
                std::cout<<"[DEBUG] "<<msg.c_str()<<std::endl;
            }
            void error(){
                std::cerr<<"[ERROR] "<<msg.c_str()<<std::endl;
           }
          void critical_error(){
              std::cerr<<"[CRITICAL ERROR] "<<msg.c_str()<<" --> Programm collapse!"<<std::endl;
              exit(-1);
            }
    };
    class NullChunkNumberInNonSysPage {
        protected:
        std::string msg;
        public:
            NullChunkNumberInNonSysPage(){ msg = "Null chunk numer in header of non-system page!"; }
            ~NullChunkNumberInNonSysPage(){}
            void debug(){
                std::cout<<"[DEBUG] "<<msg.c_str()<<std::endl;
            }
            void error(){
                std::cerr<<"[ERROR] "<<msg.c_str()<<std::endl;
           }
          void critical_error(){
              std::cerr<<"[CRITICAL ERROR] "<<msg.c_str()<<" --> Programm collapse!"<<std::endl;
              exit(-1);
            }
    }; 
    class NotNullChunkNumberInSysPage {
        protected:
        std::string msg;
        public:
            NotNullChunkNumberInSysPage(){ msg = "Not null chunk numer in header of system page!"; }
            ~NotNullChunkNumberInSysPage(){}
            void debug(){
                std::cout<<"[DEBUG] "<<msg.c_str()<<std::endl;
            }
            void error(){
                std::cerr<<"[ERROR] "<<msg.c_str()<<std::endl;
           }
          void critical_error(){
              std::cerr<<"[CRITICAL ERROR] "<<msg.c_str()<<" --> Programm collapse!"<<std::endl;
              exit(-1);
            }
    };
    class CantCreateFileToWrite {
        protected:
        std::string msg;
        public:
            CantCreateFileToWrite(){ msg = "Can't create file to write!"; }
            ~CantCreateFileToWrite(){}
            void debug(){
                std::cout<<"[DEBUG] "<<msg.c_str()<<std::endl;
            }
            void error(){
                std::cerr<<"[ERROR] "<<msg.c_str()<<std::endl;
           }
          void critical_error(){
              std::cerr<<"[CRITICAL ERROR] "<<msg.c_str()<<" --> Programm collapse!"<<std::endl;
              exit(-1);
            }
    };
    
}
#endif