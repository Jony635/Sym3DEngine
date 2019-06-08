#pragma once

#include "Module.h"
#include <vector>

union SDL_Event;

class Panel;
class PanelHierarchy;
class PanelInspector;

class ModuleImGUI : public Module
{
public:
	ModuleImGUI();

private:
	bool Start();
	bool PreUpdate();

private:
	void DockSpace();

public:
	void NotifyEvent(SDL_Event event);
	void Draw();

private:
	PanelHierarchy* hierarchy = nullptr;
	PanelInspector* inspector = nullptr;

	std::vector<Panel*> panels;
};