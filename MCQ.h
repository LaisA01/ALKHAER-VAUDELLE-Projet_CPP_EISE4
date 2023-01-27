#pragma once
#include "question.h"
//#include "button.hpp"
//#include "game.h"

using std::string; using std::pair; using std::vector;

class MCQ : public Question
{
private:
    int _i_answer;          //l'indice de la réponse correcte
public:   
    vector<string> _choices; //les choix eux meme

    MCQ(string text, int points, vector<string> choices, int i_answer):
    Question(text, points)
    {
        _choices = choices;
        _i_answer = i_answer;
    }

    string get_answer(void)
    {
        return ("La réponse correcte est: " + _choices[_i_answer] + ". ");
    }

    int get_i_answer(void) const {return _i_answer;}
    void set_i_answer(int i) {_i_answer = i;}

    int is_answer(int i)
    {
        if(i == _i_answer) return 1;
        else return 0;
    }

    virtual void operator = (const MCQ& qcm)
    {
        set_text(qcm.get_text());
        set_points(qcm.get_points());
        set_i_answer(qcm.get_i_answer());
    }

    friend ostream& operator<<(ostream& os, const MCQ& mcq)
    {
        os << mcq.get_text() << '/' << "points: "<< mcq.get_points() << '/'<< "answer: " << mcq._i_answer << std::endl;
        return os;
    }
};
