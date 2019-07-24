#include "Application.h"
#include "ModuleScene.h"
#include "ModuleRenderer.h"

#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentCamera.h"

#include "ImGUI/include/imgui.h"
#include "ImGUI/include/imgui_stdlib.h"

class ComponentMeshRenderer;

GameObject::GameObject(GameObject* parent) : parent(parent)
{
	UUID = App->GetRandomUUID();

	transform = new ComponentTransform(this);
	components.push_back(transform);
}

void GameObject::OnInspector()
{
	if (ImGui::Checkbox((std::string("Active##") + std::to_string(UUID)).data(), &active))
	{
		active = !active;
		ToggleActive();
	}
	
	ImGui::SameLine();

	ImGuiInputTextFlags flags = 0;
	flags |= ImGuiInputTextFlags_::ImGuiInputTextFlags_AutoSelectAll;

	ImGui::Text(" Name:"); 
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::AlignTextToFramePadding();
		ImGui::Text("UUID: %u", UUID);
		ImGui::EndTooltip();
	}

	ImGui::SameLine();
	ImGui::InputText("##Name", &name, flags); 

	ImGui::Separator();

	for (int i = 0; i < components.size(); ++i)
	{
		components[i]->OnInspector();
	}
}

Component* GameObject::AddComponent(ComponentType type)
{
	switch (type)
	{
		case ComponentType::MESHRENDERER:
		{
			if (this->renderer)
			{
				//TODO: LOG ERROR, ALREADY HAD ONE RENDERER
				return nullptr;
			}

			ComponentRenderer* renderer = App->renderer->AddRenderer(ComponentType::MESHRENDERER, this);
			components.push_back((Component*)renderer);		

			this->renderer = renderer;
			return (Component*)renderer;
			break;
		}

		case ComponentType::CAMERA:
		{
			if (this->camera)
			{
				//TODO: LOG ERROR, ALREADY HAD ONE CAMERA
				return nullptr;
			}

			ComponentCamera* camera = new ComponentCamera(this);
			components.push_back(camera);

			this->camera = camera;
			return camera;

			break;
		}
	}
}

void GameObject::AddChild(GameObject* child)
{
	if(child->parent)
		child->parent->EraseChild(child);
	child->parent = this;
	childs.push_back(child);

	if (child->transform)
		child->transform->UpdateMatricesFromGlobal();
}

void GameObject::EraseChild(GameObject* child)
{
	std::vector<GameObject*>::iterator iterator = std::find(childs.begin(), childs.end(), child);
	if (iterator != childs.end())
	{
		childs.erase(iterator);
	}
}

void GameObject::SetParent(GameObject* newParent)
{
	if (!newParent)
		return;

	newParent->childs.push_back(this);
	parent->EraseChild(this);
	parent = newParent;

	if (transform)
		transform->UpdateMatricesFromGlobal();
}

void GameObject::OnTransformChanged()
{
	for (Component* component : components)
	{
		component->OnTransformChanged();
	}
}

void GameObject::AddComponent(Component* component)
{

}
