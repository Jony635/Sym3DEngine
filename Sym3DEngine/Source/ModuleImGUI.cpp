#include "Application.h"
#include "ModuleImGUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer.h"

#include "PanelHierarchy.h"

#include "SDL/include/SDL.h"
#include "ImGUI/include/imgui.h"
#include "ImGUI/include/imgui_impl_sdl.h"
#include "ImGUI/include/imgui_impl_opengl3.h"

#include "Glew/include/GL/glew.h"

ModuleImGUI::ModuleImGUI()
{
	hierarchy = new PanelHierarchy();
	panels.push_back(hierarchy);
}

bool ModuleImGUI::Start()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplSDL2_InitForOpenGL((SDL_Window*)App->window->GetWindow(), (void*)App->renderer->GetContext());
	ImGui_ImplOpenGL3_Init("#version 150");

	return true;
}

bool ModuleImGUI::PreUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame((SDL_Window*)App->window->GetWindow());
	ImGui::NewFrame();

	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_NoDockingInCentralNode | ImGuiDockNodeFlags_PassthruCentralNode);

	for (Panel* panel : panels)
	{
		if (panel->active)
			panel->Draw();
	}

	return true;
}

void ModuleImGUI::NotifyEvent(SDL_Event event)
{
	ImGui_ImplSDL2_ProcessEvent(&event);
}

void ModuleImGUI::Draw()
{
	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();

		SDL_GL_MakeCurrent((SDL_Window*)App->window->GetWindow(), (SDL_GLContext)App->renderer->GetContext());
	}
}