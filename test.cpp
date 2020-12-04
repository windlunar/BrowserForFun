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

    cout << 
"/**************************************************************************************************************/"
    << endl;


    parse.createDomTree();

    //print Tree
    parse.printTreeForTest();


    return 0 ;
}