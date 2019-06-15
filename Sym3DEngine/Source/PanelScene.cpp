#include "PanelScene.h"

#include "Application.h"
#include "ModuleRenderer.h"

#include "ImGUI/include/imgui.h"

void PanelScene::Draw()
{
	ImGui::Begin("Scene", &active);
	 
	ImGui::Image((ImTextureID)App->renderer->renderedTexture, {ImGui::GetWindowWidth() - 17, ImGui::GetWindowHeight() - 35});

	ImGui::End();
}
