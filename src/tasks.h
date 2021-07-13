#include "taskstonks.h"
#include "taskdorimerun.h"
#include "taskcard.h"

#define COMMON_TASK 1
#define SHORT_TASK 2
#define LONG_TASK 3

void initTasks(SDL_Renderer* pRenderer) {
	initTaskStonks(pRenderer);
	initTaskDorimeRun(pRenderer);
	initTaskCard(pRenderer);
}

