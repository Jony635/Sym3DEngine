#include "PanelHierarchy.h"

#include "ImGUI/include/imgui.h"

void PanelHierarchy::Draw()
{
	ImGui::Begin("Hierarchy", &active);

	ImGui::Text("Here will go the treenodes");

	ImGui::End();

}
