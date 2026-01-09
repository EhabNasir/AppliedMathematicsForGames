#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(Transform* _transform, float _radius) : Collider(_transform) { m_radius = _radius; }

	virtual bool CollidesWith(Collider& _other) override { return _other.CollidesWith(*this); }
	virtual bool CollidesWith(SphereCollider& _other) override;
	virtual bool CollidesWith(BoundingBoxCollider& _other) override;
	virtual bool CollidesWith(PlaneCollider& _other) override;

	float GetRadius() const { return m_radius; }

private:
	float m_radius = 1.0f;
};

