#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

#include "loadfile.h"
#include "parse.h"
#include "dom.h"

using namespace std;

#define FILE_PATH   "./"
#define FILE_NAME   "test.html"

int main()
{
    LOADFILE load(FILE_PATH ,FILE_NAME) ;
    vector<string> readHTML = load.eraseSpace( load.loadFile() ) ;

    cout << "readHTML.size() :" << readHTML.size() << endl;
    for(int i = 0 ; i<readHTML.size(); i++){
        cout << "readHTML[" << i << "] :" << readHTML[i] << endl;
    }






    PARSE parse(readHTML) ;
    int rtn = parse.isHtml_Format();
    cout << "parse.docType :" << parse.docType << endl;
    cout << "parse.isHtml_Format() :" << rtn << endl;

    parse.initTree();
    parse.createRootNode();


    cout << 
"/**************************************************************************************************************/"
    << endl;

    
    cout << readHTML[1].size() << endl ;

    //擷取 tag name
    string tag = parse.getTagName(readHTML[6]) ;
    cout << "tag :" << tag << endl;


    //如果 tag = title or p ,擷取text data
    string text_str = parse.getTextDate(readHTML[6]) ;
    int node_type = parse.getNodeType(readHTML[6]) ;


    cout << "text data :" << text_str << endl;
    cout << "node type :" << node_type << endl;



    //if(readHTML[1].find("</") == string::npos){
    //    cout << "No Pos" << endl ;
    //}else{
    //    cout << readHTML[1].find_first_of("/") << endl ;
    //}




    cout << 
"/**************************************************************************************************************/"
    << endl;


    int head_index = parse.createChildNode(node_type ,tag ,&tree.node[ROOT]);
    //int head_index = parse.createChildNode(ELEMENT_NODE_TYPE ,head_TAGNAME ,&tree.node[ROOT]);
    //int title_index = parse.createChildNode(TEXT_NODE_TYPE ,title_TAGNAME ,&tree.node[head_index]);

    //int body_index = parse.createChildNode(ELEMENT_NODE_TYPE ,body_TAGNAME ,&tree.node[ROOT]);
    //int p_index1 = parse.createChildNode(TEXT_NODE_TYPE, p_TAGNAME ,&tree.node[body_index]) ;
    //int p_index2 = parse.createChildNode(TEXT_NODE_TYPE, p_TAGNAME ,&tree.node[body_index]) ;

    


    //print Tree
    //parse.printTree();


    return 0 ;
}