#include "Application.h"
#include "ModuleImGUI.h"
#include "ModuleWindow.h"
#include "ModuleRenderer.h"

#include "PanelHierarchy.h"
#include "PanelInspector.h"

#include "SDL/include/SDL.h"
#include "ImGUI/include/imgui.h"
#include "ImGUI/include/imgui_impl_sdl.h"
#include "ImGUI/include/imgui_impl_opengl3.h"
#include "ImGUI/include/imgui_internal.h"

#include "Glew/include/GL/glew.h"

ModuleImGUI::ModuleImGUI()
{
	hierarchy = new PanelHierarchy();
	panels.push_back(hierarchy);

	inspector = new PanelInspector();
	panels.push_back(inspector);
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
	
	ImGui::BeginMainMenuBar();
	
	if (ImGui::BeginMenu("View"))
	{
		if (ImGui::MenuItem("Hierarchy", "", hierarchy->active))
		{
			hierarchy->ToggleActive();
		}

		if (ImGui::MenuItem("Inspector", "", inspector->active))
		{
			inspector->ToggleActive();
		}

		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
	
	DockSpace();

	for (Panel* panel : panels)
	{
		if (panel->active)
			panel->Draw();
	}

	return true;
}

void ModuleImGUI::DockSpace()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();

	float y_offset = 20;

	ImGui::SetNextWindowPos({ viewport->Pos.x, viewport->Pos.y + y_offset });
	ImGui::SetNextWindowSize({ viewport->Size.x, viewport->Size.y - y_offset });
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGuiDockNodeFlags dockspace_flags = 0;
	dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;

	ImGuiWindowFlags host_window_flags = 0;
	host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
	host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		host_window_flags |= ImGuiWindowFlags_NoBackground;

	char label[32];
	ImFormatString(label, IM_ARRAYSIZE(label), "DockSpaceViewport_%08X", viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin(label, NULL, host_window_flags);
	ImGui::PopStyleVar(3);

	ImGuiID dockspace_id = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags, nullptr);
	ImGui::End();
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