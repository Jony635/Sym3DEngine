#pragma once

#include "Module.h"
#include "Component.h"

#include <vector>

class ComponentRenderer;

class ModuleRenderer : public Module
{
private:
	bool Init();
	bool Start();
	bool Update();
	bool PostUpdate();

public:
	inline const void* GetContext() const { return context; }

	ComponentRenderer* AddRenderer(ComponentType type, GameObject* gameObject);
	ComponentRenderer* AddRenderer(ComponentRenderer* renderer);
	bool EraseRenderer(ComponentRenderer* renderer);

public:
	bool vsync = true;

	//Draw to texture stuff
	uint fbo = 0;
	uint texColorBuffer = 0;
	uint rbo;

	//Shader stuff
	uint shaderProgram = 0u;

private:
	void* context = 0u;
	std::vector<ComponentRenderer*> renderers;

};