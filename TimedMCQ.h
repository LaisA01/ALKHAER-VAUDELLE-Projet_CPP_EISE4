#pragma once
#include "MCQ.h"

using std::string; using std::pair; using std::vector;

class TimedMCQ : public MCQ
{
private:
    int _timer_value;
    int _timer_counter; 
    bool _time_out; //true if timer counter == timer value 

public:   
    int get_timer_value(void) {return _timer_value;}
    void set_timer_value(int new_val) {_timer_value = new_val;}

    int get_timer_counter(void) {return _timer_counter;}
    void set_timer_counter(int new_val) {_timer_counter = new_val;}

    bool get_time_out(void) {return _time_out;}
    void set_time_out(bool new_val) {_time_out = new_val;}


    TimedMCQ(string text, int points, vector<string> choices, int i_answer, int timer_value):
    MCQ(text, points, choices, i_answer)
    {
        _timer_value = timer_value;
        _timer_value = 0;
        _time_out = false;
    }

    ~TimedMCQ();

};
