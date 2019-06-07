#include "Application.h"
#include "ModuleInput.h"
#include "ModuleImGUI.h"

#include "SDL/include/SDL.h"

bool ModuleInput::Init()
{



	return true;
}

bool ModuleInput::PreUpdate()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		App->imgui->NotifyEvent(event);
		switch (event.type)
		{
			case SDL_EventType::SDL_QUIT:
			{
				App->FinishApp();
				break;
			}
		}
	}

	return true;
}
