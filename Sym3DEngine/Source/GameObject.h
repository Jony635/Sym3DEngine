#pragma once

#include <string>
#include "Globals.h"

class GameObject
{
public:
	GameObject();

	inline bool IsActive() { return active; }
	inline void ToggleActive() { active = !active; }

	inline bool IsStatic() { return static_go; }
	inline void ToggleStatic() { static_go = !static_go; }

	inline std::string GetName() { return name; }
	inline void SetName(std::string name) { this->name = name; }

	inline uint GetUUID() { return UUID; }

private:
	std::string name;
	bool active = true;
	bool static_go = false;
	uint UUID = 0u;
};