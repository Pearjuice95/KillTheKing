#include "CObjectManager.h"
#include "CPlayerObject.h"
#include "CCloseObject.h"
#include "AnimationManager.h"
#include "CAnimator.h"
#include "YDEngine.h"
#include "CColliderBase.h"
#include "CWallObject.h"
#include "Transform.h"
#include "CBossObject.h"
#include "CRangeObject.h"
#include "SceneManager.h"
#include "Sound.h"
#include "CBackGroundObject.h"
#include <random>
#include <vector>

CObjectManager::CObjectManager()
	:m_curTime(0), m_loadingTime(60)
{
	m_playerAttackSize.x = 100; m_playerAttackSize.y = 150;
	m_playerSuperSize.x = 200; m_playerSuperSize.y = 300;
	m_playerSuperDashSize.x = 300; m_playerSuperDashSize.y = 80;
	m_playerDashAttackSize.x = 150; m_playerDashAttackSize.y = 40;
	m_monsterCenterSize.x = 30; m_monsterCenterSize.y = 15;
	m_wallSize.x = 51; m_wallSize.y = 37;
	m_playerHitSize.x = 34; m_playerHitSize.y = 42;
	m_playerSuperKnockBackSize.x = 400; m_playerSuperKnockBackSize.y = 400;
	m_BossRangeBox.x = 100; m_BossRangeBox.y = 100;
	m_BossHitBox.x = 80; m_BossHitBox.y = 90;
	m_BossJumpAttackBox.x = 150; m_BossJumpAttackBox.y = 100;
	m_BossAttackBox.x = 150; m_BossAttackBox.y = 150;
}

CObjectManager::~CObjectManager()
{
}

void CObjectManager::Initialize()
{
	isDebugMode = false;
	m_pEngine = AnimationManager::GetInstance()->m_pEngine;
	player = CPlayerObject::GetInstance();
	player->m_animator = new CAnimator(AnimationManager::GetInstance()->GetAnimationClip(player));
	player->Initialize();
	boss = CBossObject::GetInsance();
	boss->m_animator = new CAnimator(AnimationManager::GetInstance()->GetAnimationClip(boss));
	//boss->Initialize();

	backGround = CBackGroundObject::GetInstance();
	backGround->InitMap();

	CreateCloseMonster();
	CreateRangeMonster();

	//for (int i = 0; i < CloseObjectPool.size(); i++)
	//{
	//	CObjectBase* _object = CloseObjectPool[i];
	//	_object->Initialize();
	//}

	//for (int i = 0; i < RangeObjectPool.size(); i++)
	//{
	//	CObjectBase* _object = RangeObjectPool[i];
	//	_object->Initialize();
	//}

	m_ColliderBase = new CColliderBase();

	CreateWall();

	for (int i = 0; i < WallObjectPool.size(); i++)
	{
		CObjectBase* _object = WallObjectPool[i];
		_object->Initialize();
	}
}

void CObjectManager::Update(bool isdebug)
{
	isDebugMode = isdebug;
	player->Update();
	//boss->Update();
	backGround->DrawBackGround();

	switch (SceneManager::GetInstance()->m_sceneNumber)
	{
	case 1:
		LineToWallCheck(Stage00Pool);
		break;

	case 2:
		LineToWallCheck(Stage01Pool);
		break;

	case 3:
		LineToWallCheck(Stage02Pool);
		break;

	case 4:
		LineToWallCheck(Stage03Pool);
		break;

	default:
		break;
	}


	SetMonsterSpeed();
	if (player->m_isCollide == false)
	{
		for (int i = 0; i < CloseObjectPool.size(); i++)
		{
			CObjectBase* _object = CloseObjectPool[i];
			if (_object->m_isRender)
				_object->m_status = eMyStatus::IDLELEFT;
		}

		for (int i = 0; i < RangeObjectPool.size(); i++)
		{
			CObjectBase* _object = RangeObjectPool[i];
			if (_object->m_isRender)
				_object->m_status = eMyStatus::IDLELEFT;
		}
	}

	else
	{
		for (int i = 0; i < CloseObjectPool.size(); i++)
		{
			CObjectBase* _object = CloseObjectPool[i];
			if (_object->m_isRender)
				_object->Update();
		}

		for (int i = 0; i < RangeObjectPool.size(); i++)
		{
			CObjectBase* _object = RangeObjectPool[i];
			if (_object->m_isRender)
				_object->Update();
		}

		ColliderCheck();
	}


	if (player->m_totalStatus == eToTalStatus::DASH)
		player->m_pos = player->m_DashPos;

	DealDamage();

}

void CObjectManager::Render(CVector2D cvector)
{
	backGround->Render(cvector);

	//for (int i = 0; i < WallObjectPool.size(); i++)
	//{
	//	CObjectBase* _object = WallObjectPool[i];
	//	_object->Render(cvector);
	//}

	for (int i = 0; i < CloseObjectPool.size(); i++)
	{
		CObjectBase* _object = CloseObjectPool[i];
		if (_object->m_isRender)
			_object->Render(cvector);
	}

	for (int i = 0; i < RangeObjectPool.size(); i++)
	{
		CObjectBase* _object = RangeObjectPool[i];
		if (_object->m_isRender)
			_object->Render(cvector);
	}

	//boss->Render(cvector);

	player->Render(cvector);
	AnimationManager::GetInstance()->PlayerAttackEffect(player, cvector);
	AnimationManager::GetInstance()->PlayerDashAttackEffect(player, cvector);
	AnimationManager::GetInstance()->PlayerSuperAttackEffect(player, cvector);
	AnimationManager::GetInstance()->PlayerSuperDashAttackEffect(player, cvector);
	AnimationManager::GetInstance()->PlayerDashEffect(player, cvector); // super의 상태임을 확인해야 한다. (추가로 idle일때도 처리해줘야 한다.)
	AnimationManager::GetInstance()->PlayerWalkEffect(player, cvector);
	AnimationManager::GetInstance()->PlayerHitEffect(player, cvector);
	AnimationManager::GetInstance()->PlayerIDLEEffect(player, cvector);
	for (int i = 0; i < CloseObjectPool.size(); i++)
	{
		AnimationManager::GetInstance()->CloseHitEffect(player, CloseObjectPool[i], cvector);
		//AnimationManager::GetInsance()->MonsterAttackEffect(CloseObjectPool[i], cvector);
	}
	for (int i = 0; i < RangeObjectPool.size(); i++)
	{
		AnimationManager::GetInstance()->RangeHitEffect(player, RangeObjectPool[i], cvector);
		CRangeObject* object = dynamic_cast<CRangeObject*>(RangeObjectPool[i]);
		for (int j = 0; j < object->arrowpool.size(); j++)
			AnimationManager::GetInstance()->RangeArrowEffect(object->arrowpool[j], cvector);
	}
	AnimationManager::GetInstance()->BossHitEffect(CPlayerObject::GetInstance(), CBossObject::GetInsance(), cvector);

	if (isDebugMode)
	{
		switch (SceneManager::GetInstance()->m_sceneNumber)
		{
		case 1:
		{
			for (int i = 0; i < Stage00Pool.size(); i++)
				m_pEngine->DrawRect(Stage00Pool[i]->GetRECT(), 255, 0, 0);
		}
		break;
		case 2:
		{
			for (int i = 0; i < Stage01Pool.size(); i++)
				m_pEngine->DrawRect(Stage01Pool[i]->GetRECT(), 255, 0, 0);
		}
		break;
		case 3:
		{
			for (int i = 0; i < Stage02Pool.size(); i++)
				m_pEngine->DrawRect(Stage02Pool[i]->GetRECT(), 255, 0, 0);
		}
		break;
		case 4:
		{
			for (int i = 0; i < Stage03Pool.size(); i++)
				m_pEngine->DrawRect(Stage03Pool[i]->GetRECT(), 255, 0, 0);
		}
		break;
		default:
			break;
		}
	}
}

void CObjectManager::CreateCloseMonster()
{
	CCloseObject* combat;
	/*for (int i = 0; i < 15; i++)
	{
		combat = new CCloseObject(CVector2D(player->m_pos.x - 500 + (i * 50), player->m_pos.y - 500));
		combat->m_animator = new CAnimator(AnimationManager::GetInsance()->GetAnimationClip(combat));
		CloseObjectPool.push_back(combat);
	}
	for (int i = 0; i < 15; i++)
	{
		combat = new CCloseObject(CVector2D(player->m_pos.x + 500 + (i * 50), player->m_pos.y + 500));
		combat->m_animator = new CAnimator(AnimationManager::GetInsance()->GetAnimationClip(combat));
		CloseObjectPool.push_back(combat);
	}
	for (int i = 0; i < 1; i++)
	{
		combat = new CCloseObject(CVector2D(player->m_pos.x - 500, player->m_pos.y + 500 + (i * 50)));
		combat->m_animator = new CAnimator(AnimationManager::GetInsance()->GetAnimationClip(combat));
		CloseObjectPool.push_back(combat);
	}
	for (int i = 0; i < 5; i++)
	{
		combat = new CCloseObject(CVector2D(player->m_pos.x + 500 + (i * 50), player->m_pos.y + 500));
		combat->m_animator = new CAnimator(AnimationManager::GetInsance()->GetAnimationClip(combat));
		CloseObjectPool.push_back(combat);
	}
	for (int i = 0; i < 5; i++)
	{
		combat = new CCloseObject(CVector2D(player->m_pos.x - 500, player->m_pos.y + 500 + (i * 50)));
		combat->m_animator = new CAnimator(AnimationManager::GetInsance()->GetAnimationClip(combat));
		CloseObjectPool.push_back(combat);
	}*/
	//for (int i = 0; i < 1; i++)
	//{
	//	combat = new CCloseObject(CVector2D(player->m_pos.x + 500, player->m_pos.y + 500 + (i * 50)));
	//	combat->m_animator = new CAnimator(AnimationManager::GetInstance()->GetAnimationClip(combat));
	//	CloseObjectPool.push_back(combat);
	//}
}


void CObjectManager::CreateRangeMonster()
{
	CRangeObject* range;

	//for (int i = 0; i < 1; i++)
	//{
	//	range = new CRangeObject(CVector2D(100, 100));
	//	range->m_sprite = m_pEngine->LoadSpriteFromData(11, CVector2D(0, 400), 199, 99, CVector2D(-0.8f, 0.f), 0.3f);
	//	range->m_animator = new CAnimator(AnimationManager::GetInstance()->GetAnimationClip(range));
	//	RangeObjectPool.push_back(range);
	//}
}

void CObjectManager::InitCloseMonster()
{
	for (int i = 0; i < CloseObjectPool.size(); i++)
	{
		CObjectBase* _object = CloseObjectPool[i];
		_object->Initialize();
	}
}

