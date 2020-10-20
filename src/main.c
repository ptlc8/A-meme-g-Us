#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>

#define speed 6

typedef struct Player {
	float x;
	float y;
} Player;

int main(int argc, char* argv[]) {
	
	if (SDL_Init(SDL_INIT_VIDEO) == -1) { // Démarrage de la SDL // SDL_INIT_EVENTS ?
		fprintf(stderr, "Erreur d'initialisation de la SDL");
		exit(EXIT_FAILURE);
	}
	
	SDL_Window* pWindow = NULL; // Création de la fenêtre
	pWindow = SDL_CreateWindow("A-meme-g Us - Ambi x BeXws x Rojo x Asphex", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
	
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED); // Création du renderer (pour afficher)
	
	//TTF_Init(); // Démarrage de SDL_ttf pour les textes
	//TTF_Font* font = TTF_OpenFont("assets/elected-office.regular.ttf", 256); // Chargement de la police
	
	// importation de la texture proto-chungus
	SDL_Surface* image = SDL_LoadBMP("assets/proto-chungus.bmp");
	SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
	
	// création d'un player
	Player player = {0,0};
	
	// liste des touches pressées
	int keysHeld[323] = {0};
	
	while (1) {
		SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
		SDL_RenderClear(pRenderer); // Netoyage du SDL_Renderer
		
		int endProgram = 0;
		
		SDL_Event event;
		while (SDL_PollEvent(&event)) { // les events
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
				endProgram = 1;
			
			// récupération des entrées clavier
			if (event.type == SDL_KEYDOWN) keysHeld[event.key.keysym.scancode] = 1;
			if (event.type == SDL_KEYUP) keysHeld[event.key.keysym.scancode] = 0;
		}
		
		// actualisation du player
		float dx = 0;
		float dy = 0;
		if (keysHeld[79] || keysHeld[7]) dx++; // droite
		if (keysHeld[80] || keysHeld[4]) dx--; // gauche
		if (keysHeld[81] || keysHeld[22]) dy++; // bas
		if (keysHeld[82] || keysHeld[26]) dy--; // haut
		float dl = sqrtf(dx*dx+dy*dy);
		if (dl != 0) dx = dx / dl * speed;
		if (dl != 0) dy = dy / dl * speed;
		player.x += dx;
		player.y += dy;
		
		// affichage du player
		SDL_Rect r = {400-48+player.x, 400-48+player.y, 96, 96};
		SDL_RenderCopy(pRenderer, playerTexture, NULL, &r);
		
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
