#include "Application.h"
#include "ModuleRenderer.h"

#include "ComponentMeshRenderer.h"

#include "SDL/include/SDL.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"

#include "ImGUI/include/imgui.h"
#include "MathGeoLib/include/Math/float4x4.h"

#include <string>

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
uint ComponentMeshRenderer::cubeVAO = 0u;

ComponentMeshRenderer::ComponentMeshRenderer(GameObject* gameObject) : ComponentRenderer(gameObject, ComponentType::MESHRENDERER)
{}

void ComponentMeshRenderer::InitializeShapesData()
{
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);

	glGenBuffers(1, &cubeVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertex), cubeVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);

	glGenBuffers(1, &cubeIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndex), cubeIndex, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u); 
}

void ComponentMeshRenderer::Render()
{
	glBindVertexArray(cubeVAO);

	glUseProgram(App->renderer->shaderProgram);

	uint pMatrixLoc = glGetUniformLocation(App->renderer->shaderProgram, "projectionMatrix");

	glUniformMatrix4fv(pMatrixLoc, 1, GL_FALSE, math::float4x4::identity.ptr());

	uint mvMatrixLoc = glGetUniformLocation(App->renderer->shaderProgram, "modelViewMatrix");
	glUniformMatrix4fv(mvMatrixLoc, 1, GL_FALSE, math::float4x4::identity.ptr());
	
	//VERTEX POSITIONS

	uint vPositionLoc = glGetAttribLocation(App->renderer->shaderProgram, "vertexPosition");

	glBindBuffer(GL_ARRAY_BUFFER, ComponentMeshRenderer::cubeVertexBuffer);

	glEnableVertexAttribArray(vPositionLoc);

	glVertexAttribPointer(vPositionLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ComponentMeshRenderer::cubeIndexBuffer);

	glDrawElements(GL_TRIANGLES, ComponentMeshRenderer::cubeNumIndex, GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

	glDisableVertexAttribArray(vPositionLoc);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	glUseProgram(NULL);

	glBindVertexArray(NULL);

	GLenum error;
	while (error = glGetError() != GL_NO_ERROR)
	{
		const char* errorString = (const char*)glewGetErrorString(error);

		int a = 2;
	}
}

void ComponentMeshRenderer::OnInspector()
{
	if (ImGui::CollapsingHeader((std::string("Mesh Renderer##") + std::to_string(UUID)).data()))
	{
		if (ImGui::Checkbox((std::string("Active##") + std::to_string(UUID)).data(), &active))
		{
			active = !active;
			ToggleActive();
		}
		
		ImGui::SameLine();

		ImGui::AlignTextToFramePadding();
		ImGui::Text(" UUID: %u", UUID);
	}
}
