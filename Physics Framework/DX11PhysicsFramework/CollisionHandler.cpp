#include "CollisionHandler.h"
#include "GameObject.h"

void CollisionHandler::ProcessGameObjects(std::vector<GameObject*>& _gameObjects)
{
	m_collisions.clear();

	DetectCollisions(_gameObjects);
	ResolveInterpenetration();
	Resolveimpulse();
}

void CollisionHandler::DetectCollisions(std::vector<GameObject*>& _gameObjects)
{
	CollisionInfo collision;

	//Detect collison -> populate m_collisions
	for (GameObject* g : _gameObjects)
	{
		for (GameObject* i : _gameObjects)
		{
			if (g->GetPhysics()->IsCollideable() && i->GetPhysics()->IsCollideable())
			{
				if (g->GetPhysics()->GetCollider()->CollidesWith(*i->GetPhysics()->GetCollider(), collision))
				{
					//populate

					collision.obj1 = g;
					collision.obj2 = i;

					Vector3 collisionNormal = g->GetTransform()->GetPosition() - i->GetTransform()->GetPosition();
					collisionNormal.Normalize();

					collision.normal = collisionNormal;

					m_collisions.push_back(collision);
				}
			}
		}
	}
}
void CollisionHandler::Resolveimpulse()
{
	for (CollisionInfo i : m_collisions)
	{
		Vector3 relativeVelocity = i.obj1->GetPhysics()->GetVelocity() - i.obj2->GetPhysics()->GetVelocity();
		float coeffRestitution = 1.0f;

		float seperatingVelocity = i.normal * relativeVelocity;

		if (seperatingVelocity > 0)
			return;

		float totalInverseMass = i.obj1->GetPhysics()->GetInverseMass() + i.obj2->GetPhysics()->GetInverseMass();

		float scalarImpulseMag = -((1 + coeffRestitution) * (relativeVelocity * i.normal)) / totalInverseMass;

		Vector3 impulse1 = i.obj1->GetPhysics()->GetInverseMass() * scalarImpulseMag * i.normal;
		Vector3 impulse2 = -(i.obj2->GetPhysics()->GetInverseMass() * scalarImpulseMag * i.normal);

		i.obj1->GetPhysics()->ApplyImpulse(impulse1);
		i.obj2->GetPhysics()->ApplyImpulse(impulse2);
	}
}

void CollisionHandler::ResolveInterpenetration()
{
	for (CollisionInfo& i : m_collisions)
	{
		if (i.penDepth <= 0.0f)
			continue;

		PhysicsComponent* physA = i.obj1->GetPhysics();
		PhysicsComponent* physB = i.obj2->GetPhysics();

		float invMassA = physA->GetInverseMass();
		float invMassB = physB->GetInverseMass();

		float totalInvMass = invMassA + invMassB;

		// Infinite mass objects don't move
		if (totalInvMass == 0.0f)
			continue;

		Vector3 correction = i.normal * (i.penDepth / totalInvMass);

		// Move objects apart proportionally
		i.obj1->GetTransform()->SetPosition(i.obj1->GetTransform()->GetPosition() + correction * invMassA);

		i.obj2->GetTransform()->SetPosition(i.obj2->GetTransform()->GetPosition() - correction * invMassB);
	}
}