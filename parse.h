#ifndef __PARSE_H__
#define __PARSE_H__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "dom.h"

class PARSE{
    public:
        PARSE(std::vector<std::string> inputHTML);
        ~PARSE();
        
        int isHtml_Format();
        void initTree() ;
        void createRootNode();
        int createChildNode(int noteType ,std::string tagname ,NODE_t *parent_node) ;
        void printTree() ;

        std::string docType ;
        std::vector<std::string> vectorHTML ;
};



struct TREE
{
    NODE_t node[64] ;
    int nodeNum ;
    int notUsedNodeIndex ;
};



extern TREE tree ;

#endif