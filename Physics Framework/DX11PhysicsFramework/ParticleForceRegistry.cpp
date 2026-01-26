#include "ParticleForceRegistry.h"

void ParticleForceRegistry::AddParticle(PhysicsComponent* _particle, ParticleForceGenerator* _forceGenerator)
{
	ParticleForceRegistration newRegistration;
		newRegistration.particle = _particle;
		newRegistration.forceGenerator = _forceGenerator;

	m_registrations.push_back(newRegistration);
}

void ParticleForceRegistry::RemoveParticle(PhysicsComponent* _particle, ParticleForceGenerator* _forceGenerator)
{
	for (auto i = m_registrations.begin(); i != m_registrations.end();)
	{
		if (i->particle == _particle && i->forceGenerator == _forceGenerator)
		{
			i = m_registrations.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void ParticleForceRegistry::ClearRegistry()
{
	m_registrations.clear();
}

void ParticleForceRegistry::UpdateForces(float _duration)
{
	//My approach - newer c++
	//for (ParticleForceRegistration& p : m_registrations)
	//{
	//	p.forceGenerator->UpdateParticle(p.particle, _duration);
	//}

	//milligntons approach
	Registry::iterator i = m_registrations.begin();

	for (; i != m_registrations.end(); i++)
	{
		i->forceGenerator->UpdateParticle(i->particle, _duration);
	}
}