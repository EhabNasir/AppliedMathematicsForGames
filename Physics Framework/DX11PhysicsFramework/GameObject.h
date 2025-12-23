#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>
#include "Transform.h"
#include "Appearance.h"
#include "Vector3.h"
#include "Systems/PhysicsComponent.h"
#include "Systems/ParticleModel.h"

using namespace DirectX;
using namespace std;

class GameObject
{
public:
	GameObject(string type, Geometry geometry, Material material);
	~GameObject();

	string GetType() const { return _type; }

	void SetParent(GameObject * parent) { _parent = parent; }

	Transform* GetTransform() { return _transform; }
	Appearance* GetAppearance() { return _appearance; }
	PhysicsComponent* GetPhysics() { return m_particleModel; }
	bool hasPhysics = false;

	// Rendering information
	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }


	void Update(float dt);
	void Move(Vector3 direction);
	void Draw(ID3D11DeviceContext * pImmediateContext);

private:
	GameObject* _parent = nullptr;

	Transform* _transform;
	Appearance* _appearance;
	ParticleModel* m_particleModel;

	string _type;
	//XMFLOAT4X4 _world;
	XMFLOAT4X4 _world;

};

