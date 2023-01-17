#include "game.h"
#include "TimedMCQ.h"
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


