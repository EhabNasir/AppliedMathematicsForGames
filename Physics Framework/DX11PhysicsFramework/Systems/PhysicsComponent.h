#pragma once

#include "../Transform.h"
#include "../Vector3.h"

class PhysicsComponent
{
public:
	PhysicsComponent(Transform* _transform, float _mass);

	virtual void Update(float _deltaTime) = 0;

	virtual Vector3 GetVelocity() { return m_velocity; }
	virtual void SetVelocity(Vector3 _newVelocity) { m_velocity = _newVelocity; }

	virtual void AddForce(Vector3 _force) = 0 { m_netForce += _force; }

	bool accelarate = false;

protected:
	Transform* m_transform;
	float m_mass;

	Vector3 m_velocity;
	Vector3 m_acceleration;

	Vector3 m_netForce;
};