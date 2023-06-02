#pragma once
#include "CVector2D.h"
#include "CObjectBase.h"
#include <d2d1helper.h>


class CWallObject :public CObjectBase
{
public:
	CWallObject(CVector2D m_pos, RECT rect);
	~CWallObject();

private:
	RECT m_collider;
	CVector2D m_pos;

public:
	bool m_isOpen;
	//void SetColliderRect(RECT rect);

	virtual void Update() override;
	virtual void Render(CVector2D cvector) override;
	virtual void Initialize() override;
	virtual RECT GetRECT() override;
	virtual void HPDown(int damage) override;
	virtual void SetCollidertRect(CVector2D pos, CVector2D resize) override;

};