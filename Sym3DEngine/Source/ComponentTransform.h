#pragma once

#include "Component.h"
#include "MathGeoLib/include/Math/float3.h"
#include "MathGeoLib/include/Math/quat.h"
#include "MathGeoLib/include/Math/float4x4.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* gameObject);
	void OnInspector();

public:
	void UpdateMatricesFromLocal();
	void UpdateMatricesFromGlobal();

protected:
	math::float3 position, scale;
	math::Quat rotation;
	math::float4x4 localMatrix, globalMatrix;

};