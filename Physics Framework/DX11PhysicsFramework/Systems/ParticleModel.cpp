#include "ParticleModel.h"

ParticleModel::ParticleModel(Transform* _transform) : PhysicsComponent(_transform)
{

}

void ParticleModel::Update(float _deltaTime)
{
    XMFLOAT3 position = m_transform->GetPosition();

    XMVECTOR pos = XMLoadFloat3(&position);
    XMVECTOR vel = XMLoadFloat3(&m_velocity);
    XMVECTOR acc = XMLoadFloat3(&m_acceleration);

    if (accelarate)
        vel += acc * _deltaTime;

    pos += vel * _deltaTime;

    XMStoreFloat3(&m_velocity, vel);
    XMStoreFloat3(&position, pos);

    m_transform->SetPosition(position);
}

void ParticleModel::SetVelocity(XMFLOAT3 _newVelocity)
{
    m_velocity = _newVelocity;
}