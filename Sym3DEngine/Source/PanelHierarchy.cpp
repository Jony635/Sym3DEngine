#include "Application.h"
#include "ModuleScene.h"

#include "PanelHierarchy.h"

#include "ImGUI/include/imgui.h"
#include "ImGUI/include/imgui_internal.h"

#include "GameObject.h"
#include "ComponentTransform.h"

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

void OnHierarchyDoubleClick()
{
	if (ImGui::IsItemClicked() && ImGui::IsMouseDoubleClicked(0))
	{
		App->scene->DeselectAll();
	}
}

void OnGameObjectReorder(GameObject* root, int childIndex)
{
	//The dummy under this gameObject to drag and drop
	ImVec2 cursorPos = ImGui::GetCursorScreenPos();
	ImVec2 windowSize = ImGui::GetWindowSize();
	ImGui::SetCursorScreenPos({cursorPos.x, cursorPos.y - 2});
	ImGui::Dummy({ windowSize.x, 2 });
	ImGui::SetCursorScreenPos(cursorPos);

	GameObject* child = root->childs[childIndex];

	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GAMEOBJECT", ImGuiDragDropFlags_AcceptNoDrawDefaultRect | ImGuiDragDropFlags_AcceptBeforeDelivery);
		if (payload != nullptr)
		{
			GameObject* dragged = *(GameObject * *)payload->Data;
			GameObject* nextGameObject = root->childs.size() - 1 >= childIndex + 1 ? root->childs[childIndex + 1] : nullptr;

			if (dragged != child && dragged != nextGameObject)
			{
				ImDrawList* drawList = ImGui::GetWindowDrawList();
				drawList->AddLine({ cursorPos.x, cursorPos.y - 3 }, { cursorPos.x + windowSize.x - 3, cursorPos.y - 3 }, ImGui::ColorConvertFloat4ToU32({ 0.5f, 0.8f, 0.9f, 1.0f }), 3.0f);

				if (ImGui::IsMouseReleased(0))
				{
					if (dragged->parent != child->parent)
						child->parent->AddChild(dragged);

					std::vector<GameObject*>& childs = dragged->parent->childs;
					uint draggedIndex = std::find(childs.begin(), childs.end(), dragged) - childs.begin();

					childs.erase(dragged->parent->childs.begin() + draggedIndex);
					childs.insert(childs.begin() + (draggedIndex > childIndex ? childIndex + 1 : childIndex), dragged);
				}							
			}
		}

		ImGui::EndDragDropTarget();
	}
}

void OnGameObjectDropped(GameObject* root, int childIndex)
{
	//ImVec2 cursorPos = ImGui::GetCursorScreenPos();
	//ImGui::SetCursorScreenPos({ cursorPos.x, cursorPos.y - 15 });
	//ImVec2 windowSize = ImGui::GetWindowSize();
	//ImGui::Dummy({ windowSize.x, 10 });

	if (ImGui::BeginDragDropTarget())
	{
		ImGui::PushStyleColor(ImGuiCol_DragDropTarget, { 0.5f, 0.8f, 0.9f, 1.0f });
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GAMEOBJECT", ImGuiDragDropFlags_AcceptBeforeDelivery);
		ImGui::PopStyleColor();

		if (payload != nullptr && ImGui::IsMouseReleased(0))
		{
			GameObject* child = root->childs[childIndex];
			GameObject* dragged = *(GameObject**)payload->Data;
			
			std::vector<GameObject*>::iterator iterator = std::find(child->childs.begin(), child->childs.end(), dragged);
			if (iterator != child->childs.end())
			{
				//Dragged was already a child, send it to the back of the vector.

				child->EraseChild(dragged);
				child->AddChild(dragged);
			}
			else
			{
				if (dragged != child->parent)
				{
					//New child. Change parents, update locals.

					dragged->parent->EraseChild(dragged);
					child->AddChild(dragged);
				}		
				else
				{
					//Dont drag the parent into the child, that is weird
				}
			}
		}
		ImGui::EndDragDropTarget();
	}
}

void OnHierarchyGameObjectDropped()
{
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GAMEOBJECT", ImGuiDragDropFlags_AcceptNoDrawDefaultRect /*| ImGuiDragDropFlags_AcceptBeforeDelivery*/);
		if (payload != nullptr)
		{
			//Reorder, check parents, etc.

			GameObject* dragged = *(GameObject * *)payload->Data;
			App->scene->root->AddChild(dragged);
		}
		ImGui::EndDragDropTarget();
	}
}

void PanelHierarchy::DrawGameObjectsRecursive(GameObject* root)
{
	for (int i = 0; i < root->childs.size(); ++i)
	{
		GameObject* gameObject = root->childs[i];

		ImGuiTreeNodeFlags flags = 0;
		if (gameObject->childs.empty())
			flags |= ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Leaf;
		if (gameObject->selected)
			flags |= ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Selected;

		flags |= ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_OpenOnArrow;

		bool treeopened = ImGui::TreeNodeEx((gameObject->GetName() + std::string("##") + std::to_string(gameObject->GetUUID())).data(), flags);

		if (ImGui::BeginDragDropSource())
		{
			ImGui::BeginTooltip();
			ImGui::Text(gameObject->name.data());
			ImGui::EndTooltip();

			ImGui::SetDragDropPayload("GAMEOBJECT", &gameObject, sizeof(gameObject));
			ImGui::EndDragDropSource();
		}

		if (ImGui::IsItemClicked(0))
		{
			App->scene->GameObjectHierarchyClicked(gameObject);
		}

		OnGameObjectDropped(root, i);
		OnGameObjectReorder(root, i);

		if(treeopened)
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

	OnHierarchyDoubleClick();
	OnHierarchyRightClick();
	OnHierarchyGameObjectDropped();

	//THE TOP DUMMY OF THE HIERARCHY
	cursorPos = ImGui::GetCursorScreenPos();
	ImGui::SetCursorScreenPos({ windowPos.x, cursorPos.y - 3 });
	ImGui::Dummy({windowSize.x, 4});
	ImGui::SetCursorScreenPos(cursorPos);

	if(ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GAMEOBJECT", ImGuiDragDropFlags_AcceptNoDrawDefaultRect | ImGuiDragDropFlags_AcceptBeforeDelivery);
		if (payload != nullptr)
		{
			//Reorder, check parents, etc.

			GameObject* dragged = *(GameObject**)payload->Data;
			if (dragged != App->scene->root->childs[0])
			{
				ImDrawList* drawList = ImGui::GetWindowDrawList();
				drawList->AddLine({ windowPos.x, cursorPos.y - 3 }, { windowPos.x + windowSize.x, cursorPos.y - 3 }, ImGui::ColorConvertFloat4ToU32({ 0.5f, 0.8f, 0.9f, 1.0f }), 3.0f);

				if (dragged->parent == App->scene->root)
				{
					if (ImGui::IsMouseReleased(0))
					{
						std::vector<GameObject*>& childs = dragged->parent->childs;
						uint draggedIndex = std::find(childs.begin(), childs.end(), dragged) - childs.begin();

						childs.erase(dragged->parent->childs.begin() + draggedIndex);
						childs.insert(childs.begin(), dragged);
					}
				}
				else
				{
					if (ImGui::IsMouseReleased(0))
					{
						dragged->parent->EraseChild(dragged);
						App->scene->root->AddChild(dragged);

						if (dragged->transform)
							dragged->transform->UpdateMatricesFromGlobal();
					}
				}
			}
		}

		ImGui::EndDragDropTarget();
	}

	DrawGameObjectsRecursive(App->scene->root);

	ImGui::End();
}
