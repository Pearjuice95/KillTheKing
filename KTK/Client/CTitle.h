#pragma once
#include "CVector2D.h"

class CTitle
{
public:
	CTitle();
	~CTitle();

public:
	void Initialize();
	bool Update();
	void Render();
	void Finalize();
	
	void SetObject(CVector2D playerpos);
public:
	bool GameStart;
	bool EXit;
};

