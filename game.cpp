#include "game.h"

using std::string, std::pair, std::vector, std::to_string, std::cout, std::endl, std::ifstream;

//vecteurs de boutons et de boites de text
vector<Button> current_buttons_list; 
vector<Button> current_buttons_list_PhotoMCQ;
vector<Textbox> textbox_vect; 


//vecteurs de questions de differents types:
vector<MCQ*> MCQ_vector; 
vector<TrueFalse*> TF_vector;
vector<PhotoMCQ*> PhotoMCQ_vector;
vector<textboxQuestion*> textboxQuestion_vector;

//des flags:
int current_question_type = 0; //0 pour MCQ, 1 pour TF, 2 pour PhotoMCQ etc
int stop_game_flag; //a enlever si finalement on n'implemente pas un bouton arret
bool question_answered = false;  //flag primordial qui permet de passer a la question suivante
bool answer_is_correct = false;	 //sert pour l'affichage de la bonne réponse

//police de charactères openS
sf::Font openS;

//enfin le score du joueur, affiché à la fin
int score = 0;

//fonction d'init des variables initialisables avant l'onglet (window)
void Game::initVariables(void)
{
	this->window = nullptr; //bonne habitude apparement

	//init audio
	this->_click_sound_buffer.loadFromFile("audio/click.wav");
	this->_click_sound.setBuffer(_click_sound_buffer);

	this->_back_ground_music.openFromFile("audio/background_music.wav");
	this->_back_ground_music.setVolume(20);
	this->_back_ground_music.setLoop(true);
	this->_back_ground_music.play();

	//chargement de tous les questions dans la memoire: certainement pas le plus optimal mais on code pas en 1983 non plus
	loadTFQ(TF_vector);
	loadMCQ(MCQ_vector);
	loadPhotoMCQ(PhotoMCQ_vector);
	loadTBQ(textboxQuestion_vector);

	//Creation de tous les boutons
	for(int i = 0; i < 4; i++)
	{
		current_buttons_list.push_back(Button(MCQ_vector.back()->_choices[i], {300, 100*(i+1)}, {580.f, 80.f}, sf::Color(1,50,32, 80), 20, sf::Color::White));
		current_buttons_list_PhotoMCQ.push_back(Button(PhotoMCQ_vector.back()->_choices[i], {300, 250*(i+1)}, {500.f, 50.f}, sf::Color(1,50,32, 80), 20, sf::Color::White));		
	}
}

//fonction d'initialisation de l'onglet et des textbox et boutons car ils ont nécessitent que l'onglet soit deja initialisée:
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
	this->start_button = Button(" start", {this->VM.width/2, this->VM.height/2}, {110.f, 60.f},  sf::Color(1,50,32, 80), 41, sf::Color::White);

	//Creation d'une textbox pour les questions à textbox
	openS.loadFromFile("fonts/open-sans.ttf");
	textbox_vect.push_back(Textbox(*(this->window), openS));
	textbox_vect.back().setDimensons(100, 100, 400, 50);
	textbox_vect.back().setFocus(true);

	//display initialised stuff:
    this->window->display();

}

//accesseur état du jeu (marche/arret):
const bool Game::running() const
{
	return this->window->isOpen();
}

//constructeur et destructeur:
Game::Game()
{
	this->initVariables();
	this->initWindow();
}
Game::~Game()
{
	delete this->window;
}

