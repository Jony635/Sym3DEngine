#pragma once

#include "Module.h"

struct SDL_Renderer;

class ModuleRenderer : public Module
{
private:
	bool Init();
	bool Start();


private:
	SDL_Renderer* renderer = nullptr;
};