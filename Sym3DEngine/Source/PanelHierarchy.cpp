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

void OnHierarchyDoubleClick()
{
	if (ImGui::IsItemClicked() && ImGui::IsMouseDoubleClicked(0))
	{
		App->scene->DeselectAll();
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

		//The dummy under this gameObject to drag and drop
		ImVec2 cursorPos = ImGui::GetCursorScreenPos();
		ImVec2 windowSize = ImGui::GetWindowSize();
		ImGui::Dummy({ windowSize.x, 4 });
		ImGui::SetCursorScreenPos(cursorPos);

		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GAMEOBJECT", ImGuiDragDropFlags_AcceptNoDrawDefaultRect | ImGuiDragDropFlags_AcceptBeforeDelivery);
			if (payload != nullptr)
			{
				GameObject* dragged = *(GameObject**)payload->Data;
				GameObject* nextGameObject = root->childs.size() - 1 >= i+1 ? root->childs[i+1] : nullptr;

				if (dragged != gameObject && dragged != nextGameObject)
				{
					ImDrawList* drawList = ImGui::GetWindowDrawList();
					drawList->AddLine({ cursorPos.x, cursorPos.y - 3 }, { cursorPos.x + windowSize.x - 3, cursorPos.y - 3 }, ImGui::ColorConvertFloat4ToU32({ 0.5f, 0.8f, 0.9f, 1.0f }), 3.0f);

					if (dragged->parent == gameObject->parent)
					{
						//Both are brothers, only reorder the vector

						if (ImGui::IsMouseReleased(0))
						{
							std::vector<GameObject*>& childs = dragged->parent->childs;
							uint draggedIndex = std::find(childs.begin(), childs.end(), dragged) - childs.begin();
							
							childs.erase(dragged->parent->childs.begin() + draggedIndex);
							childs.insert(childs.begin() + (draggedIndex > i ? i + 1 : i), dragged);
						}	
					}
					else
					{
						//Change parents, update matrices etc
					}

				}
			}

			ImGui::EndDragDropTarget();
		}

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

	//THE TOP DUMMY OF THE HIERARCHY
	cursorPos = ImGui::GetCursorScreenPos();
	ImGui::SetCursorScreenPos({ windowPos.x, cursorPos.y - 3 });
	ImGui::Dummy({windowSize.x, 4});
	ImGui::SetCursorScreenPos(cursorPos);

	if(ImGui::BeginDragDropTarget())
	{
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		drawList->AddLine({windowPos.x, cursorPos.y - 3}, { windowPos.x + windowSize.x, cursorPos.y - 3 }, ImGui::ColorConvertFloat4ToU32({ 0.5f, 0.8f, 0.9f, 1.0f }), 3.0f);

		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GAMEOBJECT", ImGuiDragDropFlags_::ImGuiDragDropFlags_AcceptNoDrawDefaultRect);
		if (payload != nullptr)
		{
			//Reorder, check parents, etc.

			GameObject* dragged = *(GameObject**)payload->Data;
			if (dragged != App->scene->root->childs[0])
			{
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
					//Change parents
				}
			}
		}

		ImGui::EndDragDropTarget();
	}

	DrawGameObjectsRecursive(App->scene->root);

	ImGui::End();
}
