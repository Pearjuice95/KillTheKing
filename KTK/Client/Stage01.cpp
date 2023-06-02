#include "Stage01.h"
#include "CPlayerObject.h"
#include "CObjectManager.h"
#include "CColliderBase.h"
#include "CCloseObject.h"
#include "CRangeObject.h"
#include "CAnimator.h"
#include "AnimationManager.h"
#include "CCameraObject.h"
#include "Camera.h"
#include "CCameraObject.h"
#include "CObjectBase.h"
#include "enum.h"
#include "Sound.h"

Stage01::Stage01()
{

}

Stage01::~Stage01()
{

}

void Stage01::Initialize()
{
	BGMPause();
	BGM(11);

	CPlayerObject::GetInstance()->m_canControl = false;
	CPlayerObject::GetInstance()->m_isCollide = true;

	m_isStage0Clear = false;
	m_isWave01Clear = false;
	m_isWave02Clear = false;
	m_isWave03Clear = false;

	m_goalBox.left = 3080;
	m_goalBox.top = 300;
	m_goalBox.right = 3300;
	m_goalBox.bottom = 330;
	m_CloseIdx = 0;
	m_RangeIdx = 0;
	m_isWave01Render = true;
	m_isWave02Render = false;
	m_isWave03Render = false;


	m_phase = 0;
	m_time = 0.f;
	m_nowMonsterIdx = 26;
	isChangeCamera = false;

	m_isMove = false;
	RangeTargetPos01 = CVector2D(1290, 610);
	RangeTargetPos02 = CVector2D(1288, 2324);
	RangeTargetPos03 = CVector2D(2921, 606);
	RangeTargetPos04 = CVector2D(3521, 615);
	RangeTargetPos05 = CVector2D(2924, 2327);

	SetCloseObject();
	SetRangeObject();

	CPlayerObject::GetInstance()->m_HP = 5;
	CPlayerObject::GetInstance()->m_totalStatus = eToTalStatus::IDLE;
	CPlayerObject::GetInstance()->m_status = eMyStatus::IDLERIGHT;
	CPlayerObject::GetInstance()->m_superCount = 0;
	//CPlayerObject::GetInstance()->m_Hp = 5;
}

bool Stage01::Update()
{
	if (CPlayerObject::GetInstance()->m_totalStatus == eToTalStatus::DIE)
	{
		if (CPlayerObject::GetInstance()->m_animator->GetCurrentIdx() == CPlayerObject::GetInstance()->m_animator->GetTotalFrameIdx())
		{
			if (SceneManager::GetInstance()->m_wait)
			{
				SceneManager::GetInstance()->m_timer += 0.1f;
				SceneManager::GetInstance()->m_isFadein = true;
				if (SceneManager::GetInstance()->m_timer >= 20.f)
				{
					SceneManager::GetInstance()->m_sceneNumber--;
					SceneManager::GetInstance()->m_prevStage = (eScene)SceneManager::GetInstance()->m_sceneNumber;
					SceneManager::GetInstance()->m_isLoad = false;
					SceneManager::GetInstance()->m_isNextScene = false;
				}
			}

		}
	}

	if (m_isStage0Clear) // 조건이 클리어이면 false를 반납해서 Update를 멈춘다.
	{
		CObjectManager::GetInstance()->SetPlayerHitColliderBox();
		End();
		if (m_colliderBase->BoxColliderCheck(&m_goalBox, &CObjectManager::GetInstance()->playerCollider))
			return false;
	}
	else
	{
		if (!m_isWave01Clear)
		{
			Wave01();

			if (!CCameraObject::GetInsance()->isGoal && isChangeCamera == false)
				CameraMove(FirstCameraPos);
			else
			{
				CCameraObject::GetInsance()->isGoal = false;
				isChangeCamera = true;
			}
			if (CCameraObject::GetInsance()->isGoal == false && isChangeCamera == true)
			{
				CCameraObject::GetInsance()->ChangeSpeed(6.0f); // 속도
				CameraMove(SecondCameraPos);

				if (CCameraObject::GetInsance()->isGoal)
					m_phase++;
			}
			if (m_phase == 1)
			{
				Camera::GetInsance()->ChangeObject(CPlayerObject::GetInstance()); // player
				CPlayerObject::GetInstance()->m_canControl = true;
			}
		}
		else if (!m_isWave02Clear)
			Wave02();
		//else if (!m_isWave03Clear)
		//	Wave03();
		else
			m_isStage0Clear = true;
		return true;
	}
}

