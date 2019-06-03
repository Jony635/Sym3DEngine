#include <iostream>
#include <stdlib.h>

#include "SDL/include/SDL.h"
#pragma comment(lib, "SDL/SDL2main.lib")
#pragma comment(lib, "SDL/SDL2.lib")

#include "Application.h"

Application* App;

int main(int argc, char* argv[])
{ 
	App = new Application();

	while (App->state != Application::AppState::FINISH && App->state != Application::AppState::FINISH_ERROR)
	{
		switch (App->state)
		{
			case Application::AppState::START:
			{
				bool ret = App->Start();

				if (ret)
					App->state = Application::AppState::UPDATE;
				else
					App->state = Application::AppState::FINISH_ERROR;

				break;
			}
			case Application::AppState::UPDATE:
			{
				break;
			}
		}
	}

	if (App->state == Application::AppState::FINISH)
		return 0;
	else
		return -1;
}