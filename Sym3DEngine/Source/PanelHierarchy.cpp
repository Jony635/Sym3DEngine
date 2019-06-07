#include "Application.h"
#include "ModuleScene.h"

#include "PanelHierarchy.h"

#include "ImGUI/include/imgui.h"
#include "ImGUI/include/imgui_internal.h"

#include "GameObject.h"

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

			GameObject* gameObject = new GameObject();
			gameObject->SetName(std::to_string(gameObject->GetUUID()));
			App->scene->gameObjects.push_back(gameObject);
		}

		ImGui::EndPopup();
	}

	for (GameObject* gameObject : App->scene->gameObjects)
	{
		if (ImGui::TreeNode((gameObject->GetName() + std::string("##") + std::to_string(gameObject->GetUUID())).data()))
		{
			ImGui::TreePop();
		}


	}

	ImGui::TextColored({ 1.0f, 1.0f, 0.0f, 1.0f }, "GameObjects coming soon...");

	ImGui::End();
}