void Stage01::Render()
{

}

void Stage01::Finalize()
{

}

void Stage01::SetObject(CVector2D playerpos)
{
	CPlayerObject::GetInstance()->m_pos = playerpos;
}

void Stage01::Wave01()
{
	CVector2D direct;
	if (m_isWave01Render) // 첫번째 웨이브 렌더가 트루가 되면 (처음 들어오면 트루가 됨)
	{
		for (int i = 0; i < m_CloseIdx; i++)
		{
			CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[i]);
			if (object->m_DoorNum == 1)
			{
				object->m_isAlive = false;
				direct = object->m_pos.DistanceTo(CVector2D(750 + (i * 70), 500));
				object->m_pos.x += direct.x * 1.f;
				object->m_pos.y += direct.y * 1.f;
				//CameraMove(FirstCameraPos);
				object->m_status = eMyStatus::MOVELEFT;

				/*CCameraObject::GetInsance()->SetObjPos(CPlayerObject::GetInstance());
				Camera::GetInsance()->ChangeObject(CCameraObject::GetInsance());
				CCameraObject::GetInsance()->ChangeSpeed(10.f);*/
			}
			else if (object->m_DoorNum == 2)
			{
				object->m_isAlive = false;
				if (isChangeCamera)
				{
					direct = object->m_pos.DistanceTo(CVector2D(50 + (i * 70), 2500));
					object->m_pos.x += direct.x * 0.8f;
					object->m_pos.y += direct.y * 0.8f;
				}
				object->m_status = eMyStatus::MOVELEFT;
			}
		}
		if (m_phase == 1)
		{
			for (int i = 0; i < m_CloseIdx; i++)
			{
				CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[i]);
				if (object->m_DoorNum == 1)
				{
					object->m_isAlive = true;
					//		CObjectManager::GetInstance()->CloseObjectPool[i]->m_Intro = true;
				}
				else if (object->m_DoorNum == 2)
				{
					object->m_isAlive = true;
					//	CObjectManager::GetInstance()->CloseObjectPool[i]->m_Intro = true;
				}
			}
			for (int i = 0; i < m_RangeIdx; i++)
			{
				CRangeObject* object = dynamic_cast<CRangeObject*>(CObjectManager::GetInstance()->RangeObjectPool[i]);
				if (object->m_DoorNum == 1)
				{
					object->m_isAlive = true;
					object->m_pos = CVector2D(600 + (i * 200), 1000);
					object->m_status = eMyStatus::IDLERIGHT;
					object->m_totalStatus = eToTalStatus::IDLE;
					//object->m_moveSpd = 3.0f;
				}
				else if (object->m_DoorNum == 2)
				{
					object->m_isAlive = true;
					object->m_pos = CVector2D(600 + (i * 100), 2000 );
					object->m_status = eMyStatus::IDLERIGHT;
					object->m_totalStatus = eToTalStatus::IDLE;

					//object->m_moveSpd = 3.0f;
				}
			}
			m_isWave01Render = false;
		}
	}
	else // 몬스터가 죽는걸 판단해서 현재 맵에 있는 몬스터의 수로 다음 웨이브로 넘어간다. 
	{
		for (int i = 0; i < m_CloseIdx; i++)
		{
			CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[i]);
			if (object->m_totalStatus == eToTalStatus::DIE)
			{
				m_nowMonsterIdx--;
				if (m_nowMonsterIdx == 0)
					m_nowMonsterIdx = 0;
			}

		}
		for (int i = 0; i < m_RangeIdx; i++)
		{
			CRangeObject* object = dynamic_cast<CRangeObject*>(CObjectManager::GetInstance()->RangeObjectPool[i]);
			if (object->m_totalStatus == eToTalStatus::DIE)
			{
				m_nowMonsterIdx--;
				if (m_nowMonsterIdx <= 0)
				{
					m_isWave01Clear = true;
					m_isWave02Clear = false;
					m_isWave02Render = true;
					m_nowMonsterIdx = 75;
					return;
				}
			}
		}
		if (m_nowMonsterIdx > 0)
			m_nowMonsterIdx = 26;
	}
}

