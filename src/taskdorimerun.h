#include "task.h"
#include "time.h"

SDL_Texture* dorimeRunTexture;
SDL_Texture* runSkyTexture;
SDL_Texture* runTreesTexture;
SDL_Texture* runGroundTexture;

void initTaskDorimeRun(SDL_Renderer* pRenderer) {
	SDL_Surface* image = SDL_LoadBMP("assets/ameno-walk.bmp");
	dorimeRunTexture = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
	image = SDL_LoadBMP("assets/run-sky.bmp");
	runSkyTexture = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
	image = SDL_LoadBMP("assets/run-trees.bmp");
	runTreesTexture = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
	image = SDL_LoadBMP("assets/run-ground.bmp");
	runGroundTexture = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
}

void printTaskDorimeRun(Task this, SDL_Renderer* pRenderer) {
	SDL_SetRenderDrawColor(pRenderer, 128, 128, 128, 255);
	SDL_Rect rw = {W/4, H/4, W/2, H/2};
	SDL_RenderFillRect(pRenderer, &rw); // fond gris
	int w, h;
	SDL_Rect rv = {3*W/10, 3*H/10, 4*W/10, 4*H/10};
	// ciel
	SDL_QueryTexture(runSkyTexture, NULL, NULL, &w, &h);
	SDL_Rect rs = {w/6*this.vars[0]/400, 0, 5*w/6, h};
	SDL_RenderCopy(pRenderer, runSkyTexture, &rs, &rv);
	// arbres
	SDL_QueryTexture(runTreesTexture, NULL, NULL, &w, &h);
	SDL_Rect rt = {w/6*this.vars[0]/200, 0, 2*w/3, h};
	SDL_RenderCopy(pRenderer, runTreesTexture, &rt, &rv);
	// sol
	SDL_QueryTexture(runGroundTexture, NULL, NULL, &w, &h);
	SDL_Rect rg = {w/6*this.vars[0]/100, 0, w/3, h};
	SDL_RenderCopy(pRenderer, runGroundTexture, &rg, &rv);
	// sprite souris
	h = 64;
	SDL_QueryTexture(dorimeRunTexture, NULL, NULL, NULL, &h);
	SDL_Rect tile = {h*(this.vars[0]/3%6), 0, h, h};
	SDL_Rect r = {W/2-H/18, 4*H/9, H/9, H/9};
	SDL_RenderCopy(pRenderer, dorimeRunTexture, &tile, &r);
	if (this.vars[0] > 0 && this.vars[0] < 400) this.vars[0]++;
	if (this.vars[0] == 400 && !this.completed) this.completed = 1;
}

void onEventTaskDorimeRun(Task this, SDL_Event event) {
	switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT && this.vars[0] == 0) this.vars[0] = 1;
			break;
		case SDL_MOUSEBUTTONDOWN:
			
			break;
	}
}

Task newTaskDorimeRun() {
	Task t = newTask();
	t.vars = malloc(1 * sizeof(int));
	t.vars[0] = 0; // progress
	t.print = &printTaskDorimeRun;
	t.onEvent = &onEventTaskDorimeRun;
	return t;
}
