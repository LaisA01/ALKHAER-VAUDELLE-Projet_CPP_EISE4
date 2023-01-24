#pragma once
#include "question.h"
//#include "button.hpp"
//#include "game.h"

using std::string; using std::pair; using std::vector;

class MCQ : public Question
{
private:
    
    int limite_attribution_points; //la réponse doit être superieur pour avoir les points

public:   
    vector<string> _choices; //les choix eux meme

    MCQ(string text, int points, vector<string> choices, int i_answer):
    Question(text, points)
    {
        _choices = choices;
        _i_answer = i_answer;
        _q_type == "MCQ";
    }
    //~MCQ(); //à voir si on fait un destructor custom ou pas

    string get_answer(void)
    {
        return ("La réponse correcte est: " + _choices[_i_answer] + ". ");
    }

    string get_q_type(void) {return _q_type;} //pas besoin de setter sur ce membre..
    int get_i_answer(void) {return _i_answer;}

    int is_answer(int i)
    {
        if(i == _i_answer) return 1;
        else return 0;
    }
};
