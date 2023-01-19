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

using std::string; using std::pair; using std::vector;

class Button : public sf::Drawable
{
private: 

    string _button_text;    //text du bouton
    float _x_pos;           //abcisce du coin en haut à droite du bouton
    float _y_pos;           //ordonnée du coin en haut à droite du bouton
    sf::Vector2f _rect_size;
    sf::Color  _rect_fill_color;

    int _text_size;
    sf::Color _text_fill_color;
    

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        //Partie visuelle d'un bouton = rectangle + text par dessus 
        sf::Font fnt;
        fnt.loadFromFile("arial/arial.ttf");
        sf::Text txt(_button_text, fnt, _text_size);
        sf::RectangleShape rect;

        //paramètrage du rectangle et du text, à peaufiner
        rect.setPosition(_x_pos, _y_pos); 
        rect.setSize(_rect_size);
        rect.setScale(sf::Vector2f(1.f, 1.f));
        rect.setFillColor(_rect_fill_color);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(1.f);

        txt.setPosition(_x_pos, _y_pos); 
        txt.setScale(sf::Vector2f(1.f, 1.f));
        txt.setFillColor(_text_fill_color);
        txt.setOutlineColor(sf::Color::White);
        txt.setOutlineThickness(1.f);

        //enfin on dessine le rectangle et le text par dessus.
        target.draw(rect); 
        target.draw(txt);
    }
public:
    //constructeurs: (penser a ajouter destructor et/ou constructor par copie)
    
    Button(string str, pair<float,float> position, sf::Vector2f rect_size, sf::Color rect_color, int text_size, sf::Color text_fill_color)
    {
        set_button_text(str);
        set_x_pos((position.first - (rect_size.x/2)));
        set_y_pos((position.second - (rect_size.y/2))); 

        set_rect_size(rect_size);
        set_rect_fill_color(rect_color);
        set_text_size(text_size);
        set_text_fill_color(text_fill_color);
    }

    //getters et setters, pas sûr qu'on s'en serve mais je les crée au cas où:
    string get_button_text(void) {return _button_text;}
    void set_button_text(string new_text) {_button_text = new_text;}

    float get_x_pos(void) {return _x_pos;}
    void set_x_pos(float new_pos) {_x_pos = new_pos;}

    float get_y_pos(void) {return _y_pos;}
    void set_y_pos(float new_pos) {_y_pos = new_pos;}

    sf::Vector2f get_rect_size(void) {return _rect_size;}
    void set_rect_size(sf::Vector2f new_size) {_rect_size = new_size;}

    sf::Color get_rect_fill_color(void) {return _rect_fill_color;}
    void set_rect_fill_color(sf::Color new_color) {_rect_fill_color = new_color;}

    int get_text_size(void) {return _text_size;}
    void  set_text_size(int new_size) {_text_size = new_size;}  

    sf::Color get_text_fill_color(void) {return _text_fill_color;}
    void set_text_fill_color(sf::Color new_color) {_text_fill_color = new_color;}

    //méthode qui permet de regarder si le bouton a été appuyé:
    int is_mouse_on(sf::RenderWindow* win)
    {
        if(get_x_pos() < sf::Mouse::getPosition(*win).x && sf::Mouse::getPosition(*win).x < get_x_pos() + get_rect_size().x)
        {
            if(get_y_pos() < sf::Mouse::getPosition(*win).y && sf::Mouse::getPosition(*win).y < get_y_pos() + get_rect_size().y)
            {
                return 1;                
            }
        }
        return 0;
    }
};