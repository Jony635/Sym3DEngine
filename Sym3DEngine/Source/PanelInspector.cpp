#include "Application.h"
#include "ModuleScene.h"
#include "PanelInspector.h"
#include "ImGUI/include/imgui.h"

#include "GameObject.h"

void AddComponent(GameObject* gameObject)
{
	ImGui::Separator();
	float width = ImGui::GetWindowWidth() - (ImGui::GetWindowPos().x - ImGui::GetCursorScreenPos().x);
	if (ImGui::Button("Add Component", ImVec2(width, 0.0f)))
	{
		ImGui::OpenPopup("AddComponentPopup");
		ImGui::SetNextWindowPos(ImGui::GetCursorScreenPos());
		/*ImGui::SetNextWindowSize(ImVec2(width, 0.0f));*/ //Popups autoresize by default
	}

	if (ImGui::BeginPopup("AddComponentPopup", ImGuiWindowFlags_::ImGuiWindowFlags_NoMove))
	{
		if (!gameObject->renderer && ImGui::MenuItem("MeshRenderer"))
		{
			gameObject->AddComponent(ComponentType::MESHRENDERER);
		}

		ImGui::EndPopup();
	}

}

void PanelInspector::Draw()
{
	ImGui::Begin("Inspector", &active);

	ImGui::Separator();

	if (!App->scene->selections.empty())
	{
		Selection selected = App->scene->selections.back();
		if (selected.type == SelectionType::GAMEOBJECT_SELECTION)
		{
			GameObject* gameObject = (GameObject*)selected.goSelection.gameObject;
			gameObject->OnInspector();

			AddComponent(gameObject);
		}
	}

	ImGui::End();
}
