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
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

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
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	//glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glViewport(0, 0, 1920, 1080);

	for (ComponentRenderer* renderer : renderers)
		if (renderer->IsTreeActive())
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
