#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(Transform* _transform) : m_transform(_transform), m_velocity(0, 0, 0), m_acceleration(0, 2.0f, 0)
{
}