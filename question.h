#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

using std::string; using std::pair; using std::vector;

class Question
{
private:
    string _name;   //nom interne de la question, potentiellement à supprimer pas sur que ce soit utile
    int _points;    //le nb de points que vaut la question
    string _text;   //la question elle meme

public:

    Question(string name, string text, int points)
    {
        _name = name;
        _text = text;
        _points = points;

    }
    ~Question();

    string get_name(void) { return _name;}
    void   set_name(string new_name) {_name = new_name;}

    string  get_text(void) { return _text;}
    void set_text(string new_text) { _text = new_text;}

    int  get_points(void) { return _points;}
    void set_points(int new_points) { _points = new_points;}

    virtual string get_answer(void) = 0;
};

