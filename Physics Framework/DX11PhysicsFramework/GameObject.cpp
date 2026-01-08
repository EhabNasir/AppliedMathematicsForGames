#include "GameObject.h"
#include "Debug.h"

GameObject::GameObject(string type, Geometry geometry, Material material) : _type(type)
{
	_parent = nullptr;

	_transform = new Transform;

	_appearance = new Appearance(geometry, material);

	//m_physicsCompnonent = new PhysicsComponent(_transform);
	//m_particleModel = new ParticleModel(_transform, 100.0f);
	m_rigidBody = new RigidBodyModel(_transform, 100.0f);
}

GameObject::~GameObject()
{
	delete _transform;
	_transform = nullptr;

	_parent = nullptr;

	delete _appearance;
	_appearance = nullptr;
}

void GameObject::Update(float _deltaTime)
{
	if(hasPhysics)
		m_rigidBody->Update(_deltaTime);

	// Calculate world matrix
	XMMATRIX scale = XMMatrixScaling(_transform->GetScale().x, _transform->GetScale().y, _transform->GetScale().z);
	XMMATRIX rotation = XMMatrixRotationX(_transform->GetRotation().x) * XMMatrixRotationY(_transform->GetRotation().y) * XMMatrixRotationZ(_transform->GetRotation().z);
	XMMATRIX translation = XMMatrixTranslation(_transform->GetPosition().x, _transform->GetPosition().y, _transform->GetPosition().z);

	//XMStoreFloat4x4(&_world, scale * rotation * translation);
	XMStoreFloat4x4(&_world, scale * rotation * translation);

	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_world, this->GetWorldMatrix() * _parent->GetWorldMatrix());
	}

	//Debug::PrintNumber(10);
	//OutputDebugStringA("hello\n");
}

void GameObject::Move(Vector3 direction)
{
	_transform->SetPosition(_transform->GetPosition().x + direction.x,
	_transform->GetPosition().y + direction.y, 
	_transform->GetPosition().z + direction.z);
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	_appearance->Draw(pImmediateContext);
}
