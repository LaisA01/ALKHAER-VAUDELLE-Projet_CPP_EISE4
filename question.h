#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <list>

using std::string, std::pair, std::vector, std::ostream;

class Question
{
private:
    int _points;    //le nb de points que vaut la question
    string _text;   //la question elle meme

public:

    Question(string text, int points)
    {
        _text = text;
        _points = points;

    }

    string  get_text(void) const { return _text;} 
    void set_text(string new_text) { _text = new_text;}

    int  get_points(void) const { return _points;}
    void set_points(int new_points) { _points = new_points;}

    virtual int is_answer(int i){return 0;} //très crade mais je peux pas la rendre virtuelle car la classe textboxQuestions peut pas avoir la même signature 
    
    virtual void operator=(const Question& q) //surcharge d'operateur d'affectation
    {
        _points = q._points;
        _text = q._text;
    }
};
