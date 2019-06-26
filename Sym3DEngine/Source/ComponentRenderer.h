#pragma once

#include "Component.h"

class ComponentRenderer : public Component
{
public:
	ComponentRenderer(GameObject* gameObject, ComponentType type);


public:
	virtual void Render() = 0;
	virtual void OnInspector() = 0;
};