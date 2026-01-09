#pragma once

#include "../Transform.h"
#include "../Vector3.h"
#include "../Collider.h"

class PhysicsComponent
{
public:
	PhysicsComponent(Transform* _transform, float _mass);
	~PhysicsComponent();

	virtual void Update(float _deltaTime) = 0;

	virtual Vector3 GetVelocity() { return m_velocity; }
	virtual void SetVelocity(Vector3 _newVelocity) { m_velocity = _newVelocity; }

	virtual void AddForce(Vector3 _force) = 0 { m_netForce += _force; }

	virtual	void SimulateGravity() { if (isSimulatingGravity) AddForce(Vector3(0, -m_gravitationalConstant, 0)); }
	virtual	Vector3 SimulateDrag() = 0;
	virtual	void SimulateFriction(bool _hasContact, float _deltaTime) = 0;
	virtual void LinearStabiliser(Vector3 _desiredVelocity) = 0;

	bool IsCollideable() const { return m_collider != nullptr; }

	void SetCollider(Collider* _collider) { m_collider = _collider; }
	Collider* GetCollider() const { return m_collider; }

	bool accelarate = false;
	bool isSimulatingGravity = false;

protected:
	Transform* m_transform;
	float m_mass;
	float m_gravitationalConstant = 9.8f;
	float m_terminalVelocity = 15.0f;

	Vector3 m_velocity;
	Vector3 m_acceleration;

	Vector3 m_netForce;

	Collider* m_collider = nullptr;
};