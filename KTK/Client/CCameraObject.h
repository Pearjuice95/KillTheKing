#pragma once
#include "CVector2D.h"
#include "CObjectBase.h"

class CCameraObject : public CObjectBase
{
private:
	CCameraObject();
	~CCameraObject();

private:
	float m_speed;
	float m_UpY;
	float m_DownY;
	float m_LeftX;
	float m_RightX;

public:
	int m_count;
	bool isGoal;
	bool isVertial;
	bool isShake;
	bool isUpLeft;
	bool isDownRight;
	static CCameraObject* GetInsance()
	{
		static CCameraObject instance;
		return &instance;
	}

public:
	virtual void Update() override;
	virtual void Render(CVector2D cvector) override;
	virtual void Initialize() override;
	virtual RECT GetRECT() override;
	virtual void SetCollidertRect(CVector2D pos, CVector2D resize) override;
	virtual void HPDown(int damage) override;

	void ChangePos(float x, float y);
	void ChangePos2(CVector2D _Prev, CVector2D _Dest);
	void SetObjPos(CObjectBase* object);
	void ChangeSpeed(float speed);

	void ResetCount() { m_count = 0; }

	void SetShakeDistance(float distance);
	void ShakePos(float speed, bool vertical, float distance, int count);
};