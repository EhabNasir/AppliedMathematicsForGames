#pragma once
#include "../Systems/PhysicsComponent.h"

class ParticleForceGenerator
{
public:
	virtual void UpdateParticle(PhysicsComponent *particle, float duration) = 0;
};

