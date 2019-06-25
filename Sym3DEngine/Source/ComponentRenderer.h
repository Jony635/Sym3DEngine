#pragma once

#include "Component.h"

class ComponentRenderer : public Component
{
public:
	ComponentRenderer(GameObject* gameObject);


public:
	virtual void Render() = 0;
};