void CObjectManager::InitRangeMonster()
{
	for (int i = 0; i < RangeObjectPool.size(); i++)
	{
		CObjectBase* _object = RangeObjectPool[i];
		_object->Initialize();
	}
}

//void CObjectManager::SetStageObject(eScene scene)
//{
//	switch (scene)
//	{
//	case eScene::TITLE:
//	{
//		
//	}
//		break;
//	case eScene::STAGE00:
//	{
//		SetStage00Object();
//	}
//		break;
//	case eScene::STAGE01:
//	{
//		SetStage01Object();
//	}
//		break;
//	case eScene::STAGE02:
//	{
//		SetStage02Object();
//	}
//		break;
//	case eScene::STAGE03:
//	{
//		SetSgate03Object();
//	}
//		break;
//	case eScene::ENDING:
//	{
//
//	}
//		break;
//	default:
//		break;
//	}
//}
//
//void CObjectManager::SetStage00Object()
//{
//
//}
//
//void CObjectManager::SetStage01Object()
//{
//	// if (무슨카운트 > ~~)
//	for (int i = 0; i < 4; i++)
//	{
//		CloseObjectPool[i]->m_isAlive = true;
//		CloseObjectPool[i]->m_pos = CVector2D(-50, 200 + (10 * i));
//	}
//
//	for (int i = 4; i < 8; i++)
//	{
//		CloseObjectPool[i]->m_isAlive = true;
//		CloseObjectPool[i]->m_pos = CVector2D(200, -50 + (10 * i));
//	}
//
//	for (int i = 8; i < 12; i++)
//	{
//		CloseObjectPool[i]->m_isAlive = true;
//		CloseObjectPool[i]->m_pos = CVector2D(100, 100 + (10 * i));
//	}
//
//
//}
//
//void CObjectManager::SetStage02Object()
//{
//
//}
//
//void CObjectManager::SetSgate03Object()
//{
//
//}

void CObjectManager::CreateWall()
{
	for (int i = 0; i < CBackGroundObject::GetInstance()->m_stage00V.size(); i++)
	{
		Stage00Pool.push_back(CBackGroundObject::GetInstance()->m_stage00V[i]);
	}

	for (int i = 0; i < CBackGroundObject::GetInstance()->m_stage01V.size(); i++)
	{
		Stage01Pool.push_back(CBackGroundObject::GetInstance()->m_stage01V[i]);
	}

	for (int i = 0; i < CBackGroundObject::GetInstance()->m_stage02V.size(); i++)
	{
		Stage02Pool.push_back(CBackGroundObject::GetInstance()->m_stage02V[i]);
	}

	for (int i = 0; i < CBackGroundObject::GetInstance()->m_stage03V.size(); i++)
	{
		Stage03Pool.push_back(CBackGroundObject::GetInstance()->m_stage03V[i]);
	}
}

// 콜라이더 체크를 함
void CObjectManager::ColliderCheck()
{
	//MonsterCenterCheck();
	PlayerAttackColliderCheck();
	MonsterAttackDistanceCheck();

	switch (SceneManager::GetInstance()->m_sceneNumber)
	{
	case 1:
		WallColliderCheck(Stage00Pool);
		break;

	case 2:
		WallColliderCheck(Stage01Pool);
		break;

	case 3:
		WallColliderCheck(Stage02Pool);
		break;

	case 4:
	{
		WallColliderCheck(Stage03Pool);
		BossPlayerDashCheck();
	}
	break;

	default:
		break;
	}

	ArrowCollideCheck();
	BossCheckPlayerBox();
	HitBossCheck();

	if (boss->m_isPattern)
	{
		BossJumpPattern();
		BossAttackPattern();
	}
}

// 플레이어의 타격박스와 몬스터의 피격 박스를 체크하는 함수
void CObjectManager::PlayerAttackColliderCheck()
{
	//if (CObjectManager::GetInsance()->isDebugMode)
	//{
	//	RECT playerpos;
	//	playerpos.left = player->m_pos.x;
	//	playerpos.top = player->m_pos.y;
	//	playerpos.right = player->m_pos.x + 80;
	//	playerpos.bottom = player->m_pos.y + 80;
	//	RECT playertransform;
	//	playertransform.left = player->m_transform->GetLocalPosition().x;
	//	playertransform.top = player->m_transform->GetLocalPosition().y;
	//	playertransform.right = player->m_transform->GetLocalPosition().x + 80;
	//	playertransform.bottom = player->m_transform->GetLocalPosition().y + 80;

	//	m_pEngine->DrawRect(playerpos, 255, 0, 0);
	//	m_pEngine->DrawRect(playertransform, 0, 0, 0);
	//}
	if (player->m_isCollide)
	{
		if (player->m_status == eMyStatus::ATTACKUP || player->m_status == eMyStatus::ATTACKDOWN || player->m_status == eMyStatus::ATTACKRIGHT || player->m_status == eMyStatus::ATTACKLEFT ||
			player->m_status == eMyStatus::DASHATTACKUP || player->m_status == eMyStatus::DASHATTACKDOWN || player->m_status == eMyStatus::DASHATTACKRIGHT || player->m_status == eMyStatus::DASHATTACKLEFT ||
			player->m_status == eMyStatus::SATTACKUP || player->m_status == eMyStatus::SATTACKDOWN || player->m_status == eMyStatus::SATTACKRIGHT || player->m_status == eMyStatus::SATTACKLEFT ||
			player->m_status == eMyStatus::SDASHATTACKUP || player->m_status == eMyStatus::SDASHATTACKDOWN || player->m_status == eMyStatus::SDASHATTACKRIGHT || player->m_status == eMyStatus::SDASHATTACKLEFT
			)
		{
			SetPlayerAttackColliderBox();
			if (CObjectManager::GetInstance()->isDebugMode)
			{
				m_pEngine->DrawRect(collider_1, 0, 255, 0);
			}
			for (int i = 0; i < CloseObjectPool.size(); i++)
			{
				if (CloseObjectPool[i]->m_status != eMyStatus::HITRIGHT && CloseObjectPool[i]->m_status != eMyStatus::HITLEFT)
				{
					if (CloseObjectPool[i]->m_isCollide)
					{
						if (player->m_pos.x - 200 < CloseObjectPool[i]->m_pos.x && CloseObjectPool[i]->m_pos.x < player->m_pos.x + 200 &&
							player->m_pos.y - 200 < CloseObjectPool[i]->m_pos.y && CloseObjectPool[i]->m_pos.y < player->m_pos.y + 200)
						{
							SetCloseCombatHitColliderTwoBox(i);
							if (m_ColliderBase->BoxColliderCheck(&collider_1, &collider_2))
							{
								//CloseObjectPool[i]->HPDown(player->m_dmg);
								CloseObjectPool[i]->HPDown(0);
								KnockBack(CloseObjectPool[i]);
								player->PlusSuper();
								if (player->m_isDmg == false)
								{
									player->m_isDmg = true;
									SoundPlay(16);
								}
								// 넉백추가해라
							}
						}
					}
				}
			}
		}



		for (int i = 0; i < RangeObjectPool.size(); i++)
		{
			if (RangeObjectPool[i]->m_status != eMyStatus::HITRIGHT && RangeObjectPool[i]->m_status != eMyStatus::HITLEFT)
			{
				if (RangeObjectPool[i]->m_isCollide)
				{
					if (player->m_pos.x - 200 < RangeObjectPool[i]->m_pos.x && RangeObjectPool[i]->m_pos.x < player->m_pos.x + 200 &&
						player->m_pos.y - 200 < RangeObjectPool[i]->m_pos.y && RangeObjectPool[i]->m_pos.y < player->m_pos.y + 200)
					{
						SetRangerHitColliderTwoBox(i);
						if (m_ColliderBase->BoxColliderCheck(&collider_1, &collider_2))
						{
							//CloseObjectPool[i]->HPDown(player->m_dmg);
							RangeObjectPool[i]->HPDown(0);
							KnockBack(RangeObjectPool[i]);
							player->PlusSuper();
							if (player->m_isDmg == false)
							{
								player->m_isDmg = true;
								SoundPlay(16);
							}
							// 넉백추가해라
						}
					}
				}
			}
		}
	}
}


void CObjectManager::MonsterAttackColliderCheck()
{
	if (player->m_isCollide)
	{
		SetPlayerHitColliderBox();
		for (int i = 0; i < CloseObjectPool.size(); i++)
		{
			if (CloseObjectPool[i]->m_totalStatus != eToTalStatus::HIT && CloseObjectPool[i]->m_totalStatus != eToTalStatus::DIE && CloseObjectPool[i]->m_totalStatus != eToTalStatus::ATTACK)
			{
				if (player->m_pos.x - 200 < CloseObjectPool[i]->m_pos.x && CloseObjectPool[i]->m_pos.x < player->m_pos.x + 200 &&
					player->m_pos.y - 200 < CloseObjectPool[i]->m_pos.y && CloseObjectPool[i]->m_pos.y < player->m_pos.y + 200)
				{
					SetMonsterAttackDistanceCollider(i);
					if (m_ColliderBase->BoxColliderCheck(&playerCollider, &collider_2))
					{
						SetMonsterAttackStatus(i);
					}

					//else
					//{
					//	ObjectPool[i]->m_status = ObjectPool[i]->m_prevStatus;
					//}
				}
			}
		}
	}
}

void CObjectManager::MonsterCenterCheck()
{

	for (int i = 0; i < CloseObjectPool.size(); i++)
	{
		if (CloseObjectPool[i]->m_isCollide)
		{
			SetMonsterCenter_1Box(i);
			if (CObjectManager::GetInstance()->isDebugMode)
			{
				RECT playerrect;
				playerrect.left = CloseObjectPool[i]->m_pos.x - 30;
				playerrect.top = CloseObjectPool[i]->m_pos.y - 30;
				playerrect.right = CloseObjectPool[i]->m_pos.x + 30;
				playerrect.bottom = CloseObjectPool[i]->m_pos.y + 30;
				m_pEngine->DrawRect(collider_1, 0, 0, 255);
			}
			for (int j = i + 1; j < CloseObjectPool.size(); j++)
			{
				if (CloseObjectPool[j]->m_isCollide)
				{
					SetMonsterCenter_2Box(j);
					if (CObjectManager::GetInstance()->isDebugMode)
					{
						RECT recttemp;
						recttemp.left = CloseObjectPool[j]->m_pos.x - 30;
						recttemp.top = CloseObjectPool[j]->m_pos.y - 30;
						recttemp.right = CloseObjectPool[j]->m_pos.x + 30;
						recttemp.bottom = CloseObjectPool[j]->m_pos.y + 30;
						m_pEngine->DrawRect(collider_2, 0, 0, 255);
					}
					if (m_ColliderBase->BoxColliderCheck(&collider_1, &collider_2))
					{
						m_ColliderBase->PushCollisionBox(CloseObjectPool[i], CloseObjectPool[j], m_monsterCenterSize);
					}
				}
			}
		}
	}
}

