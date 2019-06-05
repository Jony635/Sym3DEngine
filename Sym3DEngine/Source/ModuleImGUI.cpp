#include "Application.h"
#include "ModuleImGUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer.h"

#include "PanelHierarchy.h"

#include "SDL/include/SDL.h"
#include "ImGUI/include/imgui.h"
#include "ImGUI/include/imgui_impl_sdl.h"
#include "ImGUI/include/imgui_impl_opengl3.h"

ModuleImGUI::ModuleImGUI()
{
	hierarchy = new PanelHierarchy();

	panels.push_back(hierarchy);
}

bool ModuleImGUI::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL((SDL_Window*)App->window->GetWindow(), (void*)App->renderer->GetContext());
	ImGui_ImplOpenGL3_Init("#version 150");




	return true;
}

bool ModuleImGUI::PreUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame((SDL_Window*)App->window->GetWindow());
	ImGui::NewFrame();

	for (Panel* panel : panels)
	{
		if(panel->active)
			panel->Draw();
	}

	return true;
}

bool ModuleImGUI::PostUpdate()
{
	ImGui::Render();
	
	return true;
}

void ModuleImGUI::NotifyEvent(SDL_Event event)
{
	ImGui_ImplSDL2_ProcessEvent(&event);
}

void ModuleImGUI::Draw()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
