#pragma once

#include <string>
#include "Globals.h"

class GameObject
{
	friend class ModuleScene;
	friend class PanelHierarchy;

public:
	GameObject();

	inline bool IsActive() { return active; }
	inline void ToggleActive() { active = !active; }

	inline bool IsStatic() { return static_go; }
	inline void ToggleStatic() { static_go = !static_go; }

	inline std::string GetName() { return name; }
	inline void SetName(std::string name) { this->name = name; }

	inline uint GetUUID() { return UUID; }

	void OnInspector();

public:
	std::vector<GameObject*> childs;

private:
	std::string name = "GameObject";
	bool active = true;
	bool static_go = false;
	uint UUID = 0u;
	bool selected = false;
};