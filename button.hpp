#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using std::string; using std::pair; using std::vector;

class Button : public sf::Drawable
{
private: 

    string _button_text;    //text du bouton
    float _x_pos;           //abcisce du coin en haut à droite du bouton
    float _y_pos;           //ordonnée du coin en haut à droite du bouton

    virtual void draw(sf::RenderTarger& target, sf::RenderStates states) const
    {
        //Partie visuelle d'un bouton = rectangle + text par dessus 
        sf::Text txt(_button_text, sf::Font::GetDefaultFont(), 30);
        sf::RectangleShape rect;

        //paramètrage du rectangle, à peaufiner
        rect.setPosition(_x_pos, _y_pos); 
        rect.setSize(sf::Vector2f(200.f, 100.f));
        rect.setScale(sf::Vector2f(0.1f, 0.1f));
        rect.setFillColor(sf::Color::Grey);
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(1.f);

        //enfin on dessine le rectangle et le text par dessus.
        target.draw(sf::RectangleShape, NULL); //à voir si sfmmerde prend les NULL pour les paramètres par défaut...
        target.draw(txt, NULL);
    }
public:
    //constructeur: (penser a ajouter destructor et/ou constructor par copie)
    Button(string str, pair<float,float> position)
    {
        set_button_text(str);
        set_x_pos(position.first());
        set_y_pos(position.second()); 
    }

    //getters et setters, pas sûr qu'on s'en serve mais je les crée au cas où:
    string get_button_text(void) {return _button_text;}
    void set_button_text(string new_text) {_button_text = new_text;}

    float get_x_pos(void) {return _x_pos;}
    void set_x_pos(float new_pos) {_x_pos = new_pos;}

    float get_y_pos(void) {return _y_pos;}
    void set_y_pos(float new_pos) {_y_pos = new_pos;}

}