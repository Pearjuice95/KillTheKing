#include "CPlayerObject.h"
#include "CInput.h"
#include "Win32.h"
#include "AnimationManager.h"
#include "Time.h"
#include "enum.h"
#include "Transform.h"
#include "CVector2D.h"
#include "CAnimator.h"
#include "CObjectManager.h"
#include "CRangeObject.h"
#include "CCloseObject.h"
#include "Sound.h"
#include <d2d1helper.h>

#define DASHDISTANCE 200
#define HALFDISTANCE 140
#define MOVEDISTANCE 6
#define HALFMOVE 4.25
#define ATTACKMOVE 15

CPlayerObject::CPlayerObject()
	: CObjectBase(CVector2D(200, 100), eObjectKind::PLAYER), m_dashTime(20), m_dashCur(0), m_atkTime(30),
	m_atkCur(0), m_secondAtkTime(15), m_secondAtkCur(0), m_isSecond(false), m_dashAtkCur(0), m_dashAtkTIme(20),
	m_superCount(50), m_superTime(600), m_superCur(0), m_dashCount(2), m_hitCur(0), m_hitTime(18), m_superUseCur(0), m_superUseTime(60),
	m_dieCur(0), m_dieTime(60)
{

}

CPlayerObject::~CPlayerObject()
{
}

void CPlayerObject::Initialize()
{
	//SetCollidertRect();
	m_transform = new Transform();
	m_transform->SetLocalPosition(m_pos);
	m_transform->SetLocalRotation(0.f);
	m_transform->SetLocalScale(CVector2D(1, 1));
	m_DashPos = m_pos;
	m_HP = 5;
	m_canControl = true;
}

