#pragma once
#include "question.h"

using std::string; using std::pair; using std::vector;

class textboxQuestion : public Question
{
private:
    string _answer_str;     //la réponse correcte à laquelle on compare l'entrée de la textbox
    
public:   
    textboxQuestion(string text, int points, string answer_str):
    Question(text, points)
    {
        _answer_str = answer_str;
    }

    void set_answer_str(string str) { _answer_str = str;}
    string get_answer_str(void) { return _answer_str;}

    int is_answer(string str)
    {
        if(_answer_str == str) return 1;
        else return 0;
    }

    void operator = (const textboxQuestion& TBQ)
    {
        set_text(TBQ.get_text());
        set_points(TBQ.get_points());
        _answer_str= TBQ._answer_str;
    }

    friend ostream& operator<<(ostream& os, const textboxQuestion& tbq)
    {
        os << tbq.get_text() << '/' << "points: "<< tbq.get_points() << '/'<< "answer: " << tbq._answer_str << std::endl;
        return os;
    }
};