#pragma once

#include "Module.h"

class ModuleTime : public Module
{
public:
	ModuleTime();
	virtual ~ModuleTime();

	bool PreUpdate();
	bool Update();
	bool PostUpdate();

public:
	inline float GetDt() const { return dt; }

private:

	float lastFrameMS = 0.0f;

	float dt = 0.0f;
	float realDt = 0.0f;
};