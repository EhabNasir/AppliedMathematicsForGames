#include "PhysicsComponent.h"
#include "../SphereCollider.h"

PhysicsComponent::PhysicsComponent(Transform* _transform, float _mass) : m_transform(_transform), m_mass(_mass), m_velocity(0, 0, 0), m_acceleration(0, 2.0f, 0)
{
	m_collider = new SphereCollider(_transform, 1);
}

PhysicsComponent::~PhysicsComponent()
{
	delete m_collider;
}