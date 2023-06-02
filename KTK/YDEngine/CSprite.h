#pragma once
/// <summary>
/// 0205 Undefined
/// sprite�� ������ ������ ����
/// �� �������� �̹� �߶����ִ� ��������Ʈ ��Ʈ �ϳ��� �ǹ���
/// </summary>
#include "CVector2D.h"

class CSprite
{
public:
	CSprite(int sheetidx, CVector2D sheetpos, int sheetwidt, int sheetheight, CVector2D pivot, float delaytime);
	~CSprite();
public:
	//ū ��������Ʈ�� �ε����� ������ ����
	int m_spriteSheetIdx;
	//��������Ʈ�� �»�� ��ǥ
	CVector2D m_sheetPos;
	//��������Ʈ�� ���� ����
	int m_sheetWidth;
	//��������Ʈ�� ���� ����
	int m_sheetHeight;

	//��������Ʈ�� ��µ� �߽���
	CVector2D m_sheetPivot;
	//���� Ŭ������ �Ѿ�� �����ð�
	float m_delayTime;
	//������ ��������Ʈ���� �����ϰ� ����� Ű �÷��� �ʿ��Ҷ� �߰� �ϴ°ɷ�

};