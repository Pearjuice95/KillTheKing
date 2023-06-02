#include "CBossObject.h"
#include "CPlayerObject.h"
#include "Transform.h"
#include "AnimationManager.h"
#include "CAnimator.h"
#include "Camera.h"
#include "CCameraObject.h"
#include "Sound.h"

CBossObject::CBossObject()
	: CObjectBase(CVector2D(-1000, -1000), eObjectKind::BOSS), m_jumpDelayTimer(40), m_jumpDmgTimer(60), m_patternTimerCur(0), m_patternPhase(0),
	m_patternDelayTimer(120), m_patternDelayCur(0), m_afterAttackDelayTimer(30)
{
}

CBossObject::~CBossObject()
{

}

void CBossObject::Update()
{
	if (m_status != eMyStatus::DIELEFT && m_status != eMyStatus::DIERIGHT)
	{
		if (m_prevStatus != m_status)
		{
			AnimationManager::GetInstance()->SetStatus(this);
		}

		m_prevStatus = m_status;

		//if (m_isHit)
		//{
		//	m_HP -= CPlayerObject::GetInstance()->m_dmg;
		//	m_isHit = false;
		//}

		if (m_HP <= 0 && !m_isDead)
		{
			SoundPlay(22);
			m_isCollide = false;
			m_isAlive = false;
			m_cancontrol = false;
			m_isDead = true;
			if (m_status == eMyStatus::IDLELEFT || m_status == eMyStatus::ATTACKLEFT || m_status == eMyStatus::DASHLEFT || m_status == eMyStatus::AFTERDASHLEFT)
			{
				m_status = eMyStatus::DIELEFT;
				m_totalStatus = eToTalStatus::DIE;
				AnimationManager::GetInstance()->SetStatus(this);
			}
			else if (m_status == eMyStatus::IDLERIGHT || m_status == eMyStatus::ATTACKRIGHT || m_status == eMyStatus::DASHRIGHT || m_status == eMyStatus::AFTERDASHRIGHT)
			{
				m_status = eMyStatus::DIERIGHT;
				m_totalStatus = eToTalStatus::DIE;
				AnimationManager::GetInstance()->SetStatus(this);
			}

			else
			{
				m_status = eMyStatus::DIERIGHT;
				m_totalStatus = eToTalStatus::DIE;
				AnimationManager::GetInstance()->SetStatus(this);
			}
		}

		if (m_cancontrol)
		{
			if (m_patternDelay)
			{
				m_patternDelayCur++;
				if (m_patternDelayTimer <= m_patternDelayCur)
				{
					m_patternDelayCur = 0;
					m_patternDelay = false;
				}
			}

			if (m_status == eMyStatus::IDLELEFT || m_status == eMyStatus::IDLERIGHT)
			{
				if (m_pos.x < CPlayerObject::GetInstance()->m_pos.x)
				{
					m_status = eMyStatus::IDLERIGHT;
				}

				else
				{
					m_status = eMyStatus::IDLELEFT;
				}
			}
		}

		m_pShadow->Update();
	}
	m_transform->SetPosition(m_pos);
}

void CBossObject::Render(CVector2D cvector)
{
	AnimationManager::GetInstance()->DrawSprite(this, 1, cvector);
	m_pShadow->Render(cvector);
}

void CBossObject::Initialize()
{
	m_transform = new Transform();
	m_transform->SetLocalPosition(m_pos);
	m_transform->SetLocalRotation(0.f);
	m_transform->SetLocalScale(CVector2D(1, 1));

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

	m_HP = 50;

	m_pShadow = new CShadowObject();
	m_pShadow->Initialize();
	m_pShadow->m_animator = new CAnimator(AnimationManager::GetInstance()->GetAnimationClip(m_pShadow));

	m_cancontrol = false;
	m_isCollide = true;
	m_status = eMyStatus::IDLELEFT;
	m_pos.x = -1000;
	m_pos.y = -1000;
	m_isDead = false;
}

RECT CBossObject::GetRECT()
{
	return m_colliderRect;
}

void CBossObject::HPDown(int damage)
{
	m_isHit = true;
}

void CBossObject::SetCollidertRect(CVector2D pos, CVector2D resize)
{

}

void CBossObject::JumpPattern_Intro()
{
	m_patternPos.x = m_pos.x;
	m_patternPos.y = m_pos.y - 300;
	m_patternTimerCur = 0;
	m_patternPhase++;

	if (m_status == eMyStatus::IDLELEFT)
		m_status = eMyStatus::DASHLEFT;

	else
		m_status = eMyStatus::DASHRIGHT;

	AnimationManager::GetInstance()->SetStatus(this);
}

