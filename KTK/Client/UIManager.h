#pragma once
#include <CVector2D.h>

class YDEngine;
class CPlayerObject;
class CAnimationClip;
class CAnimator;

class UIManager
{
private:
	UIManager();
	~UIManager();

public:
	static UIManager* GetInstance()
	{
		static UIManager instance;
		return &instance;
	}

public:
	void Initialize(YDEngine* engine);
	void Update();
	void Render();
	void DrawSprite();
	void PlayerHPUI();
	void PlayerDieUI();
	void PlayerSuperUI();
	void PlayIntroUI();

public:
	YDEngine* m_pEngine;
	CPlayerObject* m_player;
	
	// 각 UI의 위치를 저장한다.
	CVector2D m_playerHpPos;
	CVector2D m_playerDashPos;
	CVector2D m_playerSuperPos;

};

