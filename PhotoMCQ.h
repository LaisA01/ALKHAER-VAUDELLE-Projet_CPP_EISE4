#pragma once
#include "MCQ.h"

using std::string; using std::pair; using std::vector;

class PhotoMCQ : public MCQ
{
private:
    string _texture_path;
    sf::Sprite _sprite;
    sf::Texture _texture;
    int img_load_success;

public:   
    string get_texture_path(void) {return _texture_path;}
    void set_texture_path(string new_path) {_texture_path = new_path;}
    sf::Sprite get_sprite(void) {return _sprite;}
    void set_sprite(sf::Sprite new_sprite) {_sprite = new_sprite;}

    sf::Texture get_texture(void) {return _texture;}
    void set_texture(sf::Texture new_texture) {_texture = new_texture;}

    PhotoMCQ(string text, int points, vector<string> choices, int i_answer, string path):
    MCQ(text, points, choices, i_answer)
    {
        _texture_path = path;        
        if(_texture.loadFromFile(path))
        { 
            img_load_success = 1;
            _sprite.setTexture(_texture);
            _sprite.setPosition(sf::Vector2f(650, 150)); //crade mais c'est pas un projet de programmation graphique qu'on fait
        }
        else 
            img_load_success = 0;  

    }



};