void CBossObject::JumpReady()
{
	if (m_animator->GetCurrentIdx() == m_animator->GetTotalFrameIdx() - 1)
	{
		m_pShadow->m_pos = m_pos;
		m_pShadow->m_status = eMyStatus::DASHLEFT;
		m_patternPhase++;
		AnimationManager::GetInstance()->SetStatus(m_pShadow);
		SoundPlay(18);
	}
}

void CBossObject::JumpPattern_Jump()
{
	if (m_pos.y <= m_patternPos.y)
	{
		m_patternPhase++;
		m_pos.x = -1000;
		m_pos.y = -1000;
		m_pShadow->m_pos = m_pos;
	}

	else
		m_pos.y -= 30;
}

void CBossObject::JumpPatternDelayTime()
{
	m_patternTimerCur++;
	if (m_patternTimerCur >= m_jumpDelayTimer)
	{
		m_patternPhase++;
		m_patternTimerCur = 0;
		m_patternPos = CPlayerObject::GetInstance()->m_pos;
		m_pShadow->m_pos = m_patternPos;
		m_pShadow->m_status = eMyStatus::AFTERDASHLEFT;
		AnimationManager::GetInstance()->SetStatus(m_pShadow);
		/*m_pos.x = m_patternPos.x;
		m_pos.y = m_patternPos.y;

		if (m_status == eMyStatus::DASHLEFT)
			m_status = eMyStatus::AFTERDASHLEFT;

		else
			m_status = eMyStatus::AFTERDASHRIGHT;*/
	}
}

void CBossObject::JumpStomp()
{
	m_patternTimerCur++;

	if (m_patternTimerCur >= m_jumpDelayTimer)
	{
		m_pos = m_patternPos;
		m_patternPhase++;
		m_patternTimerCur = 0;

		CCameraObject::GetInsance()->ResetCount();
		CCameraObject::GetInsance()->isShake = true;
		CCameraObject::GetInsance()->SetObjPos(CPlayerObject::GetInstance());
		Camera::GetInsance()->ChangeObject(CCameraObject::GetInsance());
		CCameraObject::GetInsance()->SetShakeDistance(50.0f);

		if (m_status == eMyStatus::DASHLEFT)
			m_status = eMyStatus::AFTERDASHLEFT;

		else
			m_status = eMyStatus::AFTERDASHRIGHT;

		SoundPlay(19);
		m_pShadow->m_pos.x = -1000;
		m_pShadow->m_pos.y = -1000;
		AnimationManager::GetInstance()->SetStatus(m_pShadow);
		AnimationManager::GetInstance()->SetStatus(this);
	}
}

void CBossObject::JumpCollideDelete()
{
	if (m_animator->GetCurrentIdx() == 7)
	{
		m_patternPhase++;
	}
}

void CBossObject::JumpPatternDmg()
{
	if (m_animator->GetCurrentIdx() == m_animator->GetTotalFrameIdx() - 1)
	{
		m_patternPhase = 0;
		m_isPattern = false;
		m_jumpPatternOn = false;
		m_attacked = false;

		if (m_status == eMyStatus::AFTERDASHLEFT)
		{
			m_status = eMyStatus::IDLELEFT;
		}

		else
			m_status = eMyStatus::IDLERIGHT;

		AnimationManager::GetInstance()->SetStatus(this);
	}
}

void CBossObject::AttackPattern_intro()
{
	m_patternPos = CPlayerObject::GetInstance()->m_pos;
	m_patternPhase++;

	if (m_status == eMyStatus::IDLELEFT)
	{
		m_status = eMyStatus::ATTACKLEFT;
	}

	else
		m_status = eMyStatus::ATTACKRIGHT;

	AnimationManager::GetInstance()->SetStatus(this);
}

void CBossObject::AttackPattern_DelayTime()
{
	if (m_animator->GetCurrentIdx() == 4)
	{
		m_patternPhase++;
		SoundPlay(20);
		CCameraObject::GetInsance()->ResetCount();
		CCameraObject::GetInsance()->isShake = true;
		CCameraObject::GetInsance()->SetObjPos(CPlayerObject::GetInstance());
		Camera::GetInsance()->ChangeObject(CCameraObject::GetInsance());
		CCameraObject::GetInsance()->SetShakeDistance(30.0f);
	}
}

void CBossObject::AttackPattern_Attack()
{
	if (m_animator->GetCurrentIdx() == 6)
	{
		m_patternPhase++;
	}
}

void CBossObject::AttackPattern_AfterAttack()
{
	m_patternTimerCur++;

	if (m_afterAttackDelayTimer <= m_patternTimerCur)
	{
		if (m_status == eMyStatus::ATTACKLEFT)
		{
			m_status = eMyStatus::IDLELEFT;
		}

		else
			m_status = eMyStatus::IDLERIGHT;

		m_patternTimerCur = 0;
		m_patternPhase = 0;
		m_isPattern = false;
		m_attackPatternOn = false;
		m_attacked = false;
		AnimationManager::GetInstance()->SetStatus(this);
	}
}

