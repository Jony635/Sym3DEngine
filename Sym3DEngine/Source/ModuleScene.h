#pragma once

#include "Module.h"

#include <vector>

class GameObject;

class ModuleScene : public Module
{
public:

	ModuleScene(bool createRoot = true);

	GameObject* root = nullptr;

	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> static_gos;
	std::vector<GameObject*> dynamic_gos;
};