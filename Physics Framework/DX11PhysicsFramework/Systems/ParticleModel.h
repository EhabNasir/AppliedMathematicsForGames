#pragma once
#include "PhysicsComponent.h"

class ParticleModel : public PhysicsComponent
{
public:
	ParticleModel(Transform* _transform, float _mass);

	void Update(float _deltaTime) override;

	Vector3 GetVelocity() override { return m_velocity; }
	void SetVelocity(Vector3 _newVelocity) override;

	void AddForce(Vector3 _force) override { m_netForce += _force; }
};