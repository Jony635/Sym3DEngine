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

	inline math::float3 GetPosition() const { return position; }
	inline math::Quat GetRotation() const { return rotation; }
	inline math::float3 GetScale() const { return scale; }

	void Move(math::float3 distance);
	void MoveTo(math::float3 position);

	inline math::float4x4 GetGlobalMatrix() const { return globalMatrix; }

protected:
	math::float3 position, scale;
	math::Quat rotation;
	math::float4x4 localMatrix, globalMatrix;

};