void CPlayerObject::Update()
{

	m_DashPos = m_pos;

	if (m_isDie)
	{
		m_isCollide = false;

		m_dieCur++;
		if (m_dieCur >= m_dieTime)
		{
			m_totalStatus = eToTalStatus::DIE;
			if (m_prevMove == eMyStatus::IDLEUP)
			{
				m_status = eMyStatus::DIEUP;
			}

			else if (m_prevMove == eMyStatus::IDLEDOWN)
			{
				m_status = eMyStatus::DIEDOWN;
			}

			else if (m_prevMove == eMyStatus::IDLELEFT)
			{
				m_status = eMyStatus::DIELEFT;
			}

			else if (m_prevMove == eMyStatus::IDLERIGHT)
			{
				m_status = eMyStatus::DIERIGHT;
			}

			else
			{
				m_status = eMyStatus::DIELEFT;
			}

			m_totalStatus = eToTalStatus::DIE;
			m_isDie = false;
			m_dieCur = 0;
		}
	}

	if (m_useSuper)
	{
		m_superUseCur += 1;
		if (m_superUseCur >= m_superUseTime)
		{
			m_superUseCur = 0;
			m_useSuper = false;
			m_isSuper = true;
			m_status = eMyStatus::IDLEDOWN;
			m_totalStatus = eToTalStatus::IDLE;
		}
	}
	if (m_isSuper)
	{
		m_atkTime = 15;
		m_moveSpd = 2;
		m_dmg = 2;
		m_dashTime = 10;
		m_dashAtkTIme = 10;

		m_superCur += 1;
		if (m_superCur >= m_superTime && m_totalStatus != eToTalStatus::ATTACK && m_totalStatus != eToTalStatus::DASHATTACK)
		{
			m_isSuper = false;
			m_superCur = 0;
		}
	}

	if (!m_isSuper)
	{
		m_atkTime = 30;
		m_moveSpd = 1;
		m_dmg = 1;
		m_dashTime = 20;
		m_dashAtkTIme = 20;
	}

	if (m_totalStatus == eToTalStatus::HIT)
	{
		m_hitCur += 1;
		m_prevStatus = m_status;

		if (m_hitCur >= m_hitTime)
		{
			m_hitCur = 0;
			m_status = m_prevMove;
			m_totalStatus = eToTalStatus::IDLE;
		}
	}

	if (m_isCollide == true)
	{
		m_prevPos = m_pos;
		// 대쉬일때
		if (m_totalStatus == eToTalStatus::DASH)
		{
			m_dashCur += 1;

			if (m_dashCur >= m_dashTime)
			{
				//m_prevStatus = m_status;
				m_status = m_prevMove;
				m_dashCur = 0;
				m_totalStatus = eToTalStatus::IDLE;
			}

			else if ((CInput::GetInstance()->Key_Down('X')))
			{
				//m_animator->ResetCurrentIdx();
				m_totalStatus = eToTalStatus::DASHATTACK;
				m_hitBoss = false;
				if (m_status == eMyStatus::AFTERDASHUP || m_status == eMyStatus::SAFTERDASHUP)
				{
					if (m_isSuper)
					{
						m_status = eMyStatus::SDASHATTACKUP;
						SoundPlay(8);
					}

					else
					{
						m_status = eMyStatus::DASHATTACKUP;
						SoundPlay(3);
					}
				}

				else if (m_status == eMyStatus::AFTERDASHUPLEFT || m_status == eMyStatus::SAFTERDASHUPLEFT)
				{
					if (m_isSuper)
					{
						m_status = eMyStatus::SDASHATTACKUP;
						SoundPlay(8);
					}

					else
					{
						m_status = eMyStatus::DASHATTACKUP;
						SoundPlay(3);
					}
				}

				else if (m_status == eMyStatus::AFTERDASHDOWN || m_status == eMyStatus::SAFTERDASHDOWN)
				{
					if (m_isSuper)
					{
						m_status = eMyStatus::SDASHATTACKDOWN;
						SoundPlay(8);
					}
					else
					{
						m_status = eMyStatus::DASHATTACKDOWN;
						SoundPlay(3);
					}
				}

				else if (m_status == eMyStatus::AFTERDASHDOWNRIGHT || m_status == eMyStatus::SAFTERDASHDOWNRIGHT)
				{
					if (m_isSuper)
					{
						m_status = eMyStatus::SDASHATTACKDOWN;
						SoundPlay(8);
					}
					else
					{
						m_status = eMyStatus::DASHATTACKDOWN;
						SoundPlay(3);
					}
				}

				else if (m_status == eMyStatus::AFTERDASHRIGHT || m_status == eMyStatus::SAFTERDASHRIGHT)
				{
					if (m_isSuper)
					{
						m_status = eMyStatus::SDASHATTACKRIGHT;
						SoundPlay(8);
					}
					else
					{
						m_status = eMyStatus::DASHATTACKRIGHT;
						SoundPlay(3);
					}
				}

				else if (m_status == eMyStatus::AFTERDASHUPRIGHT || m_status == eMyStatus::SAFTERDASHUPRIGHT)
				{
					if (m_isSuper)
					{
						m_status = eMyStatus::SDASHATTACKRIGHT;
						SoundPlay(8);
					}
					else
					{
						m_status = eMyStatus::DASHATTACKRIGHT;
						SoundPlay(3);
					}
				}

				else if (m_status == eMyStatus::AFTERDASHLEFT || m_status == eMyStatus::SAFTERDASHLEFT)
				{
					if (m_isSuper)
					{
						m_status = eMyStatus::SDASHATTACKLEFT;
						SoundPlay(8);
					}
					else
					{
						m_status = eMyStatus::DASHATTACKLEFT;
						SoundPlay(3);
					}
				}

				else if (m_status == eMyStatus::AFTERDASHDOWNLEFT || m_status == eMyStatus::SAFTERDASHDOWNLEFT)
				{
					if (m_isSuper)
					{
						m_status = eMyStatus::SDASHATTACKLEFT;
						SoundPlay(8);
					}
					else
					{
						m_status = eMyStatus::DASHATTACKLEFT;
						SoundPlay(3);
					}
				}

				else
				{
					m_status = m_prevMove;
					m_totalStatus = eToTalStatus::IDLE;
				}
			}
		}

		// 공격일때
		else if (m_status == eMyStatus::ATTACKUP || m_status == eMyStatus::ATTACKDOWN || m_status == eMyStatus::ATTACKLEFT || m_status == eMyStatus::ATTACKRIGHT ||
			m_status == eMyStatus::SATTACKUP || m_status == eMyStatus::SATTACKDOWN || m_status == eMyStatus::SATTACKLEFT || m_status == eMyStatus::SATTACKRIGHT)
		{
			if (CInput::GetInstance()->Key_Down('X'))
			{
				m_isSecond = true;
			}

			m_atkCur += 1;
			m_prevStatus = m_status;

			if (m_atkCur >= m_atkTime)
			{
				//m_prevStatus = m_status;
				//m_animator->ResetCurrentIdx();
				m_atkCur = 0;


				// 어쩔수없소
				for (int i = 0; i < CObjectManager::GetInstance()->CloseObjectPool.size(); i++)
				{
					if (CObjectManager::GetInstance()->CloseObjectPool[i]->m_isHit)
					{
						CObjectManager::GetInstance()->CloseObjectPool[i]->m_HP -= m_dmg;
						CObjectManager::GetInstance()->CloseObjectPool[i]->m_isHit = false;
					}

					else
						break;
				}

				for (int i = 0; i < CObjectManager::GetInstance()->RangeObjectPool.size(); i++)
				{
					if (CObjectManager::GetInstance()->RangeObjectPool[i]->m_isHit)
					{
						CObjectManager::GetInstance()->RangeObjectPool[i]->m_HP -= m_dmg;
						CObjectManager::GetInstance()->RangeObjectPool[i]->m_isHit = false;
					}

					else
						break;
				}

				if (m_isSecond == true)
				{
					m_hitBoss = false;
					m_totalStatus = eToTalStatus::DASHATTACK;
					/*m_animator->ResetCurrentIdx();
					m_animator->ResetLoadingTime();*/
					if (m_status == eMyStatus::ATTACKUP || m_status == eMyStatus::SATTACKUP)
					{
						if (m_isSuper)
						{
							m_pos.y -= ATTACKMOVE;
							m_status = eMyStatus::SDASHATTACKUP;
							SoundPlay(8);
						}
						else
						{
							m_pos.y -= ATTACKMOVE;
							m_status = eMyStatus::DASHATTACKUP;
							SoundPlay(3);
						}
					}

					else if (m_status == eMyStatus::ATTACKDOWN || m_status == eMyStatus::SATTACKDOWN)
					{
						if (m_isSuper)
						{
							m_pos.y += ATTACKMOVE;
							m_status = eMyStatus::SDASHATTACKDOWN;
							SoundPlay(8);
						}
						else
						{
							m_pos.y += ATTACKMOVE;
							m_status = eMyStatus::DASHATTACKDOWN;
							SoundPlay(3);
						}
					}

					else if (m_status == eMyStatus::ATTACKRIGHT || m_status == eMyStatus::SATTACKRIGHT)
					{
						if (m_isSuper)
						{
							m_pos.x += ATTACKMOVE;
							m_status = eMyStatus::SDASHATTACKRIGHT;
							SoundPlay(8);
						}
						else
						{
							m_pos.x += ATTACKMOVE;
							m_status = eMyStatus::DASHATTACKRIGHT;
							SoundPlay(3);
						}
					}

					else if (m_status == eMyStatus::ATTACKLEFT || m_status == eMyStatus::SATTACKLEFT)
					{
						if (m_isSuper)
						{
							m_pos.x -= ATTACKMOVE;
							m_status = eMyStatus::SDASHATTACKLEFT;
							SoundPlay(8);
						}
						else
						{
							m_pos.x -= ATTACKMOVE;
							m_status = eMyStatus::DASHATTACKLEFT;
							SoundPlay(3);
						}
					}

					m_isSecond = false;
				}

				else
				{
					m_status = m_prevMove;
					m_totalStatus = eToTalStatus::IDLE;
					AnimationManager::GetInstance()->FrameResetEffect();

				}
			}
		}

		// 대쉬공격 
		if (m_status == eMyStatus::DASHATTACKUP || m_status == eMyStatus::DASHATTACKDOWN || m_status == eMyStatus::DASHATTACKRIGHT || m_status == eMyStatus::DASHATTACKLEFT ||
			m_status == eMyStatus::SDASHATTACKUP || m_status == eMyStatus::SDASHATTACKDOWN || m_status == eMyStatus::SDASHATTACKRIGHT || m_status == eMyStatus::SDASHATTACKLEFT)
		{
			m_dashAtkCur += 1;

			if (m_dashAtkCur >= m_dashAtkTIme)
			{
				m_status = m_prevMove;
				m_dashAtkCur = 0;
				m_totalStatus = eToTalStatus::IDLE;
				AnimationManager::GetInstance()->FrameResetEffect();
				if (m_isDmg)
				{
					SoundPlay(16);
					m_isDmg = false;
				}

			}
		}

		// 공격, 대쉬, 대쉬 공격을 안할때
		if (m_totalStatus == eToTalStatus::MOVE || m_totalStatus == eToTalStatus::IDLE)
			PlayerInput();
	}
	//if (m_isSecond)
	//{
	//	m_secondAtkCur += 1;
	//	m_prevStatus = m_status;
	//	if (m_secondAtkCur >= m_secondAtkTime)
	//	{
	//		m_status = m_prevMove;
	//		m_secondAtkCur = 0;
	//	}
	//}

	//if (m_status != eMyStatus::AFTERDASHUP && m_status != eMyStatus::AFTERDASHDOWN && m_status != eMyStatus::AFTERDASHRIGHT && m_status != eMyStatus::AFTERDASHLEFT)
	//SetCollidertRect();
	m_transform->SetPosition(m_pos); // transform이 가져야하는 player 좌표를 실시간으로 바꿔준다.
}

