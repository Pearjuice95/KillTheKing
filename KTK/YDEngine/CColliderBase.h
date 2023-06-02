#pragma once
#include "Engineenum.h"
#include <windows.h>
#include "CVector2D.h"

class CObjectBase;

/// <summary>
/// 2022.02.07 YD 
/// 
/// </summary>
class CColliderBase
{
public:
	CColliderBase();
	~CColliderBase();

private:
	// 콜라이더 종류를 알려줌 
	EColliderKind m_eColliderKind;

public:
	bool BoxColliderCheck(RECT* checkobj, RECT* targetobj);
	void PushCollisionBox(CObjectBase* checkobj, CObjectBase* targetobj, CVector2D centerSize);
	void WallCollision(CObjectBase* checkobj, CObjectBase* targetobj, CVector2D centerSize);
	/*CVector2D LineBoxCollision(CVector2D* start, CVector2D* end, CObjectBase* box, CVector2D boxSize);*/
};