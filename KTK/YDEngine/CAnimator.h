#pragma once
/// <summary>
/// Animaton Clip�� ��������ش�.
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

	// ���� ����ϰ� �ִ� Ŭ���� �ε���

	// ��ü Ŭ���� ��
	int m_totalFrameClip;
	
	// �ε� Ÿ��
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