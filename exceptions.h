#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

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
}
#endif