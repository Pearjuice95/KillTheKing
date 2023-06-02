#pragma once
/// <summary>
/// 0205 Undefined
/// sprite의 정보를 가지고 있음
/// 이 정보에는 이미 잘라져있는 스프라이트 시트 하나를 의미함
/// </summary>
#include "CVector2D.h"

class CSprite
{
public:
	CSprite(int sheetidx, CVector2D sheetpos, int sheetwidt, int sheetheight, CVector2D pivot, float delaytime);
	~CSprite();
public:
	//큰 스프라이트의 인덱스를 가지고 있음
	int m_spriteSheetIdx;
	//스프라이트의 좌상단 좌표
	CVector2D m_sheetPos;
	//스프라이트의 가로 길이
	int m_sheetWidth;
	//스프라이트의 세로 길이
	int m_sheetHeight;

	//스프라이트가 출력될 중심점
	CVector2D m_sheetPivot;
	//다음 클립으로 넘어가는 지연시간
	float m_delayTime;
	//투명도랑 스프라이트에서 제외하고 출력할 키 컬러는 필요할때 추가 하는걸로

};