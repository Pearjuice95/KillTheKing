#include "CTitle.h"
#include "CInput.h"
#include "CPlayerObject.h"
#include "Sound.h"

CTitle::CTitle()
{

}

CTitle::~CTitle()
{

}

void CTitle::Initialize()
{
	GameStart = false;
	EXit = false;
	CPlayerObject::GetInstance()->m_canControl = false;
	CPlayerObject::GetInstance()->m_isCollide = false;
}

bool CTitle::Update()
{
	if (GameStart)
		return false;
	if (CInput::GetInstance()->Key_Down(VK_SPACE))
	{
		GameStart = true;
		return false;
	}
	return true;
}

void CTitle::SetObject(CVector2D playerpos)
{
	// ���⼭ ī�޶� Set���ּ���.
	// �÷��̾� ��ǥ�� �°� �ٲ��ش�.
	CPlayerObject::GetInstance()->m_pos = playerpos;
}

void CTitle::Render()
{

}

void CTitle::Finalize()
{

}
