#pragma once
#include "enum.h"
#include "Transform.h"
#include <vector>
#include <map>
#include <d2d1.h>
#include <d2d1helper.h>

class CSprite;
class CAnimationClip;
class CAnimator;
class CVector2D;
class YDEngine;
class CObjectBase;
class CArrowObject;

class AnimationManager
{
private:
	AnimationManager();
	~AnimationManager();

public:
	//std::map<int,CAnimationClip*>* PlayerAnimClip;
	//std::map<int,CAnimationClip*>* CloseCombatAnimClip;

	std::vector<std::map<int, CAnimationClip*>> totalAnimClip;

	//std::map<int, CAnimationClip*> MonsterAnimClip;

public:
	static AnimationManager* GetInstance()
	{
		static AnimationManager instance;
		return &instance;
	}

public:
	YDEngine* m_pEngine;

	void Initialize(YDEngine* engine);
	void Update();
	void DrawSprite(CObjectBase* object, float opacity, CVector2D cvector);
	void SetStatus(CObjectBase* object);

	void LoadingSheet();

	void ObjectInit();
	void UIObjectInit();
	void EffectInit();

	CAnimationClip* GetAnimationClip(CObjectBase* object);

	std::vector<CSprite*> LoadSpriteFormData(int idx, int count, CVector2D firstsheetpos, float spacegap, int width, int height, CVector2D pivot, float delaytime);

	CVector2D GetSpriteHalfSize(CObjectBase* object);

	void OneFrameSprite(CSprite* sprite, Transform* transform, CVector2D cvector);

public:
	// �� UI�� ����ϱ� ���� �ִϸ��̼� Ŭ���� �����.
	CAnimationClip* m_playerHpUI;		// �÷��̾� ü�°��� UI
	CAnimationClip* m_playerHpDieUI;		// �÷��̾� �뽬���� UI
	CAnimationClip* m_playerSuperUI;	// �÷��̾� �ʻ�� UI

	CAnimationClip* m_introUI;
	CAnimationClip* m_endingUI;
	CAnimationClip* m_creditUI;

	CAnimator* m_playerHpAnim;
	CAnimator* m_playerHpDieAnim;
	CAnimator* m_playerSuperAnim;

	CAnimator* m_introAnim;
	CAnimator* m_endingAnim;
	CAnimator* m_creditAnim;



public:
	// �� Effect�� ����ϱ� ���� �ִϸ��̼� Ŭ���� �����.
	// Player
	// �� ����Ʈ���� �÷��̾� ���¸��� ����Ǿ���ϴ� ����Ʈ�� ����.
	// 4������ ���� �ʻ��� �ʻ�� ���� ����Ʈ�� �߰��� ����
	CAnimator* m_playerSuperUse;									// �÷��̾� �ʻ�� ���� ����Ʈ
	std::vector <CAnimator*> m_playerAttackEffect;					// �÷��̾� ���� ����Ʈ
	std::vector <CAnimator*> m_playerSecondAttackEffect;			// �÷��̾� ��� ���� ����Ʈ
	std::vector <CAnimator*> m_playerSuperAttackEffect;				// �÷��̾� �ʻ�� ���� ����Ʈ
	std::vector <CAnimator*> m_playerSuperSecondAttackEffect;		// �÷��̾� �ʻ�� ��� ���� ����Ʈ
	std::vector <CAnimator*> m_playerSuperEffect;					// �÷��̾� ���̵� ���� ����Ʈ (�˱�)
	std::vector <CAnimator*> m_playerHitEffect;						// �÷��̾� ��Ʈ ����Ʈ


	std::vector <CAnimator*> m_playerDashEffect;					// �÷��̾� �뽬 ����Ʈ
	std::vector <CAnimator*> m_playerWalkEffect;					// �÷��̾� �ȴ� ����Ʈ
	std::vector <CAnimator*> m_playerSuperWalkEffect;				// �÷��̾� �ʻ�⶧ �ȴ� ����Ʈ

	// Monster
	std::vector <CAnimationClip*> m_monsterHitEffect;					// ���Ͱ� ���� ���Ҷ� ������ ����Ʈ
	std::vector <CAnimationClip*> m_monsterSuperHitEffect;				// ���Ͱ� �ʻ�� ���� ���Ҷ� ������ ����Ʈ

	// Close Monster �Ⱦ��� ��������Ʈ�� �ϱ���� 
	//std::vector <CAnimationClip*> m_monsterAttackEffect;					// ���� ���Ͱ� �����Ҷ� ������ ����Ʈ

	// Range Monster
	std::vector <CAnimationClip*> m_monsterArrowBoomEffect;				// ���Ÿ� ���Ͱ� ȭ���� �� ������ ����Ʈ

	// Boss
	std::vector <CAnimationClip*> m_BossJumpShadowEffect;				
	std::vector <CAnimationClip*> m_BossStompShadowEffect;				


public:
	// ���°� �ٲ𶧸��� �����ؾ��ϴ� �ִϸ����͸� �������ִ� �Լ�
	void FrameResetEffect();
	// �÷��̾� �⺻ ����(�ʻ��X)
	void PlayerAttackEffect(CObjectBase* object, CVector2D cvector);
	void PlayerDashAttackEffect(CObjectBase* object, CVector2D cvector);

	void PlayerIDLEEffect(CObjectBase* object, CVector2D cvector);
	// �÷��̾� �ʻ�� ���� 
	void PlayerSuperStartEffect(CObjectBase* object, CVector2D cvector);
	// �÷��̾� �ʻ�� ����
	void PlayerSuperAttackEffect(CObjectBase* object, CVector2D cvector);
	void PlayerSuperDashAttackEffect(CObjectBase* object, CVector2D cvector);
	// �÷��̾� ��Ʈ ����Ʈ
	void PlayerHitEffect(CObjectBase* object, CVector2D cvector);
	// �÷��̾� �뽬 ����Ʈ
	void PlayerDashEffect(CObjectBase* object, CVector2D cvector);
	// �÷��̾� �ȴ� ����Ʈ
	void PlayerWalkEffect(CObjectBase* object, CVector2D cvector);
	// ���� �´� ����Ʈ
	void CloseHitEffect(CObjectBase* object, CObjectBase* monster, CVector2D cvector);
	void RangeHitEffect(CObjectBase* object, CObjectBase* monster, CVector2D cvector);
	void BossHitEffect(CObjectBase* object, CObjectBase* monster, CVector2D cvector);
	// ȭ�� ����Ʈ
	void RangeArrowEffect(CArrowObject* object,CVector2D cvector);
	// ���� ���� ���� ����Ʈ
	//void MonsterAttackEffect(CObjectBase* object, CVector2D cvector);
	void BossShadowEffect(CObjectBase* object, CVector2D printfpos, CVector2D cvector);


	void UI();
};