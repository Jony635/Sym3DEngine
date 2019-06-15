#include "Application.h"
#include "ModuleScene.h"

#include "GameObject.h"
#include "ComponentTransform.h"

#include "ImGUI/include/imgui.h"
#include "ImGUI/include/imgui_stdlib.h"

GameObject::GameObject(GameObject* parent) : parent(parent)
{
	UUID = App->GetRandomUUID();

	transform = new ComponentTransform(this);
	components.push_back(transform);
}

void GameObject::OnInspector()
{
	ImGui::Checkbox("Active", &active); ImGui::SameLine();

	ImGuiInputTextFlags flags = 0;
	flags |= ImGuiInputTextFlags_::ImGuiInputTextFlags_AutoSelectAll;

	ImGui::Text(" Name:"); ImGui::SameLine();
	ImGui::InputText("##Name", &name, flags); 

	ImGui::Separator();

	for (int i = 0; i < components.size(); ++i)
	{
		components[i]->OnInspector();
	}
}

Component* GameObject::AddComponent(ComponentType type)
{
	return nullptr;
}

void GameObject::AddChild(GameObject* gameObject)
{

}

void GameObject::EraseChild(GameObject* child)
{
	for (int i = 0; i < childs.size(); ++i)
	{
		if (childs[i] == child)
		{
			childs.erase(childs.begin() + i);
			return;
		}
	}
}

void GameObject::AddComponent(Component* component)
{

}
