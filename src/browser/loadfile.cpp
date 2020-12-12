/**
 * Date : 2020/12/5
 * Author : Yi-Ying-Lin
 * 
 */ 


#include "loadfile.h"




LOADFILE::LOADFILE(std::string inputPath ,std::string inputFileName)
{
    this->filePath = inputPath ;
    this->fileName = inputFileName ;
    this->path = this->filePath + this->fileName ;
}

LOADFILE::~LOADFILE(){}


std::string LOADFILE::loadFileTest()
{
    std::cout << "path : " << this->filePath << std::endl;

    std::string readDataBuf ;
    std::fstream fs ;

    fs.open(path.c_str(),std::fstream::in) ;

    if(fs.is_open()){
        getline(fs ,readDataBuf) ;
    }else{
        std::cout << "Can't open file!" <<std::endl ;
    }
    fs.close() ;

    return readDataBuf ;
}


std::vector<std::string> LOADFILE::loadFile()
{
    std::vector<std::string> readHTML_vec ;
    std::fstream fs(path.c_str(),std::fstream::in) ;

    std::string str ;

    if(fs.is_open())
    {
        /** 將檔案內文字一行一行讀近來後 ,從後面 push到 string vector中*/
        while(getline(fs, str))
        {
            readHTML_vec.push_back(str);
        }

    }else{
        std::cout << "Can't open file! index.html may not exist!" <<std::endl ;
        exit(0) ;
    }

    fs.close() ;

    return readHTML_vec ;
}


/** 將前後的空格去除*/
std::vector<std::string>
 LOADFILE::deleteSpaceChar(std::vector<std::string> vec)
{
    for(int k = 0 ; k < vec.size(); k++){
        if( !vec[k].empty() )
        {
            vec[k].erase(vec[k].find_last_not_of(" ") + 1);
            vec[k].erase(0 ,vec[k].find_first_not_of(" "));
        }
    }
    return vec ;
}





//LOADFILE::openFile(){
//
//}

//LOADFILE::closeFile(){
//    
//}



