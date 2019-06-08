#include "ModuleScene.h"
#include "GameObject.h"

ModuleScene::ModuleScene(bool createRoot)
{
	if(createRoot)
		root = new GameObject();
}

GameObject* ModuleScene::CreateGameObject()
{
	GameObject* ret = new GameObject();
	gameObjects.push_back(ret);
	root->childs.push_back(ret);

	return ret;
}
