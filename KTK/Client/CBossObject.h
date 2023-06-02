#pragma once
#include "CObjectBase.h"
#include "CVector2D.h"
#include "CShadowObject.h"

class CVector2D;

class CBossObject : public CObjectBase
{
private:
	CBossObject();
	~CBossObject();

public:
	static CBossObject* GetInsance()
	{
		static CBossObject instance;
		return &instance;
	}

private:
	int m_dmg;

public:
	int m_patternTimerCur;
	int m_jumpDelayTimer;
	int m_jumpDmgTimer;
	int m_patternDelayTimer;
	int m_patternDelayCur;
	int m_afterAttackDelayTimer;
	int m_patternPhase;

	bool m_jumpPatternOn;
	bool m_attackPatternOn;
	bool m_isPattern;
	bool m_patternDelay;

	bool m_isDead;
	bool m_attacked;

	bool m_cancontrol = false;

	CVector2D m_shadowPos;
	CVector2D m_patternPos;

	CShadowObject* m_pShadow;

	virtual void Update() override;
	virtual void Render(CVector2D cvector) override;
	virtual void Initialize() override;
	virtual RECT GetRECT() override;
	virtual void HPDown(int damage) override;
	void SetCollidertRect(CVector2D pos, CVector2D resize);

	void JumpPattern_Intro();
	void JumpReady();
	void JumpPattern_Jump();
	void JumpPatternDelayTime();
	void JumpStomp();
	void JumpCollideDelete();
	void JumpPatternDmg();

	void AttackPattern_intro();
	void AttackPattern_DelayTime();
	void AttackPattern_Attack();
	void AttackPattern_AfterAttack();

	std::vector<CAnimator*> HitEffect;
	std::vector<CAnimator*> SuperHitEffect;
};


