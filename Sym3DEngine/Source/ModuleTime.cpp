#include "ModuleTime.h"

#include "SDL/include/SDL.h"

ModuleTime::ModuleTime()
{

}

ModuleTime::~ModuleTime()
{

}

bool ModuleTime::PreUpdate()
{
	dt = lastFrameMS == 0.0f ? 0.0f : (SDL_GetTicks() - lastFrameMS) / 1000;

	lastFrameMS = SDL_GetTicks();
	return true;
}

bool ModuleTime::Update()
{
	return true;
}

bool ModuleTime::PostUpdate()
{
	return true;
}
