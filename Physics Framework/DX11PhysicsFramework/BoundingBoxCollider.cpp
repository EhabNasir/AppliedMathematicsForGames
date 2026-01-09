#include "BoundingBoxCollider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "Debug.h"

BoundingBoxCollider::BoundingBoxCollider(Transform* _transform) : Collider(_transform)
{
}

bool BoundingBoxCollider::CollidesWith(BoundingBoxCollider& _other)
{
	bool xOverlap = GetMin().x <= _other.GetMax().x && GetMax().x >= _other.GetMin().x;
	bool yOverlap = GetMin().y <= _other.GetMax().y && GetMax().y >= _other.GetMin().y;
	bool zOverlap = GetMin().z <= _other.GetMax().z && GetMax().z >= _other.GetMin().z;

	bool isOverlapping = xOverlap && yOverlap && zOverlap;

	//Debug::PrintArguments(" | A min: %f max: %f | B min: %f max: %f",
	//	GetMin().x, GetMax().x,
	//	_other.GetMin().x, _other.GetMax().x);

	return isOverlapping;
}

bool BoundingBoxCollider::CollidesWith(SphereCollider& _other)
{
	return false;
}

bool BoundingBoxCollider::CollidesWith(PlaneCollider& _other)
{
	return false;
}