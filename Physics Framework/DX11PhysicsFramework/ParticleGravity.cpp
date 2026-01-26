#include "ParticleGravity.h"

//NOTE: might want to check if partical has inverse mass later
void ParticleGravity::UpdateParticle(PhysicsComponent* _particle, float _duration)
{
	_particle->LinearStabiliser(Vector3(- 9.8f * _particle->GetMass(), 0.0f, 0.0f));
}