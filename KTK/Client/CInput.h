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

	/// 키를 눌렀다 뗏을 때.
	bool Key_Up(unsigned char Key_Input);
	/// 키가 처음 눌러졌을 때.
	bool Key_Down(unsigned char Key_Input);
	/// 키를 누르고 있을 때.
	bool Key_Press(unsigned char Key_Input);
};