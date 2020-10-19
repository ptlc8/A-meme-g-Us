#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>

int main(int argc, char* argv[]) {
	
	if (SDL_Init(SDL_INIT_VIDEO) == -1) { // Démarrage de la SDL // SDL_INIT_EVENTS ?
		fprintf(stderr, "Erreur d'initialisation de la SDL");
		exit(EXIT_FAILURE);
	}
	
	SDL_Window* pWindow = NULL; // Création de la fenêtre
	pWindow = SDL_CreateWindow("A-meme-g Us - Ambi x BeXws x Rojo x Asphex", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_SHOWN);
	
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); // Création du renderer (pour afficher)
	
	//TTF_Init(); // Démarrage de SDL_ttf pour les textes
	//TTF_Font* font = TTF_OpenFont("assets/elected-office.regular.ttf", 256); // Chargement de la police
	
	while (1) {
		SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
		SDL_RenderClear(pRenderer); // Netoyage du SDL_Renderer
		
		int endProgram = 0;
		
		SDL_Event event;
		while (SDL_PollEvent(&event)) { // les events
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
				endProgram = 1;
		}
		
		if (endProgram) break; // Condition d'arrêt du programme
		
		SDL_RenderPresent(pRenderer); // Affichage
		
		SDL_Delay(1000/30); // Attendre 1/30 seconde
		
	}
	
	//TTF_CloseFont(font); // Libération de la mémoire associée à la police
	//TTF_Quit(); // Arrêt de SDL_ttf
	
	SDL_DestroyRenderer(pRenderer); // Libération de la mémoire du SDL_Renderer
	
	SDL_DestroyWindow(pWindow); // Détruire la fenêtre
	
	SDL_Quit(); // Arrêt de la SDL
	
	return EXIT_SUCCESS;
}
