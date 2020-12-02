#ifndef __LOADFILE_H__
#define __LOADFILE_H__

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class LOADFILE{
    public:
        LOADFILE(std::string path ,std::string fileName) ;
        ~LOADFILE() ;
        std::string loadFileTest();
        std::vector<std::string> loadFile();
        std::vector<std::string> eraseSpace(std::vector<std::string> vec) ;

        std::string path ;
        std::string fileName ;
        std::string filePath ;

        //std::string readLineBuf ;
};


#endif