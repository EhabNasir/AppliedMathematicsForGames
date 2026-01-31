#pragma once
#include "../Systems/PhysicsComponent.h"
#include "Quaternion.h"

class RigidBodyModel : public PhysicsComponent
{
public:
	RigidBodyModel(Transform* _transform, float _mass);

	void Update(float _deltaTime) override;

	Vector3 GetVelocity() override { return m_velocity; }
	void SetVelocity(Vector3 _newVelocity) override;

	void AddForce(Vector3 _force) override { m_netForce += _force; }

	Quaternion GetOrientation() override { return m_orientation; }
	void CalculateRotation(Vector3 _force, Vector3 _point, Vector3 _halfExtents) override;

	Vector3 SimulateDrag() override;

	void SimulateFriction(bool _hasContact, float _deltaTime) override;

	void LinearStabiliser(Vector3 _desiredVelocity) override;
	void WorldLinearStabiliser(Vector3 _desiredVelocity) override;

private:
	float m_inverseMass;
	float m_linearDampening;

	Vector3 m_worldForward;
	Vector3 m_torque;
	Vector3 m_angularVelocity;
	XMVECTOR transformMatrix;
	XMFLOAT3X3 m_inertiaTensor;
	float m_angularDampening = 0.94f;
};

