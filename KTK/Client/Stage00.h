#pragma once
#include "SceneBase.h"
#include "CVector2D.h"
#include <d2d1helper.h>

class CColliderBase;
class CSprite;
class Stage00 //: public SceneBase
{
public:
	Stage00();
	~Stage00();

public:
	/*virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Finalize() override;*/
	void Initialize(CSprite* gatesprite);
	bool Update();
	void Render();
	void Finalize();

public:
	void SetObject(CVector2D playerpos);

	void Check();

	void GateEffect();

	void CloseObjectCreatePool();
	void RangeObjectCreatePool();
	

public:
	bool m_isStage0Clear;

	bool m_isSuper;

	bool m_iseffect;

	float m_time;

	CSprite* GateSprite;

	int count;
	RECT m_goalBox;
	CColliderBase* m_colliderBase;

};

