#include "Application.h"
#include "GameObject.h"

GameObject::GameObject()
{
	UUID = App->GetRandomUUID();
}