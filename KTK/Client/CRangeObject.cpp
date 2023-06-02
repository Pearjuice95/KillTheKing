#include "CRangeObject.h"
#include "AnimationManager.h"
#include "CVector2D.h"
#include "Transform.h"
#include "CPlayerObject.h"
#include "CAnimator.h"
#include "Camera.h"
#include "Sound.h"

CRangeObject::CRangeObject(CVector2D m_pos)
	:CObjectBase(m_pos, eObjectKind::RANGECOMBAT), m_atkCur(0), m_atkTime(30),
	m_hitCur(0), m_hitTime(31), m_stopCur(0), m_stopTime(100), m_atkDelayTime(240)
{

}

CRangeObject::~CRangeObject()
{

}

void CRangeObject::Initialize()
{
	m_transform = new Transform();
	m_transform->SetLocalPosition(m_pos);
	m_transform->SetLocalRotation(0.f);
	m_transform->SetLocalScale(CVector2D(1, 1));
	m_status = eMyStatus::IDLERIGHT;
	m_isAlive = true;
	m_isRender = false;
	m_isCollide = true;
	m_isMoveTO = false;

	m_arrow_1 = new CArrowObject();
	m_arrow_2 = new CArrowObject();
	m_arrow_3 = new CArrowObject();
	m_arrow_4 = new CArrowObject();

	arrowpool.push_back(m_arrow_1);
	arrowpool.push_back(m_arrow_2);
	arrowpool.push_back(m_arrow_3);
	arrowpool.push_back(m_arrow_4);

	for (int i = 0; i < arrowpool.size(); i++)
	{
		arrowpool[i]->Initialize();
	}

	HitEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_monsterHitEffect[0]));
	HitEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_monsterHitEffect[1]));
	SuperHitEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_monsterSuperHitEffect[0]));
	SuperHitEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_monsterSuperHitEffect[1]));



	HitEffect[0]->SetAnimationClip(AnimationManager::GetInstance()->m_monsterHitEffect[0]);
	HitEffect[1]->SetAnimationClip(AnimationManager::GetInstance()->m_monsterHitEffect[1]);
	SuperHitEffect[0]->SetAnimationClip(AnimationManager::GetInstance()->m_monsterSuperHitEffect[0]);
	SuperHitEffect[1]->SetAnimationClip(AnimationManager::GetInstance()->m_monsterSuperHitEffect[1]);

	m_HP = 2;
}

void CRangeObject::Update()
{
	if (m_isAlive)
	{
		m_prevStatus = m_status;
		m_prevPos = m_pos;
		if (m_isMoveTO)
		{
			//MoveToPos({ 200, 100 }, { 200,300 }, { 300,400 });
		}

		if (m_totalStatus == eToTalStatus::IDLE)
		{
			if (m_pos.x < CPlayerObject::GetInstance()->m_pos.x)
			{
				m_prevStatus = eMyStatus::IDLERIGHT;
				m_status = eMyStatus::IDLERIGHT;
				m_prevMove = eMyStatus::IDLERIGHT;
			}

			else
			{
				m_prevStatus = eMyStatus::IDLELEFT;
				m_status = eMyStatus::IDLELEFT;
				m_prevMove = eMyStatus::IDLELEFT;
			}
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
				m_totalStatus = eToTalStatus::IDLE;
			}
		}
		if (m_prevStatus != m_status)
		{
			AnimationManager::GetInstance()->SetStatus(this);
		}
	}

	for (int i = 0; i < arrowpool.size(); i++)
	{
		arrowpool[i]->Shoot();
	}

	if (!m_isMoveTO && m_totalStatus == eToTalStatus::IDLE)
	{
		m_delayCur += 1;

		if (m_delayCur >= m_atkDelayTime)
		{
			//m_prevStatus = m_status;
			//m_animator->ResetCurrentIdx();
			m_delayCur = 0;
			m_isShoot = true;
			AttackPos();
			m_isShoot = false;
		}
	}

	m_transform->SetLocalPosition(m_pos);
	m_pos = m_transform->GetLocalPosition();
}

void CRangeObject::Render(CVector2D cvector)
{
	if (m_isRender)
	{
		AnimationManager::GetInstance()->DrawSprite(this, 1, cvector);
		for (int i = 0; i < arrowpool.size(); i++)
		{
			if (arrowpool[i]->m_isAlive)
			{
				AnimationManager::GetInstance()->OneFrameSprite(m_sprite, arrowpool[i]->m_transform, Camera::GetInsance()->GetCameraVector());
			}
		}
	}
}


RECT CRangeObject::GetRECT()
{
	return m_colliderRect;
}

