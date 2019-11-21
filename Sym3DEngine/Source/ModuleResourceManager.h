#pragma once

#include "Module.h"

class ModuleResourceManager : public Module
{
	bool Init();
	bool Start();
	bool CleanUp();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
};