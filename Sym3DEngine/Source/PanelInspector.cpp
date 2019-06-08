#include "Application.h"
#include "ModuleScene.h"
#include "PanelInspector.h"
#include "ImGUI/include/imgui.h"

#include "GameObject.h"

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
		}
	}

	ImGui::End();
}