void CObjectManager::WallColliderCheck(std::vector<CObjectBase*> pool)
{
	SetPlayerHitColliderBox();
	for (int i = 0; i < pool.size(); i++)
	{
		RECT rect;
		rect = pool[i]->GetRECT();

		if (m_ColliderBase->BoxColliderCheck(&playerCollider, &rect))
		{
			m_ColliderBase->WallCollision(pool[i], player, m_playerHitSize);
		}
	}

	SetBossHitBox();
	if (CObjectManager::GetInstance()->isDebugMode)
	{
		m_pEngine->DrawRect(bossCollider, 0, 0, 255);
	}

	if (m_ColliderBase->BoxColliderCheck(&playerCollider, &bossCollider))
	{
		m_ColliderBase->WallCollision(boss, player, m_playerHitSize);
	}



	for (int i = 0; i < CloseObjectPool.size(); i++)
	{
		SetCloseCombatHitColliderTwoBox(i);
		for (int j = 0; j < pool.size(); j++)
		{
			if (CloseObjectPool[i]->m_pos.x - 200 < pool[j]->m_pos.x && pool[j]->m_pos.x < CloseObjectPool[i]->m_pos.x + 200 &&
				CloseObjectPool[i]->m_pos.y - 200 < pool[j]->m_pos.y && pool[j]->m_pos.y < CloseObjectPool[i]->m_pos.y + 200)
			{
				RECT rect;
				rect = pool[j]->GetRECT();
				if (m_ColliderBase->BoxColliderCheck(&collider_2, &rect) && CloseObjectPool[i]->m_Intro == true)
				{
					m_ColliderBase->WallCollision(pool[j], CloseObjectPool[i], m_playerHitSize);
					CloseObjectPool[i]->m_wallCollidePos = CloseObjectPool[i]->m_pos;
					CloseObjectPool[i]->m_isMoveTO = false;

					if (CloseObjectPool[i]->m_pos.y < rect.top)
					{
						CloseObjectPool[i]->m_pos.y -= 6;
						//CloseObjectPool[i]->m_wallCollidePos.x -= 20;

						if (CloseObjectPool[i]->m_pos.x < player->m_pos.x)
						{
							CloseObjectPool[i]->m_wallCollidePos.x += 110;
						}

						else
						{
							CloseObjectPool[i]->m_wallCollidePos.x -= 110;
						}
					}

					else if (CloseObjectPool[i]->m_pos.y >= rect.bottom)
					{
						CloseObjectPool[i]->m_pos.y += 6;

						if (CloseObjectPool[i]->m_pos.x < player->m_pos.x)
						{
							CloseObjectPool[i]->m_wallCollidePos.x += 110;
						}

						else
						{
							CloseObjectPool[i]->m_wallCollidePos.x -= 110;
						}
					}

					else if (CloseObjectPool[i]->m_pos.x < rect.left)
					{
						CloseObjectPool[i]->m_pos.x -= 6;
						if (CloseObjectPool[i]->m_pos.y < player->m_pos.y)
						{
							CloseObjectPool[i]->m_wallCollidePos.y += 90;
						}

						else
						{
							CloseObjectPool[i]->m_wallCollidePos.y -= 90;
						}
					}


					else if (CloseObjectPool[i]->m_pos.x >= rect.right)
					{
						CloseObjectPool[i]->m_pos.x += 6;
						if (CloseObjectPool[i]->m_pos.y < player->m_pos.y)
						{
							CloseObjectPool[i]->m_wallCollidePos.y += 90;
						}

						else
						{
							CloseObjectPool[i]->m_wallCollidePos.y -= 90;
						}
					}
				}
			}
		}
	}
}

float CObjectManager::ReturnRandom(int max)
{
	std::random_device gen;
	std::mt19937 rand(gen());
	std::uniform_int_distribution<int> dist(-max, max);

	return dist(rand);
}

void CObjectManager::SetMonsterSpeed()
{
	m_curTime += 1;
	if (m_curTime >= m_loadingTime)
	{
		for (int i = 0; i < CloseObjectPool.size(); i++)
		{
			CloseObjectPool[i]->m_moveSpd += ReturnRandom(10) * 0.5f;
			if (CloseObjectPool[i]->m_moveSpd <= 0 || CloseObjectPool[i]->m_moveSpd >= 5)
			{
				CloseObjectPool[i]->m_moveSpd = 3.0f;
			}
		}

		m_curTime = 0;
	}
}

void CObjectManager::KnockBack(CObjectBase* object)
{
	if (player->m_status == eMyStatus::ATTACKUP || player->m_status == eMyStatus::DASHATTACKUP)
	{
		object->m_pos.y -= 50;
	}

	else if (player->m_status == eMyStatus::ATTACKDOWN || player->m_status == eMyStatus::DASHATTACKDOWN)
	{
		object->m_pos.y += 50;
	}

	else if (player->m_status == eMyStatus::ATTACKLEFT || player->m_status == eMyStatus::DASHATTACKLEFT)
	{
		object->m_pos.x -= 50;
	}

	else if (player->m_status == eMyStatus::ATTACKRIGHT || player->m_status == eMyStatus::DASHATTACKRIGHT)
	{
		object->m_pos.x += 50;
	}
}

// 기획이랑 이야기 해보기
void CObjectManager::SuperKnockBack(int idx)
{
	if (boss->m_isPattern == false)
	{
		if (m_ColliderBase->BoxColliderCheck(&playerCollider, &bossCollider))
		{
			boss->m_jumpPatternOn = false;
			boss->m_attackPatternOn = true;
		}

		else
		{
			boss->m_jumpPatternOn = true;
			boss->m_attackPatternOn = false;
		}

		boss->m_isPattern = true;
	}
	if (!player->m_useSuper)
		return;

	else if (player->m_useSuper)
	{
		SetPlayerSuperColliderBox();
		for (int i = 0; i < CloseObjectPool.size(); i++)
		{
			SetCloseCombatHitColliderTwoBox(i);
			if (m_ColliderBase->BoxColliderCheck(&collider_1, &collider_2))
			{

			}
		}
	}
}

void CObjectManager::BossCheckPlayerBox()
{
	if (boss->m_cancontrol)
	{
		SetBossRangeBox();

		if (boss->m_isPattern == false && boss->m_patternDelay == false)
		{
			if (m_ColliderBase->BoxColliderCheck(&playerCollider, &bossCollider))
			{
				boss->m_jumpPatternOn = false;
				boss->m_attackPatternOn = true;
			}
			else
			{
				boss->m_jumpPatternOn = true;
				boss->m_attackPatternOn = false;
			}
			boss->m_isPattern = true;
		}
	}
}

void CObjectManager::SetBossJumpBox()
{
	collider_2.top = boss->m_pos.y - 50;
	collider_2.left = boss->m_pos.x - m_BossJumpAttackBox.x;
	collider_2.right = boss->m_pos.x + m_BossJumpAttackBox.x;
	collider_2.bottom = boss->m_pos.y + m_BossJumpAttackBox.y + 70;
}

void CObjectManager::SetBossAttackBox()
{
	if (boss->m_status == eMyStatus::ATTACKLEFT)
	{
		collider_2.top = boss->m_pos.y - m_BossAttackBox.y + 50;
		collider_2.left = boss->m_pos.x - m_BossAttackBox.x - 100;
		collider_2.right = boss->m_pos.x + m_BossAttackBox.x - 100;
		collider_2.bottom = boss->m_pos.y + m_BossAttackBox.y + 50;
	}

	else if (boss->m_status == eMyStatus::ATTACKRIGHT)
	{
		collider_2.top = boss->m_pos.y - m_BossAttackBox.y + 50;
		collider_2.left = boss->m_pos.x - m_BossAttackBox.x + 100;
		collider_2.right = boss->m_pos.x + m_BossAttackBox.x + 100;
		collider_2.bottom = boss->m_pos.y + m_BossAttackBox.y + 50;
	}
}

void CObjectManager::SetBossHitBox()
{
	if (boss->m_status == eMyStatus::IDLELEFT)
	{
		bossCollider.top = boss->m_pos.y - m_BossHitBox.y + 10;
		bossCollider.left = boss->m_pos.x - m_BossHitBox.x + 10;
		bossCollider.right = boss->m_pos.x + m_BossHitBox.x;
		bossCollider.bottom = boss->m_pos.y + m_BossHitBox.y;
	}

	else if (boss->m_status == eMyStatus::IDLERIGHT)
	{
		bossCollider.top = boss->m_pos.y - m_BossHitBox.y + 10;
		bossCollider.left = boss->m_pos.x - m_BossHitBox.x;
		bossCollider.right = boss->m_pos.x + m_BossHitBox.x - 10;
		bossCollider.bottom = boss->m_pos.y + m_BossHitBox.y;
	}

	else
	{
		bossCollider.top = boss->m_pos.y - m_BossHitBox.y + 10;
		bossCollider.left = boss->m_pos.x - m_BossHitBox.x;
		bossCollider.right = boss->m_pos.x + m_BossHitBox.x - 10;
		bossCollider.bottom = boss->m_pos.y + m_BossHitBox.y;
	}
}

void CObjectManager::BossJumpPattern()
{
	if (boss->m_jumpPatternOn)
	{
		if (boss->m_patternPhase == 0)
		{
			boss->JumpPattern_Intro();
		}

		if (boss->m_patternPhase == 1)
		{
			boss->JumpReady();
		}

		else if (boss->m_patternPhase == 2)
		{
			boss->JumpPattern_Jump();
		}

		else if (boss->m_patternPhase == 3)
		{
			boss->JumpPatternDelayTime();
		}

		else if (boss->m_patternPhase == 4)
		{
			boss->JumpStomp();
		}

		else if (boss->m_patternPhase == 5)
		{
			SetBossJumpBox();
			if (CObjectManager::GetInstance()->isDebugMode)
			{
				m_pEngine->DrawRect(collider_2, 255, 255, 0);
			}

			if (m_ColliderBase->BoxColliderCheck(&playerCollider, &collider_2) && boss->m_attacked == false)
			{
				player->HPDown(2);
				boss->m_attacked = true;
			}

			boss->JumpCollideDelete();
		}

		else if (boss->m_patternPhase == 6)
		{
			boss->JumpPatternDmg();
			boss->m_patternDelay = true;
		}
	}
}

