#pragma once

#include "Module.h"

class ModuleRenderer : public Module
{
private:
	bool Init();
	bool Start();
	bool PostUpdate();

public:
	inline const void* GetContext() const { return context; }

public:
	bool vsync = true;

private:
	void* context = 0u;


};