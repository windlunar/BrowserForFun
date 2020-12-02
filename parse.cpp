
#include "parse.h"



PARSE::PARSE(std::vector<std::string> inputHTML){
    this->vectorHTML = inputHTML ;
    this->docType = vectorHTML[0];
}



PARSE::~PARSE(){}



int PARSE::isHtml_Format(){
    if(docType == "<!DOCTYPE html>"){
        
        return 1 ;
    }else{
        std::cout << "Not html format." << std::endl ;
        return 0 ;
    }

}

