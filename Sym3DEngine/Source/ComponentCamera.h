#pragma once

#include "Component.h"
#include "MathGeoLib/include/Geometry/Frustum.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* gameObject);

	void UpdateFrustum();

private:
	math::Frustum frustum;

	float near = 0.3f, far = 3000.0f;
	float verticalFOV = 60.0f;
};