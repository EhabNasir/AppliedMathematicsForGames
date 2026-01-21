#pragma once
#include <directxmath.h>
#include <d3d11_1.h>
#include "Quaternion.h"

using namespace DirectX;
using namespace std;

class Transform
{
public:
	Transform();
	~Transform();

	// Setters and Getters for position/rotation/scale
	void SetPosition(Vector3 position) { _position = position; }
	void SetPosition(float x, float y, float z) { _position.x = x; _position.y = y; _position.z = z; }

	Vector3 GetPosition() const { return _position; }

	void SetScale(Vector3 scale) { _scale = scale; }
	void SetScale(float x, float y, float z) { _scale.x = x; _scale.y = y; _scale.z = z; }

	Vector3 GetScale() const { return _scale; }

	void SetRotation(Vector3 _rotation) { m_orientation = MakeQFromEulerAngles(_rotation.x , _rotation.y, _rotation.z); }
	void SetRotation(float x, float y, float z) { m_orientation = MakeQFromEulerAngles(x, y, z); }

	Vector3 GetRotation() const { return MakeEulerAnglesFromQ(m_orientation); }

	void SetOrientation(const Quaternion& q)
	{
		m_orientation = q;
	}
	Quaternion GetOrientation() const { return m_orientation; }

private:
	Vector3 _position;
	Quaternion m_orientation;
	Vector3 _scale;
};

