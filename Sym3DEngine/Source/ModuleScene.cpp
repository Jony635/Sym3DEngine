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

bool ModuleScene::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_DELETE) == KeyState::KEY_DOWN)
	{
		if (!selections.empty())
		{
			for (int i = 0; i < selections.size(); ++i)
			{
				Selection selection = selections[i];
				switch (selection.type)
				{
					case SelectionType::GAMEOBJECT_SELECTION:
					{
						GameObject* toDelete = (GameObject*)selection.goSelection.gameObject;
						if (toDelete->parent)
							toDelete->parent->EraseChild(toDelete);

						EraseGameObject(toDelete);

						selections.erase(selections.begin() + i);

						delete toDelete; //TODO: MOVE THIS INTO AN EVENT

						i--;
						break;
					}
				}
			}
		}
	}

	return true;
}

GameObject* ModuleScene::CreateGameObject()
{
	GameObject* ret = new GameObject(root);
	gameObjects.push_back(ret);
	root->childs.push_back(ret);

	GameObjectHierarchyClicked(ret);

	return ret;
}

void ModuleScene::GameObjectHierarchyClicked(GameObject* gameObject)
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

				//TODO: ADD THE RESOURCES CASE HERE
			}
		}

		selections.clear();
		Selection selection;
		selection.goSelection.type = SelectionType::GAMEOBJECT_SELECTION;
		selection.goSelection.gameObject = gameObject;
		selections.push_back(selection);

		gameObject->selected = true;
	}
}

void ModuleScene::DeselectAll()
{
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

			//TODO: ADD THE RESOURCES CASE HERE
		}
	}

	selections.clear();
}

void ModuleScene::EraseGameObject(GameObject* gameObject)
{
	for (int i = 0; i < gameObjects.size(); ++i)
	{
		if (gameObjects[i] == gameObject)
		{
			gameObjects.erase(gameObjects.begin() + i);
			break;
		}
	}

	for (int i = 0; i < dynamic_gos.size(); ++i)
	{
		if (dynamic_gos[i] == gameObject)
		{
			dynamic_gos.erase(dynamic_gos.begin() + i);
			break;
		}
	}

	for (int i = 0; i < static_gos.size(); ++i)
	{
		if (static_gos[i] == gameObject)
		{
			static_gos.erase(static_gos.begin() + i);
			break;
		}
	}
}