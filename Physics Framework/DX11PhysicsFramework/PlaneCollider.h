#pragma once
#include "Collider.h"

class PlaneCollider : public Collider
{
public:
	PlaneCollider(Transform* _transform);

	virtual bool CollidesWith(Collider& _other) override { return _other.CollidesWith(*this); }
	virtual bool CollidesWith(BoundingBoxCollider& _other) override;
	virtual bool CollidesWith(SphereCollider& _other) override;
};

