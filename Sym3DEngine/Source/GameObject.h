#pragma once

#include <string>
#include <vector>

#include "Globals.h"

#include "Component.h"

class ComponentTransform;
class ComponentRenderer;
class ComponentCamera;

class GameObject
{
	friend class ModuleScene;
	friend class PanelHierarchy;

public:
	GameObject(GameObject* parent = nullptr);

	inline bool IsActive() { return active; }
	inline void ToggleActive() { active = !active; }

	inline bool IsStatic() { return static_go; }
	inline void ToggleStatic() { static_go = !static_go; }

	inline std::string GetName() { return name; }
	inline void SetName(std::string name) { this->name = name; }

	inline uint GetUUID() { return UUID; }

	void OnInspector();

	Component* AddComponent(ComponentType type);
	void AddComponent(Component* component = nullptr);

	void AddChild(GameObject* gameObject = nullptr);
	void EraseChild(GameObject* child);

	void SetParent(GameObject* newParent);

	void OnTransformChanged();

public:
	std::vector<GameObject*> childs;
	std::vector<Component*> components;

	GameObject* parent = nullptr;

	//Quick Accessors
	ComponentTransform* transform = nullptr;
	ComponentRenderer* renderer = nullptr;
	ComponentCamera* camera = nullptr;

private:
	std::string name = "GameObject";
	bool active = true;
	bool static_go = false;
	uint UUID = 0u;
	bool selected = false;
};