#include "PhysicsComponent.h"
#include "../SphereCollider.h"
#include "../BoundingBoxCollider.h"
#include "../GameObject.h"

PhysicsComponent::PhysicsComponent(Transform* _transform, float _mass) : m_transform(_transform), m_mass(_mass), m_velocity(0, 0, 0), m_acceleration(0, 2.0f, 0)
{
	//m_collider = new SphereCollider(_transform, 1);
	//m_collider = new BoundingBoxCollider(_transform);
}

PhysicsComponent::~PhysicsComponent()
{
	if(m_collider != nullptr)
		delete m_collider;
}

void PhysicsComponent::ApplyImpulse(Vector3 _impulse)
{
	//Vector3 collisionNormal = m_transform->GetPosition() - _collidedObject->GetTransform()->GetPosition();
	//collisionNormal.Normalize();
	//Vector3 relativeVelocity =  GetVelocity() - _collidedObject->GetPhysics()->GetVelocity();
	//float coeffRestitution = 1.0f;

	//float seperatingVelocity = collisionNormal * relativeVelocity;

	//if (seperatingVelocity > 0)
	//	return;

	////float newSeperatingVelocity = -seperatingVelocity * coeffRestitution;

	////float deltaVelocity = newSeperatingVelocity - seperatingVelocity;

	//float totalInverseMass = GetInverseMass() + _collidedObject->GetPhysics()->GetInverseMass();

	//float scalarImpulseMag = -((1 + coeffRestitution)*(relativeVelocity * collisionNormal)) / totalInverseMass;

	//Vector3 impulse1 = GetInverseMass() * scalarImpulseMag * collisionNormal;
	//Vector3 impulse2 = -(_collidedObject->GetPhysics()->GetInverseMass() * scalarImpulseMag * collisionNormal);

	//SetVelocity(GetVelocity() + impulse1);
	//_collidedObject->GetPhysics()->SetVelocity(_collidedObject->GetPhysics()->GetVelocity() + impulse2);

	SetVelocity(GetVelocity() + _impulse);
}