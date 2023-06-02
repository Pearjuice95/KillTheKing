#include "SceneManager.h"
#include "YDEngine.h"
#include "CBackGroundObject.h"
#include "CTitle.h"
#include "Stage00.h"
#include "Stage01.h"
#include "Stage02.h"
#include "Stage03.h"
#include "CEnding.h"
#include "Camera.h"
#include "CAnimationClip.h"
#include "CAnimator.h"
#include "CSprite.h"
#include "AnimationManager.h"
#include "Sound.h"
#include "CInput.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Initialize(YDEngine* engine)
{
	m_pEngine = engine;
	m_pBackGround = CBackGroundObject::GetInstance();
	m_pBackGround->InitMap();
	m_prevStage = (eScene)m_sceneNumber;
	m_isFadein = true;
	// �� ���� �����Ѵ�. 
	m_TitleStage = new CTitle;
	m_stage00 = new Stage00;
	m_stage01 = new Stage01;
	m_stage02 = new Stage02;
	m_stage03 = new Stage03;
	m_EndingStage = new CEnding;

	m_TitleStage->Initialize();

	Camera::GetInsance()->WallException(m_sceneNumber);
	//m_scenePool.push_back(m_stage00);
	AnimationManager::GetInstance()->m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/Gate/GateOpen.png");					// 16 �������� 0�� ȭ�鿡 �̹���
	GateOpen = AnimationManager::GetInstance()->LoadSpriteFormData(16, 1, CVector2D(0, 0), 1, 211, 462, CVector2D(0.f, 0.f), 0.3f); // ���� �ʱ�ȭ
}

void SceneManager::Update()
{
	SceneStatus();

	if (CInput::GetInstance()->Key_Down('P'))
	{
		if (m_sceneNumber == 0)
		{
			m_prevStage = eScene::STAGE03;
			m_sceneNumber = 4;
		}
	}
}

void SceneManager::Render()
{
	CSprite* sprite;
	// ����ȭ�鿡 �°� ����Ѵ�. 
	if (m_sceneNumber == 0)
	{
		sprite = AnimationManager::GetInstance()->m_creditAnim->GetAnimationClip()->GetFram(AnimationManager::GetInstance()->m_creditAnim->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, 0, 0, 0, 0, 1);
		AnimationManager::GetInstance()->m_creditAnim->Play();
	}
	else if (m_sceneNumber == 5)
	{
		sprite = AnimationManager::GetInstance()->m_endingAnim->GetAnimationClip()->GetFram(AnimationManager::GetInstance()->m_endingAnim->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, 0, 0, 0, 0, 1);
		AnimationManager::GetInstance()->m_endingAnim->Play();
		//m_pEngine->DrawMapSprite(m_pBackGround->m_backgroundSprite[m_sceneNumber], 0, 0, 0, 0, 1, Camera::GetInsance()->GetCameraVector());
	}
	else
		m_pEngine->DrawMapSprite(m_pBackGround->m_backgroundSprite[m_sceneNumber], 0, 0, 0, 0, 1, Camera::GetInsance()->GetCameraVector());
	//switch (m_prevStage)
	//{
	//case eScene::TITLE:
	//	break;
	//case eScene::STAGE00:
	//	m_pEngine->DrawRect(m_stage00->m_goalBox, 255, 255, 255);
	//	//m_stage00->Render();
	//	break;
	//case eScene::STAGE01:
	//	m_pEngine->DrawRect(m_stage01->m_goalBox, 255, 255, 255);
	//	break;
	//case eScene::STAGE02:
	//	m_pEngine->DrawRect(m_stage02->m_goalBox, 255, 255, 255);
	//	break;
	//case eScene::STAGE03:
	//	//m_pEngine->DrawRect(m_stage03->m_goalBox, 255, 255, 255);
	//	break;
	//case eScene::ENDING:
	//	break;
	//default:
	//	break;
	//}
	SceneStatus();
}

void SceneManager::SceneStatus()
{
	switch (m_prevStage)
	{
		case eScene::TITLE:		// Ÿ��Ʋ
		{
			if (m_TitleStage->Update())
			{
				// KeyInput
			}
			else
			{
				EndTitle();
				//	NextScene();
			}
		}
		break;
		case eScene::STAGE00:	//Ʃ��
		{
			if (m_isLoad == false)
				LoadStage00();
			if (!m_isNextScene)
			{
				if (m_stage00->Update())
				{
					m_stage00->Render();
				}
				else
					m_isNextScene = true;
			}
			else
			{
				EndStage00();
				//NextScene();
			}

		}
		break;
		case eScene::STAGE01:	// �������� 1
		{
			// �ε��� �ȵǾ� ������ �ε��� ���ش�.
			if (m_isLoad == false)
				LoadStage01();
			// ���� ������� �Ѿ�� Ʈ���Ű� ON�� �ȵǾ� ������ ������ ����ȴ�
			if (!m_isNextScene)
			{
				if (m_stage01->Update())
				{
					m_stage01->Render();
				}
				else
					m_isNextScene = true;
			}
			// ���� ���������� ������ ���������� ������ ���� ���������� ����.
			else
			{
				EndStage01();
				//NextScene();
			}
		}
		break;
		case eScene::STAGE02:	// �������� 2
		{
			if (m_isLoad == false)
				LoadStage02();
			if (!m_isNextScene)
			{
				if (m_stage02->Update())
				{
					m_stage02->Render();
					/*test++;
					if (test == 20)
						m_isNextScene = true;*/
				}
				else
					m_isNextScene = true;
			}
			// ���� ���������� ������ ���������� ������ ���� ���������� ����.
			else
			{
				EndStage02();

			}
		}
		break;
		case eScene::STAGE03:
			if (m_isLoad == false)
				LoadStage03();
			if (!m_isNextScene)
			{
				if (m_stage03->Update())
				{
					m_stage03->Render();
				}
				else
					m_isNextScene = true;
			}
			// ���� ���������� ������ ���������� ������ ���� ���������� ����.
			else
			{
				EndStage03();
				//NextScene();
			}
			break;
		case eScene::ENDING:
			break;
		default:
			break;
	}
}

