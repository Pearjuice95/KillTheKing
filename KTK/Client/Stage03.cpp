#include "Stage03.h"
#include "CPlayerObject.h"
#include "CObjectManager.h"
#include "CBossObject.h"
#include "Camera.h"
#include "CCameraObject.h"
#include "AnimationManager.h"
#include "CAnimator.h"
#include "Sound.h"

Stage03::Stage03()
{

}

Stage03::~Stage03()
{

}

void Stage03::Initialize()
{
	BGMPause();
	CObjectManager::GetInstance()->boss->Initialize();
	m_noAcess.left = 129;
	m_noAcess.top = 0;
	m_noAcess.right = 2102;
	m_noAcess.bottom = 683;

	m_entryPoint.left = 345;
	m_entryPoint.top = 2000;
	m_entryPoint.right = 1891;
	m_entryPoint.bottom = 2237;

	m_movePos.x = 1115;
	m_movePos.y = 1579;

	CPlayerObject::GetInstance()->m_isCollide = true;
	CPlayerObject::GetInstance()->m_canControl = true;
	CPlayerObject::GetInstance()->m_HP = 5;
	CPlayerObject::GetInstance()->m_totalStatus = eToTalStatus::IDLE;
	CPlayerObject::GetInstance()->m_status = eMyStatus::IDLERIGHT;
	//CPlayerObject::GetInstance()->m_Hp = 5;

	CCameraObject::GetInsance()->m_pos = m_movePos;

	m_isBattle = false;
	m_isStart = false;
	m_playerMove = false;
	isChangeCamera = false;
	m_phasecur = -1;
	CPlayerObject::GetInstance()->m_superCount = 0;
}

bool Stage03::Update()
{
	if (CPlayerObject::GetInstance()->m_totalStatus == eToTalStatus::DIE)
	{
		if (CPlayerObject::GetInstance()->m_animator->GetCurrentIdx() == CPlayerObject::GetInstance()->m_animator->GetTotalFrameIdx())
		{
			if (SceneManager::GetInstance()->m_wait)
			{
				SceneManager::GetInstance()->m_timer += 0.1f;
				SceneManager::GetInstance()->m_isFadein = true;
				if (SceneManager::GetInstance()->m_timer >= 20.f)
				{
					SceneManager::GetInstance()->m_sceneNumber--;
					SceneManager::GetInstance()->m_prevStage = (eScene)SceneManager::GetInstance()->m_sceneNumber;
					SceneManager::GetInstance()->m_isLoad = false;
					SceneManager::GetInstance()->m_isNextScene = false;
				}
			}

		}
	}
	CObjectManager::GetInstance()->boss->Update();
	EntryPointIn();
	BossBattleScene();
	if (CBossObject::GetInsance()->m_totalStatus == eToTalStatus::DIE)
	{
		if (CBossObject::GetInsance()->m_animator->GetCurrentIdx() == CBossObject::GetInsance()->m_animator->GetTotalFrameIdx())
		{
			CBossObject::GetInsance()->m_pos = CVector2D(0, 0);
			SceneManager::GetInstance()->m_sceneNumber = 5;
		}
	}
	return true;
}

void Stage03::Render()
{
	CObjectManager::GetInstance()->boss->Render(Camera::GetInsance()->GetCameraVector());
}

void Stage03::Finalize()
{

}

void Stage03::SetObject(CVector2D playerpos)
{
	// 여기서 카메라 Set해주세요.
	// 플레이어 좌표를 맞게 바꿔준다.
	CPlayerObject::GetInstance()->m_pos = playerpos;
}

void Stage03::EntryPointIn()
{
	if (m_isStart == false && m_isBattle == false)
	{
		if (m_colliderBase->BoxColliderCheck(&m_entryPoint, &CObjectManager::GetInstance()->playerCollider))
		{
			m_phasecur++;
			m_isStart = true;
		}
	}
}

void Stage03::BossDrop()
{



}

