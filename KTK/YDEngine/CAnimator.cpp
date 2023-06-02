#include "CAnimator.h"
#include "CAnimationClip.h"
#include "CSprite.h"
#include "Time.h"
#include "../Client/CArrowObject.h"
#include "Transform.h"
#include "CVector2D.h"
#include <string>
#include <iostream>
#include <windows.h>

CAnimator::CAnimator(CAnimationClip* animationclip)
	:m_animationClip(animationclip), m_currentIdx(0), m_totalFrameClip(animationclip->GetAnimationTotalFram())
{
}

CAnimator::~CAnimator()
{
}
void CAnimator::SetAnimationClip(CAnimationClip* animationclip)
{
	this->m_animationClip = animationclip;
	m_totalFrameClip = animationclip->GetAnimationTotalFram();
	this->LoadingTime = animationclip->LoadingTime;
}

int CAnimator::Play()
{
	LoadingTime += 0.01666666f; // Time::GetInstance()->Delta();

	if (LoadingTime >= m_animationClip->GetFram(m_currentIdx)->m_delayTime)
	{
		m_currentIdx = (m_currentIdx + 1) % m_totalFrameClip;
		LoadingTime = 0.f;
	}
	//OutputDebugString((std::to_string(Time::GetInstance()->Delta()) + "\n").c_str());
	//sprite∏¶ πŸ≤„¡‡æﬂ«—¥Ÿ.
	return m_currentIdx;
}

int CAnimator::LastPlay()
{
	LoadingTime += 0.01666666f; // Time::GetInstance()->Delta();

	if (LoadingTime >= m_animationClip->GetFram(m_currentIdx)->m_delayTime)
	{
		if (m_currentIdx == m_totalFrameClip)
			return m_currentIdx;
		m_currentIdx += 1;
		LoadingTime = 0.f;
	}
	//sprite∏¶ πŸ≤„¡‡æﬂ«—¥Ÿ.
	return m_currentIdx;
}


int CAnimator::ArrowPlay(CArrowObject* object)
{
	LoadingTime += 0.01666666f; // Time::GetInstance()->Delta();

	if (LoadingTime >= m_animationClip->GetFram(m_currentIdx)->m_delayTime)
	{
		if (m_currentIdx == m_totalFrameClip)
		{
			object->m_isBreak = false;
			return m_currentIdx;
		}
		m_currentIdx += 1;
		LoadingTime = 0.f;
	}
	//sprite∏¶ πŸ≤„¡‡æﬂ«—¥Ÿ.
	return m_currentIdx;
}

void CAnimator::ResetLoadingTime()
{
	LoadingTime = 0.f;
}