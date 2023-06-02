#include "CCloseObject.h"
#include "AnimationManager.h"
#include "CVector2D.h"
#include "CPlayerObject.h"
#include "Transform.h"
#include "CAnimator.h"
#include "Sound.h"
#include "AnimationManager.h"

CCloseObject::CCloseObject(CVector2D m_pos)
	: CObjectBase(m_pos, eObjectKind::CLOSECOMBAT), m_atkCur(0), m_atkTime(60),
	m_hitCur(0), m_hitTime(31)

{

}

CCloseObject::~CCloseObject()
{

}

void CCloseObject::Initialize()
{
	//SetRect();
	m_transform = new Transform();
	m_transform->SetLocalPosition(m_pos);
	m_transform->SetLocalRotation(0.f);
	m_transform->SetLocalScale(CVector2D(1, 1));
	m_status = eMyStatus::IDLERIGHT;
	m_isAlive = true;
	m_isRender = false;
	m_isCollide = true;
	m_isMoveTO = true;
	HitEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_monsterHitEffect[0]));
	HitEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_monsterHitEffect[1]));
	SuperHitEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_monsterSuperHitEffect[0]));
	SuperHitEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_monsterSuperHitEffect[1]));
	/*AttackEffect.push_back(new CAnimator(AnimationManager::GetInsance()->m_monsterAttackEffect[0]));
	AttackEffect.push_back(new CAnimator(AnimationManager::GetInsance()->m_monsterAttackEffect[1]));*/

	HitEffect[0]->SetAnimationClip(AnimationManager::GetInstance()->m_monsterHitEffect[0]);
	HitEffect[1]->SetAnimationClip(AnimationManager::GetInstance()->m_monsterHitEffect[1]);
	SuperHitEffect[0]->SetAnimationClip(AnimationManager::GetInstance()->m_monsterSuperHitEffect[0]);
	SuperHitEffect[1]->SetAnimationClip(AnimationManager::GetInstance()->m_monsterSuperHitEffect[1]);
	/*AttackEffect[0]->SetAnimationClip(AnimationManager::GetInsance()->m_monsterAttackEffect[0]);
	AttackEffect[1]->SetAnimationClip(AnimationManager::GetInsance()->m_monsterAttackEffect[1]);*/

	m_HP = 2;

}

void CCloseObject::Update()
{

	if (m_isAlive)
	{
		m_prevPos = m_pos;
		if (m_totalStatus == eToTalStatus::MOVE || m_totalStatus == eToTalStatus::IDLE)
		{
			MoveToPlayer();
		}

		if (m_totalStatus == eToTalStatus::HIT)
		{
			m_hitCur += 1;
			m_prevStatus = m_status;

			if (m_hitCur >= m_hitTime)
			{
				m_hitCur = 0;

				if (m_HP <= 0)
				{
					SoundPlay(17);
					m_isAlive = false;
					m_isCollide = false;

					if (m_prevMove == eMyStatus::IDLELEFT || m_prevMove == eMyStatus::ATTACKLEFT || m_prevMove == eMyStatus::MOVELEFT)
					{
						m_status = eMyStatus::DIELEFT;
						m_totalStatus = eToTalStatus::DIE;
					}

					else if (m_prevMove == eMyStatus::IDLERIGHT || m_prevMove == eMyStatus::ATTACKRIGHT || m_prevMove == eMyStatus::MOVERIGHT)
					{
						m_status = eMyStatus::DIERIGHT;
						m_totalStatus = eToTalStatus::DIE;
					}

					else
					{
						m_status = eMyStatus::DIELEFT;
						m_totalStatus = eToTalStatus::DIE;
					}
				}

				else
				{
					m_status = m_prevMove;
					m_totalStatus = eToTalStatus::IDLE;
				}
			}
		}

		else if (m_totalStatus == eToTalStatus::ATTACK)
		{
			m_atkCur += 1;

			if (m_atkCur >= m_atkTime)
			{
				//m_prevStatus = m_status;
				//m_animator->ResetCurrentIdx();
				m_status = m_prevMove;
				m_atkCur = 0;
				m_totalStatus = eToTalStatus::MOVE;
				/*	for (int i = 0; i < AttackEffect.size(); i++)
					{
						AttackEffect[i]->ResetCurrentIdx();
						AttackEffect[i]->ResetLoadingTime();
				}*/
			}
		}
		if (m_prevStatus != m_status)
		{
			AnimationManager::GetInstance()->SetStatus(this);
		}
	}
	m_transform->SetLocalPosition(m_pos);
	m_pos = m_transform->GetLocalPosition();
}

void CCloseObject::Render(CVector2D cvector)
{
	//this->m_animator->SetAnimationClip(AnimationManager::GetInsance()->totalAnimClip[static_cast<int>(objectKind)].at(static_cast<int>(GetStatus())));
	if (m_isRender)
		AnimationManager::GetInstance()->DrawSprite(this, 1, cvector);
}

RECT CCloseObject::GetRECT()
{
	return m_colliderRect;
}

// 좌상단을 받아오고 width, height를 받아온다. 그에따른 Rect를 지정
void CCloseObject::SetCollidertRect(CVector2D pos, CVector2D resize)
{
	CVector2D lefttop;
	lefttop.x = pos.x - resize.x / 2;
	lefttop.y = pos.y - resize.y / 2;

	RECT rect{ lefttop.x, lefttop.y, lefttop.x + resize.x, lefttop.y + resize.y };
	m_colliderRect = rect;
}

void CCloseObject::HPDown(int damage)
{
	m_isHit = true;

	if (m_prevMove == eMyStatus::MOVELEFT)
	{
		m_totalStatus = eToTalStatus::HIT;
		m_status = eMyStatus::HITLEFT;
	}

	else
	{
		m_totalStatus = eToTalStatus::HIT;
		m_status = eMyStatus::HITRIGHT;
	}


	AnimationManager::GetInstance()->SetStatus(this);
}

//void CCloseObject::SetAlive(bool live)
//{
//	m_isAlive = live;
//}

void CCloseObject::MoveToPlayer()
{
	if (m_isMoveTO)
	{
		if (m_prevStatus == eMyStatus::ATTACKLEFT || m_prevStatus == eMyStatus::ATTACKRIGHT)
		{
			m_animator->ResetCurrentIdx();
			m_animator->ResetLoadingTime();
		}

		CVector2D direct;
		direct = m_pos.DistanceTo(CPlayerObject::GetInstance()->m_pos);
		m_pos.x += (direct.x * m_moveSpd);
		m_pos.y += (direct.y * m_moveSpd);

		if (0 < direct.x)
		{
			m_totalStatus = eToTalStatus::MOVE;
			m_status = eMyStatus::MOVERIGHT;
			m_prevStatus = eMyStatus::MOVERIGHT;
		}

		else if (direct.x < 0)
		{
			m_totalStatus = eToTalStatus::MOVE;
			m_status = eMyStatus::MOVELEFT;
			m_prevStatus = eMyStatus::MOVELEFT;
		}
	}

	else
	{
		if (abs(m_pos.x - m_wallCollidePos.x) <= m_moveSpd && abs(m_pos.y - m_wallCollidePos.y) <= m_moveSpd)
		{
			m_isMoveTO = true;
			return;
		}

		CVector2D direct;
		direct = m_pos.DistanceTo(m_wallCollidePos);
		m_pos.x += (direct.x * m_moveSpd);
		m_pos.y += (direct.y * m_moveSpd);
	}
}