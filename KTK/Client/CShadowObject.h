#pragma once
#include "CObjectBase.h"

class CShadowObject : public CObjectBase
{
public:
	CShadowObject();
	~CShadowObject();

	virtual void Update() override;
	virtual void Render(CVector2D cvector) override;
	virtual void Initialize() override;
	virtual RECT GetRECT() override;
	virtual void HPDown(int damage) override;
	void SetCollidertRect(CVector2D pos, CVector2D resize);

	std::vector<CAnimator*> JumpShadowEffect;
	std::vector<CAnimator*> StompShadowEffect;
};

