#include "ComponentTransform.h"

#include "ImGUI/include/imgui.h"
#include <string>

void ComponentTransform::OnInspector()
{
	if(ImGui::CollapsingHeader((std::string("Transform##") + std::to_string(UUID)).data()))
	{
		ImGui::Text("UUID: %u", UUID);
	}
}
