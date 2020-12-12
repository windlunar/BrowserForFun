/**
 * Date : 2020/12/5
 * Author : Yi-Ying-Lin
 * 
 */ 

#include "layout.h"





LAYOUT::LAYOUT(){
    if (!font.loadFromFile(FONT_PATH)){
        std::cout << "Can't load font file." << std::endl ;
    }

    this->title_of_window = "N/A" ;
    this->setTextLayout() ;
    this->setTextFmt(&textForRender ,this->text_layout ,p_CHAR_SIZE);
}
LAYOUT::~LAYOUT(){} 


std::string LAYOUT::getTitle_of_Window(){

    for(int k=1 ; k < tree.nodeNum ; k++){
        if(tree.node[k].tagName == title_TAGNAME){
            this->title_of_window = tree.node[k].textData ;
            break ;
        }
    }
    
    return this->title_of_window ;
}

void LAYOUT::setTextFmt(sf::Text *text_obj_ptr ,std::string text_all ,int charSize){
    text_obj_ptr->setFont(font); // font is a sf::Font
    text_obj_ptr->setString(text_all);
    text_obj_ptr->setCharacterSize(charSize); // in pixels, not points!
    text_obj_ptr->setFillColor(sf::Color::Black);
    text_obj_ptr->setStyle(sf::Text::Regular);
    text_obj_ptr->setPosition(10.0f ,10.0f);
}



void LAYOUT::setTextLayout()
{
    int count ;

    for(int k=1 ; k < tree.nodeNum ; k++){
        if(tree.node[k].noteType == TEXT_NODE_TYPE)
        {
            if(tree.node[k].tagName == "p"){
                if(count != 0) this->text_layout += "\n";
                this->text_layout += tree.node[k].textData ;
                count++ ;

            }else if(tree.node[k].tagName == "h1"){
                std::cout << "Not implement yet." << std::endl ;
            }
        }
    }
}


