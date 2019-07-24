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
	bool useInternalShapes = true;
	uint internalShapeID = 0;

	//CUBE DATA
	static float cubeVertex[];
	static unsigned int cubeIndex[];
	static const uint cubeNumVertex = 8u;
	static const uint cubeNumIndex = 36u;

		//OPENGL BUFFERS
		static uint cubeVertexBuffer;
		static uint cubeIndexBuffer;
		static uint cubeVAO;

	//PYRAMID DATA
		static float pyramidVertex[];
		static unsigned int pyramidIndex[];
		static const uint pyramidNumVertex = 5u;
		static const uint pyramidNumIndex = 18u;

		//OPENGL BUFFERS
		static uint pyramidVertexBuffer;
		static uint pyramidIndexBuffer;
		static uint pyramidVAO;

	//---------------------------------
	//MORE STANDARD SHAPES
};