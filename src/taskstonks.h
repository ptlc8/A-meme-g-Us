#include "task.h"
#include "time.h"

SDL_Texture* stonksBgTexture;
SDL_Texture* stonksGuyTexture;
SDL_Texture* stonksNotTexture;
SDL_Texture* stonksDot;
SDL_Texture* stonksArrow;

void initTaskStonks(SDL_Renderer* pRenderer) {
	SDL_Surface* image = SDL_LoadBMP("assets/stonks-bg.bmp");
	stonksBgTexture = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
	image = SDL_LoadBMP("assets/stonks-guy.bmp");
	stonksGuyTexture = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
	image = SDL_LoadBMP("assets/stonks-not.bmp");
	stonksNotTexture = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
	image = SDL_LoadBMP("assets/stonks-dot.bmp");
	stonksDot = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
	image = SDL_LoadBMP("assets/stonks-arrow.bmp");
	stonksArrow = SDL_CreateTextureFromSurface(pRenderer, image);
	SDL_FreeSurface(image);
}

void printTaskStonks(Task this, SDL_Renderer* pRenderer) {
	SDL_SetRenderDrawColor(pRenderer, 128, 128, 128, 255);
	SDL_Rect rw = {W/4, H/4, W/2, H/2};
	SDL_RenderFillRect(pRenderer, &rw);
	SDL_RenderCopy(pRenderer, stonksBgTexture, NULL, &rw);
	//if (this.vars[0] > 3)
		SDL_RenderCopy(pRenderer, (this.vars[2]>this.vars[6]) ? stonksGuyTexture : stonksNotTexture, NULL, &rw);
	SDL_SetRenderDrawColor(pRenderer, 244, 123, 30, 255);
	for (int i = 0; i < 5; i++) {
		if (i < this.vars[0]) {
			for (int j = 0; j < 8; j++)
				SDL_RenderDrawLine(pRenderer, 2*W/5 + W/14*i, H/3 + H/30*this.vars[i+2] - 4+j, 2*W/5 + W/14*(i+1), H/3 + H/30*this.vars[i+2+1] - 4+j);
		} else {
			SDL_Rect r = {2*W/5 + W/14*i - 8, H/3 + H/30*this.vars[i+2] - 8, 16, 16};
			SDL_RenderCopy(pRenderer, stonksDot, NULL, &r);
		}
	}
	if (this.vars[1] == 0) {
		SDL_Rect ra = {2*W/5 + W/14*(this.vars[0]) - 16, H/3 + H/30*this.vars[this.vars[0]+2] - 16, 32, 32};
		SDL_RenderCopy(pRenderer, stonksArrow, NULL, &ra);
	} else {
		float x1 = 2*W/5 + W/14*this.vars[0];
		float y1 = H/3 + H/30*this.vars[2+this.vars[0]];
		float x2 = 2*W/5 + W/14*(this.vars[0]+1);
		float y2 = H/3 + H/30*this.vars[2+this.vars[0]+1];
		float xp = x1 + (x2-x1)*this.vars[1]/100;
		float yp = y1 + (y2-y1)*this.vars[1]/100;
		SDL_RenderDrawLine(pRenderer, x1, y1, xp, yp);
		SDL_Rect ra = {xp - 16, yp - 16, 32, 32};
		SDL_RenderCopy(pRenderer, stonksArrow, NULL, &ra);
	}
}

void onEventTaskStonks(Task this, SDL_Event event) {
	float d, dMouse;
	switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) this.vars[1] = 0;
			break;
		case SDL_MOUSEBUTTONDOWN:
			
			break;
		case SDL_MOUSEMOTION:
			if (!(event.motion.state & SDL_BUTTON_LMASK)) break;
			d = sqrtf(powf(this.vars[2+this.vars[0]]*H/30 - this.vars[2+this.vars[0]+1]*H/30, 2) + powf(W/14, 2));
			dMouse = sqrtf(powf(H/3+this.vars[2+this.vars[0]+1]*H/30 - event.motion.y, 2) + powf(2*W/5+W/14*(this.vars[0]+1) - event.motion.x, 2));
			if (dMouse < 20) {
				this.vars[0]++;
				this.vars[1] = 0;
				if (this.vars[0] == 5) this.completed = 1;
			} else {
				this.vars[1] = dMouse >= d ? 0 : (1-dMouse/d)*100;
			}
			break;
	}
}

Task newTaskStonks() {
	Task ts = newTask();
	ts.vars = malloc(7 * sizeof(int));
	srand(time(NULL));
	ts.vars[0] = 0;
	ts.vars[1] = 0;
	for (int i = 0; i < 5; i++) { // progressP + progress + pos y des points
		ts.vars[i+2] = rand()%10;
		printf("%d\n", ts.vars[i+2]);
	}
	ts.print = &printTaskStonks;
	ts.onEvent = &onEventTaskStonks;
	return ts;
}
