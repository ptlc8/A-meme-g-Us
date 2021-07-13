#include "task.h"
#include "time.h"

SDL_Texture* cardWalletTexture;
SDL_Texture* cardReaderTexture;
SDL_Texture* cardAnalyserTexture;
SDL_Texture* pictureTexture;

void initTaskCard(SDL_Renderer* pRenderer) {
	SDL_Surface* image = SDL_LoadBMP("assets/card-wallet.bmp");
	cardWalletTexture = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
	image = SDL_LoadBMP("assets/card-reader.bmp");
	cardReaderTexture = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
	image = SDL_LoadBMP("assets/card-analyser.bmp");
	cardAnalyserTexture = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
	image = SDL_LoadBMP("assets/shrek-picture.bmp");
	pictureTexture = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
}

void printTaskCard(Task this, SDL_Renderer* pRenderer) {
	SDL_Rect r = {W/2-H/3, H/6, 2*H/3, 2*H/3};
	SDL_SetRenderDrawColor(pRenderer, 67, 73, 48, 255);
	SDL_RenderFillRect(pRenderer, &r);
	SDL_Rect picR = {W/2+1*H/27, 5*H/6-20*H/78, 2*H/3/3, 20*H/78};
	SDL_RenderCopy(pRenderer, pictureTexture, NULL, &picR);
	SDL_RenderCopy(pRenderer, cardReaderTexture, NULL, &r);
	SDL_RenderCopy(pRenderer, cardAnalyserTexture, NULL, &r);
	SDL_RenderCopy(pRenderer, cardWalletTexture, NULL, &r);
}

void onEventTaskCard(Task this, SDL_Event event) {
	
}

Task newTaskCard() {
	Task t = newTask();
	t.vars = malloc(1 * sizeof(int));
	t.vars[0] = 0; // progress
	t.print = &printTaskCard;
	t.onEvent = &onEventTaskCard;
	return t;
}
