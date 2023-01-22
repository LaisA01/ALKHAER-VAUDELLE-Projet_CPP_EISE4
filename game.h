#pragma once
#include <fstream>
#include <list>
#include <string>
#include "MCQ.h"
#include "button.hpp"
#include "TrueFalse.h"
#include "unistd.h"

#define START 0
#define QUESTION 1
#define END 2

//Faut retirer ça c'est un des sept péchés capitaux du C++
using std::string; using std::pair; using std::vector;

class Game
{
private:

    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode VM;

    void initVariables();
    void initWindow();

    int _graphics_FSM;

	Button start_button = Button(" test", {this->VM.width/2, this->VM.height/2}, sf::Vector2f(100.f, 60.f), sf::Color::Blue, 45, sf::Color::Green);
    //std::vector<MCQ> MCQ_vector;


public:
    vector<Button> choice_button_vector; // à voir si on le met en private mais pour l'instant flemme

    const bool running() const;
    Game();
    ~Game();
    void pollEvents();
    void update();
    void render();

    int get_FSM(void) {return _graphics_FSM;}
    void set_FSM(int state) {_graphics_FSM = state;}
    friend class Button; //pour donner acces aux membres SFML privés de la classe Game.

    //Load all the True/False questions from the listQTF file
    int loadTFQ(vector<TrueFalse*> &TFTable);

    //Load all the multiple choices questions from the listMCQ.txt file
    int loadMCQ(vector<MCQ*> & MCQTable);

    // Randomize a list
    template<typename T>
    void randomize(vector<T*> &listQuestion);

};