#pragma once

#include "ParticleForceGenerator.h"

class ThrustGenerator : public ParticleForceGenerator
{
	void UpdateParticle(PhysicsComponent* particle, float duration) override;
};

