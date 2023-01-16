#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "question.h"

using std::string; using std::pair; using std::vector;

class TrueFalse : public Question
{
private:
    bool answer;          //l'indice de la réponse correcte
    
public:   
    TrueFalse(string name, string text, int points, int nb_choices, vector<string> choices, int i_answer):
    Question(name, text, points)
    {
        _nb_choices = nb_choices;
        _choices = choices;
        _i_answer = i_answer;
    }
    ~TrueFalse(); //à voir si on fait un destructor custom ou pas

    string get_answer(void)
    {
        if(answer)
            return ("La réponse correcte est: vrai.");
        else
            return ("La réponse correcte est: faux.");
    }
};
