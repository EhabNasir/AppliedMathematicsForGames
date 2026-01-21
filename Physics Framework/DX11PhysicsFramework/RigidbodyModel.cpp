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


    //Rotation
    Vector3 angularAcceleration;

    angularAcceleration.x = m_torque.x / m_inertiaTensor._11;
    angularAcceleration.y = m_torque.y / m_inertiaTensor._22;
    angularAcceleration.z = m_torque.z / m_inertiaTensor._33;;

    m_angularVelocity += angularAcceleration * _deltaTime;

    Quaternion dq(0.0f, m_angularVelocity.x, m_angularVelocity.y, m_angularVelocity.z);

    dq = m_orientation * dq;
    dq *= 0.5f * _deltaTime;
    m_orientation += dq;

    //normalise orientation
    float magQ = m_orientation.Magnitude();
    if (magQ > 0)
        m_orientation /= magQ;

    m_transform->SetOrientation(m_orientation);

    //fake air-resistance
    m_angularVelocity *= m_angularDampening;

    m_torque = Vector3(0, 0, 0);

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

void RigidBodyModel::CalculateRotation(Vector3 _force,Vector3 _point, Vector3 _halfExtents)
{
    //point of force relative to centre
    Vector3 r = _point - m_transform->GetPosition();

    //t = r x f
    m_torque += r ^ _force;

    float x = _halfExtents.x * _halfExtents.x;
    float y = _halfExtents.y * _halfExtents.y;
    float z = _halfExtents.z * _halfExtents.z;

    m_inertiaTensor._11 = 1 / 12 * m_mass * (y + z);
    m_inertiaTensor._22 = 1 / 12 * m_mass * (x + z);
    m_inertiaTensor._33 = 1 / 12 * m_mass * (x + y);
}

void RigidBodyModel::LinearStabiliser(Vector3 _desiredVelocity)
{
    Vector3 unwantedVelocity = m_velocity - _desiredVelocity;

    Vector3 error = -unwantedVelocity;

    Vector3 stabiliserForce = error * 0.3;

    AddForce(stabiliserForce);
}