#pragma once
#include "Camera.h"
class Win32;
class YDEngine;
class CCloseObject;

class GameProcess
{
public:
	GameProcess();
	~GameProcess();

private:
	Win32* m_pWin32;
	//Engine static으로 바꿈 
	//각 매니저에서 알게 하려면 어쩔수 없었음..
	YDEngine* m_pEngine;
	bool isDebugMode = false;
	bool isChangeCamera = false;

public:
	void Initialize();
	void Update();
	void Render();

	void Process();
	void Finalize();



	void DebugMode();
	void DebugRender();

	const float period = 0.01666666f;
	float checkTime = 0.0f;

	// fade in out test
	float fadecount = 0;
	bool fadeIn = false;
	void FadeInOut();

};