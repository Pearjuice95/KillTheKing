#pragma once
#include "CObjectBase.h"
#include "CArrowObject.h"
#include "CSprite.h"
#include <vector>

class CAnimator;

class CRangeObject : public CObjectBase
{
public:
	CRangeObject(CVector2D m_pos);
	~CRangeObject();

private:
	int m_atkCur;
	int m_atkTime;
	int m_hitCur;
	int m_hitTime;
	int m_stopTime;
	int m_stopCur;
	int m_atkDelayTime;
	int m_delayCur;

public:
	virtual void Update() override;
	virtual void Render(CVector2D cvector) override;
	virtual void Initialize() override;
	virtual RECT GetRECT() override;
	void SetCollidertRect(CVector2D pos, CVector2D resize);
	void HPDown(int damage) override;

	CSprite* m_sprite;

	//bool m_isAlive;
	bool m_isStand_1;
	bool m_isStand_2;
	bool m_isShoot;
	CArrowObject* m_arrow_1;
	CArrowObject* m_arrow_2;
	CArrowObject* m_arrow_3;
	CArrowObject* m_arrow_4;
	std::vector<CArrowObject*> arrowpool;

	std::vector<CAnimator*> HitEffect;
	std::vector<CAnimator*> SuperHitEffect;

	int m_DoorNum;

public:
	//void SetAlive(bool live);
	void MoveToPos(CVector2D pos, CVector2D pos2, CVector2D goal);
	void AttackPos();
};

