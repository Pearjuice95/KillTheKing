#include "CArrowObject.h"
#include "CPlayerObject.h"
#include "CAnimator.h"
#include "AnimationManager.h"

CArrowObject::CArrowObject()
	: m_speed(6)
{
	
}

CArrowObject::~CArrowObject()
{

}

void CArrowObject::Initialize()
{
	m_transform = new Transform();
	m_transform->SetLocalPosition(m_pos);
	m_transform->SetLocalRotation(0.f);
	m_transform->SetLocalScale(CVector2D(1, 1));

	AttackEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_monsterArrowBoomEffect[0]));
	AttackEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_monsterArrowBoomEffect[1]));

	AttackEffect[0]->SetAnimationClip(AnimationManager::GetInstance()->m_monsterArrowBoomEffect[0]);
	AttackEffect[1]->SetAnimationClip(AnimationManager::GetInstance()->m_monsterArrowBoomEffect[1]);
}

void CArrowObject::Shoot()
{
	if (m_isAlive)
	{
		if (!m_isFly)
		{
			m_direct = m_pos.DistanceTo(m_playerPos);
			m_theta = m_pos.Theta(m_direct);
			if (CPlayerObject::GetInstance()->m_pos.y < m_pos.y)
				m_transform->SetLocalRotation(360 - m_theta);
			else
				m_transform->SetLocalRotation(m_theta);
			m_isFly = true;
			m_isBreak = false;
			for (int i = 0; i < AttackEffect.size(); i++)
			{
				AttackEffect[i]->ResetCurrentIdx();
				AttackEffect[i]->ResetLoadingTime();
			}
		}

		else if (m_isFly)
		{
			m_pos.x += (m_direct.x * m_speed);
			m_pos.y += (m_direct.y * m_speed);
		}

		m_transform->SetLocalPosition(m_pos);
	
	}
}
