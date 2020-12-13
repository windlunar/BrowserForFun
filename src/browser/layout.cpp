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
    this->setLayout() ;
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
                if(count != 0) this->str_layout += "\n";
                this->str_layout += tree.node[k].textData ;
                count++ ;

            }else if(tree.node[k].tagName == "h1"){
                std::cout << "Not implement yet." << std::endl ;
            }
        }
    }
}


void LAYOUT::setTextFmt(sf::Text *text_ptr ,std::string text_all ,int charSize ,float y_pos)
{
    text_ptr->setFont(font); // font is a sf::Font
    text_ptr->setString(text_all);
    text_ptr->setCharacterSize(charSize); // in pixels, not points!
    text_ptr->setFillColor(sf::Color::Black);
    text_ptr->setStyle(sf::Text::Regular);
    text_ptr->setPosition(10.0f ,y_pos);
}


void LAYOUT::setLayout(){

    int text_y_pos = 10 ;
    int img_num = 0 ;

    for(int k=1 ; k < tree.nodeNum ; k++){
        if(tree.node[k].noteType == TEXT_NODE_TYPE)
        {
            if(tree.node[k].tagName == "p"){
                this->str_vector.push_back(tree.node[k].textData) ;

                //設定每一行text的format
                sf::Text text ;
                this->setTextFmt(&text ,tree.node[k].textData ,p_CHAR_SIZE ,text_y_pos) ;

                //把每一行text push 到 vector中
                this->textVectorForRender.push_back(text) ;
                text_y_pos += 25 ;

            }else if(tree.node[k].tagName == "h1"){
                std::cout << "Not implement yet." << std::endl ;

            }
        //處理 img tag
        }else if(tree.node[k].tagName == img_TAGNAME){
            
            image_pose_vec.push_back(text_y_pos) ;

            //store image path to a string vector
            image_path_vec.push_back(tree.node[k].textData) ;

            //load圖片
            std::cout << "image path :" << tree.node[k].textData << std::endl ;
            sf::Sprite sprite ;

            this->loadImage(&texture_arr[img_num] ,&sprite ,tree.node[k].textData) ;

            //根據size調整大小
            float x_size = (float)texture_arr[img_num].getSize().x ;
            float y_size = (float)texture_arr[img_num].getSize().y ;
            float scale = 286 / y_size ;

            //設定 圖片縮放 ,與位置
            sprite.setScale(scale ,scale) ;
            sprite.setPosition(100 ,text_y_pos+10) ;


            //load image後 存到sprite的 vector中
            image_vec.push_back(sprite) ;

            // y大約有440的間隔
            text_y_pos += 300 ;
            img_num += 1 ;
        }
        
    }
}


void LAYOUT::renderText(sf::RenderWindow *window)
{
    for(int k = 0 ; k < this->textVectorForRender.size() ; k++){
        window->draw(this->textVectorForRender[k]);
    }
}

/**
 * 獲得 scale的方式 :
 * sf::Vector2f v = sprite.getScale() ;
 * std::cout << "v.x :" << v.x << std::endl ;
 * std::cout << "v.y :" << v.y << std::endl ;
 */ 
void LAYOUT::loadImage(sf::Texture *texture_ptr ,sf::Sprite *sprite_ptr ,std::string image_path){
    sf::FileInputStream stream;
    stream.open(image_path);

    texture_ptr->loadFromStream(stream);

    sprite_ptr->setTexture(*texture_ptr);

}


void LAYOUT::renderImage(sf::RenderWindow *window){
    for(int k = 0 ; k < this->image_vec.size() ; k++){
        window->draw(this->image_vec[k]);
    }
}


