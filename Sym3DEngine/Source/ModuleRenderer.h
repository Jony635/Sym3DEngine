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

	//Draw to texture stuff
	uint FramebufferName = 0;
	uint renderedTexture = 0;
	uint depthrenderbuffer;

	//Shader stuff
	uint shaderProgram = 0u;

private:
	void* context = 0u;

};