//fonction qui scrute les entrées du joueur et met a jour la logique du jeu en fonction de ces entrees
void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		/*Ici, on gere les questions a textbox a part pour etre compatible avec l'interface du code de textbox qu'on
		  a trouvé sur internet. C'est crade mais bon on est pas là pour faire de la programmation graphique.*/
		if(this->get_FSM() == QUESTION)
		{
			if(current_question_type == 3)
			{
				textbox_vect.back().pollEvent(this->ev);
				if(this->ev.key.code == sf::Keyboard::Enter) 
				{
					question_answered = true; //set flag
					if(textboxQuestion_vector.back()->is_answer(textbox_vect.back().getString()) == 1) //si la reponse est correcte
					{
						score += textboxQuestion_vector.back()->get_points();
						answer_is_correct = true;
					}
					else 
					{
						answer_is_correct = false;
					}
					textbox_vect.back().setString(""); //on reset la textbox entre les questions
				}
			}
		}

		//gestion fermeture de la fenetre quand l'utilisateur appuie sur echap
		if (this->ev.type == sf::Event::KeyPressed)
		{
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
		}
		if (this->ev.type == sf::Event::Closed) {this->window->close();} //fermeture de la fenetre quand on appui sur la croix en haut a droite
		
		switch (this->get_FSM()) //switch case en fonction de l'état de la machine à états du jeu 
		{
			case START:  //FSM 0: start, ici on n'a qu'un seul bouton "start" à gerer
				switch (this->ev.type)
				{
				case sf::Event::MouseButtonPressed:
					if (this->ev.mouseButton.button == sf::Mouse::Left)
					{
						if (this->start_button.is_mouse_on(this->window) == 1)
						{
							this->_click_sound.play(); //play click sound
							this->set_FSM(1);
						}
					}
					break;
				} 
				break;

			case QUESTION: //FSM 1 : question

				switch (this->ev.type) //switch imbriqué: ici on decide quel traitement faire en fonction de la variable current_question_type
				{
				case sf::Event::MouseButtonPressed:
					switch (current_question_type)
					{
					case 0: //QCM
						for(int j = 0; j < 4; j++)
						{
							if (current_buttons_list[j].is_mouse_on(this->window) == 1) //si le click était sur un des 4 boutons:
							{
								question_answered = true; //on leve le flag qui indique que l'utilisateur a repondu
								
								this->_click_sound.play(); //play click sound

								if((MCQ_vector.back()->is_answer(j)))  //enfin on regarde si la reponse est correcte
								{
									score += MCQ_vector.back()->get_points(); 
									answer_is_correct = true;
								}
								else {answer_is_correct = false;}
								break;
							}
						}
					break;
					
					case 1:  //Vrai ou faux: fonctionnement similaire aux QCM (case 0) mais avec des boutons en moins et dont le text ne change pas 
						for(int i = 0; i < 2; ++i)
						{
							if (current_buttons_list[i].is_mouse_on(this->window) == 1)
							{
								question_answered = true; //flag

								this->_click_sound.play(); //play click sound								

								if((TF_vector.back()->is_answer(i)))
								{
									score += TF_vector.back()->get_points(); 
									answer_is_correct = true;
								}
								else {answer_is_correct = false;}
								
								break;
							}
						}					
					break;
					
					case 2: //PhotoMCQ: meme fonctionnement que pour les QCM (case 0). les differences se trouvent au niveau graphique
						
						for(int j = 0; j < 4; j++)
						{
							if (current_buttons_list[j].is_mouse_on(this->window) == 1)
							{
								question_answered = true; //flag question repondue ou pas encore

								this->_click_sound.play(); //play click sound

								if((PhotoMCQ_vector.back()->is_answer(j)))
								{
									score += PhotoMCQ_vector.back()->get_points(); 
									answer_is_correct = true;
								}
								else {answer_is_correct = false;}

								break;
							}
						}				
					break; //break du case photo qcm

				break;  //break du case sf::Event::MouseButtonPressed:
				}
			}
		}
	}
}
		

//fonction qui met a jour le jeu. Ici, elle ne fait qu'appeller pollEvents mais on l'a laissé quand même pour des raisons de modularité
void Game::update()
{
	this->pollEvents();
}


