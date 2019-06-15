#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer.h"
#include "ModuleImGUI.h"

#include "SDL/include/SDL.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"

#include <iostream>

#pragma comment(lib, "Glew/libx64/glew32.lib")

#include "ImGUI/include/imgui.h"
#include "ImGUI/include/imgui_impl_opengl3.h"

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
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	if (vsync)
	{
		if (SDL_GL_SetSwapInterval(1) != 0)
		{
			std::cout << "Error setting up VSYNC. " << SDL_GetError();
			return false;
		}
	}

	//GLuint program = glCreateProgram();

	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//const GLchar* vertexShaderSource[] = { "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }" };
	//glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	//GLint vShaderCompiled = GL_FALSE; 
	//glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &vShaderCompiled ); 
	//if( vShaderCompiled != GL_TRUE ) 
	//{ 
	//	std::cout<<"Unable to compile vertex shader " << vertexShader << std::endl; 

	//	//TODO: GET ERRORS AT STRING AND LOG THEM

	//	return false;
	//}

	//glAttachShader(program, vertexShader);

	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//const GLchar* fragmentShaderSource[] = { "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }" };
	//glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	//GLint fShaderCompiled = GL_FALSE; 
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled); 
	//if (fShaderCompiled != GL_TRUE) 
	//{ 
	//	std::cout<< "Unable to compile fragment shader " << fragmentShader << std::endl; 

	//	//TODO: GET ERRORS AT STRING AND LOG THEM

	//	return false;
	//}
	//
	//glAttachShader(program, fragmentShader); 
	//glLinkProgram( program ); 
	//GLint programSuccess = GL_TRUE; 
	//glGetProgramiv( program, GL_LINK_STATUS, &programSuccess ); 
	//if( programSuccess != GL_TRUE ) 
	//{ 
	//	std::cout << "Error linking program " << program << std::endl;

	//	//TODO: GET ERRORS AT STRING AND LOG THEM

	//	return false;
	//}

	//TODO: Get uniform and atributes locations etc

	SDL_GL_MakeCurrent((SDL_Window*)App->window->GetWindow(), context);

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

	glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//----------------------------------

	App->imgui->Draw();

	SDL_GL_SwapWindow((SDL_Window*)App->window->GetWindow());

	return true;
}
