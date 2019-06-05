#pragma once

#include <vector>

class Module;
class ModuleWindow;
class ModuleRenderer;
class ModuleInput;

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

public:
	ModuleWindow* window = nullptr;
	ModuleRenderer* renderer = nullptr;
	ModuleInput* input = nullptr;


private:
	AppState state;
	std::vector<Module*> modules;
};

extern Application* App;