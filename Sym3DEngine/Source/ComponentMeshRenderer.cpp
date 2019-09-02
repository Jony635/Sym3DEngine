#include "Application.h"
#include "ModuleRenderer.h"

#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentMeshRenderer.h"
#include "ComponentCamera.h"

#include "SDL/include/SDL.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"

#include "ImGUI/include/imgui.h"
#include "MathGeoLib/include/Math/float4x4.h"

#include <string>

float ComponentMeshRenderer::cubeVertex[] = 
{
	// front
	-1.0, -1.0,  -1.0, //Bottom-left	0
	 1.0, -1.0,  -1.0, //Bottom-right	1
	 1.0,  1.0,  -1.0, //Top-right		2
	-1.0,  1.0,  -1.0, //Top-left		3
										
	// back								
	-1.0, -1.0,  1.0, //Bottom-left		4
	 1.0, -1.0,  1.0, //Bottom-right	5
	 1.0,  1.0,  1.0, //Top-right		6
	-1.0,  1.0,  1.0, //Top-left		7
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

float ComponentMeshRenderer::pyramidVertex[] =
{
	//BASE:
	1.0, -1.0, 1.0,		//BACK-RIGHT	0
	1.0, -1.0, -1.0,		//FRONT-RIGHT	1
	-1.0, -1.0, -1.0,	//FRONT-LEFT	2
	-1.0, -1.0, 1.0,		//BACK-LEFT		3

	//TOP:
	0.0, 1.0, 0.0		//TOP:			4
};

unsigned int ComponentMeshRenderer::pyramidIndex[]
{
	//BASE:
	0,3,2,
	2,1,0,

	//FRONT:
	2,1,4,
	
	//RIGHT:
	1,0,4,

	//LEFT:
	3,2,4,

	//BACK:
	0,3,4
};

uint ComponentMeshRenderer::pyramidVertexBuffer = 0u;
uint ComponentMeshRenderer::pyramidIndexBuffer = 0u;
uint ComponentMeshRenderer::pyramidVAO = 0u;

ComponentMeshRenderer::ComponentMeshRenderer(GameObject* gameObject) : ComponentRenderer(gameObject, ComponentType::MESHRENDERER)
{}

void ComponentMeshRenderer::InitializeShapesData()
{
	//CUBE:
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
	
	//PYRAMID:
	glGenVertexArrays(1, &pyramidVAO);
	glBindVertexArray(pyramidVAO);

	glGenBuffers(1, &pyramidVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, pyramidVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertex), pyramidVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);

	glGenBuffers(1, &pyramidIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pyramidIndex), pyramidIndex, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);

}

