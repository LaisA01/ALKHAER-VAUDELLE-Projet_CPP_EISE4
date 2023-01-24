#include "game.h"

using std::string, std::pair, std::vector, std::to_string;
using std::cout, std::endl, std::ifstream;


vector<Button> current_buttons_list; 
vector<Button> current_buttons_list_PhotoMCQ;


vector<MCQ*> MCQ_vector; 
vector<TrueFalse*> TF_vector;
vector<PhotoMCQ*> PhotoMCQ_vector;

//int current_question = 0; // Mdr je cherche un bug depuis 1H, c'est parce que cette variable est jamais incrémenté !
int current_question_type = 0; //0 pour MCQ, 1 pour TF, etc
int stop_game_flag;

bool question_answered = false;


int score = 0;


void Game::initVariables(void)
{
	loadTFQ(TF_vector);
	loadMCQ(MCQ_vector);
	PhotoMCQ* pizz = new PhotoMCQ("que pensez vous de la pizza", 1, {"a", "b", "c", "d"}, 0, "textures/pizza.jpeg"); //TEST
    PhotoMCQ_vector.push_back(pizz);

	/*for (int i = 0; i < MCQ_vector.size(); ++i) // TEST
	{
		cout << MCQ_vector[i]->get_points() << endl;
		cout << MCQ_vector[i]->get_i_answer() << endl;
		cout << MCQ_vector[i]->get_answer() << endl;
		cout << MCQ_vector[i]->get_points() << endl;
	}*/

	this->window = nullptr; 	

	for(int i = 0; i < 4; i++)
	{
		current_buttons_list.push_back(Button(MCQ_vector.back()->_choices[i], {300, 100*(i+1)}, sf::Vector2f(500.f, 80.f), sf::Color(251,100,32, 175), 20, sf::Color::White));
		current_buttons_list_PhotoMCQ.push_back(Button(PhotoMCQ_vector.back()->_choices[i], {300, 250*(i+1)}, sf::Vector2f(500.f, 50.f), sf::Color(251,100,32, 175), 20, sf::Color::White));		
	}
}

void Game::initWindow(void)
{
	//init window:
	this->set_FSM(START);
    this->VM.height = 500;
    this->VM.width = 1000;
    this->window = new sf::RenderWindow(this->VM, "Test", sf::Style::Default);
    this->window->setFramerateLimit(30);
    this->window->clear(sf::Color(31,100,32, 125));
	
	//init start button:
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
}

Game::~Game()
{
	delete this->window;
}

