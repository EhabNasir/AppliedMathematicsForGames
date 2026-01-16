#pragma once
#include "Collider.h"

class PlaneCollider : public Collider
{
public:
	PlaneCollider(Transform* _transform, Vector3 _normal);

	virtual bool CollidesWith(Collider& _other, CollisionInfo& _info) override { return _other.CollidesWith(*this, _info); }
	virtual bool CollidesWith(PlaneCollider& _other, CollisionInfo& _info) override;
	virtual bool CollidesWith(BoundingBoxCollider& _other, CollisionInfo& _info) override;
	virtual bool CollidesWith(SphereCollider& _other, CollisionInfo& _info) override;

private:
	Vector3 m_normal;
	float m_distance;
};

