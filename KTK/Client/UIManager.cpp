#include "UIManager.h"
#include "CSprite.h"
#include "YDEngine.h"
#include "AnimationManager.h"
#include "CAnimationClip.h"
#include "CAnimator.h"
#include "CPlayerObject.h"
#include "Transform.h"
#include "SceneManager.h"
#include <vector>

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::Initialize(YDEngine* engine)
{
	m_pEngine = engine;
	m_player = CPlayerObject::GetInstance();

	// ������ ��� ��ǥ�� ����� �ش�.
	m_playerHpPos = CVector2D(400, 0);
	m_playerDashPos = CVector2D(600, 0);
	m_playerSuperPos = CVector2D(800, 0);

}

void UIManager::Update()
{
}

void UIManager::Render()
{
	DrawSprite();
}

void UIManager::DrawSprite()
{
	//if (SceneManager::GetInstance()->m_sceneNumber == 0)
	//{
	//	PlayIntroUI();
	//}

	if (m_player == nullptr)
		return;

	PlayerHPUI();
//	PlayerDieUI();
	//PlayerSuperUI();

}

// �÷��̾� HP�� ����ϴ� UI
void UIManager::PlayerHPUI()
{

	AnimationManager::GetInstance()->UI();
	/*CSprite* sprite = AnimationManager::GetInstance()->m_playerHpUI->GetFram(AnimationManager::GetInstance()->m_playerHpAnim->GetCurrentIdx());

	for (int i = 0; i < m_player->GetHp(); i++)
		*/
		//m_pEngine->DrawSprite(sprite, sprite->m_sheetPos.x, sprite->m_sheetPos.y, m_playerHpPos.x + (sprite->m_sheetWidth * i), m_playerHpPos.y, 1);
}

// �÷��̾� Dash�� ����ϴ� UI
void UIManager::PlayerDieUI()
{
	CSprite* sprite = AnimationManager::GetInstance()->m_playerHpDieUI->GetFram(AnimationManager::GetInstance()->m_playerHpDieAnim->GetCurrentIdx());

	for (int i = 0; i < (3-m_player->GetHp()); i++)
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos.x, sprite->m_sheetPos.y, m_playerDashPos.x + (sprite->m_sheetWidth * i), m_playerDashPos.y, 1);
}

/// <summary>
/// �÷��̾� �ʻ�⸦ ����ϴ� UI
/// ���� ��������Ʈ�� ������ 10�徲�� �� ���Ŀ� ���� �Լ��� ������ �ʿ���.
/// </summary>
void UIManager::PlayerSuperUI()
{
	CSprite* sprite = AnimationManager::GetInstance()->m_playerSuperUI->GetFram(AnimationManager::GetInstance()->m_playerSuperAnim->GetCurrentIdx());

	for (int i = 0; i < m_player->GetSuper(); i++)
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos.x, sprite->m_sheetPos.y, m_playerSuperPos.x + (sprite->m_sheetWidth * i), m_playerSuperPos.y, 1);
}

//void UIManager::PlayIntroUI()
//{
//	/*CSprite* sprite = AnimationManager::GetInstance()->m_introUI->GetFram(AnimationManager::GetInstance()->m_introAnim->GetCurrentIdx());*/
//
//	AnimationManager::GetInstance()->m_introAnim->Play();
//
//	//m_pEngine->DrawSprite(sprite, sprite->m_sheetPos.x, sprite->m_sheetPos.y, 0, 0, 1);
//}
