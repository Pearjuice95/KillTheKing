#include "CObjectBase.h"

CObjectBase::CObjectBase(CVector2D m_pos,eObjectKind objectkind)
	:m_pos(m_pos), m_animator(nullptr),objectKind(objectkind), m_colliderRect(RECT()),m_isCollide(true), m_moveSpd(3.0f),
	m_status(eMyStatus::IDLERIGHT), m_prevMove(eMyStatus::IDLERIGHT), m_prevStatus(eMyStatus::IDLERIGHT), m_HP(0)
{
}

CObjectBase::~CObjectBase()
{

}

eMyStatus CObjectBase::GetStatus()
{
	return m_status;
}

void CObjectBase::SetStatus(eMyStatus status)
{
	m_status = status;
}