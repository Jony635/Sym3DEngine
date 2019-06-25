#include "ComponentMeshRenderer.h"
#include "Glew/include/GL/glew.h"

float ComponentMeshRenderer::cubeVertex[] = 
{
	// front
	-1.0, -1.0,  1.0,
	 1.0, -1.0,  1.0,
	 1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
	// back
	-1.0, -1.0, -1.0,
	 1.0, -1.0, -1.0,
	 1.0,  1.0, -1.0,
	-1.0,  1.0, -1.0
};

uint ComponentMeshRenderer::cubeIndex[] =
{
	// front
	0, 1, 2,
	2, 3, 0,
	// right
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// left
	4, 0, 3,
	3, 7, 4,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// top
	3, 2, 6,
	6, 7, 3
};

uint ComponentMeshRenderer::cubeVertexBuffer = 0u;
uint ComponentMeshRenderer::cubeIndexBuffer = 0u;

ComponentMeshRenderer::ComponentMeshRenderer(GameObject* gameObject) : ComponentRenderer(gameObject)
{}

void ComponentMeshRenderer::InitializeShapesData()
{
	glCreateBuffers(1, &cubeVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertex), cubeVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);

	glCreateBuffers(1, &cubeIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndex), cubeIndex, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u); 
}

void ComponentMeshRenderer::Render()
{
	//TODO: USE PROGRAM, SET ATTRIBUTES, AND RESET USE PROGRAM
}
