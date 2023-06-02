#include "CSprite.h"

CSprite::CSprite(int sheetidx, CVector2D sheetpos, int sheetwidth, int sheetheight, CVector2D pivot, float delaytime)
	:m_spriteSheetIdx(sheetidx), m_sheetPos(sheetpos), m_sheetWidth(sheetwidth), m_sheetHeight(sheetheight), m_sheetPivot(pivot), m_delayTime(delaytime)
{
}

CSprite::~CSprite()
{
}