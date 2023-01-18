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
    int _points;    //le nb de points que vaut la question
    string _text;   //la question elle meme

public:

    Question(string name, string text, int points)
    {
        _text = text;
        _points = points;

    }
    ~Question();

    string  get_text(void) { return _text;}
    void set_text(string new_text) { _text = new_text;}

    int  get_points(void) { return _points;}
    void set_points(int new_points) { _points = new_points;}

    virtual string get_answer(void) = 0;
};

