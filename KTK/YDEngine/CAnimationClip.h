#pragma once
#include "enum.h"
#include <string>
#include <vector>

class CSprite;

/// <summary>
/// �ִϸ��̼��� �����. 
/// </summary>
class CAnimationClip
{
public:
	CAnimationClip(std::vector<CSprite*> clip,eMyStatus status);
	~CAnimationClip();

private:
	// sprite�� ���� ���ͷ� �ִϸ��̼��� ����
	std::vector<CSprite*> m_animation;
	// �� Animation�� �̸��� �־��ش�.
	//const std::string _AnimaitonName;
	const eMyStatus m_status;

public:
	// �ε����� �ش��ϴ� Sprite�� ��ȯ�Ѵ�.
	CSprite* GetFram(int idx);
	// �� �ִϸ��̼��� �̸��� ��ȯ�Ѵ�.
	const eMyStatus GetAnimationStatus();
	// �� �ִϸ��̼��� Ŭ���� ��������Ʈ �� ����� ��ȯ�Ѵ�.
	int GetAnimationTotalFram();
	float LoadingTime;
};