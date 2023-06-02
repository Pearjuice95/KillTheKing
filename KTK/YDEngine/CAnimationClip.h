#pragma once
#include "enum.h"
#include <string>
#include <vector>

class CSprite;

/// <summary>
/// 애니메이션을 만든다. 
/// </summary>
class CAnimationClip
{
public:
	CAnimationClip(std::vector<CSprite*> clip,eMyStatus status);
	~CAnimationClip();

private:
	// sprite를 담은 벡터로 애니메이션을 구성
	std::vector<CSprite*> m_animation;
	// 이 Animation의 이름을 넣어준다.
	//const std::string _AnimaitonName;
	const eMyStatus m_status;

public:
	// 인덱스에 해당하는 Sprite를 반환한다.
	CSprite* GetFram(int idx);
	// 이 애니메이션의 이름을 반환한다.
	const eMyStatus GetAnimationStatus();
	// 이 애니메이션의 클립의 스프라이트 총 장수를 반환한다.
	int GetAnimationTotalFram();
	float LoadingTime;
};