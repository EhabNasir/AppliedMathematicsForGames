#include "PlaneCollider.h"

PlaneCollider::PlaneCollider(Transform* _transform) : Collider(_transform)
{

}

bool PlaneCollider::CollidesWith(SphereCollider& _other)
{
	return false;
}

bool PlaneCollider::CollidesWith(BoundingBoxCollider& _other)
{
	return false;
}