/*fonction qui affiche les texts, les photos, les boutons et les textbox sur l'écran 
selon l'etat de la machine a etat du jeu et le type de la question courante.*/
void Game::render()
{
	this->window->clear(sf::Color(31,100,32, 125));

	//message bienvenue:
	sf::Font fnt;
	fnt.loadFromFile("fonts/open-sans.ttf");
	sf::Text welcome_text("Quizz coupe du monde! Pour jouer, appuyez sur le bouton Start.", fnt, 35);
	sf::Text goodbye_text(" ", fnt, 35);

	//switch machine à états du jeu:
	switch(this->get_FSM())
	{

	case START:		//état écran start	

		this->window->draw(this->start_button); //bouton start
		this->window->draw(welcome_text); //text "bienvenue"
		break;

	case QUESTION:	//état partie en cours

		this->window->clear(sf::Color(31,100,32, 125));
		switch(current_question_type)
		{
		case 0: //si question MCQ
		{
			//ici on prepare les 4 boutons avec les choix possibles de la question courante puis on les affiche:
			int temp_choice_index = 0;
			for (auto it = current_buttons_list.begin(); it !=  current_buttons_list.end(); ++it)
			{
				(*(it)).set_button_text(MCQ_vector.back()->_choices[temp_choice_index]);
				this->window->draw(*(it));
				temp_choice_index++;
			}

			//on affiche le texte de la question
			this->window->draw(sf::Text(MCQ_vector.back()->get_text(),fnt, 25));


			if(question_answered == true)
			{
				//affichage de la reponse pendant 1 seconde
				sf::Text temp_text;
				temp_text.setCharacterSize(20);
				temp_text.setFont(openS);

				if(answer_is_correct == false) { temp_text.setString("Votre reponse est incorrecte! La reponse correcte est: " + MCQ_vector.back()->_choices[MCQ_vector.back()->get_i_answer()]); }
				else
				{	
					answer_is_correct == false; //on remet le flag a son par défaut
					temp_text.setString("Votre reponse est correcte!");
				}
				temp_text.setPosition(sf::Vector2f(0, 150));
				this->window->clear(sf::Color(31,100,32, 125));
				this->window->draw(temp_text);
				this->window->display();
				sleep(2);
				
				//puis on baisse le flag question_answerd pour permetter au jeu d'avancer puis on sort la question du vecteur
				question_answered = false;
				MCQ_vector.pop_back(); 
				if (MCQ_vector.empty()) {current_question_type = 1;}  //enfin on verifie s'il n'y a plus de questions de ce type avant de passer au suivant

			}

			break;
		}	

		case 1: // Si question TrueFalse
		{
			//std::cout<<*(TF_vector.back());
			//on dessine deux boutons "vrai" ou "faux"
			current_buttons_list[0].set_button_text("Faux");
			current_buttons_list[1].set_button_text("Vrai");
			this->window->draw(current_buttons_list[0]);
			this->window->draw(current_buttons_list[1]);

			//on affiche le texte de la question courante
			this->window->draw(sf::Text(TF_vector.back()->get_text(),fnt, 25));

			//et quand le joueur repond on traite puis on commence a preparer la question suivante
			if(question_answered == true) 
			{
				//affichage de la reponse pendant 1 seconde
				sf::Text temp_text;
				temp_text.setCharacterSize(50);
				temp_text.setFont(openS);

				if(answer_is_correct == false) { temp_text.setString("Votre reponse est incorrecte!"); }
				else
				{	
					answer_is_correct == false; //on remet le flag a son par défaut
					temp_text.setString("Votre reponse est correcte!");
				}
				temp_text.setPosition(sf::Vector2f(175, 150));
				this->window->clear(sf::Color(31,100,32, 125));
				this->window->draw(temp_text);
				this->window->display();
				sleep(1);
				
				//puis on baisse le flag question_answerd pour permetter au jeu d'avancer puis on sort la question du vecteur 
				question_answered = false;
				TF_vector.pop_back();
				if (TF_vector.empty()) {current_question_type = 2;} //enfin on verifie s'il n'y a plus de questions de ce type avant de passer au suivant
			}
			break;
		}

		case 2: //qcm avec photo
		{
			//Pour les commentaires du code: cf. case 0 ou QCM sans photo car il n'y a qu'une seule ligne de differente!
			int temp_choice_index = 0;
			for (auto it = current_buttons_list.begin(); it !=  current_buttons_list.end(); ++it)
			{
				(*(it)).set_button_text(PhotoMCQ_vector.back()->_choices[temp_choice_index]);
				this->window->draw(*(it));
				temp_choice_index++;
			}

			this->window->draw(sf::Text(PhotoMCQ_vector.back()->get_text(), fnt, 25));
			this->window->draw(PhotoMCQ_vector.back()->get_sprite());  //c'est cette ligne là c'est juste l'affichage de l'image lol
			if(question_answered == true)
			{

				sf::Text temp_text;
				temp_text.setCharacterSize(20);
				temp_text.setFont(openS);

				if(answer_is_correct == false) { temp_text.setString("Votre reponse est incorrecte! La reponse correcte est: " + PhotoMCQ_vector.back()->_choices[PhotoMCQ_vector.back()->get_i_answer()]); }
				else
				{	
					answer_is_correct == false; //on remet le flag a son par défaut
					temp_text.setString("Votre reponse est correcte!");
				}
				temp_text.setPosition(sf::Vector2f(0, 150));
				this->window->clear(sf::Color(31,100,32, 125));
				this->window->draw(temp_text);
				this->window->display();
				sleep(2);
				
				question_answered = false;
				PhotoMCQ_vector.pop_back(); 
				if (PhotoMCQ_vector.empty()) {current_question_type = 3;} 
			}
			
			break;
		}	

		case 3: //test text box
		{
			this->window->draw(sf::Text(textboxQuestion_vector.back()->get_text(), openS, 20));
			textbox_vect.back().draw();

			if(question_answered == true)
			{

				//on baisse le flag question_answerd pour permetter au jeu d'avancer puis on sort la question du vecteur
				question_answered = false;
				textboxQuestion_vector.pop_back(); 
				if (textboxQuestion_vector.empty()) {this->set_FSM(END);} 
		
			}

			
			break;
		}

		}
		break;

	case END:
			string message("Merci d'avoir joue ! \nVotre score est de :\n");
			message += to_string(score) + " sur 20 ";
			goodbye_text.setString(message);
			goodbye_text.setPosition(250,100);
			
			this->window->draw(goodbye_text);
			this->window->display();
			sleep(3);
			exit(0);

		break;
	}
	this->window->display();
}



