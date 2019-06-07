#include "ModuleScene.h"
#include "GameObject.h"

ModuleScene::ModuleScene(bool createRoot)
{
	if(createRoot)
		root = new GameObject();
}