void CObjectManager::BossAttackPattern()
{
	if (boss->m_attackPatternOn)
	{
		if (boss->m_patternPhase == 0)
		{
			boss->AttackPattern_intro();
		}

		if (boss->m_patternPhase == 1)
		{
			boss->AttackPattern_DelayTime();
		}

		else if (boss->m_patternPhase == 2)
		{
			SetBossAttackBox();
			m_pEngine->DrawRect(collider_2, 255, 0, 0);

			if (m_ColliderBase->BoxColliderCheck(&playerCollider, &collider_2) && boss->m_attacked == false)
			{
				player->HPDown(3);
				boss->m_attacked = true;
			}
			boss->AttackPattern_Attack();
		}

		else if (boss->m_patternPhase == 3)
		{
			boss->AttackPattern_AfterAttack();
			boss->m_patternDelay = true;
		}
	}
}

void CObjectManager::ArrowCollideCheck()
{
	for (int i = 0; i < RangeObjectPool.size(); i++)
	{
		CRangeObject* tmp = dynamic_cast<CRangeObject*>(RangeObjectPool[i]);
		for (int j = 0; j < tmp->arrowpool.size(); j++)
		{
			if (tmp->arrowpool[j]->m_isAlive)
			{
				CArrowObject* arrowtmp = tmp->arrowpool[j];
				arrowtmp->m_collider.left = arrowtmp->m_pos.x - 10;
				arrowtmp->m_collider.top = arrowtmp->m_pos.y - 10;
				arrowtmp->m_collider.right = arrowtmp->m_pos.x + 10;
				arrowtmp->m_collider.bottom = arrowtmp->m_pos.y + 10;

				if (CObjectManager::GetInstance()->isDebugMode)
				{
					RECT arrowrect;
					arrowrect.left = arrowtmp->m_collider.left;
					arrowrect.top = arrowtmp->m_collider.top;
					arrowrect.right = arrowtmp->m_collider.right;
					arrowrect.bottom = arrowtmp->m_collider.bottom;
					m_pEngine->DrawRect(arrowrect, 0, 255, 255);
				}

				for (int i = 0; i < Stage01Pool.size(); i++)
				{

					RECT rect;
					rect = Stage01Pool[i]->GetRECT();
					if (m_ColliderBase->BoxColliderCheck(&arrowtmp->m_collider, &rect))
					{
						arrowtmp->m_isAlive = false;
						arrowtmp->m_isFly = false;
						arrowtmp->m_isBreak = true;
					}

				}

				if (arrowtmp->m_isAlive && m_ColliderBase->BoxColliderCheck(&arrowtmp->m_collider, &playerCollider))
				{
					if (player->m_totalStatus != eToTalStatus::HIT && player->m_totalStatus != eToTalStatus::DASH)
					{
						player->HPDown(1);
						arrowtmp->m_isAlive = false;
						arrowtmp->m_isFly = false;
						arrowtmp->m_isBreak = true;

					}
				}
			}
		}
	}
}

void CObjectManager::DealDamage()
{
	/*if (player->m_prevStatus == eMyStatus::ATTACKDOWN || player->m_prevStatus == eMyStatus::ATTACKUP || player->m_prevStatus == eMyStatus::ATTACKLEFT || player->m_prevStatus == eMyStatus::ATTACKRIGHT ||
		player->m_prevStatus == eMyStatus::DASHATTACKUP || player->m_prevStatus == eMyStatus::DASHATTACKDOWN || player->m_prevStatus == eMyStatus::DASHATTACKLEFT || player->m_prevStatus == eMyStatus::DASHATTACKRIGHT ||
		player->m_prevStatus == eMyStatus::SATTACKUP || player->m_prevStatus == eMyStatus::SATTACKDOWN || player->m_prevStatus == eMyStatus::SATTACKLEFT || player->m_prevStatus == eMyStatus::SATTACKRIGHT ||
		player->m_prevStatus == eMyStatus::SDASHATTACKUP || player->m_prevStatus == eMyStatus::SDASHATTACKDOWN || player->m_prevStatus == eMyStatus::SDASHATTACKRIGHT || player->m_prevStatus == eMyStatus::SDASHATTACKLEFT)
	{*/
	if (player->m_totalStatus == eToTalStatus::ATTACK || player->m_totalStatus == eToTalStatus::DASHATTACK)
	{
		if (player->m_animator->GetTotalFrameIdx() - 1 == player->m_animator->GetCurrentIdx())
		{
			for (int i = 0; i < CloseObjectPool.size(); i++)
			{
				if (CloseObjectPool[i]->m_isHit)
				{
					CloseObjectPool[i]->m_HP -= player->m_dmg;
					CloseObjectPool[i]->m_isHit = false;
				}
			}

			for (int i = 0; i < RangeObjectPool.size(); i++)
			{
				if (RangeObjectPool[i]->m_isHit)
				{
					RangeObjectPool[i]->m_HP -= player->m_dmg;
					RangeObjectPool[i]->m_isHit = false;
				}
			}

			if (boss->m_isHit)
			{
				boss->m_HP -= player->m_dmg;
				boss->m_isHit = false;
			}
		}
	}
}

void CObjectManager::HitBossCheck()
{
	if (boss == nullptr)
		return;

	else
	{
		if (player->m_totalStatus == eToTalStatus::ATTACK || player->m_totalStatus == eToTalStatus::DASHATTACK)
		{
			if (boss->m_isCollide)
			{
				if (player->m_hitBoss == false)
				{
					SetPlayerAttackColliderBox();
					SetBossHitBox();
					if (m_ColliderBase->BoxColliderCheck(&collider_1, &bossCollider))
					{
						for (int i = 0; i < boss->HitEffect.size(); i++)
						{
							boss->HitEffect[i]->ResetCurrentIdx();
							boss->HitEffect[i]->ResetLoadingTime();
						}
						for (int i = 0; i < boss->HitEffect.size(); i++)
						{
							boss->HitEffect[i]->ResetCurrentIdx();
							boss->HitEffect[i]->ResetLoadingTime();
						}
						player->m_hitBoss = true;
						boss->HPDown(0);
						player->PlusSuper();

						// 넉백추가해라
					}
				}
			}
		}
	}
}

