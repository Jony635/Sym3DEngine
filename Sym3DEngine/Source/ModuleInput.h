#pragma once

#include <iostream>

#include "Module.h"

class ModuleInput : public Module
{
private:
	bool Init();
	bool PreUpdate();

};