void CRangeObject::SetCollidertRect(CVector2D pos, CVector2D resize)
{
	CVector2D lefttop;
	lefttop.x = pos.x - resize.x / 2;
	lefttop.y = pos.y - resize.y / 2;

	RECT rect{ lefttop.x, lefttop.y, lefttop.x + resize.x, lefttop.y + resize.y };
	m_colliderRect = rect;
}

void CRangeObject::HPDown(int damage)
{
	for (int i = 0; i < HitEffect.size(); i++)
	{
		HitEffect[i]->ResetCurrentIdx();
		HitEffect[i]->ResetLoadingTime();
	}
	for (int i = 0; i < SuperHitEffect.size(); i++)
	{
		SuperHitEffect[i]->ResetCurrentIdx();
		SuperHitEffect[i]->ResetLoadingTime();
	}
	m_isHit = true;

	if (m_prevMove == eMyStatus::MOVELEFT || m_status == eMyStatus::IDLELEFT)
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

//void CRangeObject::SetAlive(bool live)
//{
//	m_isAlive = live;
//}

void CRangeObject::MoveToPos(CVector2D pos, CVector2D pos2, CVector2D goal)
{
	if (m_isMoveTO)
	{
		if (m_isStand_1 == false && m_isStand_2 == false)
		{
			CVector2D direct;
			direct = m_pos.DistanceTo(pos);
			m_pos.x += (direct.x * m_moveSpd);
			m_pos.y += (direct.y * m_moveSpd);

			if (0 <= direct.x)
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

			if (abs(m_pos.x - pos.x) <= m_moveSpd && abs(m_pos.y - pos.y) <= m_moveSpd)
			{
				m_isStand_1 = true;
				m_totalStatus = eToTalStatus::IDLE;
				if (m_status == eMyStatus::MOVELEFT)
				{
					m_status = eMyStatus::IDLELEFT;
					m_prevStatus = eMyStatus::IDLELEFT;
				}

				else
				{
					m_status = eMyStatus::IDLERIGHT;
					m_prevStatus = eMyStatus::IDLERIGHT;
				}
				return;
			}
		}

		else if (m_isStand_1 && m_isStand_2 == false)
		{
			m_stopCur++;
			if (m_stopCur >= m_stopTime)
			{
				m_isStand_2 = true;
				m_stopCur = 0;
			}
		}

		else if (m_isStand_1 && m_isStand_2)
		{
			CVector2D direct;
			direct = m_pos.DistanceTo(pos2);
			m_pos.x += (direct.x * m_moveSpd);
			m_pos.y += (direct.y * m_moveSpd);

			if (0 <= direct.x)
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

			if (abs(m_pos.x - pos2.x) <= m_moveSpd && abs(m_pos.y - pos2.y) <= m_moveSpd)
			{
				m_isStand_1 = false;
				return;
			}
		}

		else if (m_isStand_1 == false && m_isStand_2)
		{
			CVector2D direct;
			direct = m_pos.DistanceTo(goal);
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

			if (abs(m_pos.x - goal.x) <= m_moveSpd && abs(m_pos.y - goal.y) <= m_moveSpd)
			{
				m_isMoveTO = false;
				m_totalStatus = eToTalStatus::IDLE;
				if (m_status == eMyStatus::MOVELEFT)
				{
					m_status = eMyStatus::IDLELEFT;
					m_prevStatus = eMyStatus::IDLELEFT;
				}

				else
				{
					m_status = eMyStatus::IDLERIGHT;
					m_prevStatus = eMyStatus::IDLERIGHT;
				}
				return;
			}
		}
	}
}

void CRangeObject::AttackPos()
{
	if (m_isShoot)
	{
		for (int i = 0; i < arrowpool.size(); i++)
		{
			if (arrowpool[i]->m_isAlive == false)
			{
				SoundPlay(15);
				if (m_status == eMyStatus::IDLELEFT)
				{
					m_status = eMyStatus::ATTACKLEFT;
					arrowpool[i]->m_pos.x = m_pos.x - 20;
				}

				else if (m_status == eMyStatus::IDLERIGHT)
				{
					m_status = eMyStatus::ATTACKRIGHT;
					arrowpool[i]->m_pos.x = m_pos.x + 20;
				}

				m_totalStatus = eToTalStatus::ATTACK;
				arrowpool[i]->m_pos.y = m_pos.y;
				arrowpool[i]->m_playerPos = CPlayerObject::GetInstance()->m_pos;
				arrowpool[i]->m_isAlive = true;
				arrowpool[i]->m_isFly = false;
				break;
			}

			else
			{
				m_status = m_prevStatus;
			}
		}
	}
}