void CObjectManager::BossPlayerDashCheck()
{
	float Gradient; // 기울기
//// y = Gradient(X-x1) + y1
	Gradient = (player->m_pos.x - player->m_DashPos.x) / (player->m_pos.y - player->m_DashPos.y); // 직선의 기울기를 구한다.

	SetBossHitBox();

	switch (player->m_status)
	{

	case eMyStatus::AFTERDASHUP:
	{
		collider_2.left = player->m_pos.x - m_playerHitSize.x;
		collider_2.top = player->m_DashPos.y - m_playerHitSize.y;
		collider_2.right = player->m_pos.x + m_playerHitSize.x;
		collider_2.bottom = player->m_pos.y;
		if (m_ColliderBase->BoxColliderCheck(&bossCollider, &collider_2))
		{
			if ((bossCollider.bottom > player->m_DashPos.y) && (player->m_DashPos.x + m_playerHitSize.x < bossCollider.left)
				&& (player->m_DashPos.x - m_playerHitSize.x > bossCollider.right));
			{
				player->m_DashPos.y = bossCollider.bottom + m_playerHitSize.y + 1;
			}
		}
	}
	break;

	case eMyStatus::SAFTERDASHUP:
	{
		collider_2.left = player->m_pos.x - m_playerHitSize.x;
		collider_2.top = player->m_DashPos.y - m_playerHitSize.y;
		collider_2.right = player->m_pos.x + m_playerHitSize.x;
		collider_2.bottom = player->m_pos.y;
		if (m_ColliderBase->BoxColliderCheck(&bossCollider, &collider_2))
		{
			if ((bossCollider.bottom > player->m_DashPos.y) && (player->m_DashPos.x + m_playerHitSize.x < bossCollider.left)
				&& (player->m_DashPos.x - m_playerHitSize.x > bossCollider.right));
			{
				player->m_DashPos.y = bossCollider.bottom + m_playerHitSize.y + 1;
			}
		}
	}
	break;

	case eMyStatus::AFTERDASHDOWN:
	{
		collider_2.left = player->m_pos.x - m_playerHitSize.x;
		collider_2.top = player->m_pos.y;
		collider_2.right = player->m_pos.x + m_playerHitSize.x;
		collider_2.bottom = player->m_DashPos.y + m_playerHitSize.y;
		if (m_ColliderBase->BoxColliderCheck(&bossCollider, &collider_2))
		{
			if ((bossCollider.top < player->m_DashPos.y) && (player->m_DashPos.x + m_playerHitSize.x > bossCollider.left)
				&& (player->m_DashPos.x - m_playerHitSize.x < bossCollider.right));
			{
				player->m_DashPos.y = bossCollider.top - m_playerHitSize.y - 1;
			}
		}
	}
	break;

	case eMyStatus::SAFTERDASHDOWN:
	{
		collider_2.left = player->m_pos.x - m_playerHitSize.x;
		collider_2.top = player->m_pos.y;
		collider_2.right = player->m_pos.x + m_playerHitSize.x;
		collider_2.bottom = player->m_DashPos.y + m_playerHitSize.y;
		if (m_ColliderBase->BoxColliderCheck(&bossCollider, &collider_2))
		{
			if ((bossCollider.top < player->m_DashPos.y) && (player->m_DashPos.x + m_playerHitSize.x > bossCollider.left)
				&& (player->m_DashPos.x - m_playerHitSize.x < bossCollider.right));
			{
				player->m_DashPos.y = bossCollider.top - m_playerHitSize.y - 1;
			}
		}
	}
	break;

	case eMyStatus::AFTERDASHLEFT:
	{
		collider_2.left = player->m_DashPos.x - m_playerHitSize.x;
		collider_2.top = player->m_pos.y - m_playerHitSize.y;
		collider_2.right = player->m_pos.x;
		collider_2.bottom = player->m_pos.y + m_playerHitSize.y;
		if (m_ColliderBase->BoxColliderCheck(&bossCollider, &collider_2))
		{
			if ((bossCollider.right > player->m_DashPos.x) && (player->m_DashPos.y + m_playerHitSize.y > bossCollider.top)
				&& (player->m_DashPos.y - m_playerHitSize.y < bossCollider.bottom));
			{
				player->m_DashPos.x = bossCollider.right + m_playerHitSize.x + 1;
			}
		}
	}
	break;

	case eMyStatus::SAFTERDASHLEFT:
	{
		collider_2.left = player->m_DashPos.x - m_playerHitSize.x;
		collider_2.top = player->m_pos.y - m_playerHitSize.y;
		collider_2.right = player->m_pos.x;
		collider_2.bottom = player->m_pos.y + m_playerHitSize.y;
		if (m_ColliderBase->BoxColliderCheck(&bossCollider, &collider_2))
		{
			if ((bossCollider.right > player->m_DashPos.x) && (player->m_DashPos.y + m_playerHitSize.y > bossCollider.top)
				&& (player->m_DashPos.y - m_playerHitSize.y < bossCollider.bottom));
			{
				player->m_DashPos.x = bossCollider.right + m_playerHitSize.x + 1;
			}
		}
	}
	break;

	case eMyStatus::AFTERDASHRIGHT:
	{
		collider_2.left = player->m_pos.x;
		collider_2.top = player->m_pos.y - m_playerHitSize.y;
		collider_2.right = player->m_DashPos.x + m_playerHitSize.x;
		collider_2.bottom = player->m_pos.y + m_playerHitSize.y;
		if (m_ColliderBase->BoxColliderCheck(&bossCollider, &collider_2))
		{
			if ((bossCollider.left < player->m_DashPos.x) && (player->m_DashPos.y + m_playerHitSize.y > bossCollider.top)
				&& (player->m_DashPos.y - m_playerHitSize.y < bossCollider.bottom));
			{
				player->m_DashPos.x = bossCollider.left - m_playerHitSize.x - 1;
			}
		}
	}
	break;

	case eMyStatus::SAFTERDASHRIGHT:
	{
		collider_2.left = player->m_pos.x;
		collider_2.top = player->m_pos.y - m_playerHitSize.y;
		collider_2.right = player->m_DashPos.x + m_playerHitSize.x;
		collider_2.bottom = player->m_pos.y + m_playerHitSize.y;
		if (m_ColliderBase->BoxColliderCheck(&bossCollider, &collider_2))
		{
			if ((bossCollider.left < player->m_DashPos.x) && (player->m_DashPos.y + m_playerHitSize.y > bossCollider.top)
				&& (player->m_DashPos.y - m_playerHitSize.y < bossCollider.bottom));
			{
				player->m_DashPos.x = bossCollider.left - m_playerHitSize.x - 1;
			}
		}
	}
	break;

	case eMyStatus::AFTERDASHDOWNLEFT:
	{
		collider_2.left = player->m_DashPos.x - m_playerHitSize.x;
		collider_2.top = player->m_pos.y;
		collider_2.right = player->m_pos.x;
		collider_2.bottom = player->m_DashPos.y + m_playerHitSize.y;
		if (m_ColliderBase->BoxColliderCheck(&bossCollider, &collider_2))
		{
			if ((bossCollider.top <= player->m_DashPos.y) && (player->m_DashPos.x <= bossCollider.right));
			{
				// (Right, y)
				float y = Gradient * (bossCollider.right - player->m_DashPos.x) + player->m_DashPos.y;
				// (x, Top)
				float x = player->m_pos.x + ((bossCollider.top - player->m_pos.y) / Gradient);

				if (bossCollider.left <= x && x <= bossCollider.right)
				{
					player->m_DashPos.x = x;
					player->m_DashPos.y = bossCollider.top - m_playerHitSize.y + 2;
				}

				else if (bossCollider.top <= y && y <= bossCollider.bottom)
				{
					player->m_DashPos.x = bossCollider.right + m_playerHitSize.x + 4;
					player->m_DashPos.y = y;
				}

				else
				{

				}
			}
		}
	}
	break;

	case eMyStatus::SAFTERDASHDOWNLEFT:
	{
		collider_2.left = player->m_DashPos.x - m_playerHitSize.x;
		collider_2.top = player->m_pos.y;
		collider_2.right = player->m_pos.x;
		collider_2.bottom = player->m_DashPos.y + m_playerHitSize.y;
		if (m_ColliderBase->BoxColliderCheck(&bossCollider, &collider_2))
		{
			if ((bossCollider.top <= player->m_DashPos.y) && (player->m_DashPos.x <= bossCollider.right));
			{
				// (Right, y)
				float y = Gradient * (bossCollider.right - player->m_DashPos.x) + player->m_DashPos.y;
				// (x, Top)
				float x = player->m_pos.x + ((bossCollider.top - player->m_pos.y) / Gradient);

				if (bossCollider.left <= x && x <= bossCollider.right)
				{
					player->m_DashPos.x = x;
					player->m_DashPos.y = bossCollider.top - m_playerHitSize.y + 2;
				}

				else if (bossCollider.top <= y && y <= bossCollider.bottom)
				{
					player->m_DashPos.x = bossCollider.right + m_playerHitSize.x + 4;
					player->m_DashPos.y = y;
				}

				else
				{

				}
			}
		}
	}
	break;

	case eMyStatus::AFTERDASHDOWNRIGHT:
	{
		if ((bossCollider.top <= player->m_DashPos.y) && (bossCollider.left <= player->m_DashPos.x));
		{
			// (Right, y)
			float y = Gradient * (bossCollider.left - player->m_DashPos.x) + player->m_DashPos.y;
			// (x, Top)
			float x = player->m_pos.x + ((bossCollider.top - player->m_pos.y) / Gradient);

			if (bossCollider.left <= x && x <= bossCollider.right)
			{
				player->m_DashPos.x = x;
				player->m_DashPos.y = bossCollider.top - m_playerHitSize.y - 4;
			}

			else if (bossCollider.top <= y && y <= bossCollider.bottom)
			{
				player->m_DashPos.x = bossCollider.left - m_playerHitSize.x + 2;
				player->m_DashPos.y = y;
			}

			else
			{

			}
		}
	}
	break;

	case eMyStatus::SAFTERDASHDOWNRIGHT:
	{
		if ((bossCollider.top <= player->m_DashPos.y) && (bossCollider.left <= player->m_DashPos.x));
		{
			// (Right, y)
			float y = Gradient * (bossCollider.left - player->m_DashPos.x) + player->m_DashPos.y;
			// (x, Top)
			float x = player->m_pos.x + ((bossCollider.top - player->m_pos.y) / Gradient);

			if (bossCollider.left <= x && x <= bossCollider.right)
			{
				player->m_DashPos.x = x;
				player->m_DashPos.y = bossCollider.top - m_playerHitSize.y - 4;
			}

			else if (bossCollider.top <= y && y <= bossCollider.bottom)
			{
				player->m_DashPos.x = bossCollider.left - m_playerHitSize.x + 2;
				player->m_DashPos.y = y;
			}

			else
			{

			}
		}
	}
	break;

	case eMyStatus::AFTERDASHUPLEFT:
	{
		if ((player->m_DashPos.y <= bossCollider.bottom) && (player->m_DashPos.x <= bossCollider.right));
		{
			// (Right, y)
			float y = Gradient * (bossCollider.right - player->m_DashPos.x) + player->m_DashPos.y;
			// (x, Top)
			float x = player->m_pos.x + ((bossCollider.bottom - player->m_pos.y) / Gradient);

			if (bossCollider.left <= x && x <= bossCollider.right)
			{
				player->m_DashPos.x = x;
				player->m_DashPos.y = bossCollider.bottom + m_playerHitSize.y + 2;
			}

			else if (bossCollider.top <= y && y <= bossCollider.bottom)
			{
				player->m_DashPos.x = bossCollider.right + m_playerHitSize.x + 2;
				player->m_DashPos.y = y;
			}

			else
			{

			}
		}
	}
	break;

	case eMyStatus::SAFTERDASHUPLEFT:
	{
		if ((player->m_DashPos.y <= bossCollider.bottom) && (player->m_DashPos.x <= bossCollider.right));
		{
			// (Right, y)
			float y = Gradient * (bossCollider.right - player->m_DashPos.x) + player->m_DashPos.y;
			// (x, Top)
			float x = player->m_pos.x + ((bossCollider.bottom - player->m_pos.y) / Gradient);

			if (bossCollider.left <= x && x <= bossCollider.right)
			{
				player->m_DashPos.x = x;
				player->m_DashPos.y = bossCollider.bottom + m_playerHitSize.y + 2;
			}

			else if (bossCollider.top <= y && y <= bossCollider.bottom)
			{
				player->m_DashPos.x = bossCollider.right + m_playerHitSize.x + 2;
				player->m_DashPos.y = y;
			}

			else
			{

			}
		}
	}
	break;

	case eMyStatus::AFTERDASHUPRIGHT:
	{
		if ((player->m_DashPos.y <= bossCollider.bottom) && (bossCollider.left <= player->m_DashPos.x));
		{
			// (Right, y)
			float y = Gradient * (bossCollider.left - player->m_DashPos.x) + player->m_DashPos.y;
			// (x, Top)
			float x = player->m_pos.x + ((bossCollider.bottom - player->m_pos.y) / Gradient);

			if (bossCollider.left <= x && x <= bossCollider.right)
			{
				player->m_DashPos.x = x;
				player->m_DashPos.y = bossCollider.bottom + m_playerHitSize.y + 2;
			}

			else if (bossCollider.top <= y && y <= bossCollider.bottom)
			{
				player->m_DashPos.x = bossCollider.left - m_playerHitSize.x + 2;
				player->m_DashPos.y = y;
			}

			else
			{

			}
		}
	}
	break;

	case eMyStatus::SAFTERDASHUPRIGHT:
	{
		if ((player->m_DashPos.y <= bossCollider.bottom) && (bossCollider.left <= player->m_DashPos.x));
		{
			// (Right, y)
			float y = Gradient * (bossCollider.left - player->m_DashPos.x) + player->m_DashPos.y;
			// (x, Top)
			float x = player->m_pos.x + ((bossCollider.bottom - player->m_pos.y) / Gradient);

			if (bossCollider.left <= x && x <= bossCollider.right)
			{
				player->m_DashPos.x = x;
				player->m_DashPos.y = bossCollider.bottom + m_playerHitSize.y + 2;
			}

			else if (bossCollider.top <= y && y <= bossCollider.bottom)
			{
				player->m_DashPos.x = bossCollider.left - m_playerHitSize.x + 2;
				player->m_DashPos.y = y;
			}

			else
			{

			}
		}
	}
	break;

	default:
		break;
	}
}

