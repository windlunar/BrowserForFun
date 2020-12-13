/**
 * Date : 2020/12/5
 * Author : Yi-Ying-Lin
 * 
 */ 

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

#include "loadfile.h"
#include "parse.h"
#include "dom.h"


#include "layout.h"



using namespace std;


#define DEFAULT_FILE_PATH   "./html_test"
#define FILE_NAME   "/index.html"


int main(int argc ,char *argv[])
{   
    string file_path ;
    if( argc != 2 ){
        cout << "Default file path :" << DEFAULT_FILE_PATH << endl ;
        file_path = DEFAULT_FILE_PATH ;
    }else{
        cout << "File path :" << argv[1] << endl ;
        file_path = argv[1] ;
    }

    
    /** 載入 HTML 檔案*/
    LOADFILE load(file_path ,FILE_NAME) ;
    vector<string> readHTML = load.deleteSpaceChar( load.loadFile() ) ;
    load.printHtmlRawData(readHTML) ;


    /** 解析 HTML*/
    PARSE parse(readHTML) ;

    parse.initTree();
    parse.createRootNode();

    parse.createDomTree();

    /** 根據tree排版*/
    LAYOUT layout ;

    /** Render*/
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "test");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        
        //render texts.
        layout.renderText(&window) ;

        //render image
        layout.renderImage(&window) ;
        
        window.display();
    }


    return 0 ;
}