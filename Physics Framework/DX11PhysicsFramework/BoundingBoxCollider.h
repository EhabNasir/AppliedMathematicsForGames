#pragma once
#include "Collider.h"
#include "Vector3.h"

class BoundingBoxCollider : public Collider
{
public:
	BoundingBoxCollider(Transform* _transform);

	virtual bool CollidesWith(Collider& _other, CollisionInfo& _info) override { return _other.CollidesWith(*this, _info); }
	virtual bool CollidesWith(BoundingBoxCollider& _other, CollisionInfo& _info) override;
	virtual bool CollidesWith(SphereCollider& _other, CollisionInfo& _info) override;
	virtual bool CollidesWith(PlaneCollider& _other, CollisionInfo& _info) override;

	Vector3 GetCentre() const { return m_transform->GetPosition(); }
	// NOTE: Transform scale represents half-size so no need to *0.5f
	Vector3 GetHalfExtents() const { return m_transform->GetScale(); }
	Vector3 GetMin() const { return GetCentre() - GetHalfExtents(); }
	Vector3 GetMax() const { return GetCentre() + GetHalfExtents(); }
};

