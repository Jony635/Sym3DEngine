#include "PanelInspector.h"
#include "ImGUI/include/imgui.h"

void PanelInspector::Draw()
{
	ImGui::Begin("Inspector", &active);

	ImGui::Text("This is the inspector panel");

	ImGui::End();
}
