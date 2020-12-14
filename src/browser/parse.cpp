/**
 * Date : 2020/12/5
 * Author : Yi-Ying-Lin
 * 
 */ 


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



int PARSE::createChildNode(int note_type ,std::string tagnameInput ,std::string text_str ,NODE_t *parent_node)
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
        << std::endl;


    //存放該 node的文字內容(如果是 text node的話)   
    if(tree.node[tree.notUsedNodeIndex].noteType != text){
        tree.node[tree.notUsedNodeIndex].textData = "NONE" ;

    }else{
        tree.node[tree.notUsedNodeIndex].textData = text_str ; 
    }

    //如果tag是img的話 ,也把src的內容存入 text_str
    if(tree.node[tree.notUsedNodeIndex].tagName == img_TAGNAME){
        tree.node[tree.notUsedNodeIndex].textData = text_str ; 
    }

    std::cout 
        << "text data :" 
        << tree.node[tree.notUsedNodeIndex].textData 
        << "\n"
        << std::endl;

    //將parentNode 指向該node的 parent
    tree.node[tree.notUsedNodeIndex].parentNode = parent_node ;


    //將新的node 放入parentNode 的childrenNode vector中
    parent_node->childrenNode.push_back(&tree.node[tree.notUsedNodeIndex]) ;


    tree.nodeNum++ ;
    tree.notUsedNodeIndex++ ;


    return tree.notUsedNodeIndex - 1 ;

}



NODE_t *PARSE::createChildReturnNodePtr(int note_type ,std::string tagnameInput ,std::string text_str ,NODE_t *parent_node)
{
    int index = createChildNode(note_type ,tagnameInput ,text_str ,parent_node) ;
    return &tree.node[index] ;

}





std::string PARSE::getTagName(std::string strVec)
{
    std::string tag ;
    if(strVec[2] == '/'){
        std::cout << "Closing tag" << std::endl;
        tag = "NA" ;
    }else{
        int k = 0 ;
        for(k ; k < strVec.size() ; k++){
            if(strVec[k] == ' ' || strVec[k] == '>'){
                break ;
            }
        }
        
        tag = strVec.substr(strVec.find_first_of("<") + 1 ,k-1) ;    
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



std::string PARSE::getTextData(std::string strVec)
{
    std::string text_str ;

    if(getTagName(strVec) == title_TAGNAME || getTagName(strVec) == p_TAGNAME){
        text_str = strVec.substr(strVec.find(">") + 1
                                ,(strVec.find("</") - strVec.find(">"))-1) ;

    /** img標籤中的 src是屬性 ,src存放圖片的url, 這邊將其當成 text data*/
    }else if(getTagName(strVec) == img_TAGNAME){

        int k = strVec.find("=")+1 ;
        for(k ; k < strVec.size() ; k++){
            if(strVec[k] == '>'){
                break ;
            }
            text_str += strVec[k] ;
        }

        std::cout << "imgae data :" << text_str << std::endl ;

    }else{
        std::cout << "In getTextData(), Not text node." << std::endl ;
        text_str = "NONE" ;
    }

    return text_str ;
    
}



void PARSE::createDomTree()
{
    NODE_t *parent_node_ptr ;
    NODE_t *current_node_ptr = &tree.node[ROOT] ;

    for(int k = 2 ; k < vectorHTML.size() ;k++){

        if( (vectorHTML[k-1].find("/") == std::string::npos ) && (vectorHTML[k][1] != '/') ){
            parent_node_ptr = current_node_ptr ;

            std::cout << "condition 1" << std::endl ;
            std::cout << "parent node tag :" << parent_node_ptr->tagName << std::endl;

            current_node_ptr = this->createChildReturnNodePtr(this->getNodeType(vectorHTML[k]) 
                                                            ,this->getTagName(vectorHTML[k]) 
                                                            ,this->getTextData(vectorHTML[k]) 
                                                            ,parent_node_ptr) ;
            
            
        }else if( (vectorHTML[k-1].find("/") != std::string::npos ) && (vectorHTML[k][1] == '/') ){
            std::cout << "condition 2" << std::endl ;
            std::cout << "parent node tag :" << parent_node_ptr->tagName << std::endl;

            current_node_ptr = current_node_ptr->parentNode ;
            parent_node_ptr = current_node_ptr->parentNode ;
            
                                                
        }else if((vectorHTML[k-1].find("/") != std::string::npos ) && (vectorHTML[k][1] != '/') ){
            
            std::cout << "condition 3" << std::endl ; 
            std::cout << "parent node tag :" << parent_node_ptr->tagName << std::endl;  

            current_node_ptr = this->createChildReturnNodePtr(this->getNodeType(vectorHTML[k]) 
                                                            ,this->getTagName(vectorHTML[k]) 
                                                            ,this->getTextData(vectorHTML[k]) 
                                                            ,parent_node_ptr) ;

        }else{
            std::cout << "Not supported HTML format." << std::endl ;
        }
        
    }    
}




void PARSE::printTreeForTest(){
    std::cout << "Not Implement Yet." << std::endl ;
}


void PARSE::getImgTagsFilePath(){
    std::string temp ;
    for(int k = 0 ; k<tree.nodeNum ; k++){
        if(tree.node[k].tagName == img_TAGNAME){
            temp = tree.node[k].textData ;
            temp += '\0' ;
            imgFilePathVec.push_back(temp) ;
        }
    }
}