// Note importante : 
// Pour les fermeture si on veux le point rapport à la mémoire 
// en réalité faudrait faire une fonction qui s'occupe de tout
// free PUIS qui close la fenêtre et bisous fin de programme
// Mais ça implique peut-être de mettre en place un mécanisme
// pour traquer tout ce qu'on alloue
// Après je crois que "new" le fait automatiquement, mais pas sûr.
void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		/*for(int i = 0; i < 4; i++) // test
		{
			if (current_buttons_list[i].is_mouse_on(this->window) == 1)
				cout << i << endl;
		}
		*/
		// À voir si on garde, la touche échap permet  ainsi
		// de fermer le jeu à tout instant.
		if (this->ev.type == sf::Event::KeyPressed)
		{
						if (this->ev.key.code == sf::Keyboard::Escape)
						{
							this->window->close();
						}
		}
		//Pareil mais avec la fermeture de l'onglet
		//Ok j'avoue c'est un peu des détails mais c'est plus propre avoue
		if (this->ev.type == sf::Event::Closed) {this->window->close();}
		switch (this->get_FSM())
		{
			case START:  //FSM 0: start
				switch (this->ev.type)
				{
				/*case sf::Event::Closed:
					this->window->close();
					break; */ 
					// A voir

				/*case sf::Event::KeyPressed:
					if (this->ev.key.code == sf::Keyboard::Escape)
					{
						this->window->close();
					}
					break;*/
					// A voir

				case sf::Event::MouseButtonPressed:
					if (this->ev.mouseButton.button == sf::Mouse::Left)
					{
						if (this->start_button.is_mouse_on(this->window) == 1)
						{
							this->set_FSM(1);
						}
					}
					break;
				} 
				break;

			case QUESTION: //FSM 1 : question

				switch (this->ev.type)
				{

				/*case sf::Event::Closed:
					this->window->close();
				break;
				*/
				/*case sf::Event::KeyPressed:
					if (this->ev.key.code == sf::Keyboard::Escape)
					{
						this->window->close();
					}
				break;
				*/
				case sf::Event::MouseButtonPressed:
					
					switch (current_question_type)
					{
					case 0: //QCM
						for(int j = 0; j < 4; j++)
						{
							if (current_buttons_list[j].is_mouse_on(this->window) == 1)
							{
								question_answered = true; //flag question repondue ou pas encore

								if((MCQ_vector.back()->is_answer(j)))
								{
									score += MCQ_vector.back()->get_points(); 
								}
								break;
							}
						}
					break;
					
					case 1:  //Vrai ou faux
						for(int i = 0; i < 2; ++i)
						{
							if (current_buttons_list[i].is_mouse_on(this->window) == 1)
							{
								question_answered = true; //flag

								if((TF_vector.back()->is_answer(i)))
								{
									score += TF_vector.back()->get_points(); 
								}
								break;
							}
						}					
					break;
					
					case 2: //PhotoMCQ
						
						for(int j = 0; j < 4; j++)
						{
							if (current_buttons_list[j].is_mouse_on(this->window) == 1)
							{
								question_answered = true; //flag question repondue ou pas encore

								if((PhotoMCQ_vector.back()->is_answer(j)))
								{
									score += PhotoMCQ_vector.back()->get_points(); 
								}
								break;
							}
						}				
					break;

				break;  //break du case sf::Event::MouseButtonPressed:
				}
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
	sf::Text goodbye_text(" ", fnt, 35);
	//welcome_text.setPosition(this->VM.width/2, 50);
	switch(this->get_FSM())
	{

	case START:		//état écran start	

		//bouton start:
		this->window->draw(this->start_button);
		this->window->draw(welcome_text);
		break;

	case QUESTION:		//état partie en cours
		//std::cout << question_answered << std::endl;
		if((MCQ_vector.empty() == true && TF_vector.empty() == true) || stop_game_flag == 1)
		{
			this->set_FSM(END);
			break;
		}

		this->window->clear(sf::Color(31,100,32, 125));
		switch(current_question_type)
		{
		case 0: //si MCQ
		{

			// Le pb venait de ce bloc, en le mettant après celui
			// du "if question anwsered" et vu qu'il travail sur la liste
			// de question, quand il reste qu'une question et que tu la pop
			// le MCQ_vector.back() cause un segfault !
			int temp_choice_index = 0;
			for (auto it = current_buttons_list.begin(); it !=  current_buttons_list.end(); ++it)
			{
				(*(it)).set_button_text(MCQ_vector.back()->_choices[temp_choice_index]);
				this->window->draw(*(it));
				temp_choice_index++;
			}

			this->window->draw(sf::Text(MCQ_vector.back()->get_text(),fnt, 25));

			if(question_answered == true)
			{
				question_answered = false;
				MCQ_vector.pop_back(); // Il est innocent votre honneur !
				if (MCQ_vector.empty()) {current_question_type = 1;} 
				//J'ajoute ça pour enchainer les questions tranquille
				// A laisser si on décide qu'il y a zéro rng dans l'ordre
				// des questions
				// Penser à retirer le com' avant le rendu 
				// Note pour si jamais on a oublié : Oupsi <3 
			}
			//cout << "points : " + to_string(MCQ_vector[current_question]->get_points()) << endl; // TEST
			//cout << "Réponse : " + to_string(MCQ_vector[current_question]->get_i_answer()) << endl; // TEST

			break;
		}	

		case 1: // Si TF
		{
			current_buttons_list[0].set_button_text("Faux");
			current_buttons_list[1].set_button_text("Vrai");
			this->window->draw(current_buttons_list[0]);
			this->window->draw(current_buttons_list[1]);

			this->window->draw(sf::Text(TF_vector.back()->get_text(),fnt, 25));

			if(question_answered == true)
			{
				question_answered = false;
				TF_vector.pop_back();
				if (MCQ_vector.empty()) {current_question_type = 2;} 
			}
			break;
		}

		case 2: //qcm avec photo
		{
			
			int temp_choice_index = 0;
			for (auto it = current_buttons_list.begin(); it !=  current_buttons_list.end(); ++it)
			{
				(*(it)).set_button_text(PhotoMCQ_vector.back()->_choices[temp_choice_index]);
				this->window->draw(*(it));
				temp_choice_index++;
			}

			this->window->draw(sf::Text(PhotoMCQ_vector.back()->get_text(),fnt, 25));
            this->window->draw(PhotoMCQ_vector.back()->get_sprite());
			if(question_answered == true)
			{
				question_answered = false;
				PhotoMCQ_vector.pop_back(); 
				if (PhotoMCQ_vector.empty()) {current_question_type = 0;} 
			}
			
			break;
		}	

		}
		break;

	case END:
			string message("Merci d'avoir joue ! \nVotre score est de :\n");
			message += to_string(score) + "\n(ok on avoue on a attribue les points au pif";
			goodbye_text.setString(message);
			goodbye_text.setPosition(this->VM.width/4, this->VM.height/2);
			
			this->window->draw(goodbye_text);



		break;
	}
	var++;
	this->window->display();
}


//Load all the TFQ. Return 0 if something wrong happened, else 1.
int Game::loadTFQ(vector<TrueFalse*> &TFTable)
{
	ifstream file("listQTF.txt");
	if (!file)
	{
		cout << "Error : Can't open listTFQ file" << endl;
		return 0;
	} 

	char sentence[256];
	int value;
	TrueFalse* pTFQuestion;
	while(file.getline(sentence, 256)) // Check if a question last and get it		
	{

		string question(sentence);
		file.getline(sentence, 256); // Get score
		string score(sentence); 	 // Used to cast from char to int, ugly I know
		file.getline(sentence, 256); // Get answer
		string answer(sentence);

		pTFQuestion = new TrueFalse(question, stoi(score), stoi(answer));
		TFTable.push_back(pTFQuestion);
	}

	return 1;
}

int Game::loadMCQ(vector<MCQ*> &MCQTable)
{
	ifstream file("listMCQ.txt");
	if(!file)
	{
		cout << "Error :  Can't open listMCQ.txt" << endl;
		return 0;
	}

	char sentence[256];
	int value;
	MCQ* pMCQuestion;
	while(file.getline(sentence, 256))
	{

		string question(sentence);

		file.getline(sentence,256);
		string reponseA(sentence);
		file.getline(sentence,256);
		string reponseB(sentence);
		file.getline(sentence,256);
		string reponseC(sentence);
		file.getline(sentence,256);
		string reponseD(sentence);

		file.getline(sentence, 256);
		string score(sentence);
		file.getline(sentence, 256);
		string answer(sentence);

		pMCQuestion = new MCQ(question, stoi(score),
		 {reponseA, reponseB, reponseC, reponseD}, stoi(answer));
		MCQTable.push_back(pMCQuestion);
	}

	return 1;
}

template<typename T>
void Game::randomize(vector<T*> &listQuestion)
{
	T* questionA;
	int size = listQuestion.size();
	int indiceA = 0;
	int indiceB = 0;
	for(auto i = 0; i < 1000; ++i) //Moi je dis y'a un point pour l'humour là
	{
		indiceA = rand() % size;
		indiceB = rand() % size;
		if (indiceA != indiceB)
		{
			questionA = listQuestion[indiceA];
			listQuestion[indiceA] = listQuestion[indiceB];
			listQuestion[indiceB] = questionA;
		}
	}

	return;
}

