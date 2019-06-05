#include "ModuleWindow.h"

#include "SDL/include/SDL.h"

bool ModuleWindow::Init()
{
	SDL_Init(SDL_INIT_VIDEO);

	flags |= SDL_WINDOW_OPENGL;
	flags |= SDL_WINDOW_RESIZABLE;
	flags |= SDL_WINDOW_SHOWN;

	window = SDL_CreateWindow("ExampleWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, flags);

	if (!window)
	{
		//TODO: LOG ERRORS
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
