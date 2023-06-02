#pragma once
#include "CObjectBase.h"


class CCloseObject : public CObjectBase
{
public:
	CCloseObject(CVector2D m_pos);
	~CCloseObject();

private:
	float m_atkSpd;
	int m_atkCur;
	int m_atkTime;
	int m_hitCur;
	int m_hitTime;

public:
	virtual void Update() override;
	virtual void Render(CVector2D cvector) override;
	virtual void Initialize() override;
	virtual RECT GetRECT() override;
	void SetCollidertRect(CVector2D pos, CVector2D resize);
	void HPDown(int damage) override;
	//bool m_isAlive;
	std::vector<CAnimator*> HitEffect;
	std::vector<CAnimator*> SuperHitEffect;
	//std::vector<CAnimator*> AttackEffect;

	int m_DoorNum;
public:
	//void SetAlive(bool live);
	void MoveToPlayer();

	
};