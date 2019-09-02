#include "ComponentTransform.h"
#include "GameObject.h"

#include "ImGUI/include/imgui.h"
#include <string>

ComponentTransform::ComponentTransform(GameObject* gameObject) : Component(gameObject, ComponentType::TRANSFORM)
{
	position = math::float3::zero;
	rotation.SetFromAxisAngle({ 0,0,0 }, 0);
	scale = math::float3::one;

	localMatrix = math::float4x4::FromTRS(position, rotation, scale);
	globalMatrix = localMatrix;

	if(gameObject && gameObject->parent && gameObject->parent->transform)
		globalMatrix = gameObject->parent->transform->globalMatrix * localMatrix;
}

void ComponentTransform::OnInspector()
{
	if(ImGui::CollapsingHeader((std::string("Transform##") + std::to_string(UUID)).data()))
	{
		ImGui::AlignTextToFramePadding();
		ImGui::Text("UUID: %u", UUID); ImGui::SameLine(0.0f, 10.0f);

		if (ImGui::Button("Reset Transform")) 
		{ 
			position =  math::float3::zero; 
			rotation = math::Quat::identity; 
			scale =  math::float3::one;

			UpdateMatricesFromLocal();
		}

		ImGui::NewLine();

		ImGui::Text("Position: ");
		if (ImGui::DragFloat3((std::string("##Position") + std::to_string(UUID)).data(), position.ptr()))
		{
			UpdateMatricesFromLocal();
		}

		ImGui::Text("Rotation: ");
		{
			float rotationAngle = 0.0f;
			math::float3 rotationAxis = math::float3::zero;
			rotation.ToAxisAngle(rotationAxis, rotationAngle);

			if (!rotationAxis.IsFinite())
				rotationAxis = math::float3::zero;
			else
				rotationAxis *= math::RadToDeg(rotationAngle);

			if (ImGui::DragFloat3((std::string("##Rotation") + std::to_string(UUID)).data(), rotationAxis.ptr(), 0.1f, 0.0f, 0.0f, "%.3f"))
			{
				rotation.SetFromAxisAngle(rotationAxis.Normalized(), math::DegToRad(rotationAxis.Length()));

				UpdateMatricesFromLocal();
			}
		}

		ImGui::Text("Scale: ");
		if (ImGui::DragFloat3((std::string("##Scale") + std::to_string(UUID)).data(), scale.ptr(), 0.01f))
		{
			UpdateMatricesFromLocal();
		}
	}
}

void ComponentTransform::UpdateMatricesFromLocal()
{
	localMatrix = math::float4x4::FromTRS(position, rotation, scale);
	globalMatrix = localMatrix;

	if (gameObject && gameObject->parent && gameObject->parent->transform)
		globalMatrix = gameObject->parent->transform->globalMatrix * localMatrix;
	
	for (GameObject* child : gameObject->childs)
	{
		if (child->transform)
			child->transform->UpdateMatricesFromLocal();
	}

	gameObject->OnTransformChanged();
}

void ComponentTransform::UpdateMatricesFromGlobal()
{
	localMatrix = gameObject->parent->transform->globalMatrix.Inverted() * globalMatrix;
	localMatrix.Decompose(position, rotation, scale);

	for (GameObject* child : gameObject->childs)
	{
		if (child->transform)
			child->transform->UpdateMatricesFromGlobal();
	}

	gameObject->OnTransformChanged();
}
