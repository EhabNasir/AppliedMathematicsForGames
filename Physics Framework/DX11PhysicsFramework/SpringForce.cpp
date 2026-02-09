#include "SpringForce.h"
#include "Debug.h"

//defines the presision of absolute magnitude operator
#define real_abs fabsf

SpringForce::SpringForce(PhysicsComponent* _other, float _restLength, float _springCoefficient)
{
	otherParticle = _other;
	restLength = _restLength;
	springCoefficient = _springCoefficient;
}

void SpringForce::UpdateParticle(PhysicsComponent* particle, float duration)
{

	Vector3 delta = particle->GetTransform()->GetPosition() - otherParticle->GetTransform()->GetPosition();

	float deltaMag = delta.Magnitude();
	if (deltaMag < 0.0001f)  // Epsilon for near-zero
		return;

	Vector3 force = -springCoefficient * (deltaMag - restLength) * (delta/deltaMag);

	particle->LinearStabiliser(force);
	otherParticle->LinearStabiliser(-force);

	Debug::PrintArguments("-%f", force.x);
}