void CPlayerObject::Render(CVector2D cvector)
{
	if (SceneManager::GetInstance()->m_sceneNumber == 0 || SceneManager::GetInstance()->m_sceneNumber == 5)
		return;

	else
		AnimationManager::GetInstance()->DrawSprite(this, 1, cvector);
}

// 좌상단을 받아오고 width, height를 받아온다. 그에따른 Rect를 지정
void CPlayerObject::SetCollidertRect(CVector2D pos, CVector2D resize)
{
	CVector2D lefttop;
	lefttop.x = pos.x - resize.x / 2;
	lefttop.y = pos.y - resize.y / 2;

	RECT rect{ lefttop.x, lefttop.y, lefttop.x + resize.x, lefttop.y + resize.y };

	m_colliderRect = rect;
}

void CPlayerObject::PlusSuper()
{
	if (m_superCount >= 50 || m_isSuper == true)
		return;

	else
	{
		m_superCount++;
		if (m_superCount == 50)
		{
			SoundPlay(23);
		}
	}
}

RECT CPlayerObject::GetRECT()
{
	return m_colliderRect;
}

void CPlayerObject::HPDown(int damage)
{
	if (m_totalStatus != eToTalStatus::HIT)
	{
		AnimationManager::GetInstance()->FrameResetEffect();
		m_animator->ResetLoadingTime();
		m_HP -= damage;
		SoundPlay(4);
		if (m_HP <= 0)
		{
			SoundPlay(5);
			m_isDie = true;
			PlayStop();
		}
		else
		{
			m_totalStatus = eToTalStatus::HIT;
			if (m_prevMove == eMyStatus::IDLEUP)
			{
				m_status = eMyStatus::HITUP;
			}

			else if (m_prevMove == eMyStatus::IDLEDOWN)
			{
				m_status = eMyStatus::HITDOWN;
			}

			else if (m_prevMove == eMyStatus::IDLELEFT)
			{
				m_status = eMyStatus::HITLEFT;
			}

			else if (m_prevMove == eMyStatus::IDLERIGHT)
			{
				m_status = eMyStatus::HITRIGHT;
			}

			else
			{
				m_status = eMyStatus::HITDOWN;
			}
		}
	}
}