void CObjectManager::LineToWallCheck(std::vector<CObjectBase*> pool)
{
	//// 먼저 현재 좌표와 대쉬할 좌표를 바탕으로 직선의 방정식을 구한다.
	// 플레이어의 x좌표가 대쉬할 좌표보다 작다면, posx, box, dashx 순으로 이루어져 있다.
	//		if ((object->GetRECT().left <= player->m_DashPos.x) && (object->GetRECT().bottom <= player->m_DashPos.y))
	//		{
	//			// 직선의 방정식과 충돌하는 박스의 y좌표를 구한다.
	//			float y = Gradient * (object->GetRECT().left - player->m_pos.x) + player->m_pos.y;
	//			// 그럼 교점은 (object->GetRECT().Left, y)가 되고 이를 플레이어 우상단으로 잡으면 자연스럽게 연출될 것 같다.
	//			player->m_pos.x = object->GetRECT().left - ((player->GetRECT().right - player->GetRECT().left) / 2);
	//			player->m_pos.y = y + ((player->GetRECT().top - player->GetRECT().bottom) / 2);
	//		}

	float Gradient; // 기울기
	//// y = Gradient(X-x1) + y1
	Gradient = (player->m_pos.x - player->m_DashPos.x) / (player->m_pos.y - player->m_DashPos.y); // 직선의 기울기를 구한다.
	for (int i = 0; i < pool.size(); i++)
	{
		RECT rect;
		rect = pool[i]->GetRECT();

		switch (player->m_status)
		{

		case eMyStatus::AFTERDASHUP:
		{
			collider_2.left = player->m_pos.x - m_playerHitSize.x;
			collider_2.top = player->m_DashPos.y - m_playerHitSize.y;
			collider_2.right = player->m_pos.x + m_playerHitSize.x;
			collider_2.bottom = player->m_pos.y;
			if (m_ColliderBase->BoxColliderCheck(&rect, &collider_2))
			{
				if ((rect.bottom > player->m_DashPos.y) && (player->m_DashPos.x + m_playerHitSize.x < rect.left)
					&& (player->m_DashPos.x - m_playerHitSize.x > rect.right));
				{
					player->m_DashPos.y = rect.bottom + m_playerHitSize.y + 1;
				}
			}
		}
		break;

		case eMyStatus::SAFTERDASHUP:
		{
			collider_2.left = player->m_pos.x - m_playerHitSize.x;
			collider_2.top = player->m_DashPos.y - m_playerHitSize.y;
			collider_2.right = player->m_pos.x + m_playerHitSize.x;
			collider_2.bottom = player->m_pos.y;
			if (m_ColliderBase->BoxColliderCheck(&rect, &collider_2))
			{
				if ((rect.bottom > player->m_DashPos.y) && (player->m_DashPos.x + m_playerHitSize.x < rect.left)
					&& (player->m_DashPos.x - m_playerHitSize.x > rect.right));
				{
					player->m_DashPos.y = rect.bottom + m_playerHitSize.y + 1;
				}
			}
		}
		break;

		case eMyStatus::AFTERDASHDOWN:
		{
			collider_2.left = player->m_pos.x - m_playerHitSize.x;
			collider_2.top = player->m_pos.y;
			collider_2.right = player->m_pos.x + m_playerHitSize.x;
			collider_2.bottom = player->m_DashPos.y + m_playerHitSize.y;
			if (m_ColliderBase->BoxColliderCheck(&rect, &collider_2))
			{
				if ((rect.top < player->m_DashPos.y) && (player->m_DashPos.x + m_playerHitSize.x > rect.left)
					&& (player->m_DashPos.x - m_playerHitSize.x < rect.right));
				{
					player->m_DashPos.y = rect.top - m_playerHitSize.y - 1;
				}
			}
		}
		break;

		case eMyStatus::SAFTERDASHDOWN:
		{
			collider_2.left = player->m_pos.x - m_playerHitSize.x;
			collider_2.top = player->m_pos.y;
			collider_2.right = player->m_pos.x + m_playerHitSize.x;
			collider_2.bottom = player->m_DashPos.y + m_playerHitSize.y;
			if (m_ColliderBase->BoxColliderCheck(&rect, &collider_2))
			{
				if ((rect.top < player->m_DashPos.y) && (player->m_DashPos.x + m_playerHitSize.x > rect.left)
					&& (player->m_DashPos.x - m_playerHitSize.x < rect.right));
				{
					player->m_DashPos.y = rect.top - m_playerHitSize.y - 1;
				}
			}
		}
		break;

		case eMyStatus::AFTERDASHLEFT:
		{
			collider_2.left = player->m_DashPos.x - m_playerHitSize.x;
			collider_2.top = player->m_pos.y - m_playerHitSize.y;
			collider_2.right = player->m_pos.x;
			collider_2.bottom = player->m_pos.y + m_playerHitSize.y;
			if (m_ColliderBase->BoxColliderCheck(&rect, &collider_2))
			{
				if ((rect.right > player->m_DashPos.x) && (player->m_DashPos.y + m_playerHitSize.y > rect.top)
					&& (player->m_DashPos.y - m_playerHitSize.y < rect.bottom));
				{
					player->m_DashPos.x = rect.right + m_playerHitSize.x + 1;
				}
			}
		}
		break;

		case eMyStatus::SAFTERDASHLEFT:
		{
			collider_2.left = player->m_DashPos.x - m_playerHitSize.x;
			collider_2.top = player->m_pos.y - m_playerHitSize.y;
			collider_2.right = player->m_pos.x;
			collider_2.bottom = player->m_pos.y + m_playerHitSize.y;
			if (m_ColliderBase->BoxColliderCheck(&rect, &collider_2))
			{
				if ((rect.right > player->m_DashPos.x) && (player->m_DashPos.y + m_playerHitSize.y > rect.top)
					&& (player->m_DashPos.y - m_playerHitSize.y < rect.bottom));
				{
					player->m_DashPos.x = rect.right + m_playerHitSize.x + 1;
				}
			}
		}
		break;

		case eMyStatus::AFTERDASHRIGHT:
		{
			collider_2.left = player->m_pos.x;
			collider_2.top = player->m_pos.y - m_playerHitSize.y;
			collider_2.right = player->m_DashPos.x + m_playerHitSize.x;
			collider_2.bottom = player->m_pos.y + m_playerHitSize.y;
			if (m_ColliderBase->BoxColliderCheck(&rect, &collider_2))
			{
				if ((rect.left < player->m_DashPos.x) && (player->m_DashPos.y + m_playerHitSize.y > rect.top)
					&& (player->m_DashPos.y - m_playerHitSize.y < rect.bottom));
				{
					player->m_DashPos.x = rect.left - m_playerHitSize.x - 1;
				}
			}
		}
		break;

		case eMyStatus::SAFTERDASHRIGHT:
		{
			collider_2.left = player->m_pos.x;
			collider_2.top = player->m_pos.y - m_playerHitSize.y;
			collider_2.right = player->m_DashPos.x + m_playerHitSize.x;
			collider_2.bottom = player->m_pos.y + m_playerHitSize.y;
			if (m_ColliderBase->BoxColliderCheck(&rect, &collider_2))
			{
				if ((rect.left < player->m_DashPos.x) && (player->m_DashPos.y + m_playerHitSize.y > rect.top)
					&& (player->m_DashPos.y - m_playerHitSize.y < rect.bottom));
				{
					player->m_DashPos.x = rect.left - m_playerHitSize.x - 1;
				}
			}
		}
		break;

		case eMyStatus::AFTERDASHDOWNLEFT:
		{
			collider_2.left = player->m_DashPos.x - m_playerHitSize.x;
			collider_2.top = player->m_pos.y;
			collider_2.right = player->m_pos.x;
			collider_2.bottom = player->m_DashPos.y + m_playerHitSize.y;
			if (m_ColliderBase->BoxColliderCheck(&rect, &collider_2))
			{
				if ((rect.top <= player->m_DashPos.y) && (player->m_DashPos.x <= rect.right));
				{
					// (Right, y)
					float y = Gradient * (rect.right - player->m_DashPos.x) + player->m_DashPos.y;
					// (x, Top)
					float x = player->m_pos.x + ((rect.top - player->m_pos.y) / Gradient);

					if (rect.left <= x && x <= rect.right)
					{
						player->m_DashPos.x = x;
						player->m_DashPos.y = rect.top - m_playerHitSize.y + 2;
					}

					else if (rect.top <= y && y <= rect.bottom)
					{
						player->m_DashPos.x = rect.right + m_playerHitSize.x + 4;
						player->m_DashPos.y = y;
					}

					else
					{

					}
				}
			}
		}
		break;

		case eMyStatus::SAFTERDASHDOWNLEFT:
		{
			collider_2.left = player->m_DashPos.x - m_playerHitSize.x;
			collider_2.top = player->m_pos.y;
			collider_2.right = player->m_pos.x;
			collider_2.bottom = player->m_DashPos.y + m_playerHitSize.y;
			if (m_ColliderBase->BoxColliderCheck(&rect, &collider_2))
			{
				if ((rect.top <= player->m_DashPos.y) && (player->m_DashPos.x <= rect.right));
				{
					// (Right, y)
					float y = Gradient * (rect.right - player->m_DashPos.x) + player->m_DashPos.y;
					// (x, Top)
					float x = player->m_pos.x + ((rect.top - player->m_pos.y) / Gradient);

					if (rect.left <= x && x <= rect.right)
					{
						player->m_DashPos.x = x;
						player->m_DashPos.y = rect.top - m_playerHitSize.y + 2;
					}

					else if (rect.top <= y && y <= rect.bottom)
					{
						player->m_DashPos.x = rect.right + m_playerHitSize.x + 4;
						player->m_DashPos.y = y;
					}

					else
					{

					}
				}
			}
		}
		break;

		case eMyStatus::AFTERDASHDOWNRIGHT:
		{
			if ((rect.top <= player->m_DashPos.y) && (rect.left <= player->m_DashPos.x));
			{
				// (Right, y)
				float y = Gradient * (rect.left - player->m_DashPos.x) + player->m_DashPos.y;
				// (x, Top)
				float x = player->m_pos.x + ((rect.top - player->m_pos.y) / Gradient);

				if (rect.left <= x && x <= rect.right)
				{
					player->m_DashPos.x = x;
					player->m_DashPos.y = rect.top - m_playerHitSize.y - 4;
				}

				else if (rect.top <= y && y <= rect.bottom)
				{
					player->m_DashPos.x = rect.left - m_playerHitSize.x + 2;
					player->m_DashPos.y = y;
				}

				else
				{

				}
			}
		}
		break;

		case eMyStatus::SAFTERDASHDOWNRIGHT:
		{
			if ((rect.top <= player->m_DashPos.y) && (rect.left <= player->m_DashPos.x));
			{
				// (Right, y)
				float y = Gradient * (rect.left - player->m_DashPos.x) + player->m_DashPos.y;
				// (x, Top)
				float x = player->m_pos.x + ((rect.top - player->m_pos.y) / Gradient);

				if (rect.left <= x && x <= rect.right)
				{
					player->m_DashPos.x = x;
					player->m_DashPos.y = rect.top - m_playerHitSize.y - 4;
				}

				else if (rect.top <= y && y <= rect.bottom)
				{
					player->m_DashPos.x = rect.left - m_playerHitSize.x + 2;
					player->m_DashPos.y = y;
				}

				else
				{

				}
			}
		}
		break;

		case eMyStatus::AFTERDASHUPLEFT:
		{
			if ((player->m_DashPos.y <= rect.bottom) && (player->m_DashPos.x <= rect.right));
			{
				// (Right, y)
				float y = Gradient * (rect.right - player->m_DashPos.x) + player->m_DashPos.y;
				// (x, Top)
				float x = player->m_pos.x + ((rect.bottom - player->m_pos.y) / Gradient);

				if (rect.left <= x && x <= rect.right)
				{
					player->m_DashPos.x = x;
					player->m_DashPos.y = rect.bottom + m_playerHitSize.y + 2;
				}

				else if (rect.top <= y && y <= rect.bottom)
				{
					player->m_DashPos.x = rect.right + m_playerHitSize.x + 2;
					player->m_DashPos.y = y;
				}

				else
				{

				}
			}
		}
		break;

		case eMyStatus::SAFTERDASHUPLEFT:
		{
			if ((player->m_DashPos.y <= rect.bottom) && (player->m_DashPos.x <= rect.right));
			{
				// (Right, y)
				float y = Gradient * (rect.right - player->m_DashPos.x) + player->m_DashPos.y;
				// (x, Top)
				float x = player->m_pos.x + ((rect.bottom - player->m_pos.y) / Gradient);

				if (rect.left <= x && x <= rect.right)
				{
					player->m_DashPos.x = x;
					player->m_DashPos.y = rect.bottom + m_playerHitSize.y + 2;
				}

				else if (rect.top <= y && y <= rect.bottom)
				{
					player->m_DashPos.x = rect.right + m_playerHitSize.x + 2;
					player->m_DashPos.y = y;
				}

				else
				{

				}
			}
		}
		break;

		case eMyStatus::AFTERDASHUPRIGHT:
		{
			if ((player->m_DashPos.y <= rect.bottom) && (rect.left <= player->m_DashPos.x));
			{
				// (Right, y)
				float y = Gradient * (rect.left - player->m_DashPos.x) + player->m_DashPos.y;
				// (x, Top)
				float x = player->m_pos.x + ((rect.bottom - player->m_pos.y) / Gradient);

				if (rect.left <= x && x <= rect.right)
				{
					player->m_DashPos.x = x;
					player->m_DashPos.y = rect.bottom + m_playerHitSize.y + 2;
				}

				else if (rect.top <= y && y <= rect.bottom)
				{
					player->m_DashPos.x = rect.left - m_playerHitSize.x + 2;
					player->m_DashPos.y = y;
				}

				else
				{

				}
			}
		}
		break;

		case eMyStatus::SAFTERDASHUPRIGHT:
		{
			if ((player->m_DashPos.y <= rect.bottom) && (rect.left <= player->m_DashPos.x));
			{
				// (Right, y)
				float y = Gradient * (rect.left - player->m_DashPos.x) + player->m_DashPos.y;
				// (x, Top)
				float x = player->m_pos.x + ((rect.bottom - player->m_pos.y) / Gradient);

				if (rect.left <= x && x <= rect.right)
				{
					player->m_DashPos.x = x;
					player->m_DashPos.y = rect.bottom + m_playerHitSize.y + 2;
				}

				else if (rect.top <= y && y <= rect.bottom)
				{
					player->m_DashPos.x = rect.left - m_playerHitSize.x + 2;
					player->m_DashPos.y = y;
				}

				else
				{

				}
			}
		}
		break;

		default:
			break;
		}
	}
}

