#pragma once
struct Key_Flag
{
	bool Key_Current_State = false;
	bool Key_Prev_State = false;
};

#include "CSingleton.h"

class CInput : public Singleton<CInput>
{
public:
	Key_Flag m_Key_Flag[256];
	CInput();
	~CInput();

	/// Ű�� ������ ���� ��.
	bool Key_Up(unsigned char Key_Input);
	/// Ű�� ó�� �������� ��.
	bool Key_Down(unsigned char Key_Input);
	/// Ű�� ������ ���� ��.
	bool Key_Press(unsigned char Key_Input);
};