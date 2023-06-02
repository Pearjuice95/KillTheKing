#include "GameProcess.h"
#include "Win32.h"
#include "YDEngine.h"
#include "Time.h"
#include "CVector2D.h"
#include "CPlayerObject.h"
#include "AnimationManager.h"
#include "CObjectManager.h"
#include "CInput.h"
#include "Camera.h"
#include "CCameraObject.h"
#include "UIManager.h"
#include "Sound.h"

GameProcess::GameProcess()
	: m_pWin32(nullptr), m_pEngine(nullptr)
{

}

GameProcess::~GameProcess()
{

}

void GameProcess::Initialize()
{
	m_pWin32 = new Win32;
	m_pEngine = new YDEngine;

	m_pWin32->Initialize();
	HWND _hWnd = m_pWin32->ReturnWindowHandle();


	m_pEngine->Initialize(_hWnd);
	AnimationManager::GetInstance()->Initialize(m_pEngine);
	CObjectManager::GetInstance()->Initialize();
	Camera::GetInsance()->WallException(1);
	Camera::GetInsance()->Initialize(CObjectManager::GetInstance()->player);
	CCameraObject::GetInsance()->Initialize();
	UIManager::GetInstance()->Initialize(m_pEngine);
	SceneManager::GetInstance()->Initialize(m_pEngine);
	SoundSystem();
	TIME->Create();
}

void GameProcess::Process()
{
	bool _isQuit = false;

	while (_isQuit != true)
	{
		if (m_pWin32->MessageLoop(_isQuit) == true)
		{
			// 메시지 처리가 있었다.
			// 단, 그 메시지가 quit이라면 바깥쪽의 while구문을 탈출한다.
		}
		else
		{
			TIME->Update();

			checkTime += TIME->Delta();
			if (period <= checkTime)
			{
				DebugMode(); // 디버깅 모드 on,off

				m_pEngine->BeginRender();

				Update(); // 각 업데이트를 돌리는 부분
				Render(); // 그리는 부분
				DebugRender(); // 디버깅에 편하기위해 그리는 모드(ON,OFF)

				m_pEngine->EndRender();
				checkTime = 0.f;
			}
		}
	}
}

void GameProcess::Update()
{
	//if (CInput::GetInstance()->Key_Down(VK_CONTROL))
	//{
	//	CCameraObject::GetInsance()->ResetCount();
	//	CCameraObject::GetInsance()->isShake = true;
	//	CCameraObject::GetInsance()->SetObjPos(CPlayerObject::GetInstance());
	//	Camera::GetInsance()->ChangeObject(CCameraObject::GetInsance());
	//	CCameraObject::GetInsance()->SetShakeDistance(30.0f);
	//}

	/*if (CInput::GetInstance()->Key_Down('T'))
	{
		if (!isChangeCamera)
		{
			isChangeCamera = true;
			CCameraObject::GetInsance()->SetObjPos(CPlayerObject::GetInstance());
			Camera::GetInsance()->ChangeObject(CCameraObject::GetInsance());
			CCameraObject::GetInsance()->ChangeSpeed(10.f);
		}

		else
		{
			isChangeCamera = false;
			CCameraObject::GetInsance()->isGoal = false;
			CCameraObject::GetInsance()->SetObjPos(CPlayerObject::GetInstance());
			Camera::GetInsance()->ChangeObject(CPlayerObject::GetInstance());
		}
	}*/

	/*if (isChangeCamera)
	{
		CCameraObject::GetInsance()->ChangePos(500, 500);
	}*/

	if (CCameraObject::GetInsance()->isShake == true)
	{
		CCameraObject::GetInsance()->ShakePos(15.0f, true, 30.0f, 3);
	}

	if (CCameraObject::GetInsance()->m_count == -2)
	{
		CCameraObject::GetInsance()->ChangePos(CPlayerObject::GetInstance()->m_pos.x, CPlayerObject::GetInstance()->m_pos.y);
	}

	if (CCameraObject::GetInsance()->m_count == -1)
	{
		Camera::GetInsance()->ChangeObject(CPlayerObject::GetInstance());
		CCameraObject::GetInsance()->ResetCount();
		CCameraObject::GetInsance()->isGoal = false;
	}

	SceneManager::GetInstance()->Update();
	//SceneManager::GetInstance()->Render();
	CObjectManager::GetInstance()->Update(isDebugMode);
	AnimationManager::GetInstance()->Update();
	Camera::GetInsance()->Update(m_pEngine->GetRenderTargetSize().width, m_pEngine->GetRenderTargetSize().height);
}

void GameProcess::Render()
{
	SceneManager::GetInstance()->Render();
	CObjectManager::GetInstance()->Render(Camera::GetInsance()->GetCameraVector());
	UIManager::GetInstance()->Render();
	SceneManager::GetInstance()->FadeInOut();
	//if (fadeIn == true)
	//{
	//	m_pEngine->FadeInOut(fadecount);
	//	if (fadecount >= 1)
	//		fadecount = 1;
	//	else
	//		fadecount += 0.02f;

	//}
	//else
	//{
	//	m_pEngine->FadeInOut(fadecount);
	//	if (fadecount <= 0)
	//		fadecount = 0;
	//	else
	//		fadecount += -0.005f;
	//}
}

void GameProcess::Finalize()
{

}

void GameProcess::DebugMode()
{
	if (CInput::GetInstance()->Key_Down(VK_HOME))
	{
		isDebugMode = !isDebugMode;
	}
}

// 디버깅용 랜더 함수 : 수정이 필요
void GameProcess::DebugRender()
{
	if (isDebugMode == false)
		return;

}

void GameProcess::FadeInOut()
{
}
