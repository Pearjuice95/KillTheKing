#pragma once
#include <d2d1.h>
#include <d2d1helper.h>
#include "CVector2D.h"
#include "SceneBase.h"
#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneManager.h"
#include <vector>

class CObjectBase;
class CPlayerObject;
class YDEngine;
class CColliderBase;
class CBossObject;
class CBackGroundObject;
class CRangeObject;
class CCloseObject;

class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager();

public:
	CPlayerObject* player;
	CBossObject* boss;
	CBackGroundObject* backGround;

	static CObjectManager* GetInstance()
	{
		static CObjectManager instance;
		return &instance;
	}
public:
	std::vector<CObjectBase*> CloseObjectPool;	// 호위병 오브젝트 풀
	std::vector<CObjectBase*> RangeObjectPool;	// 석궁병 오브젝트 풀

	std::vector<CObjectBase*> WallObjectPool;

	std::vector<CObjectBase*> Stage00Pool;	
	std::vector<CObjectBase*> Stage01Pool;
	std::vector<CObjectBase*> Stage02Pool;
	std::vector<CObjectBase*> Stage03Pool;


	// 콜라이더 관련 멤버 변수
	CColliderBase* m_ColliderBase;

	CVector2D m_simSize;					// 중심 콜라이더 사이즈 

	CVector2D m_playerAttackSize;			// 플레이어 공격 콜라이더 사이즈
	CVector2D m_playerSuperSize;			// 플레이어 필살기 공격 범위 콜라이더 사이즈
	CVector2D m_playerDashAttackSize;		// 플레이어 대시공격 사이즈
	CVector2D m_playerSuperDashSize;		// 플레이어 필살기 대시공격 사이즈
	CVector2D m_playerHitSize;				// 플레이어 피격 콜라이더 사이즈
	CVector2D m_playerSuperKnockBackSize;	// 플레이어 필살기 발동 범위

	CVector2D m_monsterAttackSize;			// 몬스터 공격 콜라이더 사이즈
	CVector2D m_monsterHitSize;				// 몬스터 피격 콜라이더 사이즈
	CVector2D m_monsterRangeSize;			// 몬스터 범위 콜라이더 사이즈
	CVector2D m_monsterCenterSize;			// 몬스터 센터 사이즈

	CVector2D m_wallSize;					// 벽 사이즈

	CVector2D m_BossHitBox;		// 히트박스
	CVector2D m_BossRangeBox;	// 패턴 범위
	CVector2D m_BossAttackBox;	// 공격 박스
	CVector2D m_BossJumpAttackBox; // 점프 찍기 박스

	RECT collider_1;
	RECT collider_2;
	RECT playerCollider;
	RECT bossCollider;

private:
	YDEngine* m_pEngine;

public:
	void Initialize();
	void Update(bool isdebug);
	void Render(CVector2D cvector);

	void CreateCloseMonster(); // 몬스터를 생성하는 함수
	void CreateRangeMonster();

	void InitCloseMonster();
	void InitRangeMonster();
	//void SetStageObject(eScene scene);

	//void SetStage00Object();
	//void SetStage01Object();
	//void SetStage02Object();
	//void SetSgate03Object();

	void CreateWall(); // 벽을 생성하는 함수

	//void PlayerToWallDistanceCheck(); // 플레이어의 대쉬 거리만큼에 벽이 있는지 체크하고 처리하는 함수
	void LineToWallCheck(std::vector<CObjectBase*> pool);

	// 콜라이더 관련 함수
	void SetPlayerAttackColliderBox(); // 플레이어 공격 RECT 바꾸기
	void SetPlayerHitColliderBox(); // 플레이어 피격 RECT 바꾸기 
	void SetPlayerSuperColliderBox(); // 필살기 범위 RECT

	void SetCloseCombatHitColliderTwoBox(int idx); // 근접병 피격박스 RECT 바꾸기
	void SetRangerHitColliderTwoBox(int idx); // 원거리 피격박스 RECT 바꾸기
	void SetMonsterAttackDistanceCollider(int idx); // 몬스터의 공격 범위로 RECT 바꾸기
	void SetMonsterAttackStatus(int idx); // 몬스터 공격 상태로 변경
	void SetMonstaerAttackColliderBox(int idx); // 몬스터 공격박스 RECT 바꾸기
	void SetMonsterCenter_1Box(int idx); // 몬스터 중심 콜라이더 RECT 바꾸기
	void SetMonsterCenter_2Box(int idx); // 몬스터 중심 콜라이더 RECT 바꾸기

	void SetWallColliderBox(int idx); // 벽 콜라이더 RECT 바꾸기

	void SetBossRangeBox();

	void ColliderCheck(); // 모든 콜라이더를 체크함

	//void SimColliderCheck();				// 플레이어와 몬스터의 sim(중심) 콜라이더를 체크하고 곂치지 않게함
	void PlayerAttackColliderCheck(); // 플레이어가 공격할때 체크하는 함수

	void MonsterAttackDistanceCheck(); // 몬스터 공격 거리 체크
	void MonsterAttackColliderCheck(); // 몬스터 공격 박스 체크
	void MonsterCenterCheck(); // 몬스터끼리 중심을 체크함
	void WallColliderCheck(std::vector<CObjectBase*> pool); // 모든 오브젝트가 벽에 닿였는지 체크하고 전 프레임으로 돌리는 함수



	float ReturnRandom(int max);
	void SetMonsterSpeed();

	void KnockBack(CObjectBase* object);
	void SuperKnockBack(int idx);

	void BossCheckPlayerBox();
	void SetBossJumpBox();
	void SetBossAttackBox();
	void SetBossHitBox();

	void BossJumpPattern();
	void BossAttackPattern();

	void ArrowCollideCheck();

	void DealDamage();

	void HitBossCheck();

	void BossPlayerDashCheck();

public:
	bool isDebugMode;

private:
	int m_loadingTime;
	int m_curTime;
};