void ComponentMeshRenderer::Render()
{
	if(useInternalShapes)
		switch (internalShapeID)
		{
			case 0:
			{
				glBindVertexArray(cubeVAO);

				glUseProgram(App->renderer->shaderProgram);

				/*uint pMatrixLoc = glGetUniformLocation(App->renderer->shaderProgram, "projectionMatrix");

				glUniformMatrix4fv(pMatrixLoc, 1, GL_FALSE, math::float4x4::identity.ptr());

				uint mvMatrixLoc = glGetUniformLocation(App->renderer->shaderProgram, "modelViewMatrix");
				glUniformMatrix4fv(mvMatrixLoc, 1, GL_FALSE, math::float4x4::identity.ptr());*/

				//VERTEX POSITIONS

				int vPositionLoc = glGetAttribLocation(App->renderer->shaderProgram, "vertexPosition");

				if (vPositionLoc != -1)
				{
					glEnableVertexAttribArray(vPositionLoc);

					glBindBuffer(GL_ARRAY_BUFFER, ComponentMeshRenderer::cubeVertexBuffer);
					glVertexAttribPointer(vPositionLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ComponentMeshRenderer::cubeIndexBuffer);

					SendUniformsToShader();

					glDrawElements(GL_TRIANGLES, ComponentMeshRenderer::cubeNumIndex, GL_UNSIGNED_INT, NULL);

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

					glDisableVertexAttribArray(vPositionLoc);

					glBindBuffer(GL_ARRAY_BUFFER, NULL);
				}	

				glUseProgram(NULL);

				glBindVertexArray(NULL);
				
				break;
			}

			case 1:
			{
				glBindVertexArray(pyramidVAO);

				glUseProgram(App->renderer->shaderProgram);

				//Matrix uniforms

				//VERTEX POSITIONS
				uint vPositionLoc = glGetAttribLocation(App->renderer->shaderProgram, "vertexPosition");
				if (vPositionLoc != -1)
				{
					glEnableVertexAttribArray(vPositionLoc);

					glBindBuffer(GL_ARRAY_BUFFER, ComponentMeshRenderer::pyramidVertexBuffer);
					glVertexAttribPointer(vPositionLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ComponentMeshRenderer::pyramidIndexBuffer);

					SendUniformsToShader();

					glDrawElements(GL_TRIANGLES, ComponentMeshRenderer::pyramidNumIndex, GL_UNSIGNED_INT, NULL);

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

					glDisableVertexAttribArray(vPositionLoc);

					glBindBuffer(GL_ARRAY_BUFFER, NULL);
				}
				
				glUseProgram(NULL);

				glBindVertexArray(NULL);

				break;
			}
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

		ImGui::NewLine();

		ImGui::AlignTextToFramePadding();
		ImGui::Text("Color: "); ImGui::SameLine(); 

		ImGui::ColorEdit4((std::string("Color##") + std::to_string(UUID)).data(), color);

		ImGui::NewLine();

		ImGui::Checkbox((std::string("Use Internal Shapes##") + std::to_string(UUID)).data(), &useInternalShapes);

		if (useInternalShapes)
		{
			if (ImGui::BeginCombo((std::string("Shape:##") + std::to_string(UUID)).data(), internalShapeID == 0u ? "Cube" : "Pyramid"))
			{
				if(ImGui::Selectable((std::string("Cube##") + std::to_string(UUID)).data()))
				{
					if (internalShapeID != 0u)
					{
						internalShapeID = 0u;


					}
				}
				else if (ImGui::Selectable((std::string("Pyramid##") + std::to_string(UUID)).data()))
				{
					if (internalShapeID != 1u)
					{
						internalShapeID = 1u;


					}
				}

				ImGui::EndCombo();
			}

		}
		else
		{
			ImGui::TextColored({ 1,0,0,1 }, "CUSTOM SHAPES NOT IMPLEMENTED FOR NOW");
		}
	}
}

void ComponentMeshRenderer::SendUniformsToShader()
{
	//Color uniform
	int colorLoc = glGetUniformLocation(App->renderer->shaderProgram, "color");
	if(colorLoc != -1)
	{
		glUniform4fv(colorLoc, 1, color);
	}

	//ProjectionMatrix uniform
	int pMatrixLoc = glGetUniformLocation(App->renderer->shaderProgram, "projectionMatrix");
	if (pMatrixLoc != -1)
	{
		math::float4x4 projectionMatrix = ComponentCamera::activeCamera->GetProjectionMatrix();
		glUniformMatrix4fv(pMatrixLoc, 1, false, projectionMatrix.ptr());
	}

	//ModelViewMatrix uniform
	int mvMatrixLoc = glGetUniformLocation(App->renderer->shaderProgram, "modelViewMatrix");
	if (mvMatrixLoc != -1)
	{
		math::float4x4 viewMatrix = ComponentCamera::activeCamera->GetViewMatrix();
		math::float4x4 modelMatrix = gameObject->transform->GetGlobalMatrix();
		math::float4x4 MVMatrix = viewMatrix * modelMatrix;

		glUniformMatrix4fv(mvMatrixLoc, 1, false, MVMatrix.ptr());
	}
}
