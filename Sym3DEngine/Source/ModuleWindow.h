#pragma once

#include "Module.h"
#include <stdint.h>

struct SDL_Window;

class ModuleWindow : public Module
{
private:
	bool Init();
	bool CleanUp();

public:
	inline const SDL_Window* GetWindow() const { return window; }

private:
	SDL_Window* window = nullptr;

	uint32_t flags = 0u;
};