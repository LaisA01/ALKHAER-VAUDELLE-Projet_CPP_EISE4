#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "TimedMCQ.h"
#include "game.h"

int main(void)
{
	//Init game
	Game game;

	//game loop
	while (game.running())   //tant que le joue tourne, exécuter:
	{
		game.update();   //la boucle de base d'un jeu: mettre à jour toutes les variables.
		game.render();   //puis afficher ce qu'il y a à afficher en fonction de ces variables.
	}

	return 0;
}


