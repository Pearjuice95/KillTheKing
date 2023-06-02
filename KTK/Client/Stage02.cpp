#include "Stage02.h"
#include "CPlayerObject.h"
#include "CObjectManager.h"
#include "CColliderBase.h"
#include "Sound.h"


Stage02::Stage02()
{

}

Stage02::~Stage02()
{

}

void Stage02::Initialize()
{
	BGMPause();
	BGM(12);
	m_goalBox.left = 750;
	m_goalBox.top = 330;
	m_goalBox.right = 1150;
	m_goalBox.bottom = 400;

	CPlayerObject::GetInstance()->m_isCollide = true;
	CPlayerObject::GetInstance()->m_canControl = true;
	CPlayerObject::GetInstance()->m_HP = 5;
	CPlayerObject::GetInstance()->m_totalStatus = eToTalStatus::IDLE;
	CPlayerObject::GetInstance()->m_status = eMyStatus::IDLERIGHT;
	CPlayerObject::GetInstance()->m_superCount = 0;
	//CPlayerObject::GetInstance()->m_Hp = 5;
}

bool Stage02::Update()
{
	Wave01();
	if (m_isStage0Clear) // 조건이 클리어이면 false를 반납해서 Update를 멈춘다.
		return false;
	else
	{
		return true;
	}
}

void Stage02::Render()
{

}

void Stage02::Finalize()
{

}

void Stage02::SetObject(CVector2D playerpos)
{
	CPlayerObject::GetInstance()->m_pos = playerpos;
}

void Stage02::Wave01()
{
	CObjectManager::GetInstance()->SetPlayerHitColliderBox();
	if (m_colliderBase->BoxColliderCheck(&m_goalBox, &CObjectManager::GetInstance()->playerCollider))
		m_isStage0Clear = true;
}

void Stage02::Wave02()
{

}

void Stage02::Wave03()
{

}
