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
	std::vector<CObjectBase*> CloseObjectPool;	// ȣ���� ������Ʈ Ǯ
	std::vector<CObjectBase*> RangeObjectPool;	// ���ú� ������Ʈ Ǯ

	std::vector<CObjectBase*> WallObjectPool;

	std::vector<CObjectBase*> Stage00Pool;	
	std::vector<CObjectBase*> Stage01Pool;
	std::vector<CObjectBase*> Stage02Pool;
	std::vector<CObjectBase*> Stage03Pool;


	// �ݶ��̴� ���� ��� ����
	CColliderBase* m_ColliderBase;

	CVector2D m_simSize;					// �߽� �ݶ��̴� ������ 

	CVector2D m_playerAttackSize;			// �÷��̾� ���� �ݶ��̴� ������
	CVector2D m_playerSuperSize;			// �÷��̾� �ʻ�� ���� ���� �ݶ��̴� ������
	CVector2D m_playerDashAttackSize;		// �÷��̾� ��ð��� ������
	CVector2D m_playerSuperDashSize;		// �÷��̾� �ʻ�� ��ð��� ������
	CVector2D m_playerHitSize;				// �÷��̾� �ǰ� �ݶ��̴� ������
	CVector2D m_playerSuperKnockBackSize;	// �÷��̾� �ʻ�� �ߵ� ����

	CVector2D m_monsterAttackSize;			// ���� ���� �ݶ��̴� ������
	CVector2D m_monsterHitSize;				// ���� �ǰ� �ݶ��̴� ������
	CVector2D m_monsterRangeSize;			// ���� ���� �ݶ��̴� ������
	CVector2D m_monsterCenterSize;			// ���� ���� ������

	CVector2D m_wallSize;					// �� ������

	CVector2D m_BossHitBox;		// ��Ʈ�ڽ�
	CVector2D m_BossRangeBox;	// ���� ����
	CVector2D m_BossAttackBox;	// ���� �ڽ�
	CVector2D m_BossJumpAttackBox; // ���� ��� �ڽ�

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

	void CreateCloseMonster(); // ���͸� �����ϴ� �Լ�
	void CreateRangeMonster();

	void InitCloseMonster();
	void InitRangeMonster();
	//void SetStageObject(eScene scene);

	//void SetStage00Object();
	//void SetStage01Object();
	//void SetStage02Object();
	//void SetSgate03Object();

	void CreateWall(); // ���� �����ϴ� �Լ�

	//void PlayerToWallDistanceCheck(); // �÷��̾��� �뽬 �Ÿ���ŭ�� ���� �ִ��� üũ�ϰ� ó���ϴ� �Լ�
	void LineToWallCheck(std::vector<CObjectBase*> pool);

	// �ݶ��̴� ���� �Լ�
	void SetPlayerAttackColliderBox(); // �÷��̾� ���� RECT �ٲٱ�
	void SetPlayerHitColliderBox(); // �÷��̾� �ǰ� RECT �ٲٱ� 
	void SetPlayerSuperColliderBox(); // �ʻ�� ���� RECT

	void SetCloseCombatHitColliderTwoBox(int idx); // ������ �ǰݹڽ� RECT �ٲٱ�
	void SetRangerHitColliderTwoBox(int idx); // ���Ÿ� �ǰݹڽ� RECT �ٲٱ�
	void SetMonsterAttackDistanceCollider(int idx); // ������ ���� ������ RECT �ٲٱ�
	void SetMonsterAttackStatus(int idx); // ���� ���� ���·� ����
	void SetMonstaerAttackColliderBox(int idx); // ���� ���ݹڽ� RECT �ٲٱ�
	void SetMonsterCenter_1Box(int idx); // ���� �߽� �ݶ��̴� RECT �ٲٱ�
	void SetMonsterCenter_2Box(int idx); // ���� �߽� �ݶ��̴� RECT �ٲٱ�

	void SetWallColliderBox(int idx); // �� �ݶ��̴� RECT �ٲٱ�

	void SetBossRangeBox();

	void ColliderCheck(); // ��� �ݶ��̴��� üũ��

	//void SimColliderCheck();				// �÷��̾�� ������ sim(�߽�) �ݶ��̴��� üũ�ϰ� ��ġ�� �ʰ���
	void PlayerAttackColliderCheck(); // �÷��̾ �����Ҷ� üũ�ϴ� �Լ�

	void MonsterAttackDistanceCheck(); // ���� ���� �Ÿ� üũ
	void MonsterAttackColliderCheck(); // ���� ���� �ڽ� üũ
	void MonsterCenterCheck(); // ���ͳ��� �߽��� üũ��
	void WallColliderCheck(std::vector<CObjectBase*> pool); // ��� ������Ʈ�� ���� �꿴���� üũ�ϰ� �� ���������� ������ �Լ�



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