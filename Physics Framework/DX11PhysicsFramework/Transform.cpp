#include "Transform.h"

Transform::Transform()
{
	SetPosition(XMFLOAT3());
	SetRotation(XMFLOAT3());
	SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));
}

Transform::~Transform()
{

}