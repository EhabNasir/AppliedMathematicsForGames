#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(Transform* _transform) : m_transform(_transform), m_velocity(0, 0, 0), m_acceleration(0, 2.0f, 0)
{
}

void PhysicsComponent::Update(float _deltaTime)
{
    XMFLOAT3 position = m_transform->GetPosition();

    XMVECTOR pos = XMLoadFloat3(&position);
    XMVECTOR vel = XMLoadFloat3(&m_velocity);
    XMVECTOR acc = XMLoadFloat3(&m_acceleration);

    if(accelarate)
        vel += acc * _deltaTime;

    pos += vel * _deltaTime;

    XMStoreFloat3(&m_velocity, vel);
    XMStoreFloat3(&position, pos);

    m_transform->SetPosition(position);
}

void PhysicsComponent::SetVelocity(XMFLOAT3 _newVelocity)
{
    m_velocity = _newVelocity;
}