#include <cmath>
#include "ParticleModel.h"
#include "../Debug.h"

ParticleModel::ParticleModel(Transform* _transform, float _mass) : PhysicsComponent(_transform, _mass)
{

}

void ParticleModel::Update(float _deltaTime)
{
    //Add forces
    ParticleModel::SimulateGravity();
    AddForce(SimulateDrag());

    Vector3 position = m_transform->GetPosition();

    //Calculate acceleration
    m_acceleration = m_netForce / m_mass;

    //Integrate Velocity
    m_velocity += m_acceleration * _deltaTime;

    //Integrate position
    position += m_velocity * _deltaTime;

    m_transform->SetPosition(position);

    //clear forces
    m_netForce = Vector3(0, 0, 0);
    m_acceleration = Vector3(0, 0, 0);
}

void ParticleModel::SetVelocity(Vector3 _newVelocity)
{
    m_velocity = _newVelocity;
}

Vector3 ParticleModel::SimulateDrag()
{
    Vector3 v = GetVelocity();
    float speed = v.Magnitude();
    v.Normalize();

    float p = 0.3f;
    float k1 = p * ((m_gravitationalConstant * m_mass) / m_terminalVelocity);
    float k2 = (1 - p) * ((m_gravitationalConstant * m_mass) / std::pow(m_terminalVelocity, 2));

    float dragMagnitude = k1 * speed + k2 * std::pow(speed, 2);

    Vector3 dragForce = -v * dragMagnitude;

    return dragForce;
}