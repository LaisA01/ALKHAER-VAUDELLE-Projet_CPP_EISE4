#pragma once
#include <fstream>
#include <list>
#include <string>
#include <iostream>
#include "MCQ.h"
#include "button.hpp"
#include "TrueFalse.h"
#include "unistd.h"
#include "PhotoMCQ.h"
#include "Textbox.hpp"
#include "textboxQuestion.h"


#define START 0
#define QUESTION 1
#define END 2

using std::string, std::pair, std::vector;

class Game
{
private:

    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode VM;

    sf::SoundBuffer _click_sound_buffer;
    sf::Sound _click_sound;

    sf::Music _back_ground_music;


    void initVariables();
    void initWindow();

    int _graphics_FSM;

	Button start_button = Button(" test", {this->VM.width/2, this->VM.height/2}, {100.f, 60.f}, sf::Color::Blue, 45, sf::Color::Green);
    //std::vector<MCQ> MCQ_vector;


public:

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

    int loadPhotoMCQ(vector<PhotoMCQ*> &PhotoMCQTable);

    int loadTBQ(vector<textboxQuestion*> &TBQTable);

    // Randomize a list
    template<typename T>
    void randomize(vector<T*> &listQuestion);

};