#pragma once

#include <iostream>
#include "Module.h"

enum KeyState
{
	KEY_IDLE,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	KeyState GetKey(uint key);
private:
	bool PreUpdate();

private:
	KeyState keyboardState[300];
};