////////////////////////////////////UTILITY FUNCTIONS////////////////////////////////////////////////////////////


//Load all the TFQ. Return 0 if something wrong happened, else 1.
int Game::loadTFQ(vector<TrueFalse*> &TFTable)
{
	ifstream file("questions/listQTF.txt");
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
	ifstream file("questions/listMCQ.txt");
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

int Game::loadPhotoMCQ(vector<PhotoMCQ*> &PhotoMCQTable)
{
	ifstream file("questions/listPhotoMCQ.txt");
	if(!file)
	{
		cout << "Error :  Can't open listPhotoMCQ.txt" << endl;
		return 0;
	}

	char sentence[256];
	int value;
	PhotoMCQ* pPhotoMCQuestion;
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

		file.getline(sentence, 256);
		string img_path(sentence);

		pPhotoMCQuestion = new PhotoMCQ(question, stoi(score),
		 {reponseA, reponseB, reponseC, reponseD}, stoi(answer), img_path);
		PhotoMCQTable.push_back(pPhotoMCQuestion);
	}

	return 1;
}


int Game::loadTBQ(vector<textboxQuestion*> &TBQTable)
{
	ifstream file("questions/listTBQ.txt");
	if(!file)
	{
		cout << "Error :  Can't open listTBQ.txt" << endl;
		return 0;
	}

	char sentence[256];
	int value;
	textboxQuestion* pTBQuestion;
	while(file.getline(sentence, 256))
	{

		string question(sentence);

		file.getline(sentence,256);
		string reponse(sentence);

		file.getline(sentence,256);
		string score(sentence);

		pTBQuestion = new textboxQuestion(question, stoi(score), reponse);
		TBQTable.push_back(pTBQuestion);
	}

	return 1;
}
