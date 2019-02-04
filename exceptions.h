#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

//WANT to add msg for function name by using constructor arg

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
}
#endif