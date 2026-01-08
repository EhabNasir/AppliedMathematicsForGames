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

	void SimulateGravity() override { if (isSimulatingGravity) AddForce(Vector3(0, -m_gravitationalConstant, 0)); }

	Vector3 SimulateDrag() override;

	void SimulateFriction(bool _hasContact, float _deltaTime) override;

	void LinearStabiliser(Vector3 _desiredVelocity) override;

private:
	Vector3 m_startPosition;
	float m_lifeTime;
	float m_resetTime;
	bool m_gravityInverted;
};