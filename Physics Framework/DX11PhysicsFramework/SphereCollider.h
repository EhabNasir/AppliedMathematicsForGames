#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(Transform* _transform, float _radius) : Collider(_transform) { m_radius = _radius; }

	virtual bool CollidesWith(Collider& _other, CollisionInfo& _info) override { return _other.CollidesWith(*this, _info); }
	virtual bool CollidesWith(SphereCollider& _other, CollisionInfo& _info) override;
	virtual bool CollidesWith(BoundingBoxCollider& _other, CollisionInfo& _info) override;
	virtual bool CollidesWith(PlaneCollider& _other, CollisionInfo& _info) override;

	float GetRadius() const { return m_radius; }

private:
	float m_radius = 1.0f;
};

