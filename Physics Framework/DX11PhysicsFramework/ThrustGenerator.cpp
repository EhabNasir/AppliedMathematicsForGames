#include "ThrustGenerator.h"
#include "RigidbodyModel.h"

void ThrustGenerator::UpdateParticle(PhysicsComponent* particle, float duration)
{
    Vector3 forwardVelocity = QVRotate(particle->GetOrientation(), particle->GetThrottle());

    Vector3 unwantedVelocity = particle->GetVelocity() - forwardVelocity;

    Vector3 error = -unwantedVelocity;

    Vector3 stabiliserForce = error * 0.3f;

    particle->AddForce(stabiliserForce);
}