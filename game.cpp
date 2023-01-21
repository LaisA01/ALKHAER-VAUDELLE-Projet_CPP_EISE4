#include "game.h"
#include "button.hpp"
#include "TrueFalse.h"
#include "outils.hh"
#include "unistd.h"

#define START 0
#define QUESTION 1

using std::string, std::pair, std::vector;



vector<vector<Button>> MCQ_choice_button_buffer; //buffer pour les boutons des QCM
vector<vector<Button>> TF_choice_button_buffer; //buffer pour les boutons des QCM

vector<MCQ*> MCQ_vector; 
vector<TrueFalse*> TF_vector;

int current_question = 0;
int current_question_type = 0; //0 pour MCQ, 1 pour TF, etc
int stop_game_flag;

bool question_answered = false;


int score = 0;


void Game::initVariables(void)
{
	loadTFQ(TF_vector);
	loadMCQ(MCQ_vector);

	this->window = nullptr; //le gars dans le tuto dit de faire ça, à voir si on garde ou pas	

	/*    TrueFalse(string text, int points, int i_answer):
    Question(text, points)
    {
        _i_answer = i_answer;
    }*/

	for(auto i : MCQ_vector)
	{
		vector<Button> temp_button_vect;
		for(int j = 0; j < 4; j++)
		{
			Button temp_button = Button(i->_choices[j], {300, 100*(j+1)}, sf::Vector2f(500.f, 80.f), sf::Color(251,100,32, 175), 20, sf::Color::White);
			temp_button_vect.push_back(temp_button);
		}
		MCQ_choice_button_buffer.push_back(temp_button_vect);
	}

	for(auto i : TF_vector)
	{
		vector<Button> temp_button_vect;

		Button temp_button = Button("Vrai", {300, 100}, sf::Vector2f(500.f, 80.f), sf::Color(251,100,32, 175), 20, sf::Color::White);
		temp_button_vect.push_back(temp_button);
		temp_button = Button("Faux", {300, 200}, sf::Vector2f(500.f, 80.f), sf::Color(251,100,32, 175), 20, sf::Color::White);
		temp_button_vect.push_back(temp_button);
	
		TF_choice_button_buffer.push_back(temp_button_vect);
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
	this->start_button = Button(" start", {this->VM.width/2, this->VM.height/2}, sf::Vector2f(110.f, 60.f), sf::Color::Blue, 45, sf::Color::Green);

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
	//question_answered = false;
	//Event polling loop
	while (this->window->pollEvent(this->ev))
	{
		switch (this->get_FSM())
		{
			case 0:  
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
					if (this->ev.mouseButton.button == sf::Mouse::Left)
					{
						if (this->start_button.is_mouse_on(this->window) == 1)
						{
							this->set_FSM(1);
						}
					//std::cout << this->start_button.is_mouse_on(this->window) << std::endl;
					}
					break;
				} 
				break;

			case 1: //FSM 1

				switch (this->ev.type)
				{
				case sf::Event::Closed:
					this->window->close();
					//break;
				case sf::Event::KeyPressed:
					if (this->ev.key.code == sf::Keyboard::Escape)
					{
						this->window->close();
					}
					//break;
				case sf::Event::MouseButtonPressed:
					switch (current_question_type)
					{
					case 0: //QCM
						for(int i = 0; i < 4; i++)
						{
							std::cout<< "test"<< std::endl;
							if (MCQ_choice_button_buffer[current_question][i].is_mouse_on(this->window) == 1)
							{
								question_answered = true; //flag

								if(i == (MCQ_vector[current_question]->get_i_answer()))
								{
									score += MCQ_vector[current_question]->get_points(); 
								}
								//this->window->close();
								break;
							}
						}
					
					//case 1:
					//break;
					
					//case 2:
					//break;
					}
				break;
				//break;
			//break;
			}
		}
	}
}
		


void Game::update()
{
	this->pollEvents();
	//std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << std::endl;
	//std::cout << "Game updated" << std::endl;

}

int var = 100;



void Game::render()
{
	//std::cout<<"Game rendered"<<std::endl;
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

	case START:		//état écran start	

		//bouton start:
		this->window->draw(this->start_button);
		this->window->draw(welcome_text);
		break;

	case QUESTION:		//état partie en cours
		std::cout << question_answered << std::endl;
		if((MCQ_vector.empty() == true && TF_vector.empty() == true) || stop_game_flag == 1)
		{
			this->set_FSM(2);
			break;
		}

		this->window->clear(sf::Color(31,100,32, 125));
		switch(current_question_type)
		{
			case 0: //si QCM normal
			this->window->draw(sf::Text(MCQ_vector.back()->get_text(),fnt, 25));
			
			vector<Button> temp_choice_vector = MCQ_choice_button_buffer.back();
			
			if(question_answered == true)
			{
				question_answered = false;
				MCQ_vector.pop_back();
			}

			for (auto it = temp_choice_vector.begin(); it != temp_choice_vector.end(); ++it)
			{
				this->window->draw(*(it));
			}

			//case 1:
			//case 2:
		}
		break;





	}
	var++;
	this->window->display();
}


