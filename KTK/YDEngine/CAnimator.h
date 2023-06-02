#pragma once
/// <summary>
/// Animaton Clip을 재생시켜준다.
/// </summary>
class CAnimationClip;
class CArrowObject;

class CAnimator
{
public:
	CAnimator(CAnimationClip* animationclip);
	~CAnimator();
private:
	CAnimationClip* m_animationClip;

	// 현재 재생하고 있는 클립의 인덱스

	// 전체 클립의 수
	int m_totalFrameClip;
	
	// 로딩 타임
	float LoadingTime;
	
public:
	int m_currentIdx;
	CAnimationClip* GetAnimationClip()const { return m_animationClip; }
	void SetAnimationClip(CAnimationClip* animationclip);
	int GetCurrentIdx() const { return m_currentIdx; }
	int GetTotalFrameIdx() const { return m_totalFrameClip; }
	int Play();
	int LastPlay();
	int ArrowPlay(CArrowObject* object);
	void ResetLoadingTime();
	void ResetCurrentIdx() { m_currentIdx = 0; }
};