#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleRenderer.h"
#include "ModuleInput.h"

Application::Application()
{
	window = new ModuleWindow();
	renderer = new ModuleRenderer();
	input = new ModuleInput();

	modules.push_back(input);
	modules.push_back(window);
	modules.push_back(renderer);

	state = AppState::START;
}

bool Application::Start()
{
	bool ret = true;

	for (int i = 0; i < modules.size() && ret; ++i)
	{
		ret = modules[i]->Init();
	}

	for (int i = 0; i < modules.size() && ret; ++i)
	{
		ret = modules[i]->Start();
	}

	if (ret)
		return true;
	else
		return false;
}

bool Application::Update()
{
	bool ret = true;

	for (int i = 0; i < modules.size() && ret; ++i)
	{
		ret = modules[i]->PreUpdate();
	}

	for (int i = 0; i < modules.size() && ret; ++i)
	{
		ret = modules[i]->Update();
	}

	for (int i = 0; i < modules.size() && ret; ++i)
	{
		ret = modules[i]->PostUpdate();
	}

	if (ret)
		return true;
	else
		return false;
}
