#pragma once
#include "ParticleForceGenerator.h"

class SpringForce : public ParticleForceGenerator
{
public:
	SpringForce(bool _isSingle, PhysicsComponent* _other, float _restLength, float _springCoefficient);

	PhysicsComponent* otherParticle;
	float restLength;
	float springCoefficient;

	bool isSingle; //Decides if both particles effect each other or one simply follows

	void UpdateParticle(PhysicsComponent* particle, float duration) override;
};