void CPlayerObject::PlayerInput()
{

	m_prevStatus = m_status;
	// test
	//CVector2D Up(0, -3);
	// 기본 이동
	if (m_canControl)
	{
		if (m_isWalk == false && CInput::GetInstance()->Key_Down(VK_UP)) // && 충돌체크 ++
		{
			m_isWalk = true;

			PlayWalk();
		}

		else if (m_isWalk == false && CInput::GetInstance()->Key_Down(VK_DOWN)) // && 충돌체크 ++
		{
			m_isWalk = true;

			PlayWalk();
		}

		else if (m_isWalk == false && CInput::GetInstance()->Key_Down(VK_LEFT)) // && 충돌체크 ++
		{
			m_isWalk = true;

			PlayWalk();
		}

		else if (m_isWalk == false && CInput::GetInstance()->Key_Down(VK_RIGHT)) // && 충돌체크 ++
		{
			m_isWalk = true;

			PlayWalk();
		}

		if (m_isWalk == true && !CInput::GetInstance()->Key_Press(VK_UP) && !CInput::GetInstance()->Key_Press(VK_DOWN) && !CInput::GetInstance()->Key_Press(VK_LEFT) &&
			!CInput::GetInstance()->Key_Press(VK_RIGHT)) // && 충돌체크 ++
		{
			m_isWalk = false;

			PlayStop();
		}

		if (CInput::GetInstance()->Key_Press(VK_UP)) // && 충돌체크 ++
		{
			m_totalStatus = eToTalStatus::MOVE;
			m_prevMove = eMyStatus::IDLEUP;
			if (CInput::GetInstance()->Key_Press(VK_LEFT))
			{
				m_pos.y -= HALFMOVE * m_moveSpd;
				m_pos.x -= HALFMOVE * m_moveSpd;

				if (m_isSuper)
					m_status = eMyStatus::SMOVEUP;

				else
					m_status = eMyStatus::MOVEUP;
			}

			else if (CInput::GetInstance()->Key_Press(VK_RIGHT))
			{
				m_pos.y -= HALFMOVE * m_moveSpd;
				m_pos.x += HALFMOVE * m_moveSpd;

				if (m_isSuper)
					m_status = eMyStatus::SMOVERIGHT;

				else
					m_status = eMyStatus::MOVERIGHT;
			}

			else
			{//m_transform->Translate(Up);
				m_pos.y -= MOVEDISTANCE * m_moveSpd;
				if (m_isSuper)
					m_status = eMyStatus::SMOVEUP;

				else
					m_status = eMyStatus::MOVEUP;
			}
		}

		else if (CInput::GetInstance()->Key_Press(VK_LEFT))
		{
			if (m_isSuper)
				m_status = eMyStatus::SMOVELEFT;

			else
				m_status = eMyStatus::MOVELEFT;

			m_totalStatus = eToTalStatus::MOVE;
			m_prevMove = eMyStatus::IDLELEFT;

			if (CInput::GetInstance()->Key_Press(VK_DOWN))
			{
				m_pos.y += HALFMOVE * m_moveSpd;
				m_pos.x -= HALFMOVE * m_moveSpd;
			}
			// test
			//m_transform->SetLocalRotation(m_transform->GetLocalRotation() + 90.f);
			else
				m_pos.x -= MOVEDISTANCE * m_moveSpd;
		}

		else if (CInput::GetInstance()->Key_Press(VK_DOWN))
		{
			if (m_isSuper)
				m_status = eMyStatus::SMOVEDOWN;
			else
				m_status = eMyStatus::MOVEDOWN;

			m_totalStatus = eToTalStatus::MOVE;
			m_prevMove = eMyStatus::IDLEDOWN;

			if (CInput::GetInstance()->Key_Press(VK_RIGHT))
			{
				m_pos.y += HALFMOVE * m_moveSpd;
				m_pos.x += HALFMOVE * m_moveSpd;
			}

			else
				m_pos.y += MOVEDISTANCE * m_moveSpd;
		}

		else if (CInput::GetInstance()->Key_Press(VK_RIGHT))
		{
			if (m_isSuper)
				m_status = eMyStatus::SMOVERIGHT;
			else
				m_status = eMyStatus::MOVERIGHT;

			m_totalStatus = eToTalStatus::MOVE;
			m_prevMove = eMyStatus::IDLERIGHT;

			m_pos.x += MOVEDISTANCE * m_moveSpd;
		}

		if (CInput::GetInstance()->Key_Up(VK_UP))
		{
			m_status = m_prevMove;
			m_totalStatus = eToTalStatus::IDLE;
		}


		if (CInput::GetInstance()->Key_Up(VK_LEFT))
		{
			m_status = m_prevMove;
			m_totalStatus = eToTalStatus::IDLE;
		}


		if (CInput::GetInstance()->Key_Up(VK_DOWN))
		{
			m_status = m_prevMove;
			m_totalStatus = eToTalStatus::IDLE;
		}

		if (CInput::GetInstance()->Key_Up(VK_RIGHT))
		{
			m_status = m_prevMove;
			m_totalStatus = eToTalStatus::IDLE;
		}


		//if (CInput::GetInstance()->Key_Down(VK_SHIFT))
		//{
		//	// test
		//	m_transform->SetLocalRotation(m_transform->GetLocalRotation() + 90.f);
		//}

		if (CInput::GetInstance()->Key_Down('Z'))
		{
			if (m_superCount >= 50 && m_isSuper == false)
			{
				SoundPlay(6);
				m_useSuper = true;
				m_superCount = 0;
				m_status = eMyStatus::SUPERUSE;
				m_totalStatus = eToTalStatus::SUPER;
			}
		}
		// 대시
		/*if (CInput::GetInstance()->Key_Down(VK_SPACE) && CInput::GetInstance()->Key_Press('W') && CInput::GetInstance()->Key_Press('D'))
		{
			m_status = static_cast<int> (MyStatus::DASH);
			m_Pos.y -= 30;
			m_Pos.x += 30;
		}

		if (CInput::GetInstance()->Key_Down(VK_SPACE) && CInput::GetInstance()->Key_Press('A') && CInput::GetInstance()->Key_Press('W'))
		{
			m_status = static_cast<int> (MyStatus::DASH);
			m_Pos.y -= 30;
			m_Pos.x -= 30;
		}

		if (CInput::GetInstance()->Key_Down(VK_SPACE) && CInput::GetInstance()->Key_Press('S') && CInput::GetInstance()->Key_Press('A'))
		{
			m_status = static_cast<int> (MyStatus::DASH);
			m_Pos.y += 30;
			m_Pos.x -= 30;
		}

		if (CInput::GetInstance()->Key_Down(VK_SPACE) && CInput::GetInstance()->Key_Press('D') && CInput::GetInstance()->Key_Press('S'))
		{
			m_status = static_cast<int> (MyStatus::DASH);
			m_Pos.y += 30;
			m_Pos.x += 30;
		}*/

		if (CInput::GetInstance()->Key_Down(VK_SPACE))
		{
			AnimationManager::GetInstance()->FrameResetEffect();
			SoundPlay(1);

			if (m_status == eMyStatus::MOVEUP || m_status == eMyStatus::IDLEUP || m_status == eMyStatus::SMOVEUP)
			{
				/*	if (CInput::GetInstance()->Key_Press(VK_LEFT))
					{
						if (!m_isSuper)
						{
							m_DashPos.y -= HALFDISTANCE;
							m_DashPos.x -= HALFDISTANCE;
							m_status = eMyStatus::AFTERDASHUPLEFT;
						}

						else if (m_isSuper)
						{
							m_DashPos.y -= HALFDISTANCE * 2;
							m_DashPos.x -= HALFDISTANCE * 2;
							m_status = eMyStatus::SAFTERDASHUPLEFT;
						}
					}*/

					/*else
					{*/
				if (!m_isSuper)
				{
					m_DashPos.y -= DASHDISTANCE;
					m_status = eMyStatus::AFTERDASHUP;
				}

				else if (m_isSuper)
				{
					m_DashPos.y -= DASHDISTANCE * 2;
					m_status = eMyStatus::SAFTERDASHUP;
				}
				//}

				//m_prevStatus = eMyStatus::AFTERDASHUP;
				m_totalStatus = eToTalStatus::DASH;
			}

			else if (m_status == eMyStatus::SMOVELEFT || m_status == eMyStatus::MOVELEFT || m_status == eMyStatus::IDLELEFT)
			{
				//if (CInput::GetInstance()->Key_Press(VK_DOWN))
				//{
				//	if (!m_isSuper)
				//	{
				//		m_DashPos.y += HALFDISTANCE;
				//		m_DashPos.x -= HALFDISTANCE;
				//		//m_prevStatus = eMyStatus::AFTERDASHUP;
				//		m_status = eMyStatus::AFTERDASHDOWNLEFT;
				//	}

				//	else if (m_isSuper)
				//	{
				//		m_DashPos.y += HALFDISTANCE * 2;
				//		m_DashPos.x -= HALFDISTANCE * 2;
				//		//m_prevStatus = eMyStatus::AFTERDASHUP;
				//		m_status = eMyStatus::SAFTERDASHDOWNLEFT;
				//	}
				//}

				//else
				//{

				if (!m_isSuper)
				{
					m_DashPos.x -= DASHDISTANCE;
					m_status = eMyStatus::AFTERDASHLEFT;
				}

				else if (m_isSuper)
				{
					m_DashPos.x -= DASHDISTANCE * 2;
					m_status = eMyStatus::SAFTERDASHLEFT;
				}
				//}

				//m_prevStatus = eMyStatus::AFTERDASHLEFT;
				m_totalStatus = eToTalStatus::DASH;
			}

			else if (m_status == eMyStatus::SMOVEDOWN || m_status == eMyStatus::MOVEDOWN || m_status == eMyStatus::IDLEDOWN)
			{
				//if (CInput::GetInstance()->Key_Press(VK_RIGHT))
				//{
				//	if (!m_isSuper)
				//	{
				//		m_DashPos.y += HALFDISTANCE;
				//		m_DashPos.x += HALFDISTANCE;
				//		//m_prevStatus = eMyStatus::AFTERDASHLEFT;
				//		m_status = eMyStatus::AFTERDASHDOWNRIGHT;
				//	}

				//	else if (m_isSuper)
				//	{
				//		m_DashPos.y += HALFDISTANCE * 2;
				//		m_DashPos.x += HALFDISTANCE * 2;
				//		//m_prevStatus = eMyStatus::AFTERDASHLEFT;
				//		m_status = eMyStatus::SAFTERDASHDOWNRIGHT;
				//	}
				//}

				//else
				//{
				if (!m_isSuper)
				{
					m_DashPos.y += DASHDISTANCE;
					m_status = eMyStatus::AFTERDASHDOWN;
				}

				else if (m_isSuper)
				{
					m_DashPos.y += DASHDISTANCE * 2;
					m_status = eMyStatus::SAFTERDASHDOWN;
				}
				//}
				m_totalStatus = eToTalStatus::DASH;
			}

			else if (m_status == eMyStatus::SMOVERIGHT || m_status == eMyStatus::MOVERIGHT || m_status == eMyStatus::IDLERIGHT)
			{

				/*	if (CInput::GetInstance()->Key_Press(VK_UP))
					{
						if (!m_isSuper)
						{
							m_DashPos.y -= HALFDISTANCE;
							m_DashPos.x += HALFDISTANCE;
							m_status = eMyStatus::AFTERDASHUPRIGHT;
						}

						else
						{
							m_DashPos.y -= HALFDISTANCE * 2;
							m_DashPos.x += HALFDISTANCE * 2;
							m_status = eMyStatus::SAFTERDASHUPRIGHT;
						}
					}

					else
					{*/
				if (!m_isSuper)
				{
					m_DashPos.x += DASHDISTANCE;
					m_status = eMyStatus::AFTERDASHRIGHT;
				}

				else
				{
					m_DashPos.x += DASHDISTANCE * 2;
					m_status = eMyStatus::SAFTERDASHRIGHT;
				}
				//}
				m_totalStatus = eToTalStatus::DASH;
			}
		}

		if (CInput::GetInstance()->Key_Down('X'))
		{
			AnimationManager::GetInstance()->FrameResetEffect();
			m_hitBoss = false;
			m_isDmg = false;
			if (CInput::GetInstance()->Key_Press(VK_UP))
			{
				//m_prevStatus = eMyStatus::ATTACKUP;
				if (!m_isSuper)
				{
					m_pos.y -= ATTACKMOVE;
					m_status = eMyStatus::ATTACKUP;
					SoundPlay(2);
				}

				else
				{
					m_pos.y -= ATTACKMOVE;
					m_status = eMyStatus::SATTACKUP;
					SoundPlay(7);
				}

				m_totalStatus = eToTalStatus::ATTACK;
			}

			else if (CInput::GetInstance()->Key_Press(VK_LEFT))
			{
				//m_prevStatus = eMyStatus::ATTACKLEFT;
				if (!m_isSuper)
				{
					m_pos.x -= ATTACKMOVE;
					m_status = eMyStatus::ATTACKLEFT;
					SoundPlay(2);
				}

				else
				{
					m_pos.x -= ATTACKMOVE;
					m_status = eMyStatus::SATTACKLEFT;
					SoundPlay(7);
				}

				m_totalStatus = eToTalStatus::ATTACK;
			}

			else if (CInput::GetInstance()->Key_Press(VK_RIGHT))
			{
				//m_prevStatus = eMyStatus::ATTACKRIGHT;
				if (!m_isSuper)
				{
					m_pos.x += ATTACKMOVE;
					m_status = eMyStatus::ATTACKRIGHT;
					SoundPlay(2);
				}
				else
				{
					m_pos.x += ATTACKMOVE;
					m_status = eMyStatus::SATTACKRIGHT;
					SoundPlay(7);
				}
				m_totalStatus = eToTalStatus::ATTACK;
			}

			else if (CInput::GetInstance()->Key_Press(VK_DOWN))
			{
				//m_prevStatus = eMyStatus::ATTACKDOWN;
				if (!m_isSuper)
				{
					m_pos.y += ATTACKMOVE;
					m_status = eMyStatus::ATTACKDOWN;
					SoundPlay(2);
				}
				else
				{
					m_pos.y += ATTACKMOVE;
					m_status = eMyStatus::SATTACKDOWN;
					SoundPlay(7);
				}
				m_totalStatus = eToTalStatus::ATTACK;
			}

			else
			{
				if (m_status == eMyStatus::IDLEUP)
				{
					//m_prevStatus = eMyStatus::ATTACKUP;
					if (!m_isSuper)
					{
						m_pos.y -= ATTACKMOVE;
						m_status = eMyStatus::ATTACKUP;
						SoundPlay(2);
					}
					else
					{
						m_pos.y -= ATTACKMOVE;
						m_status = eMyStatus::SATTACKUP;
						SoundPlay(7);
					}
					m_totalStatus = eToTalStatus::ATTACK;
				}

				else if (m_status == eMyStatus::IDLEDOWN)
				{
					//m_prevStatus = eMyStatus::ATTACKDOWN;
					if (!m_isSuper)
					{
						m_pos.y += ATTACKMOVE;
						m_status = eMyStatus::ATTACKDOWN;
						SoundPlay(2);
					}
					else
					{
						m_pos.y += ATTACKMOVE;
						m_status = eMyStatus::SATTACKDOWN;
						SoundPlay(7);
					}
					m_totalStatus = eToTalStatus::ATTACK;
				}

				else if (m_status == eMyStatus::IDLELEFT)
				{
					//m_prevStatus = eMyStatus::ATTACKLEFT;
					if (!m_isSuper)
					{
						m_pos.x -= ATTACKMOVE;
						m_status = eMyStatus::ATTACKLEFT;
						SoundPlay(2);
					}
					else
					{
						m_pos.x -= ATTACKMOVE;
						m_status = eMyStatus::SATTACKLEFT;
						SoundPlay(7);
					}
					m_totalStatus = eToTalStatus::ATTACK;
				}

				else if (m_status == eMyStatus::IDLERIGHT)
				{
					//m_prevStatus = eMyStatus::ATTACKRIGHT;
					if (!m_isSuper)
					{
						m_pos.x += ATTACKMOVE;
						m_status = eMyStatus::ATTACKRIGHT;
						SoundPlay(2);
					}
					else
					{
						m_pos.x += ATTACKMOVE;
						m_status = eMyStatus::SATTACKRIGHT;
						SoundPlay(7);
					}
					m_totalStatus = eToTalStatus::ATTACK;
				}
			}

		}
	}

	else
		PlayStop();

	if (m_prevStatus != m_status)
	{
		AnimationManager::GetInstance()->SetStatus(this);
	}

	//else if (!m_isWalk)
	//{
	//	SoundStop(34);
	//}
	// 순서가 중요함 SET -> GET 순서로 해야함(별표 5개)
	m_transform->SetLocalPosition(m_pos);
	m_pos = m_transform->GetLocalPosition();
	//else if (CInput::GetInstance()->Key_Down(VK_SPACE) && CInput::GetInstance()->Key_Press('A'))
	//{
	//	m_status = static_cast<int> (MyStatus::DASH);
	//	m_Pos.x -= 30;
	//}

	//else if (CInput::GetInstance()->Key_Down(VK_SPACE) && CInput::GetInstance()->Key_Press('S'))
	//{
	//	m_status = static_cast<int> (MyStatus::DASH);
	//	m_Pos.y += 30;
	//}


	//else if (CInput::GetInstance()->Key_Down(VK_SPACE) && CInput::GetInstance()->Key_Press('D'))
	//{
	//	m_status = static_cast<int> (MyStatus::DASH);
	//	m_Pos.x += 30;
	//}
}

