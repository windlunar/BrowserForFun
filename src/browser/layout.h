/**
 * Date : 2020/12/5
 * Author : Yi-Ying-Lin
 * 
 */ 

#ifndef __LAYOUT_H__
#define __LAYOUT_H__


//sudo apt-get install libsfml-dev
#include <SFML/Graphics.hpp>
#include <SFML/System/InputStream.hpp>
#include <SFML/System/FileInputStream.hpp>
#include <SFML/System/MemoryInputStream.hpp>


#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include "loadfile.h"
#include "dom.h"
#include "parse.h"



#define WIN_WIDTH   1024
#define WIN_HEIGHT  960

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
        std::string str_layout ;



        std::vector<sf::Text> textVectorForRender ;
        std::vector<std::string> str_vector ;
        void setLayout() ;

        void setTextFmt(sf::Text *text_obj_ptr ,std::string text_all ,int charSize ,float y_pos) ;
        void renderText(sf::RenderWindow *window) ;


        std::vector<int> image_pose_vec ;
        std::vector<std::string> image_path_vec ;

        std::vector<sf::Sprite> image_vec ;
        sf::Texture texture_arr[16] ;
        //sf::Sprite sprite_arr[16] ;

        void loadImage(sf::Texture *texture_ptr ,sf::Sprite *sprite_ptr ,std::string image_path) ;
        void renderImage(sf::RenderWindow *window) ;
};


#endif