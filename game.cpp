#include "game.h"
#include "button.hpp"

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
    this->window->clear(sf::Color(31,100,32, 125));
	//Button test_button("test", {100,100});

	//this->window->draw(test_button);

    this->window->display();


}



//accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

//not accessors:
Game::Game()
{
	this->initVariables();
	this->initWindow();
	//this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}


void Game::pollEvents()
{
	//Event polling loop
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();

			}
			break;
		}
	}

}


void Game::update()
{
	this->pollEvents();
	std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << std::endl;

}



void Game::render()
{
	this->window->clear(sf::Color(31,100,32, 125));

	Button test_button("test", {100, 300}, sf::Vector2f(100.f, 100.f), sf::Color::Blue, 100, sf::Color::Green);

	this->window->draw(test_button);
	//this->window->draw(this->enemy);

	this->window->display();
}


