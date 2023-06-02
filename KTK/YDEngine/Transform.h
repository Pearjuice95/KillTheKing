#pragma once
#include <d2d1helper.h>
#include "CVector2D.h"

// ��ȯ ����� ����� �Լ�
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
	// LocalPosition ��������
	// �θ� ��ü�� ��ǥ�� �������� ������ ��ǥ�� �ǹ���
	void SetLocalPosition(CVector2D position);
	void SetLocalRotation(float rotation);
	void SetLocalScale(CVector2D scale);
	CVector2D GetLocalPosition() const;
	float GetLocalRotation() const;
	CVector2D GetLocalScale() const;

	// WorldPosition ��������
	// ȭ���� �������� �»���� (0,0)�� �ش�(�Ƹ��� �׷�)
	void SetPosition(CVector2D position);
	void SetRotation(float rotation);
	void SetScale(CVector2D scale);
	CVector2D GetPosition();
	float GetRotation();
	CVector2D GetScale();

public:
	void Translate(CVector2D& translation); // �̵��� �����ִ� �Լ�
	void Rotate(float angle); // ȸ���ϴ� �Լ�
	D2D1::Matrix3x2F TransformMatrix();

private:
	// ��ȯ ��� ����
	D2D1::Matrix3x2F MakeTranslateMatrix(CVector2D& delta);
	D2D1::Matrix3x2F MakeRotateMatrix(float angle);
	D2D1::Matrix3x2F MakeScaleMatrix(CVector2D& delta);

	D2D1::Matrix3x2F MakeTranslateMatrix();
	D2D1::Matrix3x2F MakeRotateMatrix();
	D2D1::Matrix3x2F MakeScaleMatrix();

};