#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer.h"
#include "ModuleImGUI.h"

#include "ComponentMeshRenderer.h"

#include "SDL/include/SDL.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"

#include <iostream>

#pragma comment(lib, "Glew/libx64/glew32.lib")

#include "ImGUI/include/imgui.h"
#include "ImGUI/include/imgui_impl_opengl3.h"

#include "DefaultShader.h"

bool ModuleRenderer::Init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	context = SDL_GL_CreateContext((SDL_Window*)App->window->GetWindow());
	if (!context) 
	{ 
		std::cout<<"OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_GL_MakeCurrent((SDL_Window*)App->window->GetWindow(), context);

	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << "Error initializing glew. " << glewGetErrorString(error) << std::endl;
		return false;
	}

	glClearColor(0.f, 0.f, 0.f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	if (vsync)
	{
		if (SDL_GL_SetSwapInterval(1) != 0)
		{
			std::cout << "Error setting up VSYNC. " << SDL_GetError();
			return false;
		}
	}

	//DEFAULT SHADER PROGRAM

	ComponentMeshRenderer::InitializeShapesData();
	shaderProgram = glCreateProgram();

	//VERTEX SHADER
	uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string source = DEFAULT_VS;

	const GLchar* src = (const GLchar*)source.c_str();
	glShaderSource(vertexShader, 1, &src, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		//VERTEX SHADER HAS COMPILE-TIME ERRORS!
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); //TODO: LOG THIS INTO THE CONSOLE.
		return false;
	}

	//FRAGMENT SHADER
	uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	source = DEFAULT_FS;
	src = source.c_str();

	glShaderSource(fragmentShader, 1, &src, NULL);
	glCompileShader(fragmentShader);
	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		//FRAGMENT SHADER HAS COMPILE-TIME ERRORS!
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog); //TODO: LOG THIS INTO THE CONSOLE.
		return false;
	}

	//ATTACH THE SHADERS TO THE PROGRAM
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) 
	{
		//SHADER PROGRAM FAILED WHILE LINKING!
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog); //TODO: LOG THIS INTO THE CONSOLE.
		return false;
	}

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	return true;
}

bool ModuleRenderer::Start()
{
	FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	glGenTextures(1, &renderedTexture);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

bool ModuleRenderer::PostUpdate()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Render the scene ------------------
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	//glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (ComponentRenderer* renderer : renderers)
		renderer->Render();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//----------------------------------

	App->imgui->Draw();

	SDL_GL_SwapWindow((SDL_Window*)App->window->GetWindow());

	return true;
}

ComponentRenderer* ModuleRenderer::AddRenderer(ComponentType type, GameObject* gameObject)
{
	ComponentRenderer* ret = nullptr;
	switch (type)
	{
		case ComponentType::MESHRENDERER:
		{
			ret = new ComponentMeshRenderer(gameObject);
			renderers.push_back(ret);
			break;
		}
		case ComponentType::RENDERER2D:
		{
			break;
		}
	}
	return ret;
}

ComponentRenderer* ModuleRenderer::AddRenderer(ComponentRenderer* renderer)
{
	if (!renderer)
		return nullptr;

	renderers.push_back(renderer);

	return renderer;
}

bool ModuleRenderer::EraseRenderer(ComponentRenderer* renderer)
{
	std::vector<ComponentRenderer*>::iterator it = std::find(renderers.begin(), renderers.end(), renderer);
	if (it != renderers.end())
	{
		renderers.erase(it);
		return true;
	}

	return false;
}
