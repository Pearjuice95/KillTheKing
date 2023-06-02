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
	// 각 UI에 재생하기 위한 애니메이션 클립을 만든다.
	CAnimationClip* m_playerHpUI;		// 플레이어 체력관련 UI
	CAnimationClip* m_playerHpDieUI;		// 플레이어 대쉬관련 UI
	CAnimationClip* m_playerSuperUI;	// 플레이어 필살기 UI

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
	// 각 Effect를 재생하기 위한 애니메이션 클립을 만든다.
	// Player
	// 각 이펙트에는 플레이어 상태마다 재생되어야하는 이펙트가 들어간다.
	// 4방향이 들어가고 필살기는 필살기 시작 이펙트가 추가로 들어간다
	CAnimator* m_playerSuperUse;									// 플레이어 필살기 시작 이펙트
	std::vector <CAnimator*> m_playerAttackEffect;					// 플레이어 공격 이펙트
	std::vector <CAnimator*> m_playerSecondAttackEffect;			// 플레이어 찌르기 공격 이펙트
	std::vector <CAnimator*> m_playerSuperAttackEffect;				// 플레이어 필살기 공격 이펙트
	std::vector <CAnimator*> m_playerSuperSecondAttackEffect;		// 플레이어 필살기 찌르기 공격 이펙트
	std::vector <CAnimator*> m_playerSuperEffect;					// 플레이어 아이들 오라 이펙트 (검기)
	std::vector <CAnimator*> m_playerHitEffect;						// 플레이어 히트 이펙트


	std::vector <CAnimator*> m_playerDashEffect;					// 플레이어 대쉬 이펙트
	std::vector <CAnimator*> m_playerWalkEffect;					// 플레이어 걷는 이펙트
	std::vector <CAnimator*> m_playerSuperWalkEffect;				// 플레이어 필살기때 걷는 이펙트

	// Monster
	std::vector <CAnimationClip*> m_monsterHitEffect;					// 몬스터가 공격 당할때 나오는 이펙트
	std::vector <CAnimationClip*> m_monsterSuperHitEffect;				// 몬스터가 필살기 공격 당할때 나오는 이펙트

	// Close Monster 안쓰고 스프라이트로 하기로함 
	//std::vector <CAnimationClip*> m_monsterAttackEffect;					// 근접 몬스터가 공격할때 나오는 이펙트

	// Range Monster
	std::vector <CAnimationClip*> m_monsterArrowBoomEffect;				// 원거리 몬스터가 화살을 쏠때 나오는 이펙트

	// Boss
	std::vector <CAnimationClip*> m_BossJumpShadowEffect;				
	std::vector <CAnimationClip*> m_BossStompShadowEffect;				


public:
	// 상태가 바뀔때마다 리셋해야하는 애니메이터를 리셋해주는 함수
	void FrameResetEffect();
	// 플레이어 기본 공격(필살기X)
	void PlayerAttackEffect(CObjectBase* object, CVector2D cvector);
	void PlayerDashAttackEffect(CObjectBase* object, CVector2D cvector);

	void PlayerIDLEEffect(CObjectBase* object, CVector2D cvector);
	// 플레이어 필살기 시작 
	void PlayerSuperStartEffect(CObjectBase* object, CVector2D cvector);
	// 플레이어 필살기 공격
	void PlayerSuperAttackEffect(CObjectBase* object, CVector2D cvector);
	void PlayerSuperDashAttackEffect(CObjectBase* object, CVector2D cvector);
	// 플레이어 히트 이펙트
	void PlayerHitEffect(CObjectBase* object, CVector2D cvector);
	// 플레이어 대쉬 이팩트
	void PlayerDashEffect(CObjectBase* object, CVector2D cvector);
	// 플레이어 걷는 이펙트
	void PlayerWalkEffect(CObjectBase* object, CVector2D cvector);
	// 몬스터 맞는 이펙트
	void CloseHitEffect(CObjectBase* object, CObjectBase* monster, CVector2D cvector);
	void RangeHitEffect(CObjectBase* object, CObjectBase* monster, CVector2D cvector);
	void BossHitEffect(CObjectBase* object, CObjectBase* monster, CVector2D cvector);
	// 화살 이펙트
	void RangeArrowEffect(CArrowObject* object,CVector2D cvector);
	// 근접 몬스터 공격 이펙트
	//void MonsterAttackEffect(CObjectBase* object, CVector2D cvector);
	void BossShadowEffect(CObjectBase* object, CVector2D printfpos, CVector2D cvector);


	void UI();
};