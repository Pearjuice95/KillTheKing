#include "CAnimationClip.h"

CAnimationClip::CAnimationClip(std::vector<CSprite*> _clip, eMyStatus status)
	:m_animation(_clip), m_status(status), LoadingTime(0.f)
{
}

CAnimationClip::~CAnimationClip()
{
}

CSprite* CAnimationClip::GetFram(int idx)
{
	if (idx < 0)
		return m_animation[0];
	if(idx>=m_animation.size())
		return m_animation[m_animation.size() - 1];

	return m_animation[idx];
}

const eMyStatus CAnimationClip::GetAnimationStatus()
{
	return m_status;
}

int CAnimationClip::GetAnimationTotalFram()
{
	//static_cast는 형변환인데 에러를 안뜨게 함
	return static_cast<int>(m_animation.size());
}