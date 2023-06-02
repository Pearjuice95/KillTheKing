#pragma once
#include "CVector2D.h"
#include "CVector2D.h"
#include "CColliderBase.h"
#include <d2d1helper.h>

class Stage03
{
public:
	Stage03();
	~Stage03();

public:
	void Initialize();
	bool Update();
	void Render();
	void Finalize();

	void SetObject(CVector2D playerpos);

	void EntryPointIn();
	void BossDrop();
	void MakeInvisibleWall();
	void RemakeCamera();
	void MoveToPosition();

	void BossBattleScene();

	int m_phasecur = -1;

	RECT m_noAcess;
	RECT m_entryPoint;

	CVector2D m_movePos;

	CColliderBase* m_colliderBase;

	bool m_isBattle;
	bool m_isStart;
	bool m_playerMove;
	bool isChangeCamera;
};

