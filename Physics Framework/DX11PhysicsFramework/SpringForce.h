#pragma once
#include "ParticleForceGenerator.h"

class SpringForce : public ParticleForceGenerator
{
public:
	SpringForce(PhysicsComponent* _other, float _restLength, float _springCoefficient);

	PhysicsComponent* otherParticle;
	float restLength;
	float springCoefficient;

	void UpdateParticle(PhysicsComponent* particle, float duration) override;
};