// 공격범위 안에 플레이어가 존재하면 공격 상태로 변경
void CObjectManager::MonsterAttackDistanceCheck()
{
	if (CObjectManager::GetInstance()->isDebugMode)
	{
		RECT playerrect;
		playerrect.left = player->m_pos.x - 200;
		playerrect.top = player->m_pos.y - 200;
		playerrect.right = player->m_pos.x + 200;
		playerrect.bottom = player->m_pos.y + 200;
		m_pEngine->DrawRect(playerrect, 255, 255, 255);
		m_pEngine->DrawRect(playerCollider, 0, 255, 255);
	}

	RECT monsterrect;
	RECT monsterattackrect;
	if (player->m_isCollide)
	{
		SetPlayerHitColliderBox();
		for (int i = 0; i < CloseObjectPool.size(); i++)
		{
			if (CObjectManager::GetInstance()->isDebugMode)
			{
				monsterrect.left = CloseObjectPool[i]->m_pos.x - 50;
				monsterrect.top = CloseObjectPool[i]->m_pos.y - 30;
				monsterrect.right = CloseObjectPool[i]->m_pos.x + 50;
				monsterrect.bottom = CloseObjectPool[i]->m_pos.y + 30;
				m_pEngine->DrawRect(monsterrect, 255, 255, 255);


				if (CloseObjectPool[i]->m_status == eMyStatus::ATTACKLEFT)
				{
					if (CObjectManager::GetInstance()->isDebugMode)
					{
						monsterattackrect.left = CloseObjectPool[i]->m_pos.x - 80;
						monsterattackrect.top = CloseObjectPool[i]->m_pos.y - 60;
						monsterattackrect.right = CloseObjectPool[i]->m_pos.x;
						monsterattackrect.bottom = CloseObjectPool[i]->m_pos.y + 60;
						m_pEngine->DrawRect(monsterattackrect, 0, 255, 0);
					}
				}

				else if (CloseObjectPool[i]->m_status == eMyStatus::ATTACKLEFT)
				{
					if (CObjectManager::GetInstance()->isDebugMode)
					{
						monsterattackrect.left = CloseObjectPool[i]->m_pos.x;
						monsterattackrect.top = CloseObjectPool[i]->m_pos.y - 60;
						monsterattackrect.right = CloseObjectPool[i]->m_pos.x + 80;
						monsterattackrect.bottom = CloseObjectPool[i]->m_pos.y + 60;
						m_pEngine->DrawRect(monsterattackrect, 0, 255, 0);
					}
				}
			}

			if (CloseObjectPool[i]->m_totalStatus != eToTalStatus::HIT && CloseObjectPool[i]->m_totalStatus != eToTalStatus::DIE)
			{
				if (player->m_pos.x - 200 < CloseObjectPool[i]->m_pos.x && CloseObjectPool[i]->m_pos.x < player->m_pos.x + 200 &&
					player->m_pos.y - 200 < CloseObjectPool[i]->m_pos.y && CloseObjectPool[i]->m_pos.y < player->m_pos.y + 200)
				{
					SetMonsterAttackDistanceCollider(i);

					if (m_ColliderBase->BoxColliderCheck(&playerCollider, &collider_2))
					{
						SetMonsterAttackStatus(i);
						SetMonstaerAttackColliderBox(i);

						if (m_ColliderBase->BoxColliderCheck(&playerCollider, &collider_2))
						{
							// 근접 몬스터가 근접 공격할때 하는것 
							if (player->m_totalStatus != eToTalStatus::HIT && player->m_totalStatus != eToTalStatus::DASH)
							{
								if (CloseObjectPool[i]->m_animator->GetCurrentIdx() >= 2)
								{
									AnimationManager::GetInstance()->FrameResetEffect();
									player->HPDown(1);
								}
							}
						}
					}

					//else
					//{
					//	ObjectPool[i]->m_status = ObjectPool[i]->m_prevStatus;
					//}
				}
			}
		}
	}
}

// collider_1 의 RECT값을 변경
void CObjectManager::SetPlayerAttackColliderBox()
{
	float temp;
	switch (player->GetStatus())
	{
	case eMyStatus::ATTACKUP:
	{
		collider_1.left = player->m_pos.x - (m_playerAttackSize.y / 2);
		collider_1.top = player->m_pos.y - m_playerAttackSize.x + 10;
		collider_1.right = player->m_pos.x + (m_playerAttackSize.y / 2);
		collider_1.bottom = player->m_pos.y + 10;
	}
	break;

	case eMyStatus::ATTACKDOWN:
	{
		collider_1.left = player->m_pos.x - (m_playerAttackSize.y / 2);
		collider_1.top = player->m_pos.y;
		collider_1.right = player->m_pos.x + (m_playerAttackSize.y / 2);
		collider_1.bottom = player->m_pos.y + m_playerAttackSize.x;
	}
	break;

	case eMyStatus::ATTACKRIGHT:
	{
		collider_1.left = player->m_pos.x;
		collider_1.top = player->m_pos.y - (m_playerAttackSize.y / 2);
		collider_1.right = player->m_pos.x + m_playerAttackSize.x;
		collider_1.bottom = player->m_pos.y + (m_playerAttackSize.y / 2);
	}
	break;

	case eMyStatus::ATTACKLEFT:
	{
		collider_1.left = player->m_pos.x - m_playerAttackSize.x;
		collider_1.top = player->m_pos.y - (m_playerAttackSize.y / 2);
		collider_1.right = player->m_pos.x;
		collider_1.bottom = player->m_pos.y + (m_playerAttackSize.y / 2);
	}
	break;

	case eMyStatus::DASHATTACKUP:
	{
		collider_1.left = player->m_pos.x - (m_playerDashAttackSize.y / 2);
		collider_1.top = player->m_pos.y - m_playerDashAttackSize.x;
		collider_1.right = player->m_pos.x + (m_playerDashAttackSize.y / 2);
		collider_1.bottom = player->m_pos.y;
	}
	break;

	case eMyStatus::DASHATTACKDOWN:
	{
		collider_1.left = player->m_pos.x - (m_playerDashAttackSize.y / 2);
		collider_1.top = player->m_pos.y;
		collider_1.right = player->m_pos.x + (m_playerDashAttackSize.y / 2);
		collider_1.bottom = player->m_pos.y + m_playerDashAttackSize.x;
	}
	break;

	case eMyStatus::DASHATTACKLEFT:
	{
		collider_1.left = player->m_pos.x - m_playerDashAttackSize.x;
		collider_1.top = player->m_pos.y - (m_playerDashAttackSize.y / 2);
		collider_1.right = player->m_pos.x;
		collider_1.bottom = player->m_pos.y + (m_playerDashAttackSize.y / 2);
	}
	break;

	case eMyStatus::DASHATTACKRIGHT:
	{
		collider_1.left = player->m_pos.x;
		collider_1.top = player->m_pos.y - (m_playerDashAttackSize.y / 2);
		collider_1.right = player->m_pos.x + m_playerDashAttackSize.x;
		collider_1.bottom = player->m_pos.y + (m_playerDashAttackSize.y / 2);
	}
	break;

	case eMyStatus::SATTACKUP:
	{
		collider_1.left = player->m_pos.x - (m_playerSuperSize.y / 2);
		collider_1.top = player->m_pos.y - m_playerSuperSize.x + 10;
		collider_1.right = player->m_pos.x + (m_playerSuperSize.y / 2);
		collider_1.bottom = player->m_pos.y + 10;
	}
	break;

	case eMyStatus::SATTACKDOWN:
	{
		collider_1.left = player->m_pos.x - (m_playerSuperSize.y / 2);
		collider_1.top = player->m_pos.y;
		collider_1.right = player->m_pos.x + (m_playerSuperSize.y / 2);
		collider_1.bottom = player->m_pos.y + m_playerSuperSize.x;
	}
	break;

	case eMyStatus::SATTACKRIGHT:
	{
		collider_1.left = player->m_pos.x;
		collider_1.top = player->m_pos.y - (m_playerSuperSize.y / 2);
		collider_1.right = player->m_pos.x + m_playerSuperSize.x;
		collider_1.bottom = player->m_pos.y + (m_playerSuperSize.y / 2);
	}
	break;

	case eMyStatus::SATTACKLEFT:
	{
		collider_1.left = player->m_pos.x - m_playerSuperSize.x;
		collider_1.top = player->m_pos.y - (m_playerSuperSize.y / 2);
		collider_1.right = player->m_pos.x;
		collider_1.bottom = player->m_pos.y + (m_playerSuperSize.y / 2);
	}
	break;

	case eMyStatus::SDASHATTACKUP:
	{
		collider_1.left = player->m_pos.x - (m_playerSuperDashSize.y / 2);
		collider_1.top = player->m_pos.y - m_playerSuperDashSize.x;
		collider_1.right = player->m_pos.x + (m_playerSuperDashSize.y / 2);
		collider_1.bottom = player->m_pos.y;
	}
	break;

	case eMyStatus::SDASHATTACKDOWN:
	{
		collider_1.left = player->m_pos.x - (m_playerSuperDashSize.y / 2);
		collider_1.top = player->m_pos.y;
		collider_1.right = player->m_pos.x + (m_playerSuperDashSize.y / 2);
		collider_1.bottom = player->m_pos.y + m_playerSuperDashSize.x;
	}
	break;

	case eMyStatus::SDASHATTACKLEFT:
	{
		collider_1.left = player->m_pos.x - m_playerSuperDashSize.x;
		collider_1.top = player->m_pos.y - (m_playerSuperDashSize.y / 2);
		collider_1.right = player->m_pos.x;
		collider_1.bottom = player->m_pos.y + (m_playerSuperDashSize.y / 2);
	}
	break;

	case eMyStatus::SDASHATTACKRIGHT:
	{
		collider_1.left = player->m_pos.x;
		collider_1.top = player->m_pos.y - (m_playerSuperDashSize.y / 2);
		collider_1.right = player->m_pos.x + m_playerSuperDashSize.x;
		collider_1.bottom = player->m_pos.y + (m_playerSuperDashSize.y / 2);
	}
	break;
	default:
		break;
	}
}

