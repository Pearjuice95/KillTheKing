#include "Stage00.h"
#include "CObjectManager.h"
#include "CPlayerObject.h"
#include "CColliderBase.h"
#include "CCloseObject.h"
#include "CRangeObject.h"
#include "CAnimator.h"
#include "AnimationManager.h"
#include "YDEngine.h"
#include "CSprite.h"
#include "Camera.h"
#include "Sound.h"

Stage00::Stage00()
	:m_isStage0Clear(false)
{

}

Stage00::~Stage00()
{

}

void Stage00::Initialize(CSprite* gatesprite)
{
	// 도착 지점의 좌표를 가지고 있는다.
	BGMPause();
	BGM(10);
	m_goalBox.left = 1150;
	m_goalBox.top = 300;
	m_goalBox.right = 1500;
	m_goalBox.bottom = 600;
	CloseObjectCreatePool();
	RangeObjectCreatePool();
	CPlayerObject::GetInstance()->m_isCollide = true;
	CPlayerObject::GetInstance()->m_canControl = true;
	m_isSuper = false;
	m_iseffect = false;
	m_time = 0.0f;
	GateSprite = gatesprite;
	count = 0;
	m_isStage0Clear = false;
	CPlayerObject::GetInstance()->m_isCollide = true;
	CPlayerObject::GetInstance()->m_canControl = true;
	CPlayerObject::GetInstance()->m_HP = 5;
	CPlayerObject::GetInstance()->m_totalStatus = eToTalStatus::IDLE;
	CPlayerObject::GetInstance()->m_status = eMyStatus::IDLERIGHT;
	CPlayerObject::GetInstance()->m_superCount = 50;
	
	//CPlayerObject::GetInstance()->m_Hp = 5;
}

bool Stage00::Update()
{
	if (m_isStage0Clear) // 조건이 클리어이면 false를 반납해서 Update를 멈춘다.
	{
		CObjectManager::GetInstance()->SetPlayerHitColliderBox();
		if (m_colliderBase->BoxColliderCheck(&m_goalBox, &CObjectManager::GetInstance()->playerCollider))
			return false;
	}
	else
	{
		Check();
		return true;
	}
}

void Stage00::Render()
{
	GateEffect();
}

void Stage00::Finalize()
{

}

void Stage00::SetObject(CVector2D playerpos)
{
	// 플레이어 좌표를 맞게 바꿔준다.
	CPlayerObject::GetInstance()->m_pos = playerpos;
}

void Stage00::Check()
{
	CObjectManager::GetInstance()->SetPlayerAttackColliderBox();
	if (CPlayerObject::GetInstance()->m_superCount == 0)
		m_isSuper = true;
	if (m_isSuper && m_colliderBase->BoxColliderCheck(&m_goalBox, &CObjectManager::GetInstance()->collider_1))
		if (CPlayerObject::GetInstance()->m_animator->GetCurrentIdx() >= CPlayerObject::GetInstance()->m_animator->GetTotalFrameIdx() - 1)
		{
			SoundPlay(24);
			count++;
			CPlayerObject::GetInstance()->m_animator->ResetCurrentIdx();
			CPlayerObject::GetInstance()->m_animator->ResetLoadingTime();

		}
	if (count > 5)
	{
		m_iseffect = true;
	}

	else if (count == 5)
	{
		SoundPlay(25);
	}
}

void Stage00::GateEffect()
{
	if (m_iseffect == true || m_isStage0Clear == true)
	{
		AnimationManager::GetInstance()->m_pEngine->DrawSprite(GateSprite, 1168, 192, 1, Camera::GetInsance()->GetCameraVector());
		m_time += 0.1f;
		if (m_time >= 12.0f)
			m_isStage0Clear = true;
	}

}


void Stage00::CloseObjectCreatePool()
{
	CCloseObject* combat;
	for (int i = 0; i < 100; i++)
	{
		combat = new CCloseObject(CVector2D(400, 350));
		combat->m_animator = new CAnimator(AnimationManager::GetInstance()->GetAnimationClip(combat));
		combat->m_isRender = false;
		CObjectManager::GetInstance()->CloseObjectPool.push_back(combat);
	}
	CObjectManager::GetInstance()->InitCloseMonster();
}

void Stage00::RangeObjectCreatePool()
{
	CRangeObject* range;
	for (int i = 0; i < 50; i++)
	{
		range = new CRangeObject(CVector2D(100, 100));
		range->m_sprite = AnimationManager::GetInstance()->m_pEngine->LoadSpriteFromData(11, CVector2D(0, 400), 199, 99, CVector2D(-0.8f, 0.f), 0.3f);
		range->m_animator = new CAnimator(AnimationManager::GetInstance()->GetAnimationClip(range));
		range->m_isRender = false;
		CObjectManager::GetInstance()->RangeObjectPool.push_back(range);
	}
	CObjectManager::GetInstance()->InitRangeMonster();
}
