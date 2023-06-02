#pragma once
#include "CObjectBase.h"
#include "CVector2D.h"
#include "CWallObject.h"
#include <string.h>

class Transform;
class YDEngine;
class CSprite;
class JsonParser;
class CPlayerObject;

class CBackGroundObject : public CObjectBase
{
private:
	CBackGroundObject();
	~CBackGroundObject();
public:
	static CBackGroundObject* GetInstance()
	{
		static CBackGroundObject instance;
		return &instance;
	}

	YDEngine* pEngine;
	CSprite* m_backgroundSprite[6];

	RECT Stage0BGC[7];
	RECT Stage1BGC[25];
	RECT Stage2BGC[20];
	RECT Stage3BGC[14];

	std::vector<RECT> Stage00;
	std::vector<RECT> Stage01;
	std::vector<RECT> Stage02;
	std::vector<RECT> Stage03;

	std::vector<int> vlocationList;

	RECT m_backGroundCollider; // 콜라이더를 바꾸기위한 하나의 RECT 
	RECT m_GateCollider;; // 콜라이더를 바꾸기위한 하나의 RECT 

	std::vector<CWallObject*> m_stage00V;
	std::vector<CWallObject*> m_stage01V;
	std::vector<CWallObject*> m_stage02V;
	std::vector<CWallObject*> m_stage03V;

private:


public:
	void InitMap();
	void LoadBackGround();
	void ChangeSprite();
	void DrawBackGround();
	void SetBackGroundCollider();
	RECT MakeRect(std::vector<int> vlo, int index); // 뭔가 이상하다
	RECT MakeRect(int left, int top, int right, int bottom);
	void readingCSV();

	void PushRECT();

	virtual void Update() override;
	virtual void Render(CVector2D cvector) override;
	virtual void Initialize() override;
	virtual RECT GetRECT() override;
	virtual void HPDown(int damage) override;
	virtual void SetCollidertRect(CVector2D pos, CVector2D resize) override;

};

