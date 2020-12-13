/**
 * Date : 2020/12/5
 * Author : Yi-Ying-Lin
 * 
 */ 


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
        int createChildNode(int note_type ,std::string tagnameInput ,std::string text_str ,NODE_t *parent_node) ;
        NODE_t *createChildReturnNodePtr(int note_type ,std::string tagnameInput ,std::string text_str ,NODE_t *parent_node);

        std::string getTagName(std::string strVec);
        int getNodeType(std::string tag_name_input);
        std::string getTextData(std::string strVec);
        void createDomTree() ;

        void printTreeForTest() ;

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