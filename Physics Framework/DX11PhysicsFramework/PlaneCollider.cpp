#include <cmath>
#include "PlaneCollider.h"
#include "BoundingBoxCollider.h"
#include "SphereCollider.h"

PlaneCollider::PlaneCollider(Transform* _transform, Vector3 _normal) : Collider(_transform)
{
	m_normal = _normal;
	m_normal.Normalize();
	m_distance = -(_normal * _transform->GetPosition());
}

bool PlaneCollider::CollidesWith(PlaneCollider& _other)
{
	return false;
}

bool PlaneCollider::CollidesWith(SphereCollider& _other)
{
	float radius = _other.GetRadius();
	Vector3 sphereCentre = _other.GetPosition();

	float distance = (m_normal * sphereCentre) + m_distance;

	return distance <= radius;
}

bool PlaneCollider::CollidesWith(BoundingBoxCollider& _other)
{
	Vector3 boxCentre = _other.GetCentre();
	Vector3 halfExtent = _other.GetHalfExtents();

	float projectedRadius = halfExtent.x * std::abs(m_normal.x) +
		halfExtent.y * std::abs(m_normal.y) +
		halfExtent.z * std::abs(m_normal.z);

	float distance = (m_normal * boxCentre) + m_distance;

	return distance <= projectedRadius;
}