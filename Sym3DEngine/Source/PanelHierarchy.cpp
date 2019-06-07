#include "PanelHierarchy.h"

#include "ImGUI/include/imgui.h"
#include "ImGUI/include/imgui_internal.h"

void PanelHierarchy::Draw()
{
	ImGui::Begin("Hierarchy", &active);

	ImVec2 cursorPos = ImGui::GetCursorScreenPos();
	ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 windowSize = ImGui::GetWindowSize();
	windowSize.y -= 7.1;

	ImGui::SetCursorScreenPos(windowPos);
	//ImGui::GetWindowDrawList()->AddRectFilled(windowPos, { windowPos.x + windowSize.x, windowPos.y + windowSize.y }, ImGui::ColorConvertFloat4ToU32(ImVec4(1, .15, .15, 1)));
	ImGui::Dummy(windowSize);
	ImGui::SetCursorScreenPos(cursorPos);

	if (ImGui::IsItemClicked(1))
	{
		ImGui::OpenPopup("Create GameObject Popup");
	}

	if(ImGui::BeginPopup("Create GameObject Popup"))
	{
		if (ImGui::MenuItem("Create Empty"))
		{
			//TODO: Create an empty gameObject with a tranform
		}

		ImGui::EndPopup();
	}

	ImGui::TextColored({ 1.0f, 1.0f, 0.0f, 1.0f }, "GameObjects coming soon...");

	ImGui::End();
}
