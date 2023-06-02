#include "CWallObject.h"
#include "Transform.h"
#include "AnimationManager.h"

CWallObject::CWallObject(CVector2D m_pos, RECT rect)
	: CObjectBase(CVector2D(m_pos), eObjectKind::WALL), m_collider(rect)
{

}

CWallObject::~CWallObject()
{

}

void CWallObject::Initialize()
{
	m_transform = new Transform();
	m_transform->SetLocalPosition(m_pos);
	m_transform->SetLocalRotation(0.f);
	m_transform->SetLocalScale(CVector2D(1, 1));
	m_status = eMyStatus::IDLERIGHT;
	m_isCollide - true;
	m_pos.y = m_collider.top + ((m_collider.bottom - m_collider.top) / 2);
	m_pos.x = m_collider.left +((m_collider.right - m_collider.left) / 2);
}

void CWallObject::Update()
{
	m_transform->SetLocalPosition(m_pos);
	m_pos = m_transform->GetLocalPosition();
}

void CWallObject::Render(CVector2D cvector)
{
	//AnimationManager::GetInstance()->DrawSprite(this, 1, cvector);

}

RECT CWallObject::GetRECT()
{
	return m_collider;
}

//void CWallObject::SetCollidertRect(RECT rect)
//{
//	m_collider = rect;
//}

void CWallObject::HPDown(int damage)
{

}

void CWallObject::SetCollidertRect(CVector2D pos, CVector2D resize)
{

}
