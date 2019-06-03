#include "Application.h"

#include "Module.h"
#include "ModuleInput.h"

Application::Application()
{
	input = new ModuleInput();

	modules.push_back(input);

	state = AppState::START;
}

bool Application::Start()
{
	bool ret = true;
	for (int i = 0; i < modules.size() && ret; ++i)
	{
		ret = modules[i]->Start();
	}

	if (ret)
		return true;
	else
		return false;
}
