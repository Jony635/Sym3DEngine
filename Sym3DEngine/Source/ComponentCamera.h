#pragma once

#include "Component.h"
#include "MathGeoLib/include/Geometry/Frustum.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* gameObject);

	void UpdateFrustum();
	void OnTransformChanged();

	math::float4x4 GetViewMatrix() const;
	math::float4x4 GetProjectionMatrix() const;

public:
	static ComponentCamera* activeCamera;
	static ComponentCamera* editorCamera;
	static ComponentCamera* gameCamera;

	bool isEditorCamera = false;

private:
	math::Frustum frustum;

	float near = 0.01f, far = 3000.0f;
	float verticalFOV = 60.0f;
};