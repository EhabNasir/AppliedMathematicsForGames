#include <cmath>

#include "RigidbodyModel.h"
#include "../Debug.h"

RigidBodyModel::RigidBodyModel(Transform* _transform, float _mass) : PhysicsComponent(_transform, _mass)
{

}

void RigidBodyModel::Update(float _deltaTime)
{
    //Add forces
    RigidBodyModel::SimulateGravity();
    AddForce(SimulateDrag());
    //SimulateFriction(true, _deltaTime);

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

void RigidBodyModel::SetVelocity(Vector3 _newVelocity)
{
    m_velocity = _newVelocity;
}

Vector3 RigidBodyModel::SimulateDrag()
{
    Vector3 v = GetVelocity();
    float speed = v.Magnitude();
    if (speed <= 0.0001f)
        return Vector3(0, 0, 0);

    v.Normalize();

    float p = 0.3f;
    float k1 = p * ((m_gravitationalConstant * m_mass) / m_terminalVelocity);
    float k2 = (1 - p) * ((m_gravitationalConstant * m_mass) / std::pow(m_terminalVelocity, 2));

    float dragMagnitude = k1 * speed + k2 * std::pow(speed, 2);

    Vector3 dragForce = -v * dragMagnitude;

    return dragForce;
}

void RigidBodyModel::SimulateFriction(bool _hasContact, float deltaTime)
{
    if (_hasContact)
    {
        Vector3 v = GetVelocity();
        float speed = v.Magnitude();

        if (speed > 0.1f)
        {
            Vector3 dir = v;
            dir.Normalize();

            float normal = m_mass * m_gravitationalConstant;
            float kineticFrictionCoeff = 9.0f;

            Vector3 frictionForce = -dir * (kineticFrictionCoeff * normal);

            float frictionAcceleration = frictionForce.Magnitude() / m_mass;

            float dv = frictionAcceleration * deltaTime;

            if (dv >= speed)
            {
                m_velocity = Vector3(0, 0, 0);
            }
            else
            {
                AddForce(frictionForce);
            }
        }
    }
}

void RigidBodyModel::LinearStabiliser(Vector3 _desiredVelocity)
{
    Vector3 unwantedVelocity = m_velocity - _desiredVelocity;

    Vector3 error = -unwantedVelocity;

    Vector3 stabiliserForce = error * 0.3;

    AddForce(stabiliserForce);
}