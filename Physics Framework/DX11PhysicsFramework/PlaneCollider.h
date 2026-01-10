#pragma once
#include "Collider.h"

class PlaneCollider : public Collider
{
public:
	PlaneCollider(Transform* _transform, Vector3 _normal);

	virtual bool CollidesWith(Collider& _other) override { return _other.CollidesWith(*this); }
	virtual bool CollidesWith(PlaneCollider& _other) override;
	virtual bool CollidesWith(BoundingBoxCollider& _other) override;
	virtual bool CollidesWith(SphereCollider& _other) override;

private:
	Vector3 m_normal;
	float m_distance;
};

