#include "SphereCollider.h"
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
