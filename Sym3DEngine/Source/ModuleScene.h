#pragma once

#include "Module.h"
#include "Selection.h"

#include <vector>

class GameObject;

class ModuleScene : public Module
{
public:
	ModuleScene(bool createRoot = true);
	bool Update();

public:
	GameObject* CreateGameObject();
	void GameObjectHierarchyClicked(GameObject* gameObject);
	void DeselectAll();

	void EraseGameObject(GameObject* gameObject);

public:
	GameObject* root = nullptr;

	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> static_gos;
	std::vector<GameObject*> dynamic_gos;

	std::vector<Selection> selections;
};