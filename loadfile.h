/**
 * Date : 2020/12/5
 * Author : Yi-Ying-Lin
 * 
 */ 

#ifndef __LOAD_FILE_H__
#define __LOAD_FILE_H__

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class LOADFILE
{
    public:
        LOADFILE(std::string path ,std::string fileName) ;
        ~LOADFILE() ;
        std::string loadFileTest();
        std::vector<std::string> loadFile();
        std::vector<std::string> deleteSpaceChar(std::vector<std::string> vec) ;

        std::string path ;
        std::string fileName ;
        std::string filePath ;
};


#endif