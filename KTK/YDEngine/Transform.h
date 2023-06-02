#pragma once
#include <d2d1helper.h>
#include "CVector2D.h"

// 변환 행렬을 만드는 함수
class Transform
{
public:
	Transform();
	~Transform();

public:
	void Init();
	void Update();

private:
	const double PI = 3.1415926;
	CVector2D LocalPosition;
	float LocalRotation;
	CVector2D LocalScale;

public:
	// LocalPosition 설정해줌
	// 부모 객체의 좌표를 기준으로 설정된 좌표를 의미함
	void SetLocalPosition(CVector2D position);
	void SetLocalRotation(float rotation);
	void SetLocalScale(CVector2D scale);
	CVector2D GetLocalPosition() const;
	float GetLocalRotation() const;
	CVector2D GetLocalScale() const;

	// WorldPosition 설정해줌
	// 화면을 기준으로 좌상단이 (0,0)에 해당(아마도 그럼)
	void SetPosition(CVector2D position);
	void SetRotation(float rotation);
	void SetScale(CVector2D scale);
	CVector2D GetPosition();
	float GetRotation();
	CVector2D GetScale();

public:
	void Translate(CVector2D& translation); // 이동을 시켜주는 함수
	void Rotate(float angle); // 회전하는 함수
	D2D1::Matrix3x2F TransformMatrix();

private:
	// 변환 행렬 생성
	D2D1::Matrix3x2F MakeTranslateMatrix(CVector2D& delta);
	D2D1::Matrix3x2F MakeRotateMatrix(float angle);
	D2D1::Matrix3x2F MakeScaleMatrix(CVector2D& delta);

	D2D1::Matrix3x2F MakeTranslateMatrix();
	D2D1::Matrix3x2F MakeRotateMatrix();
	D2D1::Matrix3x2F MakeScaleMatrix();

};