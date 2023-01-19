#include "game.h"
#include "button.hpp"
#include "TrueFalse.h"
using std::string; using std::pair; using std::vector;

struct q
{
	MCQ M;
	//TrueFalse TF;
	int question_type; //0 for MCQ, 1 for TF, 2 for TimedMCQ, etc..

};

vector<Button> choice_button_buffer; //buffer pour les boutons des QCM

//a remplacer par des vecteurs générés automatiquement par des fonctions de lecture de fichier:
vector<MCQ> MCQ_vector; 
vector<q> current_questions; //vector des questions de la partie en cours

void Game::initVariables(void)
{
	this->window = nullptr; //le gars dans le tuto dit de faire ça, à voir si on garde ou pas	

	q Q1{.M = MCQ("Combien d'esclaves sont mort pour construire les stades de la CDM Qatar 2022?", 1, 4, 
	{"Quelques dizaines", "Quelques centaines", "Nan mai sa a rien a voire conentrons nou sur le foutbol", 
	"c parsque c un paye arab que vou dite sa c sa?"}, 1), .question_type = 0};
	
	current_questions.push_back(Q1);

	for(int i = 0; i < current_questions[0].M.get_nb_choices(); i++)
	{
		choice_button_buffer.push_back(Button(current_questions[0].M._choices[i], {300, 100*(i+1)},
		 sf::Vector2f(500.f, 80.f), sf::Color(251,100,32, 175), 20, sf::Color::White));
	}

}

void Game::initWindow(void)
{
	//init window:
	this->set_FSM(0);
    this->VM.height = 500;
    this->VM.width = 1000;
    this->window = new sf::RenderWindow(this->VM, "Test", sf::Style::Default);
    this->window->setFramerateLimit(30);
    this->window->clear(sf::Color(31,100,32, 125));
	


	//init buttons:
	this->start_button = Button(" test", {this->VM.width/2, this->VM.height/2}, sf::Vector2f(100.f, 60.f), sf::Color::Blue, 45, sf::Color::Green);

	//display initialised stuff:
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

		case sf::Event::MouseButtonPressed:
			switch(this->get_FSM())				
			{
			case 0:
				if (this->ev.mouseButton.button == sf::Mouse::Left)
				{
					if (this->start_button.is_mouse_on(this->window) == 1)
					{
						this->set_FSM(1);
					}
					std::cout << this->start_button.is_mouse_on(this->window) << std::endl;
				}
				break;
			case 1:
				this->window->close();
				break;
			}
			break;
		}
	}

}


void Game::update()
{
	this->pollEvents();
	//std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << std::endl;

}



void Game::render()
{
	this->window->clear(sf::Color(31,100,32, 125));
	
	/*Pour le compte rendu: re-afficher des objets qui ne 
	changent pas à chaque frame n'est peutetre pas la chose la plus 
	optimale qu'on peut faire mais dans le cadre de ce module de C++ 
	qui ne porte pas la programmation graphique, nous n'avons pas vu 
	l'utilité d'aller plus loin sur ce sujet. */

	//message bienvenue:
	sf::Font fnt;
	fnt.loadFromFile("arial/arial.ttf");
	sf::Text welcome_text("Quizz coupe du monde! Pour jouer, appuyez sur le bouton Start.", fnt, 35);
	//welcome_text.setPosition(this->VM.width/2, 50);
	switch(this->get_FSM())
	{

	case 0:						
		//bouton start:
		this->window->draw(this->start_button);
		this->window->draw(welcome_text);
		break;
	case 1:
		this->window->clear(sf::Color(31,100,32, 125));
		
		this->window->draw(sf::Text(current_questions[0].M.get_text(),fnt, 25));
		for(int i = 0; i < current_questions[0].M.get_nb_choices(); i++)
		{
			this->window->draw(choice_button_buffer[i]);
		}


	}
	//this->window->draw(this->enemy);

	this->window->display();
}


