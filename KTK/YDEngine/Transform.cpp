#include "Transform.h"
#include <cmath>

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Init()
{
}

void Transform::Update()
{
}

void Transform::SetLocalPosition(CVector2D position)
{
	LocalPosition = position;
}

void Transform::SetLocalRotation(float rotation)
{
	LocalRotation = rotation;
}

void Transform::SetLocalScale(CVector2D scale)
{
	LocalScale = scale;
}

#pragma region Getter
CVector2D Transform::GetLocalPosition() const
{
	return LocalPosition;
}

float Transform::GetLocalRotation() const
{
	return LocalRotation;
}

CVector2D Transform::GetLocalScale() const
{
	return LocalScale;
}
#pragma endregion


void Transform::SetPosition(CVector2D _position)
{
	LocalPosition = _position;
}

void Transform::SetRotation(float _rotation)
{
	LocalRotation = _rotation;
}

void Transform::SetScale(CVector2D _scale)
{
	LocalScale = _scale;
}

CVector2D Transform::GetPosition()
{
	return LocalPosition;
}

float Transform::GetRotation()
{
	return LocalRotation;
}

CVector2D Transform::GetScale()
{
	return LocalScale;
}

D2D1::Matrix3x2F Transform::MakeTranslateMatrix(CVector2D& delta)
{
	D2D1::Matrix3x2F _translation;
	_translation._11 = 1.f; _translation._12 = 0.f;
	_translation._21 = 0.f; _translation._22 = 1.f;
	_translation._31 = delta.x; _translation._32 = delta.y;

	return _translation;
}

D2D1::Matrix3x2F Transform::MakeRotateMatrix(float angle)
{
	// cos sin은 cmath에서 angle을 받지 않고  radian을 받는다. 
	D2D1::Matrix3x2F _rotation;
	_rotation._11 = cos(angle * (PI / 180)); _rotation._12 = sin(angle * (PI / 180));
	_rotation._21 = -sin(angle * (PI / 180)); _rotation._22 = cos(angle * (PI / 180));
	_rotation._31 = 0; _rotation._32 = 0;
	return _rotation;
}

D2D1::Matrix3x2F Transform::MakeScaleMatrix(CVector2D& delta)
{
	return D2D1::Matrix3x2F();
}

D2D1::Matrix3x2F Transform::MakeTranslateMatrix()
{
	D2D1::Matrix3x2F _translation;
	_translation._11 = 1.f; _translation._12 = 0.f;
	_translation._21 = 0.f; _translation._22 = 1.f;
	_translation._31 = LocalPosition.x; _translation._32 = LocalPosition.y;

	return _translation;
}

// LocalRotation을 고정하면 안움직인다. 계속 바꿔줘야함(너무 당연한 말이지만 헷갈렸다)
D2D1::Matrix3x2F Transform::MakeRotateMatrix()
{
	D2D1::Matrix3x2F _rotation;
	_rotation._11 = cos(LocalRotation * (PI / 180)); _rotation._12 = sin(LocalRotation * (PI / 180));
	_rotation._21 = -sin(LocalRotation * (PI / 180)); _rotation._22 = cos(LocalRotation * (PI / 180));
	_rotation._31 = 0; _rotation._32 = 0;
	return _rotation;
}

D2D1::Matrix3x2F Transform::MakeScaleMatrix()
{
	D2D1::Matrix3x2F _Scale;
	_Scale._11 = LocalScale.x; _Scale._12 = 0.f;
	_Scale._21 = 0.f; _Scale._22 = LocalScale.y;
	_Scale._31 = 0.f; _Scale._32 = 0.f;

	return _Scale;
}

// 이동 벡터를 넣어준다
void Transform::Translate(CVector2D& translation)
{
	CVector2D transPos;
	D2D1::Matrix3x2F _transmatrix = MakeTranslateMatrix(translation);
	transPos.x = (LocalPosition.x * _transmatrix._11) + (LocalPosition.x * _transmatrix._21) + _transmatrix._31;
	transPos.y = (LocalPosition.y * _transmatrix._12) + (LocalPosition.y * _transmatrix._22) + _transmatrix._32;

	//transPos.x = (D2D1::Matrix3x2F::Identity() * _transmatrix._11) + (LocalPosition.x * _transmatrix._21) + _transmatrix._31;
	//transPos.y = (LocalPosition.y * _transmatrix._12) + (LocalPosition.y * _transmatrix._22) + _transmatrix._32;

	LocalPosition = transPos;
}

void Transform::Rotate(float angle)
{
	CVector2D rotatepos;
	D2D1::Matrix3x2F _rotatematrix = MakeRotateMatrix(angle);
	rotatepos.x = (LocalPosition.x * _rotatematrix._11) + (LocalPosition.x * _rotatematrix._21) + _rotatematrix._31;
	rotatepos.y = (LocalPosition.y * _rotatematrix._21) + (LocalPosition.y * _rotatematrix._22) + _rotatematrix._32;

	LocalPosition = rotatepos;
}

D2D1::Matrix3x2F Transform::TransformMatrix()
{
	D2D1::Matrix3x2F _transformMatrix;
	return _transformMatrix = MakeScaleMatrix() * MakeRotateMatrix() * MakeTranslateMatrix();
}