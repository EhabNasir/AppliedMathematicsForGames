#pragma once
#include "Transform.h"
#include "Vector3.h"

class SphereCollider;

class Collider
{
public:
	Collider(Transform* _transform) { m_transform = _transform; }

	virtual bool CollidesWith(Collider& _other) = 0;
	virtual bool CollidesWith(SphereCollider& _other) = 0;

	Vector3 GetPosition() const { return m_transform->GetPosition(); }

protected:
	Transform* m_transform;
};