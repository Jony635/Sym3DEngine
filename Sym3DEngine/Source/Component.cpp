#include "Component.h"

#include "Application.h"

Component::Component()
{
	UUID = App->GetRandomUUID();
}
