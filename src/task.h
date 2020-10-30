#include <SDL.h>
#include <SDL_ttf.h>

typedef struct Task {
	void (*print)(struct Task this, SDL_Renderer* renderer);
	void (*onEvent)(struct Task this, SDL_Event event);
	int completed;
	int* vars;
} Task;

Task newTask() {
	Task t;
	t.completed = 0;
	return t;
}

