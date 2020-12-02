#ifndef __PARSE_H__
#define __PARSE_H__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

class PARSE{
    public:
        PARSE(std::vector<std::string> inputHTML);
        ~PARSE();
        
        int isHtml_Format();

        std::string docType ;
        std::vector<std::string> vectorHTML ;
};



#endif