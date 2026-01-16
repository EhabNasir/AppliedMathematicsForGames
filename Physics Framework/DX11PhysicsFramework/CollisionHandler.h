#pragma once
#include <vector>
#include "Vector3.h"

class GameObject;

struct CollisionInfo
{
	GameObject* obj1;
	GameObject* obj2;

	Vector3 normal;
	float penDepth;
};

class CollisionHandler
{
public:
	void ProcessGameObjects(std::vector<GameObject*>& _gameObjects);
	void DetectCollisions(std::vector<GameObject*>& _gameObjects);
	void Resolveimpulse();
	void ResolveInterpenetration();
private:
	std::vector<CollisionInfo> m_collisions;
};

