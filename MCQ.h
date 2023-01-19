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
    string _q_type;          //vu qu'il n ya pas de methode IsInstanceOf() en c++, on garde le type de la question dans la classe elle meme 

public:   
    vector<string> _choices; //les choix eux meme

    MCQ(string text, int points, int nb_choices, vector<string> choices, int i_answer):
    Question(text, points)
    {
        _nb_choices = nb_choices;
        _choices = choices;
        _i_answer = i_answer;
        _q_type == "MCQ";
    }
    //~MCQ(); //à voir si on fait un destructor custom ou pas

    string get_answer(void)
    {
        return ("La réponse correcte est: " + _choices[_i_answer] + ". ");
    }

    int get_nb_choices(void) {return _nb_choices;}
    void set_nb_choices(int new_nb) {_nb_choices = new_nb;}

    string get_q_type(void) {return _q_type;} //pas besoin de setter sur ce membre..

};
