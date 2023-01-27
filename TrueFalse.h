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

    string get_answer(void)
    {
        if(_i_answer)
            return ("La réponse correcte est: vrai.");
        else
            return ("La réponse correcte est: faux.");
    }

    int get_i_answer(void) { return _i_answer;}

    int is_answer(int i)
    {
        if(i == _i_answer) return 1;
        else return 0;
    }

    void operator = (const TrueFalse& TFQ)
    {
        set_text(TFQ.get_text());
        set_points(TFQ.get_points());
        _i_answer= TFQ._i_answer;
    }

    friend ostream& operator<<(ostream& os, const TrueFalse& tfq)
    {
        os << tfq.get_text() << '/' << "points: "<< tfq.get_points() << '/'<< "answer: " << tfq._i_answer << std::endl;
        return os;
    }

};