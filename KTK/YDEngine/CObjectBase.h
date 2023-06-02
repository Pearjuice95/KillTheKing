#pragma once
#include "CVector2D.h"
#include "enum.h"
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <vector>

class CAnimator;
class Transform;

class CObjectBase
{
public:
	CObjectBase(CVector2D m_pos, eObjectKind objectkind);
	~CObjectBase();

	eMyStatus GetStatus();

	void SetStatus(eMyStatus status);

public:
	float m_moveSpd;
	eObjectKind objectKind; // 오브젝트 종류

	CAnimator* m_animator; // 오브젝트의 애니메이터

	CVector2D m_pos; // 중심좌표
	CVector2D m_prevPos;
	CVector2D m_DashPos;
	eMyStatus m_prevMove;

	CVector2D m_wallCollidePos;


	eMyStatus m_prevStatus;
	eMyStatus m_status; // 현재 상태

	eToTalStatus m_totalStatus;

	RECT m_colliderRect; // 콜라이더를 바꾸기위한 하나의 RECT 

	Transform* m_transform;

	// 콜라이더를 키고 끈다(전체 콜라이더)
	bool m_isCollide;

	bool m_isMoveTO;

	bool m_isHit;
	//test
	std::vector<int> m_keyValue;

	bool m_isAlive;
	bool m_isRender;

	int m_HP;

	bool m_Intro;


public:
	virtual void Update() abstract;
	virtual void Render(CVector2D cvector) abstract;
	virtual void Initialize() abstract;
	virtual RECT GetRECT() abstract;
	virtual void SetCollidertRect(CVector2D pos, CVector2D resize) abstract;
	virtual void HPDown(int damage) abstract;


	void OnCollider() { m_isCollide = true; }
	void OffCollider() { m_isCollide = false; }
	bool GetIsCollider() { return m_isCollide; }
};