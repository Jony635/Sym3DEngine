#pragma once

#include "Globals.h"

enum SelectionType
{
	GAMEOBJECT_SELECTION = 0x100
};

struct GameObjectSelection
{
	uint type;
	void* gameObject;
};

union Selection
{
	uint type;
	GameObjectSelection goSelection;
};