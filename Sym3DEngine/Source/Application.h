#pragma once

#include <vector>

class Module;
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


public:
	ModuleInput* input = nullptr;


private:
	AppState state;

	std::vector<Module*> modules;
};

extern Application* App;