#include "Application.h"
#include "ModuleScene.h"

#include "PanelHierarchy.h"

#include "ImGUI/include/imgui.h"
#include "ImGUI/include/imgui_internal.h"

#include "GameObject.h"

void OnHierarchyRightClick()
{
	if (ImGui::IsItemClicked(1))
	{
		ImGui::OpenPopup("HierarchyRightClicked");
	}

	if (ImGui::BeginPopup("HierarchyRightClicked"))
	{
		if (ImGui::MenuItem("Create Empty"))
		{
			App->scene->CreateGameObject();
		}

		ImGui::EndPopup();
	}
}

void DrawGameObjectsRecursive(GameObject* root)
{
	for (GameObject* gameObject : root->childs)
	{
		ImGuiTreeNodeFlags flags = 0;
		if (gameObject->childs.empty())
			flags |= ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Leaf;

		if(ImGui::TreeNodeEx((gameObject->GetName() + std::string("##") + std::to_string(gameObject->GetUUID())).data(), flags))
		{
			DrawGameObjectsRecursive(gameObject);
			ImGui::TreePop();
		}
	}
}

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

	OnHierarchyRightClick();

	DrawGameObjectsRecursive(App->scene->root);

	ImGui::End();
}
