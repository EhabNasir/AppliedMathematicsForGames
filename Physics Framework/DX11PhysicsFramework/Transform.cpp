#include "Transform.h"

Transform::Transform()
{
	SetPosition(Vector3(0,0,0));
	SetRotation(XMFLOAT3());
	SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));
}

Transform::~Transform()
{

}