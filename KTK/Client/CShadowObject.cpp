#include "CShadowObject.h"
#include "AnimationManager.h"
#include "CAnimator.h"

CShadowObject::CShadowObject()
	: CObjectBase(CVector2D(-100,-100), eObjectKind::ETC)
{

}

CShadowObject::~CShadowObject()
{

}

void CShadowObject::Update()
{

	m_transform->SetPosition(m_pos);
}

void CShadowObject::Render(CVector2D cvector)
{
	AnimationManager::GetInstance()->DrawSprite(this, 1, cvector);
}

void CShadowObject::Initialize()
{
	m_status = eMyStatus::DASHLEFT;

	m_transform = new Transform();
	m_transform->SetLocalPosition(m_pos);
	m_transform->SetLocalRotation(0.f);
	m_transform->SetLocalScale(CVector2D(1, 1));

	JumpShadowEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_BossJumpShadowEffect[0]));
	JumpShadowEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_BossJumpShadowEffect[1]));

	StompShadowEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_BossStompShadowEffect[0]));
	StompShadowEffect.push_back(new CAnimator(AnimationManager::GetInstance()->m_BossStompShadowEffect[1]));

	JumpShadowEffect[0]->SetAnimationClip(AnimationManager::GetInstance()->m_BossJumpShadowEffect[0]);
	JumpShadowEffect[1]->SetAnimationClip(AnimationManager::GetInstance()->m_BossJumpShadowEffect[1]);

	StompShadowEffect[0]->SetAnimationClip(AnimationManager::GetInstance()->m_BossStompShadowEffect[0]);
	StompShadowEffect[1]->SetAnimationClip(AnimationManager::GetInstance()->m_BossStompShadowEffect[1]);
}

RECT CShadowObject::GetRECT()
{
	return m_colliderRect;
}

void CShadowObject::HPDown(int damage)
{

}

void CShadowObject::SetCollidertRect(CVector2D pos, CVector2D resize)
{

}