void Stage01::Wave02()
{
	CVector2D direct;
	if (m_isWave02Render) // 두번째 웨이브 렌더가 트루가 되면 (처음 들어오면 트루가 됨)
	{
		int countclose3 = 0;
		int countclose4 = 0;
		int countclose6 = 0;
		for (int i = 0; i < m_CloseIdx; i++)
		{
			CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[i]);
			if (object->m_DoorNum == 3 && countclose3 < 5)
			{
				object->m_isAlive = false;
				direct = object->m_pos.DistanceTo(CVector2D(2500 + (i * 70), 500));
				object->m_pos.x += direct.x * 2.f;
				object->m_pos.y += direct.y * 2.f;
				//CameraMove(FirstCameraPos);
				object->m_status = eMyStatus::MOVELEFT;
				countclose3++;
				/*CCameraObject::GetInsance()->SetObjPos(CPlayerObject::GetInstance());
				Camera::GetInsance()->ChangeObject(CCameraObject::GetInsance());
				CCameraObject::GetInsance()->ChangeSpeed(10.f);*/
			}
			else if (object->m_DoorNum == 4 && countclose4 < 5)
			{
				object->m_isAlive = false;
				if (isChangeCamera)
				{
					direct = object->m_pos.DistanceTo(CVector2D(2500 + (i * 70), 2500));
					object->m_pos.x += direct.x * 2.0f;
					object->m_pos.y += direct.y * 2.0f;
				}
				object->m_status = eMyStatus::MOVELEFT;
				countclose4++;
			}
			else if (object->m_DoorNum == 6 && countclose6 < 6)
			{
				object->m_isAlive = false;
				if (isChangeCamera)
				{
					direct = object->m_pos.DistanceTo(CVector2D(2500, 1450 - (i * 70)));
					object->m_pos.x += direct.x * 2.0f;
					object->m_pos.y += direct.y * 2.0f;
				}
				object->m_status = eMyStatus::MOVELEFT;
				countclose6++;
			}
		}
		int countRange3 = 0;
		int countRange4 = 0;
		int countRange6 = 0;
		for (int i = 0; i < m_RangeIdx; i++)
		{

			CRangeObject* object = dynamic_cast<CRangeObject*>(CObjectManager::GetInstance()->RangeObjectPool[i]);
			if (object->m_DoorNum == 3 && countRange3 < 2)
			{
				object->m_isAlive = false;
				direct = object->m_pos.DistanceTo(CVector2D(2000 + (i * 70), 1500));
				object->m_pos.x += direct.x * 2.0f;
				object->m_pos.y += direct.y * 2.0f;
				object->m_totalStatus = eToTalStatus::IDLE;
				object->m_status = eMyStatus::IDLERIGHT;
				countRange3++;
			}
			else if (object->m_DoorNum == 4 && countRange4 < 2)
			{
				object->m_isAlive = false;
				if (isChangeCamera)
				{
					direct = object->m_pos.DistanceTo(CVector2D(2000 + (i * 70), 1500 - (i * 80)));
					object->m_pos.x += direct.x * 2.0f;
					object->m_pos.y += direct.y * 2.0f;
				}
				object->m_totalStatus = eToTalStatus::IDLE;
				object->m_status = eMyStatus::IDLERIGHT;
				countRange4++;
			}
			else if (object->m_DoorNum == 6 && countRange6 < 2)
			{
				object->m_isAlive = false;
				if (isChangeCamera)
				{
					direct = object->m_pos.DistanceTo(CVector2D(2500 - (i * 100), 2000 ));
					object->m_pos.x += direct.x * 2.0f;
					object->m_pos.y += direct.y * 2.0f;
				}
				object->m_totalStatus = eToTalStatus::IDLE;
				object->m_status = eMyStatus::IDLERIGHT;
				countRange6++;
			}
		}
		m_time += 0.1f;
		if (m_time >= 30.0f)
		{
			m_isMove = true;
		}
		else
		{
			int countclose3 = 0;
			int countclose4 = 0;
			int countclose6 = 0;

			for (int i = 0; i < m_CloseIdx; i++)
			{
				CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[i]);
				if (object->m_DoorNum == 3 && countclose3 < 5)
				{
					object->m_isAlive = true;
					//CObjectManager::GetInstance()->CloseObjectPool[i]->m_Intro = true;
				//	countclose3++;
				}
				else if (object->m_DoorNum == 4 && countclose4 < 5)
				{
					object->m_isAlive = true;
					//CObjectManager::GetInstance()->CloseObjectPool[i]->m_Intro = true;
				//	countclose4++;
				}
				else if (object->m_DoorNum == 6 && countclose6 < 6)
				{
					object->m_isAlive = true;
					//CObjectManager::GetInstance()->CloseObjectPool[i]->m_Intro = true;
					//countclose6++;
				}
			}
			int countRange3 = 0;
			int countRange4 = 0;
			int countRange6 = 0;
			for (int i = 0; i < m_RangeIdx; i++)
			{

				CRangeObject* object = dynamic_cast<CRangeObject*>(CObjectManager::GetInstance()->RangeObjectPool[i]);
				if (object->m_DoorNum == 3 && countRange3 < 2)
				{
					object->m_isAlive = true;
					object->m_pos = CVector2D(2800, 1000 + (i * 80));
					object->m_status = eMyStatus::ATTACKLEFT;
					//object->m_moveSpd = 3.0f;
					//countRange3++;
				}
				else if (object->m_DoorNum == 4 && countRange4 < 2)
				{
					object->m_isAlive = true;
					object->m_pos = CVector2D(3200, 500 + (i * 80));
					object->m_status = eMyStatus::ATTACKLEFT;
					//countRange4++;

					//object->m_moveSpd = 3.0f;
				}
				else if (object->m_DoorNum == 6 && countRange6 < 1)
				{
					object->m_isAlive = true;
					object->m_pos = CVector2D(3000, 1600 + (i * 80));
					object->m_status = eMyStatus::ATTACKLEFT;
					//countRange6++;
//
					//object->m_moveSpd = 3.0f;
				}
			}
			m_isWave02Render = false;
		}
	}

	else // 몬스터가 죽는걸 판단해서 현재 맵에 있는 몬스터의 수로 다음 웨이브로 넘어간다. 
	{
		for (int i = 0; i < m_CloseIdx; i++)
		{
			CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[i]);
			if (object->m_totalStatus == eToTalStatus::DIE)
			{
				m_nowMonsterIdx--;
				if (m_nowMonsterIdx == 0)
					m_isStage0Clear = true;
			}

		}
		for (int i = 0; i < m_RangeIdx; i++)
		{
			CRangeObject* object = dynamic_cast<CRangeObject*>(CObjectManager::GetInstance()->RangeObjectPool[i]);
			if (object->m_totalStatus == eToTalStatus::DIE)
			{
				m_nowMonsterIdx--;
				if (m_nowMonsterIdx <= 0)
				{
					m_isWave02Clear = true;
					m_isWave03Clear = false;
					m_isWave03Render = true;
					m_isStage0Clear = true;
					m_nowMonsterIdx = 75;
					return;
				}
			}

		}
		if (m_nowMonsterIdx > 0)
			m_nowMonsterIdx = 75;
	}
}

