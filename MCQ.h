#pragma once
#include "question.h"
//#include "button.hpp"
//#include "game.h"

using std::string; using std::pair; using std::vector;

class MCQ : public Question
{
private:
    int _nb_choices;        //le nombre de choix, pas vraiment besoin car on peut faire .size() sur le vector mais plus propre comme ça
    int _i_answer;          //l'indice de la réponse correcte
    
public:   
    vector<string> _choices; //les choix eux meme

    MCQ(string text, int points, int nb_choices, vector<string> choices, int i_answer):
    Question(text, points)
    {
        _nb_choices = nb_choices;
        _choices = choices;
        _i_answer = i_answer;
    }
    //~MCQ(); //à voir si on fait un destructor custom ou pas

    string get_answer(void)
    {
        return ("La réponse correcte est: " + _choices[_i_answer] + ". ");
    }

    int get_nb_choices(void) {return _nb_choices;}
    void set_nb_choices(int new_nb) {_nb_choices = new_nb;}

};
