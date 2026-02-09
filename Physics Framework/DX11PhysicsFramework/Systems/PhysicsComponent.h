#pragma once

#include "../Transform.h"
#include "../Vector3.h"
#include "../Collider.h"
//#include "../GameObject.h"

class GameObject;

class PhysicsComponent
{
public:
	PhysicsComponent(Transform* _transform, float _mass);
	~PhysicsComponent();

	virtual void Update(float _deltaTime) = 0;

	Transform* GetTransform() { return m_transform; }

	virtual Vector3 GetVelocity() { return m_velocity; }
	virtual void SetVelocity(Vector3 _newVelocity) { m_velocity = _newVelocity; }

	float GetTerminalVelocity() { return m_terminalVelocity; }

	virtual float GetInverseMass() { return m_inverseMass; }
	virtual float GetMass() { return m_mass; }
	void SetInverseMass(float _newMass) { m_inverseMass = _newMass; }
	void SetMass(float _newMass) { m_mass = _newMass; }
	float GetGravitationalConstant() { return m_gravitationalConstant; }

	virtual void AddForce(Vector3 _force) { m_netForce += _force; }
	virtual void LinearStabiliser(Vector3 _desiredVelocity) = 0;
	virtual void WorldLinearStabiliser(Vector3 _desiredVelocity) = 0;

	virtual Quaternion GetOrientation() { return m_orientation; }
	virtual Vector3 GetAngularVelocity() { return m_velocity; }
	virtual void SetAngularVelocity(Vector3 _newVelocity) { m_angularVelocity = _newVelocity; }
	virtual void AddRotationalForce(Vector3 _force) { m_netAngularForce += _force; }
	virtual void CalculateRotation( Vector3 _force, Vector3 _point, Vector3 _halfExtents) = 0;

	virtual	void SimulateGravity() { if (isSimulatingGravity) AddForce(Vector3(0, -m_gravitationalConstant, 0)); }
	virtual	Vector3 SimulateDrag() = 0;
	virtual	void SimulateFriction(bool _hasContact, float _deltaTime) = 0;
	virtual void ApplyImpulse(Vector3 _impulse);

	//Ship Variables -> abstract later
	Vector3 GetThrottle() { return m_throttle; }
	virtual void SetThrottle(Vector3 _throttle) { m_throttle += _throttle; }

	bool IsCollideable() const { return m_collider != nullptr; }

	void SetCollider(Collider* _collider) { m_collider = _collider; }
	Collider* GetCollider() const { return m_collider; }

	bool accelarate = false;
	bool isSimulatingGravity = false;

protected:
	Transform* m_transform;
	float m_mass;
	float m_inverseMass = 1/ m_mass;
	float m_gravitationalConstant = 9.8f;
	float m_terminalVelocity = 15.0f;

	Vector3 m_velocity;
	Vector3 m_acceleration;
	Vector3 m_netForce;

	//Ship Variables -> abstract later
	Vector3 m_throttle = Vector3(0, 0, 0);

	Quaternion m_orientation;
	Vector3 m_netAngularForce;
	Vector3 m_angularVelocity;

	Collider* m_collider = nullptr;
};