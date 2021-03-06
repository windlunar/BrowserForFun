/**
 * Date : 2020/12/5
 * Author : Yi-Ying-Lin
 * 
 */ 

#ifndef __DOM_H__
#define __DOM_H__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

//root is the next tag of <!DOCTYPE html>
#define ROOT    0

//Element tag name
#define html_TAGNAME    "html" 
#define head_TAGNAME    "head"
#define body_TAGNAME    "body"

//Text tag name
#define p_TAGNAME       "p" 
#define h1_TAGNAME      "h1" 
#define title_TAGNAME   "title"
#define img_TAGNAME     "img"


#define ROOT_ELEMENT_NODE_TYPE    0
#define ELEMENT_NODE_TYPE    1
#define TEXT_NODE_TYPE    2



enum NODE_TYPE{
    rootElement = 0,
    element = 1,
    text = 2
};




struct NODE_t{
    std::vector<NODE_t *> childrenNode ;
    NODE_t *parentNode;

    std::string tagName ;    
    enum NODE_TYPE noteType ;

    std::string textData ;
};






extern NODE_t document ;
extern NODE_t node[64] ;

#endif