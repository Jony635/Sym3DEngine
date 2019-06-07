#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleRenderer.h"
#include "ModuleInput.h"
#include "ModuleImGUI.h"
#include "ModuleScene.h"

Application::Application()
{
	window = new ModuleWindow();
	renderer = new ModuleRenderer();
	input = new ModuleInput();
	imgui = new ModuleImGUI();
	scene = new ModuleScene();

	modules.push_back(input);
	modules.push_back(window);
	modules.push_back(scene);
	modules.push_back(imgui);
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

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = modules.size() - 1; i >= 0 && ret; --i)
	{
		ret = modules[i]->CleanUp();
	}

	if (ret)
		return true;
	else
		return false;
}

uint Application::GetRandomUUID()
{
	std::default_random_engine e1(rd());

	std::uniform_int_distribution<uint32_t> uniform_dist(0, UINT32_MAX);
	uint number = uniform_dist(e1);

	return number;
}
