#include <algorithm>

#include "BoundingBoxCollider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "Debug.h"

BoundingBoxCollider::BoundingBoxCollider(Transform* _transform) : Collider(_transform)
{
}

bool BoundingBoxCollider::CollidesWith(BoundingBoxCollider& _other, CollisionInfo& _info)
{
    _info.halfExtents = GetHalfExtents();

	bool xOverlap = GetMin().x <= _other.GetMax().x && GetMax().x >= _other.GetMin().x;
	bool yOverlap = GetMin().y <= _other.GetMax().y && GetMax().y >= _other.GetMin().y;
	bool zOverlap = GetMin().z <= _other.GetMax().z && GetMax().z >= _other.GetMin().z;

    // for penDepth
    float overlapX = min(GetMax().x, _other.GetMax().x) - max(GetMin().x, _other.GetMin().x);
    float overlapY = min(GetMax().y, _other.GetMax().y) - max(GetMin().y, _other.GetMin().y);
    float overlapZ = min(GetMax().z, _other.GetMax().z) - max(GetMin().z, _other.GetMin().z);

    //Check which axis has the leastaroony overlapparoony
    if (overlapX < overlapY && overlapX < overlapZ)
    {
        _info.penDepth = overlapX;
    }
    else if (overlapY < overlapZ)
    {
        _info.penDepth = overlapY;
    }
    else
    {
        _info.penDepth = overlapZ;
    }

	bool isOverlapping = xOverlap && yOverlap && zOverlap;

	return isOverlapping;
}

bool BoundingBoxCollider::CollidesWith(SphereCollider& _other, CollisionInfo& _info)
{
	return false;
}

bool BoundingBoxCollider::CollidesWith(PlaneCollider& _other, CollisionInfo& _info)
{
	return false;
}