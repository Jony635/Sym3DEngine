#pragma once

#include <vector>
#include "Globals.h"
#include <random>

class Module;
class ModuleWindow;
class ModuleRenderer;
class ModuleInput;
class ModuleImGUI;
class ModuleScene;
class ModuleTime;

class Application
{
	enum AppState
	{
		NO_STATE = -1,
		START,
		UPDATE,
		FINISH,
		FINISH_ERROR
	};

	friend int main(int argc, char* argv[]);


public:
	Application();
	bool Start();
	bool Update();
	bool CleanUp();

public:
	inline void FinishApp() { state = AppState::FINISH; }

	uint GetRandomUUID();

public:
	ModuleWindow* window = nullptr;
	ModuleRenderer* renderer = nullptr;
	ModuleInput* input = nullptr;
	ModuleImGUI* imgui = nullptr;
	ModuleScene* scene = nullptr;
	ModuleTime* time = nullptr;

private:
	AppState state;
	std::vector<Module*> modules;

	std::random_device rd;
};

extern Application* App;