void SceneManager::NextScene()
{
	m_sceneNumber++;
	m_prevStage = (eScene)m_sceneNumber;
	m_isNextScene = false;
}


void SceneManager::LoadTitle()
{
	m_isLoad = true; // �ε��� �Ǿ����Ƿ� �̸� true�� �ٲ��ش�.
	m_isEnd = false;
	//if (m_ready)
	//	m_isFadein = true; // �ε��Ǵ� ������ ȭ���� ��������Ѵ�.
		//BGMPause();
	BGM(9);
	m_TitleStage->SetObject(CVector2D(0, 0));
}

void SceneManager::EndTitle()
{
	if (m_wait)
	{
		m_timer += 0.1f;
		m_isFadein = false;
		if (m_timer >= 20.f)
		{
			m_timer = 0.f;
			m_isLoad = false;
			m_isEnd = true;
			m_wait = false;
			NextScene();
		}
	}
}

// Ʃ�縮�� �ε�
void SceneManager::LoadStage00()
{
	//m_sceneNumber = static_cast<int>(eScene::STAGE00);
	m_stage00->Initialize(GateOpen[0]);

	m_isLoad = true; // �ε��� �Ǿ����Ƿ� �̸� true�� �ٲ��ش�.
	m_isEnd = false;
	m_isFadein = true; // �ε��Ǵ� ������ ȭ���� ��������Ѵ�. 

	m_stage00->SetObject(CVector2D(150, 420)); // Ʃ�� 
	Camera::GetInsance()->WallException(m_sceneNumber);


	//m_curScene = m_scenePool[0];

	//m_curScene->Initialize();
}

void SceneManager::EndStage00()
{
	if (m_wait)
	{
		m_timer += 0.1f;
		m_isFadein = false;
		if (m_timer >= 20.f)
		{
			m_timer = 0.f;
			m_isLoad = false;
			m_isEnd = true;
			m_wait = false;
			NextScene();
		}
	}

}

void SceneManager::LoadStage01()
{
	//m_sceneNumber = eScene::STAGE01;
	m_isLoad = true; // �ε��� �Ǿ����Ƿ� �̸� true�� �ٲ��ش�.
	m_isEnd = false;
	m_isFadein = true; // �ε��Ǵ� ������ ȭ���� ��������Ѵ�. 


	m_stage01->SetObject(CVector2D(400, 1450)); // �������� 1�� �ҷ��ش�. 
	m_stage01->Initialize();
	Camera::GetInsance()->WallException(m_sceneNumber);

	//m_curScene = m_scenePool[1]; // ���� ��鿡 Ǯ�� �ִ� ���� �ִ´�. 

	//m_curScene->Initialize();	// �׸��� ���� ����� �ʱ�ȭ �Ѵ�.
}


void SceneManager::LoadStage02()
{
	m_isLoad = true; 
	m_isEnd = false;
	m_isFadein = true; 

	m_stage02->SetObject(CVector2D(950, 2700));  
	m_stage02->Initialize();
	Camera::GetInsance()->WallException(m_sceneNumber);
}

void SceneManager::LoadStage03()
{
	m_isLoad = true; // �ε��� �Ǿ����Ƿ� �̸� true�� �ٲ��ش�.
	m_isEnd = false;
	m_isFadein = true; // �ε��Ǵ� ������ ȭ���� ��������Ѵ�.

	m_stage03->SetObject(CVector2D(1110, 4080)); // �������� 3�� �ҷ��ش�. 
	m_stage03->Initialize();
	Camera::GetInsance()->WallException(m_sceneNumber);
}

void SceneManager::EndStage01()
{
	if (m_wait)
	{
		m_timer += 0.1f;
		m_isFadein = false;
		if (m_timer >= 20.f)
		{
			m_timer = 0.f;
			m_isLoad = false;
			m_isEnd = true;
			m_wait = false;
			NextScene();
		}
	}


	//LoadStage02(); // ���� �ð��� �帥�� ����ؾ��Ѵ�.
}

void SceneManager::EndStage02()
{
	if (m_wait)
	{
		m_timer += 0.1f;
		m_isFadein = false;
		if (m_timer >= 20.f)
		{
			m_timer = 0.f;
			m_isLoad = false;
			m_isEnd = true;
			m_wait = false;
			NextScene();
		}
	}
}

void SceneManager::EndStage03()
{
	if (m_wait)
	{
		m_timer += 0.1f;
		m_isFadein = false;
		if (m_timer >= 20.f)
		{
			m_timer = 0.f;
			m_isLoad = false;
			m_isEnd = true;
			m_wait = false;
			NextScene();
		}
	}
}



void SceneManager::ReStart()
{

}

void SceneManager::LoadTitleScene()
{

}

void SceneManager::LoadDieScene()
{

}

void SceneManager::LoadEndingScene()
{

}

void SceneManager::FadeInOut()
{
	if (!m_isFadein)
	{

		m_pEngine->FadeInOut(m_fadeinCount);
		if (1 <= m_fadeinCount)
			m_fadeinCount = 1;

		else
			m_fadeinCount += 0.02f;
	}

	else if (m_isFadein)
	{
		m_pEngine->FadeInOut(m_fadeinCount);
		if (m_fadeinCount <= 0)
		{
			m_fadeinCount = 0;
			m_wait = true;
		}
		else
			m_fadeinCount -= 0.005f;
	}

}
