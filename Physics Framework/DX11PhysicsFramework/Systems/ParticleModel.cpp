#include "ParticleModel.h"
#include "../Debug.h"

ParticleModel::ParticleModel(Transform* _transform, float _mass) : PhysicsComponent(_transform, _mass)
{

}

void ParticleModel::Update(float _deltaTime)
{
    Vector3 position = m_transform->GetPosition();

    m_acceleration = m_netForce / m_mass;

    m_velocity += m_acceleration * _deltaTime;

    position += m_velocity * _deltaTime;

    m_transform->SetPosition(position);

    m_netForce = Vector3(0, 0, 0);
    m_acceleration = Vector3(0, 0, 0);
}

void ParticleModel::SetVelocity(Vector3 _newVelocity)
{
    m_velocity = _newVelocity;
}