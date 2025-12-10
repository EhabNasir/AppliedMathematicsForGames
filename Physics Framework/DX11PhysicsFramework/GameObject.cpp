#include "GameObject.h"

GameObject::GameObject(string type, Geometry geometry, Material material) : _geometry(geometry), _type(type), _material(material)
{
	_parent = nullptr;

	_transform = new Transform;

	_transform->SetPosition(XMFLOAT3());
	_transform->SetRotation(XMFLOAT3());
	_transform->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));
	//_position = XMFLOAT3();
	//_rotation = XMFLOAT3();
	//_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	_textureRV = nullptr;
}

GameObject::~GameObject()
{
	delete _transform;
	_transform = nullptr;

	_parent = nullptr;
	_textureRV = nullptr;
	_geometry.indexBuffer = nullptr;
	_geometry.vertexBuffer = nullptr;
}

void GameObject::Update(float dt)
{
	// Calculate world matrix
	//XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	//XMMATRIX rotation = XMMatrixRotationX(_rotation.x) * XMMatrixRotationY(_rotation.y) * XMMatrixRotationZ(_rotation.z);
	//XMMATRIX translation = XMMatrixTranslation(_position.x, _position.y, _position.z);

	XMMATRIX scale = XMMatrixScaling(_transform->GetScale().x, _transform->GetScale().y, _transform->GetScale().z);
	XMMATRIX rotation = XMMatrixRotationX(_transform->GetRotation().x) * XMMatrixRotationY(_transform->GetRotation().y) * XMMatrixRotationZ(_transform->GetRotation().z);
	XMMATRIX translation = XMMatrixTranslation(_transform->GetPosition().x, _transform->GetPosition().y, _transform->GetPosition().z);

	XMStoreFloat4x4(&_world, scale * rotation * translation);

	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_world, this->GetWorldMatrix() * _parent->GetWorldMatrix());
	}
}

void GameObject::Move(XMFLOAT3 direction)
{
	//_position.x += direction.x;
	//_position.y += direction.y;
	//_position.z += direction.z;
	_transform->SetPosition(_transform->GetPosition().x + direction.x, _transform->GetPosition().y + direction.y, _transform->GetPosition().z + direction.z);
	//_position.x += direction.x;
	//_position.y += direction.y;
	//_position.z += direction.z;
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}
