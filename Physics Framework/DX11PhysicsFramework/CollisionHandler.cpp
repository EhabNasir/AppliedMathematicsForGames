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
	for (size_t a = 0; a < _gameObjects.size(); ++a)
	{
		for (size_t b = a + 1; b < _gameObjects.size(); ++b)
		{
			GameObject* objA = _gameObjects[a];
			GameObject* objB = _gameObjects[b];

			if (!objA->GetPhysics()->IsCollideable() || !objB->GetPhysics()->IsCollideable())
				continue;

			if (objA->GetPhysics()->GetCollider()->CollidesWith(*objB->GetPhysics()->GetCollider(), collision))
			{
				collision.obj1 = objA;
				collision.obj2 = objB;

				Vector3 collisionNormal = objA->GetTransform()->GetPosition() - objB->GetTransform()->GetPosition();
				collisionNormal.Normalize();
				collision.normal = collisionNormal;

				m_collisions.push_back(collision);
			}
		}
	}
}
void CollisionHandler::Resolveimpulse()
{
	for (CollisionInfo i : m_collisions)
	{
		// Only apply impulse if penetration exists
		if (i.penDepth <= 0.0f)
			continue;

		Vector3 relativeVelocity = i.obj1->GetPhysics()->GetVelocity() - i.obj2->GetPhysics()->GetVelocity();
		float coeffRestitution = 0.5f;

		float seperatingVelocity = i.normal * relativeVelocity;

		if (seperatingVelocity > 0)
			continue;

		float totalInverseMass = i.obj1->GetPhysics()->GetInverseMass() + i.obj2->GetPhysics()->GetInverseMass();

		float scalarImpulseMag = -((1 + coeffRestitution) * (relativeVelocity * i.normal)) / totalInverseMass;

		Vector3 impulse1 = i.obj1->GetPhysics()->GetInverseMass() * scalarImpulseMag * i.normal;
		Vector3 impulse2 = -(i.obj2->GetPhysics()->GetInverseMass() * scalarImpulseMag * i.normal);

		Vector3 point = i.obj1->GetTransform()->GetPosition() + Vector3(0, 0, 1);
		Vector3 point2 = i.obj2->GetTransform()->GetPosition() + Vector3(0, 0, 1);

		i.obj1->GetPhysics()->ApplyImpulse(impulse1);
		i.obj1->GetPhysics()->CalculateRotation(impulse1, point, i.halfExtents);
		i.obj2->GetPhysics()->ApplyImpulse(impulse2);
		i.obj2->GetPhysics()->CalculateRotation(impulse2, point2, i.halfExtents);
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