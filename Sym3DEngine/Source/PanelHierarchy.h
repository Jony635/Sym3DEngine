#pragma once

#include "Panel.h"

class GameObject;

class PanelHierarchy : public Panel
{
public:
	void Draw();

private:
	void DrawGameObjectsRecursive(GameObject* root);
};