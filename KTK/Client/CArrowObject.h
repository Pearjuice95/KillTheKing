#pragma once
#include "CVector2D.h"
#include "Transform.h"
#include <vector>

class CAnimator;

class CArrowObject
{
public:
	CArrowObject();
	~CArrowObject();

public:
	CVector2D m_pos;
	CVector2D m_playerPos;
	CVector2D m_direct;
	Transform* m_transform;
	RECT m_collider;

	std::vector<CAnimator*> AttackEffect;

	
	int m_speed;
	bool m_isAlive;
	bool m_isFly;
	bool m_isCollide;
	bool m_isBreak;
	float m_theta;
public:
	void Initialize();
	void Shoot();
};