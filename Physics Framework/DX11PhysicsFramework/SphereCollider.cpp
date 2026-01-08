#include "SphereCollider.h"

bool SphereCollider::CollidesWith(SphereCollider& _other)
{
	float distance = _other.m_transform->GetPosition().Magnitude() - m_transform->GetPosition().Magnitude();

	if (distance < _other.GetRadius() + GetRadius())
	{
		//Is colliding = true;
	}
}
