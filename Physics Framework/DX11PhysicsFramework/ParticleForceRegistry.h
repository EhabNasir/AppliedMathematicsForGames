#pragma once
#include "ParticleForceGenerator.h"
#include <vector>

class ParticleForceRegistry
{
protected:
	// NOTE: Keeps track of one force genetrator and the particle its applied to
	struct ParticleForceRegistration
	{
		PhysicsComponent* particle;
		ParticleForceGenerator* forceGenerator;
	};

	typedef std::vector<ParticleForceRegistration> Registry;
	Registry m_registrations;

public:
	void AddParticle(PhysicsComponent* _particle, ParticleForceGenerator* _forceGenerator);
	void RemoveParticle(PhysicsComponent* _particle, ParticleForceGenerator* _forceGenerator);
	void ClearRegistry();
	void UpdateForces(float _duration);

};

