#pragma once
#include "PhysicsComponent.h"

class ParticleModel : public PhysicsComponent
{
public:
	ParticleModel(Transform* _transform);

	void Update(float _deltaTime) override;

	XMFLOAT3 GetVelocity() override { return m_velocity; }
	void SetVelocity(XMFLOAT3 _newVelocity) override;
};