#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(Transform* _transform, float _radius) : Collider(m_transform) { _radius = m_radius; }

	virtual bool CollidesWith(Collider& _other) override { return _other.CollidesWith(*this); }
	virtual bool CollidesWith(SphereCollider& _other) override;

	float GetRadius() const { return m_radius; }

private:
	float m_radius = 1.0f;
};

