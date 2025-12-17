#pragma once

#include "../Transform.h"
#include "../Vector3.h"

class PhysicsComponent
{
public:
	PhysicsComponent(Transform* _transform);

	void Update(float _deltaTime);

	XMFLOAT3 GetVelocity() { return m_velocity; }
	void SetVelocity(XMFLOAT3 _newVelocity);

	bool accelarate = false;

protected:
	Transform* m_transform;
	XMFLOAT3 m_velocity;
	XMFLOAT3 m_acceleration;
};