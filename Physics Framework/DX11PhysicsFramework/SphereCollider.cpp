#include "SphereCollider.h"
#include "BoundingBoxCollider.h"
#include "PlaneCollider.h"
#include <cmath>

bool SphereCollider::CollidesWith(SphereCollider& _other)
{
	Vector3 distance = _other.m_transform->GetPosition() - m_transform->GetPosition();

	if (distance.Magnitude() <= _other.GetRadius() + GetRadius())
	{
		return true;
	}

	return false;
}

bool SphereCollider::CollidesWith(BoundingBoxCollider& _other)
{
	return false;
}

bool SphereCollider::CollidesWith(PlaneCollider& _other)
{
	return false;
}
