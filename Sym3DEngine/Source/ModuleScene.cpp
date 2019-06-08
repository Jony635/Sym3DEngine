#include "Application.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "GameObject.h"

#include "SDL/include/SDL.h"

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

void ModuleScene::GameObjectClicked(GameObject* gameObject)
{
	if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
	{
		if (gameObject->selected)
		{
			gameObject->selected = false;
			for (int i = 0; i < selections.size(); ++i)
			{
				if (selections[i].type == SelectionType::GAMEOBJECT_SELECTION)
				{
					if (selections[i].goSelection.gameObject == gameObject)
					{
						selections.erase(selections.begin() + i);
						break;
					}
				}
			}
		}
		else
		{
			gameObject->selected = true;

			Selection selection;
			selection.goSelection.type = SelectionType::GAMEOBJECT_SELECTION;
			selection.goSelection.gameObject = gameObject;

			selections.push_back(selection);
		}
	}
	else
	{
		gameObject->selected = true;

		for (int i = 0; i < selections.size(); ++i)
		{
			switch (selections[i].type)
			{
				case SelectionType::GAMEOBJECT_SELECTION:
				{
					GameObject* gameObject = (GameObject*)selections[i].goSelection.gameObject;
					gameObject->selected = false;
					break;
				}
			}
		}

		selections.clear();
		Selection selection;
		selection.goSelection.type = SelectionType::GAMEOBJECT_SELECTION;
		selection.goSelection.gameObject = gameObject;
		selections.push_back(selection);
	}
}
