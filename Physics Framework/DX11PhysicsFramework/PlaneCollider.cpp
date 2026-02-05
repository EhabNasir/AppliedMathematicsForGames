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

bool PlaneCollider::CollidesWith(PlaneCollider& _other, CollisionInfo& _info)
{
	return false;
}

bool PlaneCollider::CollidesWith(SphereCollider& _other, CollisionInfo& _info)
{
	//if distance between plane & sphere < than sphere radius then colliosn
	float radius = _other.GetRadius();
	Vector3 sphereCentre = _other.GetPosition();

	//float distance = m_normal.y - sphereCentre.y;
	float distance = (m_normal * sphereCentre) + m_distance;

	_info.normal = m_normal;
	_info.penDepth = radius - distance;

	return distance <= radius;
}

bool PlaneCollider::CollidesWith(BoundingBoxCollider& _other, CollisionInfo& _info)
{
	Vector3 boxCentre = _other.GetCentre();
	Vector3 halfExtent = _other.GetHalfExtents();

	float projectedRadius = std::abs(m_normal.x) * halfExtent.x +
							std::abs(m_normal.y) * halfExtent.y +
							std::abs(m_normal.z) * halfExtent.z;

	//distance isn't doing anything for some reason -> should offset from world origin??
	//Dot(normal, any point on plane) + offset from origin
	float distance = (m_normal * boxCentre) + m_distance;

	if (distance <= projectedRadius)
	{
		_info.penDepth = projectedRadius - distance;
		_info.normal = m_normal;

		//used halfextent but this just represents the contact point
		_info.halfExtents = boxCentre - m_normal * distance;

		return true;
	}

	return false;
}