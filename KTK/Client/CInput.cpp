#include "CInput.h"
#include <windows.h>

CInput::CInput()
{

}

CInput::~CInput()
{

}

bool CInput::Key_Up(unsigned char Key_Input)
{
	/// ���� �Էµ� Ű�� �������� ���� �������·� �÷��׹ٲ�..
	if (GetAsyncKeyState(Key_Input))
	{
		m_Key_Flag[Key_Input].Key_Current_State = true;
	}

	else
	{
		m_Key_Flag[Key_Input].Key_Current_State = false;
	}

	/// �������� ���ȴ� ���°� �̹��� Ű�� �������� ( Ű�� ���� �� )
	if (m_Key_Flag[Key_Input].Key_Current_State == false &&
		m_Key_Flag[Key_Input].Key_Prev_State == true)
	{
		m_Key_Flag[Key_Input].Key_Prev_State = m_Key_Flag[Key_Input].Key_Current_State;
		return true;
	}

	/// �������� ����.
	m_Key_Flag[Key_Input].Key_Prev_State = m_Key_Flag[Key_Input].Key_Current_State;
	return false;
}

bool CInput::Key_Down(unsigned char Key_Input)
{
	/// ���� �Էµ� Ű�� �������� ���� �������·� �÷��׹ٲ�..
	if (GetAsyncKeyState(Key_Input))
	{
		m_Key_Flag[Key_Input].Key_Current_State = true;
	}

	else
	{
		m_Key_Flag[Key_Input].Key_Current_State = false;
	}

	/// ���� �̹��� ���Ȱ� �������� �������ʾ����� ( Ű�� ������ �� )
	if (m_Key_Flag[Key_Input].Key_Current_State == true &&
		m_Key_Flag[Key_Input].Key_Prev_State == false)
	{
		m_Key_Flag[Key_Input].Key_Prev_State = m_Key_Flag[Key_Input].Key_Current_State;
		return true;
	}

	/// �������� ����.
	m_Key_Flag[Key_Input].Key_Prev_State = m_Key_Flag[Key_Input].Key_Current_State;
	return false;
}

bool CInput::Key_Press(unsigned char Key_Input)
{
	if (GetAsyncKeyState(Key_Input))
	{
		return true;
	}

	return false;
}