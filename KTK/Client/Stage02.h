#pragma once
#include "CVector2D.h"
#include <d2d1helper.h>

class CColliderBase;

class Stage02
{
public:
	Stage02();
	~Stage02();

public:
	void Initialize();
	bool Update();
	void Render();
	void Finalize();
public:
	void SetObject(CVector2D playerpos);

	void Wave01();
	void Wave02();
	void Wave03();


public:
	bool m_isStage0Clear;
	RECT m_goalBox;
	CColliderBase* m_colliderBase;
};

