#include "Application.h"
#include "ModuleScene.h"
#include "GameObject.h"

#include "ImGUI/include/imgui.h"
#include "ImGUI/include/imgui_stdlib.h"

GameObject::GameObject()
{
	UUID = App->GetRandomUUID();
}

void GameObject::OnInspector()
{
	ImGui::Checkbox("Active", &active); ImGui::SameLine();

	ImGuiInputTextFlags flags = 0;
	flags |= ImGuiInputTextFlags_::ImGuiInputTextFlags_AutoSelectAll;

	ImGui::Text(" Name:"); ImGui::SameLine();
	ImGui::InputText("##Name", &name, flags); 
}
