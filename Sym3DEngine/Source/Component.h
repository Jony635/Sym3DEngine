#pragma once

#include "Globals.h"

enum class ComponentType
{
	NO_TYPE = -1,
	TRANSFORM



};

class Component
{
public:
	Component();

	virtual void OnInspector() {}

protected:
	uint UUID = 0u;
};