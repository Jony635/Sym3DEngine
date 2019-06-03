#include "ModuleWindow.h"

#include "SDL/include/SDL.h"

bool ModuleWindow::Init()
{
	flags |= 0;
	flags |= SDL_WINDOW_RESIZABLE;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("ExampleWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 840, 480, flags);

	if (!window)
	{
		return false;
	}

	return true;
}

bool ModuleWindow::CleanUp()
{
	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	SDL_Quit();

	return true;
}
