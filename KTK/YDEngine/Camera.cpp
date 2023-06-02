#include "Camera.h"
#include "Transform.h"
#include "CObjectBase.h"

Camera::Camera()
{
}

Camera::~Camera()
{

}

void Camera::Initialize(CObjectBase* object)
{
	m_object = object;
	m_size = CVector2D(0, 0);
	m_cameraPosition = CVector2D(0, 0);
}

void Camera::Update(int x, int y)
{
	CVector2D cameraPos;
	CVector2D leftTopPos;

	cameraPos = m_object->m_pos;

	if (cameraPos.x <= m_left)
	{
		cameraPos.x = m_left;
	}
	else if (m_right <= cameraPos.x)
	{
		cameraPos.x = m_right;
	}

	if (cameraPos.y < m_top)
	{
		cameraPos.y = m_top;
	}

	else if (cameraPos.y > m_bottom)
	{
		cameraPos.y = m_bottom;
	}

	leftTopPos = cameraPos - CVector2D(m_size.x / 2, m_size.y / 2);
	m_cameraPosition = leftTopPos;
	SetCameraSize(x, y);
}

void Camera::SetCameraSize(int x, int y)
{
	m_size.x = x;
	m_size.y = y;
}

void Camera::ChangeObject(CObjectBase* object)
{
	m_object = object;
}

void Camera::WallException(int stage)
{
	switch (stage)
	{
	case 0:	// 타이틀
	{
		m_left = 300;
		m_top = 300;
		m_right = 900;
		m_bottom = 900;
	}
	break;
	case 1:	// 튜톨 카메라 설정 끝남.
	{
		m_left = 650;
		m_top = 400;
		m_right = 750;
		m_bottom = 500;
	}
	break;
	case 2: // 카메라 설정 끝남.
	{
		m_left = 700;
		m_top = 475;
		m_right = 3425;
		m_bottom = 2450;
	}
	break;
	case 3: // 카메라 설정 끝남. 
	{
		m_left = 767;
		m_top = 352;
		m_right = 1133;
		m_bottom = 2750;
	}
	break;
	case 4: // 카메라 설정 끝남.
	{
		m_left = 760;
		m_top = 350;
		m_right = 1480;
		m_bottom = 4150;
	}
	break;
	default:
		break;
	}
}
