#pragma once
#include "ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator
{
	void UpdateParticle(PhysicsComponent* _particle, float _duration) override;
};

