#include "GameObject.h"
#include "ComponentCamera.h"
#include "ComponentTransform.h"

ComponentCamera* ComponentCamera::activeCamera = nullptr;
ComponentCamera* ComponentCamera::editorCamera = nullptr;
ComponentCamera* ComponentCamera::gameCamera = nullptr;

ComponentCamera::ComponentCamera(GameObject* gameObject) : Component(gameObject, ComponentType::CAMERA)
{
	frustum.SetKind(math::FrustumProjectiveSpace::FrustumSpaceGL, math::FrustumHandedness::FrustumRightHanded);
	frustum.SetViewPlaneDistances(near, far);

	//TODO: GET THE ASPECT RATIO FROM IMGUI WINDOW / SDL
	frustum.SetVerticalFovAndAspectRatio(verticalFOV, 16 / 9);

	UpdateFrustum();
}

void ComponentCamera::UpdateFrustum()
{
	if (gameObject->transform)
	{
		math::float4x4 globalMat = gameObject->transform->GetGlobalMatrix();

		math::float3 up, front;
		up = globalMat.TransformDir(math::float3(0, 1, 0));
		front = globalMat.TransformDir(math::float3(0, 0, 1));

		math::float3 globalPos, scale;
		math::Quat rotate;

		globalMat.Decompose(globalPos, rotate, scale);

		frustum.SetFrame(globalPos, front, up);
	}
}

void ComponentCamera::OnTransformChanged()
{
	UpdateFrustum();
}
