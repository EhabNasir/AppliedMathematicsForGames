#pragma once

#include "../Transform.h"
#include "../Vector3.h"

class PhysicsComponent
{
public:
	PhysicsComponent(Transform* _transform);

	virtual void Update(float _deltaTime) = 0;

	virtual XMFLOAT3 GetVelocity() { return m_velocity; }
	virtual void SetVelocity(XMFLOAT3 _newVelocity) { m_velocity = _newVelocity; }

	bool accelarate = false;

protected:
	Transform* m_transform;
	XMFLOAT3 m_velocity;
	XMFLOAT3 m_acceleration;
};