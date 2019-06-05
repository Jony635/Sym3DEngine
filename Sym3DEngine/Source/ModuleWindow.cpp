#include "ModuleWindow.h"

#include "SDL/include/SDL.h"

bool ModuleWindow::Init()
{
	flags |= SDL_WINDOW_OPENGL;
	flags |= SDL_WINDOW_RESIZABLE;
	flags |= SDL_WINDOW_SHOWN;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	window = SDL_CreateWindow("ExampleWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, flags);

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
