#pragma once
#include "ParticleForceGenerator.h"

class ParticleDrag : public ParticleForceGenerator
{
	void UpdateParticle(PhysicsComponent* _particle, float _duration) override;
};

