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
    string get_texture_path(void) const {return _texture_path;}
    void set_texture_path(string new_path) {_texture_path = new_path;}
    sf::Sprite get_sprite(void) const {return _sprite;}
    void set_sprite(sf::Sprite new_sprite) {_sprite = new_sprite;}

    sf::Texture get_texture(void) const {return _texture;}
    void set_texture(sf::Texture new_texture) {_texture = new_texture;}

    PhotoMCQ(string text, int points, vector<string> choices, int i_answer, string path):
    MCQ(text, points, choices, i_answer)
    {
        _texture_path = path;        
        if(_texture.loadFromFile(path))
        { 
            img_load_success = 1;
            _sprite.setTexture(_texture);
            _sprite.setPosition(sf::Vector2f(600, 50)); //crade mais c'est pas un projet de programmation graphique qu'on fait
            _sprite.setScale(sf::Vector2f(0.5, 0.5));
        }
        else 
            img_load_success = 0;  
    }

    void operator = (const PhotoMCQ& pqcm)
    {
        set_text(pqcm.get_text());
        set_points(pqcm.get_points());
        set_i_answer(pqcm.get_i_answer());
        set_texture_path(pqcm.get_texture_path());
        set_sprite(pqcm.get_sprite());
        set_texture(pqcm.get_texture());
    }

};
