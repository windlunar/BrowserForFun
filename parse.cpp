
#include "parse.h"



TREE tree ;


PARSE::PARSE(std::vector<std::string> inputHTML)
{
    this->vectorHTML = inputHTML ;
    this->docType = vectorHTML[0];
}



PARSE::~PARSE(){}



int PARSE::isHtml_Format()
{
    if(docType == "<!DOCTYPE html>"){
        
        return 1 ;
    }else{
        std::cout << "Not html format." << std::endl ;
        return 0 ;
    }

}



void PARSE::initTree()
{
    tree.nodeNum = 0 ;
    tree.notUsedNodeIndex = 0 ;

}



void PARSE::createRootNode()
{
    tree.node[ROOT].noteType = rootElement ;
    tree.node[ROOT].tagName = html_TAGNAME ;
    
    if(tree.node[ROOT].noteType != text){
        tree.node[ROOT].textData = "NONE" ;
    }
    
    tree.node[ROOT].parentNode = nullptr ;
    tree.nodeNum++ ;
    tree.notUsedNodeIndex++ ;
}



int PARSE::createChildNode(int note_type ,std::string tagnameInput ,NODE_t *parent_node)
{
    std::cout << "Node index " << tree.notUsedNodeIndex << " Not used yet." << std::endl;
    

    //設定 node type
    tree.node[tree.notUsedNodeIndex].noteType = (enum NODE_TYPE)note_type ;
    std::cout 
        << "So ,create tree.node[" 
        << tree.notUsedNodeIndex << "]:\n"
        << "node Type :" << tree.node[tree.notUsedNodeIndex].noteType 
        << std::endl;


    //設定 tag name
    tree.node[tree.notUsedNodeIndex].tagName = tagnameInput ;
    std::cout 
        << "tag Name :" 
        << tree.node[tree.notUsedNodeIndex].tagName 
        << "\n"
        << std::endl;


    //存放該 node的文字內容(如果是 text node的話)
    if(tree.node[tree.notUsedNodeIndex].noteType != text){
        tree.node[tree.notUsedNodeIndex].textData = "NONE" ;

    }else{
        tree.node[tree.notUsedNodeIndex].textData = "Text data Not implement Yet" ; //Not implement Yet.
    }


    //將parentNode 指向該node的 parent
    tree.node[tree.notUsedNodeIndex].parentNode = parent_node ;


    //將新的node 放入parentNode 的childrenNode vector中
    parent_node->childrenNode.push_back(&tree.node[tree.notUsedNodeIndex]) ;


    tree.nodeNum++ ;
    tree.notUsedNodeIndex++ ;


    return tree.notUsedNodeIndex - 1 ;

}


void PARSE::printTree(){
    std::cout << "\nPrint Tree :" << std::endl;
    std::cout << "Size of Root's children :" << tree.node[ROOT].childrenNode.size() << std::endl ;
    
    std::cout 
        << "Root node\n:" 
        << tree.node[ROOT].tagName
        << "," << tree.node[ROOT].noteType 
        << std::endl;

    std::cout 
        << "   " 
        << tree.node[ROOT].childrenNode[0]->tagName
        << "," << tree.node[ROOT].childrenNode[0]->noteType 
        << std::endl ;


    std::cout 
        << "       " 
        << tree.node[ROOT].childrenNode[0]->childrenNode[0]->tagName
        << "," 
        << tree.node[ROOT].childrenNode[0]->childrenNode[0]->noteType 
        << std::endl ;


    std::cout 
        << "   " << tree.node[ROOT].childrenNode[1]->tagName
        << "," << tree.node[ROOT].childrenNode[1]->noteType << std::endl ;


    std::cout 
        << "       " 
        << tree.node[ROOT].childrenNode[1]->childrenNode[0]->tagName
        << "," 
        << tree.node[ROOT].childrenNode[1]->childrenNode[0]->noteType 
        << std::endl ;


    std::cout 
        << "       " 
        << tree.node[ROOT].childrenNode[1]->childrenNode[1]->tagName
        << "," 
        << tree.node[ROOT].childrenNode[1]->childrenNode[1]->noteType 
        << std::endl ;
}


std::string PARSE::getTagName(std::string strVec)
{
    std::string tag ;
    if(strVec[2] == '/'){
        std::cout << "Just Closing tag" << std::endl;
        tag = "NA" ;
    }else{
        tag = strVec.substr(strVec.find_first_of("<") + 1
                                ,(strVec.find_first_of(">") - strVec.find_first_of("<"))-1) ;
    }
    return tag ;
}



int PARSE::getNodeType(std::string strVec)
{
    if(getTagName(strVec) == title_TAGNAME || getTagName(strVec) == p_TAGNAME){
        return TEXT_NODE_TYPE ;
    }else{
        return ELEMENT_NODE_TYPE ;
    }
}



std::string PARSE::getTextDate(std::string strVec)
{
    std::string text_str ;

    if(getTagName(strVec) == title_TAGNAME || getTagName(strVec) == p_TAGNAME){
        text_str = strVec.substr(strVec.find(">") + 1
                                ,(strVec.find("</") - strVec.find(">"))-1) ;
    }else{
        std::cout << "In getTextDate(), Not text node." << std::endl ;
        text_str = "NONE" ;
    }

    return text_str ;
}