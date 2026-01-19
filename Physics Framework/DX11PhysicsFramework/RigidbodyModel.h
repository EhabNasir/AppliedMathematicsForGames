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

	void CalculateRotation(Vector3 _force, Vector3 _leverArm, XMFLOAT3X3 _inertia, float _deltaTime);

	//void SimulateGravity() override { if (isSimulatingGravity) AddForce(Vector3(0, -m_gravitationalConstant, 0)); }

	Vector3 SimulateDrag() override;

	void SimulateFriction(bool _hasContact, float _deltaTime) override;

	void LinearStabiliser(Vector3 _desiredVelocity) override;

	//void ApplyImpulse(GameObject* _collisionObject) override;

private:
	float m_inverseMass = 1/m_mass;
	float m_linearDampening;

	Quaternion m_orientation;
	Vector3 m_angularVelocity;
	XMVECTOR transformMatrix;
};

