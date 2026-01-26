#include <cmath>

#include "ParticleDrag.h"

void ParticleDrag::UpdateParticle(PhysicsComponent* _particle, float _duration)
{
    Vector3 v = _particle->GetVelocity();
    float speed = v.Magnitude();
    if (speed <= 0.0001f)
        return;

    v.Normalize();

    float p = 0.3f;
    float k1 = p * ((_particle->GetGravitationalConstant() * _particle->GetMass()) / _particle->GetTerminalVelocity());
    float k2 = (1 - p) * ((_particle->GetGravitationalConstant() * _particle->GetMass()) / std::pow(_particle->GetTerminalVelocity(), 2));

    float dragMagnitude = k1 * speed + k2 * std::pow(speed, 2);

    Vector3 dragForce = -v * dragMagnitude;

    _particle->AddForce(dragForce);
}