/**
 * Date : 2020/12/5
 * Author : Yi-Ying-Lin
 * 
 */ 

#ifndef __LAYOUT_H__
#define __LAYOUT_H__


//sudo apt-get install libsfml-dev
#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include "loadfile.h"
#include "dom.h"
#include "parse.h"



#define WIN_WIDTH   800
#define WIN_HEIGHT  600

#define FONT_PATH   "./font/Ubuntu-M.ttf"
#define p_CHAR_SIZE 18

class LAYOUT{
    public:
        LAYOUT() ;
        ~LAYOUT() ;

        sf::Font font;
        sf::Text textForRender ;

        std::string getTitle_of_Window();
        void setTextFmt(sf::Text *text ,std::string textData ,int charSize);
        void setTextLayout();

        std::string title_of_window  ;
        std::string text_layout ;
};


#endif