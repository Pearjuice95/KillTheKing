#include "CCameraObject.h"
#include "CObjectBase.h"
#include "enum.h"
#include "Transform.h"
#include "CPlayerObject.h"
#include <cmath>

CCameraObject::CCameraObject()
	:CObjectBase({ 0,0 }, eObjectKind::ETC), m_speed(1.0f), m_count(0), isGoal(false), isShake(false), isVertial(false),
	isUpLeft(false), isDownRight(false)
{

}

CCameraObject::~CCameraObject()
{

}

void CCameraObject::Update()
{

}

void CCameraObject::Render(CVector2D cvector)
{

}

void CCameraObject::Initialize()
{
	m_transform = new Transform();
	m_transform->SetLocalPosition(m_pos);
	m_transform->SetLocalRotation(0.f);
	m_transform->SetLocalScale(CVector2D(1, 1));
	//m_pos.x = 200;
	//m_pos.y = 500;
}

RECT CCameraObject::GetRECT()
{
	return m_colliderRect;
}

void CCameraObject::SetCollidertRect(CVector2D pos, CVector2D resize)
{

}

void CCameraObject::HPDown(int damage)
{

}

void CCameraObject::ChangePos(float x, float y)
{
	float check = m_speed / 2.f;
	if (abs(m_pos.x - x) <= check && abs(m_pos.y - y) <= check)
	{
		if (!isShake)
			isGoal = true;

		if (isUpLeft)
		{
			isUpLeft = false;
			isDownRight = true;
		}

		else
		{
			isDownRight = false;
			isUpLeft = true;
		}

		m_count++;
	}

	if (!isGoal)
	{
		CVector2D District;
		District.x = x;
		District.y = y;

		CVector2D Direct = m_pos.DistanceTo(District);

		m_pos.x += (Direct.x * m_speed);
		m_pos.y += (Direct.y * m_speed);
	}
}

void CCameraObject::ChangePos2(CVector2D _Prev, CVector2D _Dest)
{

}

void CCameraObject::SetObjPos(CObjectBase* object)
{
	m_pos = object->m_pos;
}

void CCameraObject::ChangeSpeed(float speed)
{
	m_speed = speed;
}

void CCameraObject::SetShakeDistance(float distance)
{
	m_UpY = m_pos.y - distance;
	m_DownY = m_pos.y + distance;

	m_LeftX = m_pos.x - distance;
	m_RightX = m_pos.x + distance;

	isUpLeft = true;
}

void CCameraObject::ShakePos(float speed, bool vertical, float distance, int count)
{
	m_speed = speed;

	//ChangePos(m_pos.x, m_UpY);
	//
	//std::mt19937 _gen(1000);
	//std::uniform_int_distribution<> _Range(-30, 30);

	//CVector2D _temp = m_pos;

	//_temp.x += _Range(_gen);
	//_temp.y += _Range(_gen);

	if (vertical && m_count <= count)
	{
		if (isUpLeft)
		{
			ChangePos(m_pos.x, m_UpY);
		}

		else if (isDownRight)
		{
			ChangePos(m_pos.x, m_DownY);
		}
	}

	else if (!vertical && m_count <= count)
	{
		if (isUpLeft)
		{
			ChangePos(m_LeftX, m_pos.y);
		}

		else if (isDownRight)
		{
			ChangePos(m_RightX, m_pos.y);
		}
	}

	if (m_count > count)
	{
		isShake = false;
		m_count = -2;
	}
}
