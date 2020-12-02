#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

#include "loadfile.h"
#include "parse.h"
//#include "dom.h"

using namespace std;

#define FILE_PATH   "./"
#define FILE_NAME   "tabs.html"

int main()
{
    LOADFILE load(FILE_PATH ,FILE_NAME) ;

    vector<string> readHTML_vec = load.eraseSpace( load.loadFile() ) ;

    cout << "readDataBuf.size() :" << readHTML_vec.size() << endl;
    for(int i = 0 ; i<readHTML_vec.size(); i++){
        cout << "readDataBuf[" << i << "] :" << readHTML_vec[i] << endl;
    }

    cout << "readHTML_vec[2].size() :" << readHTML_vec[2].size() << endl;
    cout << "readHTML_vec[2] :" << readHTML_vec[2] << endl;


    PARSE parse(readHTML_vec) ;
    int rtn = parse.isHtml_Format();
    cout << "parse.docType :" << parse.docType << endl;
    cout << "parse.isHtml_Format() :" << rtn << endl;


    

    //NODE_t node ;
    //node.noteType = text ;
    //cout << node.noteType << endl;

    return 0 ;
}