#include "SphereCollider.h"
#include "BoundingBoxCollider.h"
#include "PlaneCollider.h"
#include <cmath>

bool SphereCollider::CollidesWith(SphereCollider& _other, CollisionInfo& _info)
{
	Vector3 distance = _other.m_transform->GetPosition() - m_transform->GetPosition();

	float radiiSum = _other.GetRadius() + GetRadius();

	_info.penDepth =  radiiSum - distance.Magnitude();

	if (distance.Magnitude() <= radiiSum)
	{
		return true;
	}

	return false;
}

bool SphereCollider::CollidesWith(BoundingBoxCollider& _other, CollisionInfo& _info)
{
	return false;
}

bool SphereCollider::CollidesWith(PlaneCollider& _other, CollisionInfo& _info)
{
	return false;
}
