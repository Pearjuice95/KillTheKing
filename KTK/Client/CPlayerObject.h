#pragma once
#include "CObjectBase.h"

class Transform;

class CPlayerObject : public CObjectBase
{
private:
	CPlayerObject();
	~CPlayerObject();

public:
	static CPlayerObject* GetInstance()
	{
		static CPlayerObject instance;
		return &instance;
	}

public:

	int m_superCount;
	float m_moveSpd;
	float m_atkSpd;
	int m_dashCount;
	int m_dashTime;
	int m_dashCur;
	int m_atkTime;
	int m_atkCur;
	int m_secondAtkTime;
	int m_secondAtkCur;
	int m_dashAtkTIme;
	int m_dashAtkCur;
	int m_hitCur;
	int m_hitTime;

	int m_superUseTime;
	int m_superUseCur;

	int m_superTime;
	int m_superCur;

	int m_dieTime;
	int m_dieCur;

	bool m_isSecond;


public:
	virtual void Update() override;
	virtual void Render(CVector2D cvector) override;
	virtual void Initialize() override;
	virtual RECT GetRECT() override;
	virtual void HPDown(int damage) override;
	void SetCollidertRect(CVector2D pos, CVector2D resize);
	void PlusSuper();
	int m_dmg;
	bool m_useSuper;
	bool m_isDmg;
	bool m_isSuper;
	bool m_isDie;

	bool m_isWalk = false;

	bool m_hitBoss;
	bool m_canControl;

public:
	void PlayerInput();

public:
	int GetHp() const { return m_HP; }
	int GetdashCount() const { return m_dashCount; }
	int GetSuper() const { return m_superCount; }
	void DealDamage();

};