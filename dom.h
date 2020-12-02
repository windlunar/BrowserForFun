#ifndef __DOM_H__
#define __DOM_H__

#include <stdio.h>
#include <iostream>
#include <string>


enum NODE_TYPE{
    element = 0,
    text = 1
};

struct NODE_t{
    NODE_t *childNode ;
    enum NODE_TYPE noteType ;

};

struct ELEMENT{
    std::string tagName ;
    std::string attribute ;
};

struct TEXT{
    std::string textData ;
};


struct TAGNAME{
    std::string html = "html" ;
    std::string head = "head" ;
    std::string body = "body" ;
    std::string p = "p" ;
    std::string h1 = "h1" ;
};



#endif