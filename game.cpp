#pragma once
#include "game.h"

using std::string; using std::pair; using std::vector;

void Game::initVariables(void)
{
    this->window = nullptr; //le gars dans le tuto dit de faire ça, à voir si on garde ou pas
}

void Game::initWindow(void)
{
    this->VM.height = 500;
    this->VM.width = 1000;
    this->window = new sf::RenderWindow(this->VM, "Test", sf::Style::Default);
    this->window->setFramerateLimit(30);
}