void CObjectManager::SetPlayerHitColliderBox()
{
	playerCollider.left = player->m_pos.x - m_playerHitSize.x;
	playerCollider.top = player->m_pos.y - m_playerHitSize.y;
	playerCollider.right = player->m_pos.x + m_playerHitSize.x;
	playerCollider.bottom = player->m_pos.y + m_playerHitSize.y;

	/*if (player->m_status == eMyStatus::ATTACKUP)
	{
		playerCollider.top += 20;
		playerCollider.bottom += 20;
	}

	else if (player->m_status == eMyStatus::ATTACKDOWN)
	{
		playerCollider.top -= 10;
		playerCollider.bottom -= 10;
	}*/
}

void CObjectManager::SetPlayerSuperColliderBox()
{
	collider_1.left = player->m_pos.x - m_playerSuperKnockBackSize.x;
	collider_1.top = player->m_pos.y - m_playerSuperKnockBackSize.y;
	collider_1.right = player->m_pos.x + m_playerSuperKnockBackSize.x;
	collider_1.bottom = player->m_pos.y + m_playerSuperKnockBackSize.y;
}

void CObjectManager::SetCloseCombatHitColliderTwoBox(int idx)
{
	collider_2.left = CloseObjectPool[idx]->m_pos.x - 34; //나중에 define쓰기
	collider_2.top = CloseObjectPool[idx]->m_pos.y - 42;
	collider_2.right = CloseObjectPool[idx]->m_pos.x + 34;
	collider_2.bottom = CloseObjectPool[idx]->m_pos.y + 42;
}

void CObjectManager::SetRangerHitColliderTwoBox(int idx)
{
	collider_2.left = RangeObjectPool[idx]->m_pos.x - 34; //나중에 define쓰기x
	collider_2.top = RangeObjectPool[idx]->m_pos.y - 42;
	collider_2.right = RangeObjectPool[idx]->m_pos.x + 34;
	collider_2.bottom = RangeObjectPool[idx]->m_pos.y + 42;
}

void CObjectManager::SetMonsterAttackDistanceCollider(int idx)
{
	collider_2.left = CloseObjectPool[idx]->m_pos.x - 50;
	collider_2.top = CloseObjectPool[idx]->m_pos.y - 30;
	collider_2.right = CloseObjectPool[idx]->m_pos.x + 50;
	collider_2.bottom = CloseObjectPool[idx]->m_pos.y + 30;
}

void CObjectManager::SetMonsterAttackStatus(int idx)
{
	if (CloseObjectPool[idx]->m_totalStatus != eToTalStatus::ATTACK)
	{
		SoundPlay(14);
		CloseObjectPool[idx]->m_totalStatus = eToTalStatus::ATTACK;

		if (CloseObjectPool[idx]->m_status == eMyStatus::MOVEUP)
		{
			CloseObjectPool[idx]->m_status = eMyStatus::ATTACKUP;
			CloseObjectPool[idx]->m_prevStatus = eMyStatus::ATTACKUP;
			CloseObjectPool[idx]->m_prevMove = eMyStatus::MOVEUP;

		}

		else if (CloseObjectPool[idx]->m_status == eMyStatus::MOVEDOWN)
		{
			CloseObjectPool[idx]->m_prevStatus = eMyStatus::ATTACKDOWN;
			CloseObjectPool[idx]->m_status = eMyStatus::ATTACKDOWN;
			CloseObjectPool[idx]->m_prevMove = eMyStatus::MOVEDOWN;
		}

		else if (CloseObjectPool[idx]->m_status == eMyStatus::MOVELEFT)
		{
			CloseObjectPool[idx]->m_prevStatus = eMyStatus::ATTACKLEFT;
			CloseObjectPool[idx]->m_status = eMyStatus::ATTACKLEFT;
			CloseObjectPool[idx]->m_prevMove = eMyStatus::MOVELEFT;
		}

		else if (CloseObjectPool[idx]->m_status == eMyStatus::MOVERIGHT)
		{
			CloseObjectPool[idx]->m_prevStatus = eMyStatus::ATTACKRIGHT;
			CloseObjectPool[idx]->m_status = eMyStatus::ATTACKRIGHT;
			CloseObjectPool[idx]->m_prevMove = eMyStatus::MOVERIGHT;
		}

		CloseObjectPool[idx]->m_animator->ResetLoadingTime();
		CloseObjectPool[idx]->m_animator->ResetCurrentIdx();
		/*	else
			{
				ObjectPool[idx]->m_prevStatus = eMyStatus::ATTACKLEFT;
				ObjectPool[idx]->m_status = eMyStatus::ATTACKLEFT;
			}*/
	}
}

void CObjectManager::SetMonstaerAttackColliderBox(int idx)
{
	if (CloseObjectPool[idx]->m_status == eMyStatus::ATTACKLEFT)
	{
		collider_2.left = CloseObjectPool[idx]->m_pos.x - 80;
		collider_2.top = CloseObjectPool[idx]->m_pos.y - 60;
		collider_2.right = CloseObjectPool[idx]->m_pos.x;
		collider_2.bottom = CloseObjectPool[idx]->m_pos.y + 60;
	}

	else
	{
		collider_2.left = CloseObjectPool[idx]->m_pos.x;
		collider_2.top = CloseObjectPool[idx]->m_pos.y - 60;
		collider_2.right = CloseObjectPool[idx]->m_pos.x + 80;
		collider_2.bottom = CloseObjectPool[idx]->m_pos.y + 60;
	}
}

void CObjectManager::SetMonsterCenter_1Box(int idx)
{
	collider_1.left = CloseObjectPool[idx]->m_pos.x - m_monsterCenterSize.x;
	collider_1.top = CloseObjectPool[idx]->m_pos.y - m_monsterCenterSize.y + 30;
	collider_1.right = CloseObjectPool[idx]->m_pos.x + m_monsterCenterSize.x;
	collider_1.bottom = CloseObjectPool[idx]->m_pos.y + m_monsterCenterSize.y + 30;
}

void CObjectManager::SetMonsterCenter_2Box(int idx)
{
	collider_2.left = CloseObjectPool[idx]->m_pos.x - m_monsterCenterSize.x;
	collider_2.top = CloseObjectPool[idx]->m_pos.y - m_monsterCenterSize.y + 30;
	collider_2.right = CloseObjectPool[idx]->m_pos.x + m_monsterCenterSize.x;
	collider_2.bottom = CloseObjectPool[idx]->m_pos.y + m_monsterCenterSize.y + 30;
}

void CObjectManager::SetWallColliderBox(int idx)
{
	collider_1.left = WallObjectPool[idx]->m_pos.x - m_wallSize.x;
	collider_1.top = WallObjectPool[idx]->m_pos.y - m_wallSize.y;
	collider_1.right = WallObjectPool[idx]->m_pos.x + m_wallSize.x;
	collider_1.bottom = WallObjectPool[idx]->m_pos.y + m_wallSize.y;
}

void CObjectManager::SetBossRangeBox()
{
	bossCollider.left = boss->m_pos.x - m_BossRangeBox.x;
	bossCollider.top = boss->m_pos.y - m_BossRangeBox.y;
	bossCollider.right = boss->m_pos.x + m_BossRangeBox.x;
	bossCollider.bottom = boss->m_pos.y + m_BossRangeBox.y;
}

// 보류된 함수
//void CObjectManager::SimColliderCheck()
//{
//	// 플레이어랑 몬스터랑 곂칠일이 있을까? 
//	if (player->m_isCollide)
//	{
//		PlayerColliderBoxChange(player->m_pos, CVector2D(10, 10));
//		for (int i = 0; i < ObjectPool.size(); i++)
//		{
//			if (ObjectPool[i]->m_isCollide)
//			{
//				// 중심의 콜라이더를 세팅해줌
//				MonsterColliderBoxChange(i, ObjectPool[i]->m_pos, CVector2D(10, 10));
//				// 중심의 콜라이더가 부딪혔을때 어떻게 처리 할 것인가에 대한 함수
//				if (m_ColliderBase->BoxColliderCheck(player, ObjectPool[i]))
//				{
//					// 왔던 방향의 반대로 가야한다
//				}
//			}
//		}
//	}
//}