#pragma once

#include "ComponentRenderer.h"

class ComponentMeshRenderer : public ComponentRenderer
{
public:
	ComponentMeshRenderer(GameObject* gameObject);

	static void InitializeShapesData();

private:
	void Render();
	void OnInspector();

private:
	//CUBE DATA
	static float cubeVertex[8 * 3];
	static unsigned int cubeIndex[12 * 3];
	static const uint cubeNumVertex = 8u;
	static const uint cubeNumIndex = 36u;

		//OPENGL BUFFERS
		static uint cubeVertexBuffer;
		static uint cubeIndexBuffer;
		static uint cubeVAO;


	//---------------------------------
	//MORE STANDARD SHAPES
};