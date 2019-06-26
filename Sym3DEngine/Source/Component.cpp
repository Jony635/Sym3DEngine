#include "Application.h"
#include "GameObject.h"
#include "Component.h"

Component::Component(GameObject* gameObject, ComponentType type) : gameObject(gameObject), type(type)
{
	UUID = App->GetRandomUUID();
}

bool Component::IsTreeActive() const
{
	bool treeActive = active;
	GameObject* go = this->gameObject;

	while (treeActive && go)
	{
		treeActive = go->IsActive();
		go = go->parent;
	}

	return treeActive;
}
