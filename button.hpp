#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <SFML/Graphics/Text.hpp>
#include "game.h"

using std::string, std::pair, std::vector;

class Button : public sf::Drawable
{
private: 

    pair <float, float> _button_pos; //abscisce, ordonnée du coin en haut à droite
    pair <float, float> _rect_size;  //dimension du cadre du bouton
   
    string _button_text;    //text du bouarton
    sf::Color  _rect_fill_color;

    int _text_size;
    sf::Color _text_fill_color;
    

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        //Partie visuelle d'un bouton = rectangle + text par dessus 
        sf::Font fnt;
        fnt.loadFromFile("fonts/open-sans.ttf");
        sf::Text txt(_button_text, fnt, _text_size);
        sf::RectangleShape rect;

        //paramètrage du rectangle et du text, à peaufiner
        rect.setPosition(_button_pos.first, _button_pos.second); 
        rect.setSize(sf::Vector2f(_rect_size.first, _rect_size.second));
        rect.setScale(sf::Vector2f(1.f, 1.f));
        rect.setFillColor(_rect_fill_color);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(2.f);

        txt.setPosition(_button_pos.first, _button_pos.second); 
        txt.setScale(sf::Vector2f(1.f, 1.f));
        txt.setFillColor(_text_fill_color);
        txt.setOutlineColor(sf::Color::Black);
        txt.setOutlineThickness(1.f);

        //enfin on dessine le rectangle et le text par dessus.
        target.draw(rect); 
        target.draw(txt);
    }
public:
    //constructeurs: (penser a ajouter destructor et/ou constructor par copie)
    
    Button(string str, pair<float,float> position, pair <float, float> rect_size, sf::Color rect_color, int text_size, sf::Color text_fill_color)
    {
        set_button_text(str);
        set_x_pos((position.first - (rect_size.first/2)));
        set_y_pos((position.second - (rect_size.second/2))); 

        set_rect_size(rect_size);
        set_rect_fill_color(rect_color);
        set_text_size(text_size);
        set_text_fill_color(text_fill_color);
    }

    //getters et setters, pas sûr qu'on s'en serve mais je les crée au cas où:
    string get_button_text(void) {return _button_text;}
    void set_button_text(string new_text) {_button_text = new_text;}

    float get_x_pos(void) {return _button_pos.first;}
    void set_x_pos(float new_pos) {_button_pos.first = new_pos;}

    float get_y_pos(void) {return _button_pos.second;}
    void set_y_pos(float new_pos) {_button_pos.second = new_pos;}

    pair <float, float> get_rect_size(void) {return _rect_size;}
    void set_rect_size(pair <float, float> new_size) {_rect_size = new_size;}

    sf::Color get_rect_fill_color(void) {return _rect_fill_color;}
    void set_rect_fill_color(sf::Color new_color) {_rect_fill_color = new_color;}

    int get_text_size(void) {return _text_size;}
    void  set_text_size(int new_size) {_text_size = new_size;}  

    sf::Color get_text_fill_color(void) {return _text_fill_color;}
    void set_text_fill_color(sf::Color new_color) {_text_fill_color = new_color;}

    //méthode qui permet de regarder si le bouton a été appuyé:
    int is_mouse_on(sf::RenderWindow* win)
    {
        if(get_x_pos() < sf::Mouse::getPosition(*win).x && sf::Mouse::getPosition(*win).x < get_x_pos() + get_rect_size().first)
        {
            if(get_y_pos() < sf::Mouse::getPosition(*win).y && sf::Mouse::getPosition(*win).y < get_y_pos() + get_rect_size().second)
            {   
                return 1;                
            }
        }
        return 0;
    }
};