//
//void Stage01::Wave03()
//{
//	CVector2D direct;
//	if (m_isWave03Render) // 두번째 웨이브 렌더가 트루가 되면 (처음 들어오면 트루가 됨)
//	{
//		int countclose3 = 0;
//		int countclose4 = 0;
//		int countclose6 = 0;
//
//		for (int i = 0; i < m_CloseIdx; i++)
//		{
//			CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[i]);
//			if (object->m_DoorNum == 3 )
//			{
//				countclose3++;
//				if (5 <= countclose3 <= 10)
//				{
//					object->m_isAlive = false;
//					direct = object->m_pos.DistanceTo(CVector2D(2500 + (i * 70), 500));
//					object->m_pos.x += direct.x * 2.f;
//					object->m_pos.y += direct.y * 2.f;
//					//CameraMove(FirstCameraPos);
//					object->m_status = eMyStatus::MOVELEFT;
//				}
//				/*CCameraObject::GetInsance()->SetObjPos(CPlayerObject::GetInstance());
//				Camera::GetInsance()->ChangeObject(CCameraObject::GetInsance());
//				CCameraObject::GetInsance()->ChangeSpeed(10.f);*/
//			}
//			else if (object->m_DoorNum == 4)
//			{
//				countclose4++;
//				if (5 <= countclose4 <= 10)
//				{
//					object->m_isAlive = false;
//					if (isChangeCamera)
//					{
//						direct = object->m_pos.DistanceTo(CVector2D(2500 + (i * 70), 2500));
//						object->m_pos.x += direct.x * 2.0f;
//						object->m_pos.y += direct.y * 2.0f;
//					}
//					object->m_status = eMyStatus::MOVELEFT;
//				}
//			}
//			else if (object->m_DoorNum == 5)
//			{
//				object->m_isAlive = false;
//				if (isChangeCamera)
//				{
//					direct = object->m_pos.DistanceTo(CVector2D(400, 1450 + (i * 50)));
//					object->m_pos.x += direct.x * 2.0f;
//					object->m_pos.y += direct.y * 2.0f;
//				}
//				object->m_status = eMyStatus::MOVELEFT;
//			}
//			else if (object->m_DoorNum == 6)
//			{
//				countclose6++;
//				if (6 <= countclose6 <= 12)
//				{
//					object->m_isAlive = false;
//					if (isChangeCamera)
//					{
//						direct = object->m_pos.DistanceTo(CVector2D(2500, 1450 - (i * 70)));
//						object->m_pos.x += direct.x * 2.0f;
//						object->m_pos.y += direct.y * 2.0f;
//					}
//					object->m_status = eMyStatus::MOVELEFT;
//				}
//			}
//		}
//		int countRange3 = 0;
//		int countRange4 = 0;
//		int countRange6 = 0;
//		for (int i = 0; i < m_RangeIdx; i++)
//		{
//			CRangeObject* object = dynamic_cast<CRangeObject*>(CObjectManager::GetInstance()->RangeObjectPool[i]);
//			if (object->m_DoorNum == 3)
//			{
//				countRange3++;
//				if (2 <= countRange3 <= 4)
//				{
//					object->m_isAlive = false;
//					direct = object->m_pos.DistanceTo(CVector2D(2000 + (i * 70), 500));
//					object->m_pos.x += direct.x * 2.0f;
//					object->m_pos.y += direct.y * 2.0f;
//					object->m_status = eMyStatus::MOVELEFT;
//				}
//			}
//			else if (object->m_DoorNum == 4)
//			{
//				countRange4++;
//				if (2 <= countRange4 <= 4)
//				{
//					object->m_isAlive = false;
//					if (isChangeCamera)
//					{
//						direct = object->m_pos.DistanceTo(CVector2D(2000 + (i * 70), 2500));
//						object->m_pos.x += direct.x * 2.0f;
//						object->m_pos.y += direct.y * 2.0f;
//					}
//					object->m_status = eMyStatus::MOVELEFT;
//				}
//			}
//			else if (object->m_DoorNum == 6)
//			{
//				countRange6++;
//				if (2 <= countRange6 <= 3)
//				{
//					object->m_isAlive = false;
//					if (isChangeCamera)
//					{
//						direct = object->m_pos.DistanceTo(CVector2D(2000, 1450 - (i * 70)));
//						object->m_pos.x += direct.x * 2.0f;
//						object->m_pos.y += direct.y * 2.0f;
//					}
//					object->m_status = eMyStatus::MOVELEFT;
//				}
//			}
//		}
//		m_time += 0.1f;
//		if (m_time >= 30.0f)
//		{
//			m_isMove = true;
//		}
//		else
//		{
//			int countclose3 = 0;
//			int countclose4 = 0;
//			int countclose6 = 0;
//
//			for (int i = 0; i < m_CloseIdx; i++)
//			{
//				CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[i]);
//				if (object->m_DoorNum == 3)
//				{
//					countclose3++;
//					if (5 <= countclose3 <= 10)
//					{
//						object->m_isAlive = true;
//						CObjectManager::GetInstance()->CloseObjectPool[i]->m_Intro = true;
//					}
//				}
//				else if (object->m_DoorNum == 4)
//				{
//					countclose3++;
//					if (5 <= countclose4 <= 10)
//					{
//						object->m_isAlive = true;
//						CObjectManager::GetInstance()->CloseObjectPool[i]->m_Intro = true;
//					}
//				}
//				else if (object->m_DoorNum == 5)
//				{
//					object->m_isAlive = true;
//					CObjectManager::GetInstance()->CloseObjectPool[i]->m_Intro = true;
//				}
//				else if (object->m_DoorNum == 6)
//				{
//					countclose3++;
//					if (6 <= countclose6 <= 12)
//					{
//						object->m_isAlive = true;
//						CObjectManager::GetInstance()->CloseObjectPool[i]->m_Intro = true;
//					}
//				}
//			}
//			int countRange3 = 0;
//			int countRange4 = 0;
//			int countRange6 = 0;
//			for (int i = 0; i < m_RangeIdx; i++)
//			{
//				CRangeObject* object = dynamic_cast<CRangeObject*>(CObjectManager::GetInstance()->RangeObjectPool[i]);
//				if (object->m_DoorNum == 3)
//				{
//					countRange3++;
//					if (2 <= countRange3 <= 4)
//					{
//						object->m_isAlive = true;
//						object->m_pos = CVector2D(2000, 1000 + (i * 80));
//						object->m_status = eMyStatus::ATTACKLEFT;
//					}
//					//object->m_moveSpd = 3.0f;
//				}
//				else if (object->m_DoorNum == 4)
//				{
//					countRange4++;
//					if (2 <= countRange4 <= 4)
//					{
//						object->m_isAlive = true;
//						object->m_pos = CVector2D(3000, 500 + (i * 80));
//						object->m_status = eMyStatus::ATTACKLEFT;
//					}
//					//object->m_moveSpd = 3.0f;
//				}
//				else if (object->m_DoorNum == 6)
//				{
//					countRange6++;
//					if (2 <= countRange6 <= 3)
//					{
//						object->m_isAlive = true;
//						object->m_pos = CVector2D(3000, 1600 + (i * 40));
//						object->m_status = eMyStatus::ATTACKLEFT;
//					}
//					//object->m_moveSpd = 3.0f;
//				}
//			}
//			m_isWave02Render = false;
//		}
//	}
//
//	else // 몬스터가 죽는걸 판단해서 현재 맵에 있는 몬스터의 수로 다음 웨이브로 넘어간다. 
//	{
//		for (int i = 0; i < m_CloseIdx; i++)
//		{
//			CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[i]);
//			if (object->m_totalStatus == eToTalStatus::DIE)
//			{
//				m_nowMonsterIdx--;
//				if (m_nowMonsterIdx == 0)
//					m_isStage0Clear = true;
//			}
//
//		}
//		for (int i = 0; i < m_RangeIdx; i++)
//		{
//			CRangeObject* object = dynamic_cast<CRangeObject*>(CObjectManager::GetInstance()->RangeObjectPool[i]);
//			if (object->m_totalStatus == eToTalStatus::DIE)
//			{
//				m_nowMonsterIdx--;
//				if (m_nowMonsterIdx <<= 0)
//				{
//					m_isWave03Clear = true;
//					m_isWave03Render = true;
//				}
//			}
//
//		}
//		if (m_nowMonsterIdx > 0)
//			m_nowMonsterIdx = 54;
//	}
//}
//

