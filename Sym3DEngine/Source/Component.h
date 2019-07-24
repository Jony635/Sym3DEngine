#pragma once

#include "Globals.h"

enum class ComponentType
{
	NO_TYPE = -1,
	TRANSFORM,
	MESHRENDERER,
	RENDERER2D,
	CAMERA
};

class GameObject;

class Component
{
public:
	Component(GameObject* gameObject, ComponentType type);

	virtual void OnInspector() {}
	virtual void OnTransformChanged() {}

public:
	inline bool IsActive() const { return active; }
	bool IsTreeActive() const;
	inline void ToggleActive() { active = !active; }

protected:
	bool active = true;
	ComponentType type = ComponentType::NO_TYPE;
	uint UUID = 0u;
	GameObject* gameObject = nullptr;
};