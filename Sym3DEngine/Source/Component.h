#pragma once

#include "Globals.h"

enum class ComponentType
{
	NO_TYPE = -1,
	TRANSFORM



};

class GameObject;

class Component
{
public:
	Component(GameObject* gameObject);

	virtual void OnInspector() {}

protected:
	uint UUID = 0u;
	GameObject* gameObject = nullptr;
};