void Stage01::CameraMove(CVector2D pos)
{
	if (!CCameraObject::GetInsance()->isGoal)
		CCameraObject::GetInsance()->ChangePos(pos.x, pos.y); // 어디로
}

void Stage01::CameraSet(CObjectBase* startobject, CObjectBase* moveobject)
{
	CCameraObject::GetInsance()->SetObjPos(startobject); // player
	Camera::GetInsance()->ChangeObject(moveobject);	// Cameraobject
	CCameraObject::GetInsance()->ChangeSpeed(3.f); // 속도
}


// 처음 들어올때 오브젝트들의 좌표를 설정해두고 숨겨둔다.
void Stage01::SetCloseObject()
{
	CameraSet(CPlayerObject::GetInstance(), CCameraObject::GetInsance());
	CObjectManager::GetInstance()->InitCloseMonster();
	for (int i = 0; i < 10; i++)
	{
		CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]);
		object->m_isRender = true;
		object->m_isAlive = false;
		object->m_DoorNum = 1;
		//FirstCameraPos.x = object->m_pos.x + 500;
		//FirstCameraPos.y = object->m_pos.y;
		CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]->m_pos = CVector2D(950, -10);
		FirstCameraPos.x = CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]->m_pos.x;
		FirstCameraPos.y = CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]->m_pos.y;
		m_CloseIdx++;
	}
	for (int i = 0; i < 10; i++)
	{
		CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]);
		object->m_isRender = true;
		object->m_isAlive = false;
		object->m_DoorNum = 2;
		/*SecondCameraPos.x = object->m_pos.x;
		SecondCameraPos.y = object->m_pos.y;*/
		CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]->m_pos = CVector2D(950, 2900);
		SecondCameraPos.x = CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]->m_pos.x;
		SecondCameraPos.y = CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]->m_pos.y;
		m_CloseIdx++;
	}
	for (int i = 0; i < 15; i++)
	{
		CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]);
		object->m_isRender = true;
		object->m_isAlive = false;
		object->m_DoorNum = 3;
		CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]->m_pos = CVector2D(3150, 50);
		m_CloseIdx++;
	}
	for (int i = 0; i < 15; i++)
	{
		CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]);
		object->m_isRender = true;
		object->m_isAlive = false;
		object->m_DoorNum = 4;
		CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]->m_pos = CVector2D(3150, 2900);
		m_CloseIdx++;
	}
	for (int i = 0; i < 15; i++)
	{
		CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]);
		object->m_isRender = true;
		object->m_isAlive = false;
		object->m_DoorNum = 6;
		CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]->m_pos = CVector2D(4300, 1450);
		m_CloseIdx++;
	}
	for (int i = 0; i < 10; i++)
	{
		CCloseObject* object = dynamic_cast<CCloseObject*>(CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]);
		object->m_isRender = true;
		object->m_isAlive = false;
		object->m_DoorNum = 5;
		CObjectManager::GetInstance()->CloseObjectPool[m_CloseIdx]->m_pos = CVector2D(-10, 1450);
		m_CloseIdx++;
	}

}
void Stage01::SetRangeObject()
{
	int temp = 0;
	// RangeObject 이동 좌표 설정하기 
	CObjectManager::GetInstance()->InitRangeMonster();
	for (int i = 0; i < 3; i++)
	{
		CRangeObject* object = dynamic_cast<CRangeObject*>(CObjectManager::GetInstance()->RangeObjectPool[m_RangeIdx]);
		object->m_isRender = true;
		object->m_DoorNum = 1;
		object->m_moveSpd = 0;
		object->MoveToPos(CVector2D(1290, 610), CVector2D(1290, 610), CVector2D(1290, 610));
		CObjectManager::GetInstance()->RangeObjectPool[m_RangeIdx]->m_pos = CVector2D(950, -10);
		m_RangeIdx++;
	}
	for (int i = 0; i < 3; i++)
	{
		CRangeObject* object = dynamic_cast<CRangeObject*>(CObjectManager::GetInstance()->RangeObjectPool[m_RangeIdx]);
		object->m_isRender = true;
		object->m_DoorNum = 2;
		object->m_moveSpd = 0;
		object->MoveToPos(CVector2D(1288, 2324), CVector2D(1288, 2324), CVector2D(1288, 2324));
		CObjectManager::GetInstance()->RangeObjectPool[m_RangeIdx]->m_pos = CVector2D(950, 2900);
		m_RangeIdx++;
	}
	for (int i = 0; i < 5; i++)
	{
		CRangeObject* object = dynamic_cast<CRangeObject*>(CObjectManager::GetInstance()->RangeObjectPool[m_RangeIdx]);
		object->m_isRender = true;
		object->m_DoorNum = 6;
		object->m_moveSpd = 0;
		object->MoveToPos(CVector2D(2921, 606), CVector2D(2921, 606), CVector2D(2921, 606));
		CObjectManager::GetInstance()->RangeObjectPool[m_RangeIdx]->m_pos = CVector2D(4300, 1450);
		m_RangeIdx++;
	}
	for (int i = 0; i < 5; i++)
	{
		CRangeObject* object = dynamic_cast<CRangeObject*>(CObjectManager::GetInstance()->RangeObjectPool[m_RangeIdx]);
		object->m_isRender = true;
		object->m_DoorNum = 3;
		object->m_moveSpd = 0;
		CObjectManager::GetInstance()->RangeObjectPool[m_RangeIdx]->m_pos = CVector2D(3150, 50);
		m_RangeIdx++;
	}
	for (int i = 0; i < 4; i++)
	{
		CRangeObject* object = dynamic_cast<CRangeObject*>(CObjectManager::GetInstance()->RangeObjectPool[m_RangeIdx]);
		object->m_isRender = true;
		object->m_DoorNum = 4;
		object->m_moveSpd = 0;

		CObjectManager::GetInstance()->RangeObjectPool[m_RangeIdx]->m_pos = CVector2D(3150, 2900);
		m_RangeIdx++;
	}
}

void Stage01::End()
{
	for (int i = 0; i < CObjectManager::GetInstance()->CloseObjectPool.size(); i++)
	{
		CObjectManager::GetInstance()->CloseObjectPool[i]->m_isRender = false;
	}
	for (int i = 0; i < CObjectManager::GetInstance()->RangeObjectPool.size(); i++)
	{
		CObjectManager::GetInstance()->RangeObjectPool[i]->m_isRender = false;
	}
}
