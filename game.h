#pragma once
#include "MCQ.h"
#include "button.hpp"

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
;

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

};