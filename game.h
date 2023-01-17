#pragma once
#include "MCQ.h"

using std::string; using std::pair; using std::vector;

class Game
{
private:

    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode VM;

    void initVariables();
    void initWindow();

public:

    const bool running() const;
    Game();
    ~Game();
    void pollEvents();
    void Game::update();
    void Game::render();

}