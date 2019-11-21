#include "Application.h"
#include "ModuleInput.h"
#include "ModuleImGUI.h"

KeyState ModuleInput::GetKey(uint key)
{
	return keyboardState[key];
}

bool ModuleInput::PreUpdate()
{
	int arraySize;
	const Uint8* keyboard = SDL_GetKeyboardState(&arraySize);

	for (int i = 0; i < arraySize; ++i)
	{
		switch (keyboardState[i])
		{
			case KeyState::KEY_IDLE:
			{
				if (keyboard[i] == 1)
					keyboardState[i] = KeyState::KEY_DOWN;
				break;
			}
			case KeyState::KEY_DOWN:
			{
				if (keyboard[i] == 1)
					keyboardState[i] = KeyState::KEY_REPEAT;
				else
					keyboardState[i] = KeyState::KEY_UP;
				break;
			}
			case KeyState::KEY_REPEAT:
			{
				if (keyboard[i] == 0)
					keyboardState[i] = KeyState::KEY_UP;
				break;
			}
			case KeyState::KEY_UP:
			{
				if (keyboard[i] == 1)
					keyboardState[i] = KeyState::KEY_DOWN;
				else
					keyboardState[i] = KeyState::KEY_IDLE;
				break;
			}

		}
	}

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
