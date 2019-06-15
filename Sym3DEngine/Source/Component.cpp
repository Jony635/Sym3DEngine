#include "Component.h"

#include "Application.h"

Component::Component(GameObject* gameObject) : gameObject(gameObject)
{
	UUID = App->GetRandomUUID();
}
