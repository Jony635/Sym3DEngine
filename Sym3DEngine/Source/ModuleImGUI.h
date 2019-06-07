#pragma once

#include "Module.h"
#include <vector>

union SDL_Event;

class Panel;
class PanelHierarchy;

class ModuleImGUI : public Module
{
public:
	ModuleImGUI();

private:

	bool Start();
	bool PreUpdate();

public:
	void NotifyEvent(SDL_Event event);
	void Draw();

private:
	PanelHierarchy* hierarchy = nullptr;

	std::vector<Panel*> panels;
};