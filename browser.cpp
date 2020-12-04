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


#define FILE_PATH   "./html_test/"
#define FILE_NAME   "test.html"


int main(int argc ,char *argv[])
{
    /** 載入 HTML 檔案*/
    LOADFILE load(FILE_PATH ,FILE_NAME) ;
    vector<string> readHTML = load.deleteSpaceChar( load.loadFile() ) ;

    cout << "readHTML.size() :" << readHTML.size() << endl;
    for(int i = 0 ; i<readHTML.size(); i++){
        cout << "readHTML[" << i << "] :" << readHTML[i] << endl;
    }

    /** 解析 HTML*/
    PARSE parse(readHTML) ;

    parse.initTree();
    parse.createRootNode();

    parse.createDomTree();


    /** 根據tree排版*/
    LAYOUT layout ;

    /** Render*/
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), layout.getTitle_of_Window());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(layout.textForRender);
        window.display();
    }

    return 0 ;
}