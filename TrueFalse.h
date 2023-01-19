#pragma once
#include "question.h"

using std::string; using std::pair; using std::vector;

class TrueFalse : public Question
{
private:
    int _i_answer;          //la réponse correcte
    
public:   
    TrueFalse(string text, int points, int i_answer):
    Question(text, points)
    {
        _i_answer = i_answer;
    }
    ~TrueFalse(); //à voir si on fait un destructor custom ou pas

    string get_answer(void)
    {
        if(_i_answer)
            return ("La réponse correcte est: vrai.");
        else
            return ("La réponse correcte est: faux.");
    }
};