void Stage03::MakeInvisibleWall()
{

}

void Stage03::RemakeCamera()
{

}

void Stage03::MoveToPosition()
{
	CPlayerObject::GetInstance()->m_canControl = false;
	CPlayerObject::GetInstance()->m_status = eMyStatus::MOVEUP;
	m_playerMove = true;
	m_phasecur++;
}

void Stage03::BossBattleScene()
{
	if (m_phasecur == 0)
	{
		MoveToPosition();
	}

	if (m_phasecur == 1)
	{
		CPlayerObject::GetInstance()->m_pos.y -= 10;

		if (CPlayerObject::GetInstance()->m_pos.y <= m_movePos.y)
		{
			BGM(12);
			m_phasecur++;
			CCameraObject::GetInsance()->SetObjPos(CPlayerObject::GetInstance());
			Camera::GetInsance()->ChangeObject(CCameraObject::GetInsance());
			CCameraObject::GetInsance()->ChangeSpeed(6.f);
		}
	}

	else if (m_phasecur == 2)
	{
		CCameraObject::GetInsance()->ChangePos(1115, 719);
		if (CCameraObject::GetInsance()->isGoal == true)
		{
			m_phasecur++;
		}
	}

	else if (m_phasecur == 3)
	{
		CCameraObject::GetInsance()->isGoal = false;
		CBossObject::GetInsance()->m_patternPos.x = 1115;
		CBossObject::GetInsance()->m_patternPos.y = 719;
		CBossObject::GetInsance()->m_pShadow->m_pos = CBossObject::GetInsance()->m_patternPos;
		CBossObject::GetInsance()->m_pShadow->m_status = eMyStatus::AFTERDASHLEFT;
		AnimationManager::GetInstance()->SetStatus(CBossObject::GetInsance()->m_pShadow);
		m_phasecur++;
	}

	else if (m_phasecur == 4)
	{
		CBossObject::GetInsance()->m_patternTimerCur++;

		if (CBossObject::GetInsance()->m_patternTimerCur >= CBossObject::GetInsance()->m_jumpDelayTimer)
		{
			CBossObject::GetInsance()->m_pos = CBossObject::GetInsance()->m_patternPos;
			CBossObject::GetInsance()->m_patternTimerCur = 0;

			CCameraObject::GetInsance()->ResetCount();
			CCameraObject::GetInsance()->isShake = true;
			CCameraObject::GetInsance()->SetObjPos(CBossObject::GetInsance());
			Camera::GetInsance()->ChangeObject(CCameraObject::GetInsance());
			CCameraObject::GetInsance()->SetShakeDistance(50.0f);

			SoundPlay(19);
			CBossObject::GetInsance()->m_status = eMyStatus::AFTERDASHLEFT;
			CBossObject::GetInsance()->m_pShadow->m_pos.x = -1000;
			CBossObject::GetInsance()->m_pShadow->m_pos.y = -1000;
			AnimationManager::GetInstance()->SetStatus(CBossObject::GetInsance()->m_pShadow);
			AnimationManager::GetInstance()->SetStatus(CBossObject::GetInsance());

			m_phasecur++;
		}
	}

	else if (m_phasecur == 5)
	{
		if (CBossObject::GetInsance()->m_animator->GetCurrentIdx() == CBossObject::GetInsance()->m_animator->GetTotalFrameIdx() - 1)
		{
			CBossObject::GetInsance()->m_status = eMyStatus::IDLELEFT;
			m_phasecur++;
		}
	}

	else if (m_phasecur == 6)
	{
		CCameraObject::GetInsance()->SetObjPos(CPlayerObject::GetInstance());
		Camera::GetInsance()->ChangeObject(CPlayerObject::GetInstance());
		CBossObject::GetInsance()->m_cancontrol = true;
		CPlayerObject::GetInstance()->m_canControl = true;
		m_phasecur++;
		BGMPause();
		BGM(13);
	}
}