//void CPlayerObject::DealDamage()
//{
//	if (m_prevStatus == eMyStatus::ATTACKDOWN || m_prevStatus == eMyStatus::ATTACKUP || m_prevStatus == eMyStatus::ATTACKLEFT || m_prevStatus == eMyStatus::ATTACKRIGHT ||
//		m_prevStatus == eMyStatus::DASHATTACKUP || m_prevStatus == eMyStatus::DASHATTACKDOWN || m_prevStatus == eMyStatus::DASHATTACKLEFT || m_prevStatus == eMyStatus::DASHATTACKRIGHT ||
//		m_prevStatus == eMyStatus::SATTACKUP || m_prevStatus == eMyStatus::SATTACKDOWN || m_prevStatus == eMyStatus::SATTACKLEFT || m_prevStatus == eMyStatus::SATTACKRIGHT ||
//		m_prevStatus == eMyStatus::SDASHATTACKUP || m_prevStatus == eMyStatus::SDASHATTACKDOWN || m_prevStatus == eMyStatus::SDASHATTACKRIGHT || m_prevStatus == eMyStatus::SDASHATTACKLEFT)
//	{
//		if (m_totalStatus != eToTalStatus::ATTACK && m_totalStatus != eToTalStatus::DASHATTACK)
//		{
//			for (int i = 0; i < )
//		}
//	}
//}
