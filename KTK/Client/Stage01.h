#pragma once
#include "SceneBase.h"
#include "CVector2D.h"
#include <d2d1helper.h>

class CColliderBase;
class CObjectBase;
class Stage01 //: public SceneBase
{
public:
	Stage01();
	~Stage01();

public:
	void Initialize();
	bool Update();
	void Render();
	void Finalize();

	void SetObject(CVector2D playerpos);

	void SetCloseObject();
	void SetRangeObject();

	void Wave01();
	void Wave02();
	//void Wave03();

	void CameraMove(CVector2D moveto);
	void CameraSet(CObjectBase* startobject, CObjectBase* moveobject);

	void End();
public:
	bool m_isStage0Clear;
	bool m_isWave01Clear;
	bool m_isWave02Clear;
	bool m_isWave03Clear;

	bool m_isWave01Render;
	bool m_isWave02Render;
	bool m_isWave03Render;


	int m_CloseIdx;
	int m_RangeIdx;

	int m_phase;

	int m_nowMonsterIdx;

	bool isChangeCamera;

	float m_time;

	bool m_isMove;

	int current;
	CVector2D FirstCameraPos;
	CVector2D SecondCameraPos;

	CVector2D RangeTargetPos01;
	CVector2D RangeTargetPos02;
	CVector2D RangeTargetPos03;
	CVector2D RangeTargetPos04;
	CVector2D RangeTargetPos05;

	RECT m_goalBox;
	CColliderBase* m_colliderBase;

private:

};

