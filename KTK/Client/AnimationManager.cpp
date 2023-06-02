#include "AnimationManager.h"
#include "CAnimationClip.h"
#include "CAnimator.h"
#include "CVector2D.h"
#include "YDEngine.h"
#include "CSprite.h"
#include "GameProcess.h"
#include "enum.h"
#include "CObjectBase.h"
#include "CCloseObject.h"
#include "Transform.h"
#include "CRangeObject.h"
#include "CPlayerObject.h"
#include "CBossObject.h"
#include "SceneManager.h"
#include <vector>

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::Initialize(YDEngine* engine)
{
	m_pEngine = engine;

	LoadingSheet();
	ObjectInit();
	UIObjectInit();
	EffectInit();
}

void AnimationManager::Update()
{
}

void AnimationManager::LoadingSheet()
{
	// 스프라이트 시트를 불러옴
	// Object Sprite Load
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/ObjectSheet/PlayerSheet.png");					// 0
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/ObjectSheet/CloseSheet.png");					// 1
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/ObjectSheet/BossSheet.png");					// 2	
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/ObjectSheet/PlayerSuperSheet.png");			// 3
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/ObjectSheet/RangeSheet.png");					// 4
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/ObjectSheet/PlayerSuperUseSheet.png");			// 5

	// UI Sprite Load
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/UI/Stage00_UI.png");							// 6
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/UI/UISheet.png");								// 7

	//Effect Sprite Load
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/Effect/playereffect.png");						// 8
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/Effect/superplayereffect.png");				// 9
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/Effect/playerdasheffect.png");					// 10
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/Effect/monstereffect.png");					// 11
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/Effect/BossEffectSheet.png");					// 12 그림자 시트

	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/CreditSheet.png");						// 13 그림자 시트
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/CreditSheet.png");						// 14 그림자 시트
	m_pEngine->LoadSpriteSheet(L"../Resourse/SpriteSheet/EndingSheet.png");						// 15 그림자 시트

}

#pragma region Init
void AnimationManager::ObjectInit()
{
	//각 애니메이션마다 벡터를 생성하면 됨
	//애니메이션 스프라이트를 가지고 있는 벡터 생성
#pragma region vector<CSprite*>
	static std::vector<CSprite*> playerAtkUp;
	static std::vector<CSprite*> playerAtkDown;
	static std::vector<CSprite*> playerAtkRight;
	static std::vector<CSprite*> playerAtkLeft;

	static std::vector<CSprite*> playerSuperAtkUp;
	static std::vector<CSprite*> playerSuperAtkDown;
	static std::vector<CSprite*> playerSuperAtkRight;
	static std::vector<CSprite*> playerSuperAtkLeft;

	static std::vector<CSprite*> playerMoveUp;
	static std::vector<CSprite*> playerMoveDown;
	static std::vector<CSprite*> playerMoveRight;
	static std::vector<CSprite*> playerMoveLeft;

	static std::vector<CSprite*> playerSuperMoveUp;
	static std::vector<CSprite*> playerSuperMoveDown;
	static std::vector<CSprite*> playerSuperMoveRight;
	static std::vector<CSprite*> playerSuperMoveLeft;

	static std::vector<CSprite*> playerDashUp;
	static std::vector<CSprite*> playerIDLEUp;
	static std::vector<CSprite*> playerDashDown;
	static std::vector<CSprite*> playerDashRight;
	static std::vector<CSprite*> playerDashLeft;

	static std::vector<CSprite*> playerSuperDashUp;
	static std::vector<CSprite*> playerSuperDashDown;
	static std::vector<CSprite*> playerSuperDashRight;
	static std::vector<CSprite*> playerSuperDashLeft;

	static std::vector<CSprite*> playerHitUp;
	static std::vector<CSprite*> playerHitDown;
	static std::vector<CSprite*> playerHitRight;
	static std::vector<CSprite*> playerHitLeft;

	static std::vector<CSprite*> playerDashAtkUp;
	static std::vector<CSprite*> playerDashAtkDown;
	static std::vector<CSprite*> playerDashAtkRight;
	static std::vector<CSprite*> playerDashAtkLeft;

	static std::vector<CSprite*> playerSuperDashAtkUp;
	static std::vector<CSprite*> playerSuperDashAtkDown;
	static std::vector<CSprite*> playerSuperDashAtkRight;
	static std::vector<CSprite*> playerSuperDashAtkLeft;

	static std::vector<CSprite*> playerDieUp;
	static std::vector<CSprite*> playerDieDown;
	static std::vector<CSprite*> playerDieRight;
	static std::vector<CSprite*> playerDieLeft;

	static std::vector<CSprite*> playerIDLEDown;
	static std::vector<CSprite*> playerIDLERight;
	static std::vector<CSprite*> playerIDLELeft;

	static std::vector<CSprite*> playerUseSuper;

	static std::vector<CSprite*> closeAtkRight;
	static std::vector<CSprite*> closeAtkLeft;

	static std::vector<CSprite*> closeIDLERight;
	static std::vector<CSprite*> closeIDLELeft;

	static std::vector<CSprite*> closeMoveRight;
	static std::vector<CSprite*> closeMoveLeft;

	static std::vector<CSprite*> closeMove2Right;
	static std::vector<CSprite*> closeMove2Left;

	static std::vector<CSprite*> closeHitRight;
	static std::vector<CSprite*> closeHitLeft;

	static std::vector<CSprite*> closeDieRight;
	static std::vector<CSprite*> closeDieLeft;

	static std::vector<CSprite*> wall;

	static std::vector<CSprite*> bossIDLELEFT;
	static std::vector<CSprite*> bossIDLERIGHT;
	static std::vector<CSprite*> bossJumpLeft;
	static std::vector<CSprite*> bossJumpRight;
	static std::vector<CSprite*> bossDieLeft;
	static std::vector<CSprite*> bossDieRight;
	static std::vector<CSprite*> bossStampLeft;
	static std::vector<CSprite*> bossStampRight;
	static std::vector<CSprite*> bossAttackLeft;
	static std::vector<CSprite*> bossAttackRight;

	static std::vector<CSprite*> bossShadowLargetoSmall;
	static std::vector<CSprite*> bossShadowSmalltoLarge;

	static std::vector<CSprite*> rangeAtkRight;
	static std::vector<CSprite*> rangeAtkLeft;

	static std::vector<CSprite*> rangeIDLERight;
	static std::vector<CSprite*> rangeIDLELeft;

	static std::vector<CSprite*> rangeMoveRight;
	static std::vector<CSprite*> rangeMoveLeft;

	static std::vector<CSprite*> rangeHitRight;
	static std::vector<CSprite*> rangeHitLeft;

	static std::vector<CSprite*> rangeDieRight;
	static std::vector<CSprite*> rangeDieLeft;


	// 스프라이트 시트를 불러옴
#pragma endregion vector<CSprite*>

#pragma region SpriteDataInput
	//스프라이트를 짤라서 넣음
	/*CSprite* WalkAnimOne = m_pEngine->LoadSpriteFromData(0, CVector2D(7, 69), 18, 26, CVector2D(0.5f, 0.5f), 0.3f);
	CSprite* WalkAnimTwo = m_pEngine->LoadSpriteFromData(0, CVector2D(36, 69), 18, 26, CVector2D(0.5f, 0.5f), 0.3f);
	CSprite* WalkAnimThree = m_pEngine->LoadSpriteFromData(0, CVector2D(69, 69), 18, 26, CVector2D(0.5f, 0.5f), 0.3f);*/

	playerAtkUp = LoadSpriteFormData(0, 4, CVector2D(0, 0), 0, 171, 159, CVector2D(-0.2f, -0.5f), 0.125f);
	playerAtkDown = LoadSpriteFormData(0, 4, CVector2D(0, 165), 0, 171, 131, CVector2D(0.0f, 0.2f), 0.125f);
	playerAtkRight = LoadSpriteFormData(0, 4, CVector2D(0, 304), 0, 167, 107, CVector2D(0.0f, -0.3f), 0.125f);
	playerAtkLeft = LoadSpriteFormData(0, 4, CVector2D(0, 2448), 0, 168, 107, CVector2D(0.0f, -0.3f), 0.125f);

	playerSuperAtkUp = LoadSpriteFormData(3, 7, CVector2D(0, 3200), 0, 399, 399, CVector2D(0.f, 0.f), 0.035f);
	playerSuperAtkDown = LoadSpriteFormData(3, 7, CVector2D(0, 2800), 0, 399, 399, CVector2D(0.0f, 0.0f), 0.035f);
	playerSuperAtkRight = LoadSpriteFormData(3, 7, CVector2D(0, 2000), 0, 399, 399, CVector2D(0.0f, 0.f), 0.035f);
	playerSuperAtkLeft = LoadSpriteFormData(3, 7, CVector2D(0, 2400), 0, 399, 399, CVector2D(0.0f, 0.f), 0.035f);

	playerMoveUp = LoadSpriteFormData(0, 4, CVector2D(0, 432), 0, 83, 95, CVector2D(0.f, 0.f), 0.3f);
	playerMoveDown = LoadSpriteFormData(0, 4, CVector2D(0, 531), 0, 87, 91, CVector2D(0.f, 0.f), 0.3f);
	playerMoveRight = LoadSpriteFormData(0, 4, CVector2D(0, 627), 0, 71, 83, CVector2D(0.f, -0.2f), 0.3f);
	playerMoveLeft = LoadSpriteFormData(0, 4, CVector2D(0, 2560), 0, 71, 83, CVector2D(0.f, -0.3f), 0.3f);

	playerSuperMoveUp = LoadSpriteFormData(3, 3, CVector2D(0, 750), 0, 249, 249, CVector2D(0.f, 0.f), 0.15f);
	playerSuperMoveDown = LoadSpriteFormData(3, 4, CVector2D(0, 500), 0, 249, 249, CVector2D(0.f, 0.f), 0.15f);
	playerSuperMoveRight = LoadSpriteFormData(3, 4, CVector2D(0, 0), 0, 249, 249, CVector2D(0.f, 0.f), 0.15f);
	playerSuperMoveLeft = LoadSpriteFormData(3, 4, CVector2D(0, 250), 0, 249, 249, CVector2D(0.f, 0.f), 0.15f);

	// 대쉬 애니메이션이 어색하다
	playerDashUp = LoadSpriteFormData(0, 4, CVector2D(0, 758), 0, 87, 95, CVector2D(0.f, 0.f), 0.144f);
	playerDashDown = LoadSpriteFormData(0, 4, CVector2D(0, 856), 0, 91, 79, CVector2D(0.f, 0.f), 0.144f);
	playerDashRight = LoadSpriteFormData(0, 4, CVector2D(0, 945), 0, 87, 75, CVector2D(0.f, 0.2f), 0.144f);
	playerDashLeft = LoadSpriteFormData(0, 4, CVector2D(0, 2648), 0, 87, 75, CVector2D(0.f, 0.2f), 0.144f);

	playerSuperDashUp = LoadSpriteFormData(3, 7, CVector2D(0, 1750), 0, 249, 249, CVector2D(0.f, 0.f), 0.04f);
	playerSuperDashDown = LoadSpriteFormData(3, 7, CVector2D(0, 1500), 0, 249, 249, CVector2D(0.f, 0.f), 0.04f);
	playerSuperDashRight = LoadSpriteFormData(3, 8, CVector2D(0, 1000), 0, 249, 249, CVector2D(0.f, 0.0f), 0.04f);
	playerSuperDashLeft = LoadSpriteFormData(3, 8, CVector2D(0, 1250), 0, 249, 249, CVector2D(0.f, 0.0f), 0.04f);

	playerHitUp = LoadSpriteFormData(0, 3, CVector2D(0, 1050), 0, 79, 91, CVector2D(0.f, 0.f), 0.1f);
	playerHitDown = LoadSpriteFormData(0, 3, CVector2D(0, 1144), 0, 83, 91, CVector2D(0.f, 0.f), 0.1f);
	playerHitRight = LoadSpriteFormData(0, 3, CVector2D(0, 1238), 0, 75, 75, CVector2D(0.f, 0.f), 0.1f);
	playerHitLeft = LoadSpriteFormData(0, 3, CVector2D(0, 2726), 0, 75, 75, CVector2D(0.f, 0.f), 0.1f);

	playerDashAtkUp = LoadSpriteFormData(0, 4, CVector2D(0, 1350), 0, 91, 151, CVector2D(0.f, 0.f), 0.08f);
	playerDashAtkDown = LoadSpriteFormData(0, 4, CVector2D(0, 1504), 0, 99, 135, CVector2D(0.f, 0.f), 0.08f);
	playerDashAtkRight = LoadSpriteFormData(0, 4, CVector2D(0, 1644), 0, 143, 91, CVector2D(0.f, 0.f), 0.08f);
	playerDashAtkLeft = LoadSpriteFormData(0, 4, CVector2D(0, 2806), 0, 143, 91, CVector2D(0.f, 0.f), 0.08f);

	playerSuperDashAtkUp = LoadSpriteFormData(3, 7, CVector2D(0, 4800), 0, 399, 399, CVector2D(0.f, 0.f), 0.022f);
	playerSuperDashAtkDown = LoadSpriteFormData(3, 7, CVector2D(0, 4400), 0, 399, 399, CVector2D(0.f, 0.f), 0.022f);
	playerSuperDashAtkRight = LoadSpriteFormData(3, 7, CVector2D(0, 3600), 0, 399, 399, CVector2D(0.f, 0.f), 0.022f);
	playerSuperDashAtkLeft = LoadSpriteFormData(3, 7, CVector2D(0, 4000), 0, 399, 399, CVector2D(0.f, 0.f), 0.022f);

	playerDieUp = LoadSpriteFormData(0, 6, CVector2D(0, 1791), 1, 95, 99, CVector2D(0.f, 0.f), 0.3f);
	playerDieDown = LoadSpriteFormData(0, 6, CVector2D(0, 1895), 1, 103, 139, CVector2D(0.f, 0.f), 0.3f);
	playerDieRight = LoadSpriteFormData(0, 6, CVector2D(0, 2039), 1, 111, 70, CVector2D(0.f, 0.f), 0.3f);
	playerDieLeft = LoadSpriteFormData(0, 6, CVector2D(0, 2901), 1, 111, 70, CVector2D(0.f, 0.f), 0.3f);

	playerIDLEUp = LoadSpriteFormData(0, 4, CVector2D(0, 2144), 1, 79, 87, CVector2D(0.f, 0.f), 0.3f);
	playerIDLEDown = LoadSpriteFormData(0, 4, CVector2D(0, 2235), 1, 83, 79, CVector2D(0.f, 0.f), 0.3f);
	playerIDLERight = LoadSpriteFormData(0, 4, CVector2D(0, 2318), 1, 67, 75, CVector2D(0.f, 0.f), 0.3f);
	playerIDLELeft = LoadSpriteFormData(0, 4, CVector2D(0, 2975), 1, 67, 75, CVector2D(0.f, 0.f), 0.3f);

	playerUseSuper = LoadSpriteFormData(5, 15, CVector2D(0, 0), 0, 399, 399, CVector2D(0.f, 0.f), 0.06f);

	closeAtkRight = LoadSpriteFormData(1, 5, CVector2D(0, 1184), 0, 157, 115, CVector2D(0.f, 0.f), 0.3f);
	closeAtkLeft = LoadSpriteFormData(1, 5, CVector2D(0, 1300), 0, 157, 115, CVector2D(0.f, 0.f), 0.3f);

	closeIDLERight = LoadSpriteFormData(1, 4, CVector2D(0, 108), 0, 95, 87, CVector2D(0.f, 0.f), 0.3f);
	closeIDLELeft = LoadSpriteFormData(1, 4, CVector2D(0, 700), 0, 95, 87, CVector2D(0.f, 0.f), 0.3f);

	closeMoveRight = LoadSpriteFormData(1, 8, CVector2D(0, 201), 0, 103, 91, CVector2D(0.0f, 0.0f), 0.3f);
	closeMoveLeft = LoadSpriteFormData(1, 8, CVector2D(0, 793), 0, 103, 91, CVector2D(0.0f, 0.0f), 0.3f);

	closeMove2Right = LoadSpriteFormData(1, 8, CVector2D(0, 298), 0, 95, 91, CVector2D(0.0f, 0.0f), 0.3f);
	closeMove2Left = LoadSpriteFormData(1, 8, CVector2D(0, 890), 0, 95, 91, CVector2D(0.0f, 0.0f), 0.3f);

	closeHitRight = LoadSpriteFormData(1, 3, CVector2D(0, 395), 0, 107, 83, CVector2D(0.0f, 0.0f), 0.3f);
	closeHitLeft = LoadSpriteFormData(1, 3, CVector2D(0, 987), 0, 107, 83, CVector2D(0.0f, 0.0f), 0.3f);

	closeDieLeft = LoadSpriteFormData(1, 7, CVector2D(0, 1076), 0, 111, 83, CVector2D(0.0f, 0.0f), 0.3f);
	closeDieRight = LoadSpriteFormData(1, 7, CVector2D(0, 484), 0, 111, 83, CVector2D(0.0f, 0.0f), 0.3f);


	bossIDLELEFT = LoadSpriteFormData(2, 6, CVector2D(0, 0), 0, 299, 299, CVector2D(0.f, 0.f), 0.3f);
	bossIDLERIGHT = LoadSpriteFormData(2, 6, CVector2D(0, 300), 0, 299, 299, CVector2D(0.f, 0.f), 0.3f);
	bossJumpLeft = LoadSpriteFormData(2, 6, CVector2D(0, 600), 0, 299, 349, CVector2D(0.f, -0.3f), 0.08f);
	bossJumpRight = LoadSpriteFormData(2, 6, CVector2D(0, 950), 0, 299, 349, CVector2D(0.f, -0.3f), 0.08f);
	bossDieLeft = LoadSpriteFormData(2, 13, CVector2D(0, 1300), 0, 349, 299, CVector2D(0.f, 0.f), 0.9f);
	bossDieRight = LoadSpriteFormData(2, 13, CVector2D(0, 1600), 0, 349, 299, CVector2D(0.0f, 0.f), 0.9f);
	bossStampLeft = LoadSpriteFormData(2, 13, CVector2D(0, 1900), 0, 599, 579, CVector2D(0.0f, -0.2f), 0.15f);
	bossStampRight = LoadSpriteFormData(2, 13, CVector2D(0, 2480), 0, 599, 579, CVector2D(0.0f, -0.2f), 0.15f);
	bossAttackLeft = LoadSpriteFormData(2, 9, CVector2D(0, 3060), 0, 599, 479, CVector2D(-0.4f, 0.2f), 0.5f);
	bossAttackRight = LoadSpriteFormData(2, 9, CVector2D(0, 3540), 0, 599, 479, CVector2D(0.4f, 0.2f), 0.5f);

	bossShadowLargetoSmall = LoadSpriteFormData(12, 4, CVector2D(0, 200), 0, 279, 299, CVector2D(0.f, 0.f), 0.15);
	bossShadowSmalltoLarge = LoadSpriteFormData(12, 4, CVector2D(0, 500), 0, 279, 299, CVector2D(0.f, 0.f), 0.3);


#pragma endregion SpriteDataInput

	rangeIDLERight = LoadSpriteFormData(4, 4, CVector2D(0, 0), 0, 63, 83, CVector2D(0.f, 0.f), 0.3f);
	rangeIDLELeft = LoadSpriteFormData(4, 4, CVector2D(0, 473), 0, 63, 83, CVector2D(0.f, 0.f), 0.3f);

	rangeMoveRight = LoadSpriteFormData(4, 8, CVector2D(0, 90), 0, 63, 91, CVector2D(0.f, 0.f), 0.3f);
	rangeMoveLeft = LoadSpriteFormData(4, 8, CVector2D(0, 562), 0, 63, 91, CVector2D(0.f, 0.f), 0.3f);

	rangeAtkRight = LoadSpriteFormData(4, 3, CVector2D(0, 188), 0, 75, 75, CVector2D(0.f, 0.f), 0.1f);
	rangeAtkLeft = LoadSpriteFormData(4, 3, CVector2D(0, 659), 0, 75, 75, CVector2D(0.f, 0.f), 0.1f);

	rangeHitRight = LoadSpriteFormData(4, 3, CVector2D(0, 275), 0, 71, 80, CVector2D(0.0f, 0.0f), 0.3f);
	rangeHitLeft = LoadSpriteFormData(4, 3, CVector2D(0, 740), 0, 71, 80, CVector2D(0.0f, 0.0f), 0.3f);

	rangeDieRight = LoadSpriteFormData(4, 6, CVector2D(0, 364), 0, 84, 76, CVector2D(0.0f, 0.0f), 0.3f);
	rangeDieLeft = LoadSpriteFormData(4, 6, CVector2D(0, 825), 0, 84, 76, CVector2D(0.0f, 0.0f), 0.3f);

	//애니메이션 스프라이트를 벡터에 넣어줌
#pragma region InputAnimationClip
	static CAnimationClip* atkUpClip = new CAnimationClip(playerAtkUp, eMyStatus::ATTACKUP);
	static CAnimationClip* atkDownClip = new CAnimationClip(playerAtkDown, eMyStatus::ATTACKDOWN);
	static CAnimationClip* atkRightClip = new CAnimationClip(playerAtkRight, eMyStatus::ATTACKRIGHT);
	static CAnimationClip* atkLeftClip = new CAnimationClip(playerAtkLeft, eMyStatus::ATTACKLEFT);

	static CAnimationClip* superAtkUpClip = new CAnimationClip(playerSuperAtkUp, eMyStatus::SATTACKUP);
	static CAnimationClip* superAtkDownClip = new CAnimationClip(playerSuperAtkDown, eMyStatus::SATTACKDOWN);
	static CAnimationClip* superAtkRightClip = new CAnimationClip(playerSuperAtkRight, eMyStatus::SATTACKRIGHT);
	static CAnimationClip* superAtkLeftClip = new CAnimationClip(playerSuperAtkLeft, eMyStatus::SATTACKLEFT);

	static CAnimationClip* moveUpClip = new CAnimationClip(playerMoveUp, eMyStatus::MOVEUP);
	static CAnimationClip* moveDownClip = new CAnimationClip(playerMoveDown, eMyStatus::MOVEDOWN);
	static CAnimationClip* moveRightClip = new CAnimationClip(playerMoveRight, eMyStatus::MOVERIGHT);
	static CAnimationClip* moveLeftClip = new CAnimationClip(playerMoveLeft, eMyStatus::MOVELEFT);

	static CAnimationClip* SuperMoveUpClip = new CAnimationClip(playerSuperMoveUp, eMyStatus::SMOVEUP);
	static CAnimationClip* SuperMoveDownClip = new CAnimationClip(playerSuperMoveDown, eMyStatus::SMOVEDOWN);
	static CAnimationClip* SuperMoveRightClip = new CAnimationClip(playerSuperMoveRight, eMyStatus::SMOVERIGHT);
	static CAnimationClip* SuperMoveLeftClip = new CAnimationClip(playerSuperMoveLeft, eMyStatus::SMOVELEFT);

	static CAnimationClip* afterDashUpClip = new CAnimationClip(playerDashUp, eMyStatus::AFTERDASHUP);
	static CAnimationClip* afterDashUpRightClip = new CAnimationClip(playerDashRight, eMyStatus::AFTERDASHUPRIGHT);
	static CAnimationClip* afterDashUpLeftClip = new CAnimationClip(playerDashUp, eMyStatus::AFTERDASHUPLEFT);
	static CAnimationClip* afterDashDownClip = new CAnimationClip(playerDashDown, eMyStatus::AFTERDASHDOWN);
	static CAnimationClip* afterDashDownRightClip = new CAnimationClip(playerDashDown, eMyStatus::AFTERDASHDOWNRIGHT);
	static CAnimationClip* afterDashDownLeftClip = new CAnimationClip(playerDashLeft, eMyStatus::AFTERDASHDOWNLEFT);
	static CAnimationClip* afterDashRightClip = new CAnimationClip(playerDashRight, eMyStatus::AFTERDASHRIGHT);
	static CAnimationClip* afterDashLeftClip = new CAnimationClip(playerDashLeft, eMyStatus::AFTERDASHLEFT);

	static CAnimationClip* SuperAfterDashUpClip = new CAnimationClip(playerSuperDashUp, eMyStatus::SAFTERDASHUP);
	static CAnimationClip* SuperAfterDashUpRightClip = new CAnimationClip(playerSuperDashRight, eMyStatus::SAFTERDASHUPRIGHT);
	static CAnimationClip* SuperAfterDashUpLeftClip = new CAnimationClip(playerSuperDashUp, eMyStatus::SAFTERDASHUPLEFT);
	static CAnimationClip* SuperAfterDashDownClip = new CAnimationClip(playerSuperDashDown, eMyStatus::SAFTERDASHDOWN);
	static CAnimationClip* SuperAfterDashDownRightClip = new CAnimationClip(playerSuperDashDown, eMyStatus::SAFTERDASHDOWNRIGHT);
	static CAnimationClip* SuperAfterDashDownLeftClip = new CAnimationClip(playerSuperDashLeft, eMyStatus::SAFTERDASHDOWNLEFT);
	static CAnimationClip* SuperAfterDashRightClip = new CAnimationClip(playerSuperDashRight, eMyStatus::SAFTERDASHRIGHT);
	static CAnimationClip* SuperAfterDashLeftClip = new CAnimationClip(playerSuperDashLeft, eMyStatus::SAFTERDASHLEFT);

	static CAnimationClip* dashUpClip = new CAnimationClip(playerMoveUp, eMyStatus::DASHUP);
	static CAnimationClip* dashDownClip = new CAnimationClip(playerMoveDown, eMyStatus::DASHDOWN);
	static CAnimationClip* dashRightClip = new CAnimationClip(playerMoveRight, eMyStatus::DASHRIGHT);
	static CAnimationClip* dashLeftClip = new CAnimationClip(playerMoveLeft, eMyStatus::DASHLEFT);

	static CAnimationClip* SuperDashUpClip = new CAnimationClip(playerSuperMoveUp, eMyStatus::SDASHUP);
	static CAnimationClip* SuperDashDownClip = new CAnimationClip(playerSuperMoveDown, eMyStatus::SDASHDOWN);
	static CAnimationClip* SuperDashRightClip = new CAnimationClip(playerSuperMoveRight, eMyStatus::SDASHRIGHT);
	static CAnimationClip* SuperDashLeftClip = new CAnimationClip(playerSuperMoveLeft, eMyStatus::SDASHLEFT);

	static CAnimationClip* hitUpClip = new CAnimationClip(playerHitUp, eMyStatus::HITUP);
	static CAnimationClip* hitDownClip = new CAnimationClip(playerHitDown, eMyStatus::HITDOWN);
	static CAnimationClip* hitRightClip = new CAnimationClip(playerHitRight, eMyStatus::HITRIGHT);
	static CAnimationClip* hitLeftClip = new CAnimationClip(playerHitLeft, eMyStatus::HITLEFT);

	static CAnimationClip* dashAtkUpClip = new CAnimationClip(playerDashAtkUp, eMyStatus::DASHATTACKUP);
	static CAnimationClip* dashAtkDownClip = new CAnimationClip(playerDashAtkDown, eMyStatus::DASHATTACKDOWN);
	static CAnimationClip* dashAtkRightClip = new CAnimationClip(playerDashAtkRight, eMyStatus::DASHATTACKRIGHT);
	static CAnimationClip* dashAtkLeftClip = new CAnimationClip(playerDashAtkLeft, eMyStatus::DASHATTACKLEFT);

	static CAnimationClip* SuperDashAtkUpClip = new CAnimationClip(playerSuperDashAtkUp, eMyStatus::SDASHATTACKUP);
	static CAnimationClip* SuperDashAtkDownClip = new CAnimationClip(playerSuperDashAtkDown, eMyStatus::SDASHATTACKDOWN);
	static CAnimationClip* SuperDashAtkRightClip = new CAnimationClip(playerSuperDashAtkRight, eMyStatus::SDASHATTACKRIGHT);
	static CAnimationClip* SuperDashAtkLeftClip = new CAnimationClip(playerSuperDashAtkLeft, eMyStatus::SDASHATTACKLEFT);

	static CAnimationClip* dieUpClip = new CAnimationClip(playerDieUp, eMyStatus::DIEUP);
	static CAnimationClip* dieDownClip = new CAnimationClip(playerDieDown, eMyStatus::DIEDOWN);
	static CAnimationClip* dieRightClip = new CAnimationClip(playerDieRight, eMyStatus::DIERIGHT);
	static CAnimationClip* dieLeftClip = new CAnimationClip(playerDieLeft, eMyStatus::DIELEFT);

	static CAnimationClip* idleUpClip = new CAnimationClip(playerIDLEUp, eMyStatus::IDLEUP);
	static CAnimationClip* idleDownClip = new CAnimationClip(playerIDLEDown, eMyStatus::IDLEDOWN);
	static CAnimationClip* idleRightClip = new CAnimationClip(playerIDLERight, eMyStatus::IDLERIGHT);
	static CAnimationClip* idleLeftClip = new CAnimationClip(playerIDLELeft, eMyStatus::IDLELEFT);

	static CAnimationClip* useSuperClip = new CAnimationClip(playerUseSuper, eMyStatus::SUPERUSE);

	// 근접병

	static CAnimationClip* closeAtkRightClip = new CAnimationClip(closeAtkRight, eMyStatus::ATTACKRIGHT);
	static CAnimationClip* closeAtkLeftClip = new CAnimationClip(closeAtkLeft, eMyStatus::ATTACKLEFT);

	static CAnimationClip* closeMoveRightClip = new CAnimationClip(closeMoveRight, eMyStatus::MOVERIGHT);
	static CAnimationClip* closeMoveLeftClip = new CAnimationClip(closeMoveLeft, eMyStatus::MOVELEFT);

	//static CAnimationClip* closeMove2RightClip = new CAnimationClip(closeMoveRight, eMyStatus::MOVERIGHT);
	//static CAnimationClip* closeMove2LeftClip = new CAnimationClip(closeMoveLeft, eMyStatus::MOVELEFT);

	static CAnimationClip* closeHitRightClip = new CAnimationClip(closeHitRight, eMyStatus::HITRIGHT);
	static CAnimationClip* closeHitLeftClip = new CAnimationClip(closeHitLeft, eMyStatus::HITLEFT);

	static CAnimationClip* closeDieRightClip = new CAnimationClip(closeDieRight, eMyStatus::DIERIGHT);
	static CAnimationClip* closeDieLeftClip = new CAnimationClip(closeDieLeft, eMyStatus::DIELEFT);

	static CAnimationClip* closeIdleRightClip = new CAnimationClip(closeIDLERight, eMyStatus::IDLERIGHT);
	static CAnimationClip* closeIdleLeftClip = new CAnimationClip(closeIDLELeft, eMyStatus::IDLELEFT);

	// 원거리

	static CAnimationClip* rangeAtkRightClip = new CAnimationClip(rangeAtkRight, eMyStatus::ATTACKRIGHT);
	static CAnimationClip* rangeAtkLeftClip = new CAnimationClip(rangeAtkLeft, eMyStatus::ATTACKLEFT);

	static CAnimationClip* rangeMoveRightClip = new CAnimationClip(rangeMoveRight, eMyStatus::MOVERIGHT);
	static CAnimationClip* rangeMoveLeftClip = new CAnimationClip(rangeMoveLeft, eMyStatus::MOVELEFT);

	static CAnimationClip* rangeHitRightClip = new CAnimationClip(rangeHitRight, eMyStatus::HITRIGHT);
	static CAnimationClip* rangeHitLeftClip = new CAnimationClip(rangeHitLeft, eMyStatus::HITLEFT);

	static CAnimationClip* rangeDieRightClip = new CAnimationClip(rangeDieRight, eMyStatus::DIERIGHT);
	static CAnimationClip* rangeDieLeftClip = new CAnimationClip(rangeDieLeft, eMyStatus::DIELEFT);

	static CAnimationClip* rangeIdleRightClip = new CAnimationClip(rangeIDLERight, eMyStatus::IDLERIGHT);
	static CAnimationClip* rangeIdleLeftClip = new CAnimationClip(rangeIDLELeft, eMyStatus::IDLELEFT);


	// 보스

	static CAnimationClip* bossIDLELeftClip = new CAnimationClip(bossIDLELEFT, eMyStatus::IDLELEFT);
	static CAnimationClip* bossIDLERightClip = new CAnimationClip(bossIDLERIGHT, eMyStatus::IDLERIGHT);
	static CAnimationClip* bossJumpLeftClip = new CAnimationClip(bossJumpLeft, eMyStatus::DASHLEFT);
	static CAnimationClip* bossJumpRightClip = new CAnimationClip(bossJumpRight, eMyStatus::DASHRIGHT);
	static CAnimationClip* bossDieLeftClip = new CAnimationClip(bossDieLeft, eMyStatus::DIELEFT);
	static CAnimationClip* bossDieRightClip = new CAnimationClip(bossDieRight, eMyStatus::DIERIGHT);
	static CAnimationClip* bossStampLeftClip = new CAnimationClip(bossStampLeft, eMyStatus::AFTERDASHLEFT);
	static CAnimationClip* bossStampRightClip = new CAnimationClip(bossStampRight, eMyStatus::AFTERDASHRIGHT);
	static CAnimationClip* bossAttackLeftClip = new CAnimationClip(bossAttackLeft, eMyStatus::ATTACKLEFT);
	static CAnimationClip* bossAttackRightClip = new CAnimationClip(bossAttackRight, eMyStatus::ATTACKRIGHT);


	static CAnimationClip* bossShadowLargetoSmallClip = new CAnimationClip(bossShadowLargetoSmall, eMyStatus::DASHRIGHT);
	static CAnimationClip* bossShadowLargetoSmall2Clip = new CAnimationClip(bossShadowLargetoSmall, eMyStatus::DASHLEFT);
	static CAnimationClip* bossShadowSmalltoLargeClip = new CAnimationClip(bossShadowSmalltoLarge, eMyStatus::AFTERDASHRIGHT);
	static CAnimationClip* bossShadowSmalltoLargeClip2 = new CAnimationClip(bossShadowSmalltoLarge, eMyStatus::AFTERDASHLEFT);


	//static CAnimationClip* bossShadowSmallClip= new CAnimationClip()
#pragma endregion InputAnimationClip

	std::map<int, CAnimationClip*> playerAnimClip;

#pragma region playermap insert
	playerAnimClip.insert(std::make_pair(static_cast<int>(atkUpClip->GetAnimationStatus()), atkUpClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(atkDownClip->GetAnimationStatus()), atkDownClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(atkRightClip->GetAnimationStatus()), atkRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(atkLeftClip->GetAnimationStatus()), atkLeftClip));

	playerAnimClip.insert(std::make_pair(static_cast<int>(superAtkUpClip->GetAnimationStatus()), superAtkUpClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(superAtkDownClip->GetAnimationStatus()), superAtkDownClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(superAtkRightClip->GetAnimationStatus()), superAtkRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(superAtkLeftClip->GetAnimationStatus()), superAtkLeftClip));

	playerAnimClip.insert(std::make_pair(static_cast<int>(moveUpClip->GetAnimationStatus()), moveUpClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(moveRightClip->GetAnimationStatus()), moveRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(moveDownClip->GetAnimationStatus()), moveDownClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(moveLeftClip->GetAnimationStatus()), moveLeftClip));

	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperMoveUpClip->GetAnimationStatus()), SuperMoveUpClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperMoveRightClip->GetAnimationStatus()), SuperMoveRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperMoveDownClip->GetAnimationStatus()), SuperMoveDownClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperMoveLeftClip->GetAnimationStatus()), SuperMoveLeftClip));

	playerAnimClip.insert(std::make_pair(static_cast<int>(afterDashUpClip->GetAnimationStatus()), afterDashUpClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(afterDashDownClip->GetAnimationStatus()), afterDashDownClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(afterDashRightClip->GetAnimationStatus()), afterDashRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(afterDashLeftClip->GetAnimationStatus()), afterDashLeftClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(afterDashUpLeftClip->GetAnimationStatus()), afterDashUpLeftClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(afterDashUpRightClip->GetAnimationStatus()), afterDashUpRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(afterDashDownLeftClip->GetAnimationStatus()), afterDashDownLeftClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(afterDashDownRightClip->GetAnimationStatus()), afterDashDownRightClip));

	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperAfterDashUpClip->GetAnimationStatus()), SuperAfterDashUpClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperAfterDashDownClip->GetAnimationStatus()), SuperAfterDashDownClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperAfterDashRightClip->GetAnimationStatus()), SuperAfterDashRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperAfterDashLeftClip->GetAnimationStatus()), SuperAfterDashLeftClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperAfterDashUpLeftClip->GetAnimationStatus()), SuperAfterDashUpLeftClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperAfterDashUpRightClip->GetAnimationStatus()), SuperAfterDashUpRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperAfterDashDownLeftClip->GetAnimationStatus()), SuperAfterDashDownLeftClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperAfterDashDownRightClip->GetAnimationStatus()), SuperAfterDashDownRightClip));

	playerAnimClip.insert(std::make_pair(static_cast<int>(dashUpClip->GetAnimationStatus()), dashUpClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(dashDownClip->GetAnimationStatus()), dashDownClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(dashRightClip->GetAnimationStatus()), dashRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(dashLeftClip->GetAnimationStatus()), dashLeftClip));

	playerAnimClip.insert(std::make_pair(static_cast<int>(hitUpClip->GetAnimationStatus()), hitUpClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(hitDownClip->GetAnimationStatus()), hitDownClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(hitRightClip->GetAnimationStatus()), hitRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(hitLeftClip->GetAnimationStatus()), hitLeftClip));

	playerAnimClip.insert(std::make_pair(static_cast<int>(dashAtkUpClip->GetAnimationStatus()), dashAtkUpClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(dashAtkDownClip->GetAnimationStatus()), dashAtkDownClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(dashAtkRightClip->GetAnimationStatus()), dashAtkRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(dashAtkLeftClip->GetAnimationStatus()), dashAtkLeftClip));

	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperDashAtkUpClip->GetAnimationStatus()), SuperDashAtkUpClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperDashAtkDownClip->GetAnimationStatus()), SuperDashAtkDownClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperDashAtkRightClip->GetAnimationStatus()), SuperDashAtkRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(SuperDashAtkLeftClip->GetAnimationStatus()), SuperDashAtkLeftClip));

	playerAnimClip.insert(std::make_pair(static_cast<int>(dieUpClip->GetAnimationStatus()), dieUpClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(dieDownClip->GetAnimationStatus()), dieDownClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(dieRightClip->GetAnimationStatus()), dieRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(dieLeftClip->GetAnimationStatus()), dieLeftClip));

	playerAnimClip.insert(std::make_pair(static_cast<int>(idleUpClip->GetAnimationStatus()), idleUpClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(idleDownClip->GetAnimationStatus()), idleDownClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(idleRightClip->GetAnimationStatus()), idleRightClip));
	playerAnimClip.insert(std::make_pair(static_cast<int>(idleLeftClip->GetAnimationStatus()), idleLeftClip));

	playerAnimClip.insert(std::make_pair(static_cast<int>(useSuperClip->GetAnimationStatus()), useSuperClip));

#pragma endregion playermap insert

	totalAnimClip.push_back(playerAnimClip);

	std::map<int, CAnimationClip*> CloseCombatAnimClip;

#pragma region closeAnimclip insert
	CloseCombatAnimClip.insert(std::make_pair(static_cast<int>(closeAtkRightClip->GetAnimationStatus()), closeAtkRightClip));
	CloseCombatAnimClip.insert(std::make_pair(static_cast<int>(closeAtkLeftClip->GetAnimationStatus()), closeAtkLeftClip));

	CloseCombatAnimClip.insert(std::make_pair(static_cast<int>(closeMoveRightClip->GetAnimationStatus()), closeMoveRightClip));
	CloseCombatAnimClip.insert(std::make_pair(static_cast<int>(closeMoveLeftClip->GetAnimationStatus()), closeMoveLeftClip));

	CloseCombatAnimClip.insert(std::make_pair(static_cast<int>(closeHitRightClip->GetAnimationStatus()), closeHitRightClip));
	CloseCombatAnimClip.insert(std::make_pair(static_cast<int>(closeHitLeftClip->GetAnimationStatus()), closeHitLeftClip));

	CloseCombatAnimClip.insert(std::make_pair(static_cast<int>(closeDieRightClip->GetAnimationStatus()), closeDieRightClip));
	CloseCombatAnimClip.insert(std::make_pair(static_cast<int>(closeDieLeftClip->GetAnimationStatus()), closeDieLeftClip));

	CloseCombatAnimClip.insert(std::make_pair(static_cast<int>(closeIdleRightClip->GetAnimationStatus()), closeIdleRightClip));
	CloseCombatAnimClip.insert(std::make_pair(static_cast<int>(closeIdleLeftClip->GetAnimationStatus()), closeIdleLeftClip));

#pragma endregion closeAnimclip insert
	totalAnimClip.push_back(CloseCombatAnimClip);

	std::map<int, CAnimationClip*> BossAniClip;

#pragma region BossAnimclip insert
	BossAniClip.insert(std::make_pair(static_cast<int>(bossIDLELeftClip->GetAnimationStatus()), bossIDLELeftClip));
	BossAniClip.insert(std::make_pair(static_cast<int>(bossIDLERightClip->GetAnimationStatus()), bossIDLERightClip));
	BossAniClip.insert(std::make_pair(static_cast<int>(bossJumpLeftClip->GetAnimationStatus()), bossJumpLeftClip));
	BossAniClip.insert(std::make_pair(static_cast<int>(bossJumpRightClip->GetAnimationStatus()), bossJumpRightClip));
	BossAniClip.insert(std::make_pair(static_cast<int>(bossDieLeftClip->GetAnimationStatus()), bossDieLeftClip));
	BossAniClip.insert(std::make_pair(static_cast<int>(bossDieRightClip->GetAnimationStatus()), bossDieRightClip));
	BossAniClip.insert(std::make_pair(static_cast<int>(bossStampLeftClip->GetAnimationStatus()), bossStampLeftClip));
	BossAniClip.insert(std::make_pair(static_cast<int>(bossStampRightClip->GetAnimationStatus()), bossStampRightClip));
	BossAniClip.insert(std::make_pair(static_cast<int>(bossAttackLeftClip->GetAnimationStatus()), bossAttackLeftClip));
	BossAniClip.insert(std::make_pair(static_cast<int>(bossAttackRightClip->GetAnimationStatus()), bossAttackRightClip));

#pragma endregion BossAnimclip insert
	totalAnimClip.push_back(BossAniClip);


	/*std::map<int, CAnimationClip*> WallAniClip;

	totalAnimClip.push_back(WallAniClip);*/

	std::map<int, CAnimationClip*> RangeAnimClip;

#pragma region rangeAnimclip insert
	RangeAnimClip.insert(std::make_pair(static_cast<int>(rangeAtkRightClip->GetAnimationStatus()), rangeAtkRightClip));
	RangeAnimClip.insert(std::make_pair(static_cast<int>(rangeAtkLeftClip->GetAnimationStatus()), rangeAtkLeftClip));

	RangeAnimClip.insert(std::make_pair(static_cast<int>(rangeMoveRightClip->GetAnimationStatus()), rangeMoveRightClip));
	RangeAnimClip.insert(std::make_pair(static_cast<int>(rangeMoveLeftClip->GetAnimationStatus()), rangeMoveLeftClip));

	RangeAnimClip.insert(std::make_pair(static_cast<int>(rangeHitRightClip->GetAnimationStatus()), rangeHitRightClip));
	RangeAnimClip.insert(std::make_pair(static_cast<int>(rangeHitLeftClip->GetAnimationStatus()), rangeHitLeftClip));

	RangeAnimClip.insert(std::make_pair(static_cast<int>(rangeDieRightClip->GetAnimationStatus()), rangeDieRightClip));
	RangeAnimClip.insert(std::make_pair(static_cast<int>(rangeDieLeftClip->GetAnimationStatus()), rangeDieLeftClip));

	RangeAnimClip.insert(std::make_pair(static_cast<int>(rangeIdleRightClip->GetAnimationStatus()), rangeIdleRightClip));
	RangeAnimClip.insert(std::make_pair(static_cast<int>(rangeIdleLeftClip->GetAnimationStatus()), rangeIdleLeftClip));

#pragma endregion RangeAnimClip insert
	totalAnimClip.push_back(RangeAnimClip);


	std::map<int, CAnimationClip*> ETCAnimClip;

	ETCAnimClip.insert(std::make_pair(static_cast<int>(bossShadowLargetoSmallClip->GetAnimationStatus()), bossShadowLargetoSmallClip));
	ETCAnimClip.insert(std::make_pair(static_cast<int>(bossShadowLargetoSmall2Clip->GetAnimationStatus()), bossShadowLargetoSmall2Clip));
	ETCAnimClip.insert(std::make_pair(static_cast<int>(bossShadowSmalltoLargeClip->GetAnimationStatus()), bossShadowSmalltoLargeClip));
	ETCAnimClip.insert(std::make_pair(static_cast<int>(bossShadowSmalltoLargeClip2->GetAnimationStatus()), bossShadowSmalltoLargeClip2));

	totalAnimClip.push_back(ETCAnimClip);
}

void AnimationManager::UIObjectInit()
{
	static std::vector<CSprite*> playerHeart;
	static std::vector<CSprite*> playerHeartDie;
	static std::vector<CSprite*> playerSuper;

	static std::vector<CSprite*> Intro;
	static std::vector<CSprite*> Credit;
	static std::vector<CSprite*> Ending;

	playerSuper = LoadSpriteFormData(7, 11, CVector2D(0, 0), 0, 283, 154, CVector2D(0.f, 0.f), 0.3f);
	playerHeart = LoadSpriteFormData(7, 4, CVector2D(0, 155), 0, 63, 99, CVector2D(0.f, 0.f), 0.3f);
	playerHeartDie = LoadSpriteFormData(7, 4, CVector2D(0, 255), 0, 98, 98, CVector2D(0.f, 0.f), 0.3f);

	Intro = LoadSpriteFormData(13, 6, CVector2D(0, 0), 0, 1279, 719, CVector2D(0.f, 0.f), 0.3f);
	Credit = LoadSpriteFormData(14, 6, CVector2D(0, 0), 0, 1279, 719, CVector2D(0.f, 0.f), 0.3f);
	Ending = LoadSpriteFormData(15, 6, CVector2D(0, 0), 0, 1279, 719, CVector2D(0.f, 0.f), 0.3f);


	m_playerSuperUI = new CAnimationClip(playerSuper, eMyStatus::IDLEUP);
	m_playerHpUI = new CAnimationClip(playerHeart, eMyStatus::IDLEUP);
	m_playerHpDieUI = new CAnimationClip(playerHeartDie, eMyStatus::IDLEUP);

	m_playerHpAnim = new CAnimator(m_playerHpUI);
	m_playerHpDieAnim = new CAnimator(m_playerHpDieUI);
	m_playerSuperAnim = new CAnimator(m_playerSuperUI);

	m_introUI = new CAnimationClip(Intro, eMyStatus::IDLEUP);
	m_endingUI = new CAnimationClip(Credit, eMyStatus::IDLEUP);
	m_creditUI = new CAnimationClip(Ending, eMyStatus::IDLEUP);

	m_introAnim = new CAnimator(m_introUI);
	m_endingAnim = new CAnimator(m_endingUI);
	m_creditAnim = new CAnimator(m_creditUI);

	m_playerHpAnim->SetAnimationClip(m_playerHpUI);
	m_playerHpDieAnim->SetAnimationClip(m_playerHpDieUI);
	m_playerSuperAnim->SetAnimationClip(m_playerSuperUI);

	m_introAnim->SetAnimationClip(m_introUI);
	m_endingAnim->SetAnimationClip(m_endingUI);
	m_creditAnim->SetAnimationClip(m_creditUI);
}

void AnimationManager::EffectInit()
{
#pragma region 8
	// 플레이어 두번째 공격
	static std::vector<CSprite*> playersecondrightattack;
	static std::vector<CSprite*> playerseconddownattack;
	static std::vector<CSprite*> playersecondupattack;
	static std::vector<CSprite*> playersecondleftattack;

	// 플레이어 일반 공격
	static std::vector<CSprite*> playerrightattack;
	static std::vector<CSprite*> playerdownattack;
	static std::vector<CSprite*> playerupattack;
	static std::vector<CSprite*> playerleftattack;

	// 몬스터 히트 이펙트
	static std::vector<CSprite*> monsterrighthit;
	static std::vector<CSprite*> monsterlefthit;
#pragma  endregion sheet 8

#pragma region sheet 9

	// 9
	// 플레이어 필살기 검 이펙트
	static std::vector<CSprite*> playersuperupeffect;
	static std::vector<CSprite*> playersuperlefteffect;
	static std::vector<CSprite*> playersuperdowneffect;
	static std::vector<CSprite*> playersuperrighteffect;

	// 플레이어 필살기 이펙트
	static std::vector<CSprite*> playersuperattack;				// 필살기 시작 모션
	static std::vector<CSprite*> playerrightsuperattack;
	static std::vector<CSprite*> playerdownsuperattack;
	static std::vector<CSprite*> playerupsuperattack;
	static std::vector<CSprite*> playerleftsuperattack;

	// 필레이어 필살기 두번째 공격
	static std::vector<CSprite*> playersupersecondrightattack;
	static std::vector<CSprite*> playersuperseconddownattack;
	static std::vector<CSprite*> playersupersecondupattack;
	static std::vector<CSprite*> playersupersecondleftattack;

	// 몬스터 필살기 히트 이펙트
	static std::vector<CSprite*> monstersuperrighthit;
	static std::vector<CSprite*> monstersuperlefthit;
#pragma endregion

#pragma region Sheet 10
	// 플레이어 대쉬 이펙트
	static std::vector<CSprite*> playerrightdash;
	static std::vector<CSprite*> playerdowndash;
	static std::vector<CSprite*> playerupdash;
	static std::vector<CSprite*> playerleftdash;

	// 플레이어 걷는 이펙트
	static std::vector<CSprite*> playerrightwalk;
	static std::vector<CSprite*> playerdownwalk;
	static std::vector<CSprite*> playerupwalk;
	static std::vector<CSprite*> playerleftwalk;
	// 플레이어 필살기 걷는 이펙트
	static std::vector<CSprite*> playersuperrightwalk;
	static std::vector<CSprite*> playersuperdownwalk;
	static std::vector<CSprite*> playersuperupwalk;
	static std::vector<CSprite*> playersuperleftwalk;
#pragma endregion Sheet 10

#pragma region sheet 11
	static std::vector<CSprite*> monsterAtkRight;
	static std::vector<CSprite*> monsterAtkLeft;
	static std::vector<CSprite*> monsterBoomRight;
	static std::vector<CSprite*> monsterBoomLeft;
	static std::vector<CSprite*> playerBoomRight;
	static std::vector<CSprite*> playerBoomLeft;

	static std::vector<CSprite*> arrowLeft;
#pragma endregion sheet 11

	static std::vector<CSprite*> bossJumpShadow;
	static std::vector<CSprite*> bossStompShadow;


#pragma region Sheet 8 player attack(+second attack) + monster hit
	playersecondrightattack = LoadSpriteFormData(8, 4, CVector2D(0, 0), 0, 399, 199, CVector2D(0.f, 0.f), 0.07f);		// right
	playerseconddownattack = LoadSpriteFormData(8, 4, CVector2D(0, 201), 0, 199, 399, CVector2D(0.f, 0.f), 0.07f);		// down
	playersecondupattack = LoadSpriteFormData(8, 4, CVector2D(0, 602), 0, 199, 399, CVector2D(0.f, 0.f), 0.07f);		// up
	playersecondleftattack = LoadSpriteFormData(8, 4, CVector2D(0, 2334), 0, 399, 199, CVector2D(0.f, 0.f), 0.07f);		// left

	playerrightattack = LoadSpriteFormData(8, 5, CVector2D(0, 1008), 0, 299, 199, CVector2D(0.f, 0.f), 0.09f);			// right
	playerdownattack = LoadSpriteFormData(8, 5, CVector2D(0, 1209), 0, 399, 399, CVector2D(0.f, 0.f), 0.09f);			// down
	playerupattack = LoadSpriteFormData(8, 5, CVector2D(0, 1610), 0, 399, 399, CVector2D(0.f, 0.f), 0.09f);				// up
	playerleftattack = LoadSpriteFormData(8, 5, CVector2D(0, 2534), 0, 299, 199, CVector2D(0.f, 0.f), 0.09f);			// left

	monsterrighthit = LoadSpriteFormData(8, 4, CVector2D(0, 2025), 0, 199, 299, CVector2D(0.f, 0.f), 0.12f);				// right
	monsterlefthit = LoadSpriteFormData(8, 4, CVector2D(0, 2734), 0, 199, 299, CVector2D(0.f, 0.f), 0.12f);				// left

	arrowLeft = LoadSpriteFormData(8, 1, CVector2D(0, 400), 0, 199, 99, CVector2D(0.f, 0.f), 0.3f);

	CAnimationClip* playersecondrightattackClip = new CAnimationClip(playersecondrightattack, eMyStatus::DASHATTACKRIGHT);
	CAnimationClip* playerseconddownattackClip = new CAnimationClip(playerseconddownattack, eMyStatus::DASHATTACKDOWN);
	CAnimationClip* playersecondupattackClip = new CAnimationClip(playersecondupattack, eMyStatus::DASHATTACKUP);
	CAnimationClip* playersecondleftattackClip = new CAnimationClip(playersecondleftattack, eMyStatus::DASHATTACKLEFT);

	CAnimationClip* playerrightattackClip = new CAnimationClip(playerrightattack, eMyStatus::ATTACKRIGHT);
	CAnimationClip* playerdownattackClip = new CAnimationClip(playerdownattack, eMyStatus::ATTACKDOWN);
	CAnimationClip* playerupattackClip = new CAnimationClip(playerupattack, eMyStatus::ATTACKUP);
	CAnimationClip* playerleftattackClip = new CAnimationClip(playerleftattack, eMyStatus::ATTACKLEFT);

	m_monsterHitEffect.push_back(new CAnimationClip(monsterrighthit, eMyStatus::HITRIGHT));
	m_monsterHitEffect.push_back(new CAnimationClip(monsterlefthit, eMyStatus::HITLEFT));

	m_playerSecondAttackEffect.push_back(new CAnimator(playersecondrightattackClip));
	m_playerSecondAttackEffect.push_back(new CAnimator(playerseconddownattackClip));
	m_playerSecondAttackEffect.push_back(new CAnimator(playersecondupattackClip));
	m_playerSecondAttackEffect.push_back(new CAnimator(playersecondleftattackClip));

	m_playerAttackEffect.push_back(new CAnimator(playerrightattackClip));
	m_playerAttackEffect.push_back(new CAnimator(playerdownattackClip));
	m_playerAttackEffect.push_back(new CAnimator(playerupattackClip));
	m_playerAttackEffect.push_back(new CAnimator(playerleftattackClip));

	m_playerSecondAttackEffect[0]->SetAnimationClip(playersecondrightattackClip);
	m_playerSecondAttackEffect[1]->SetAnimationClip(playerseconddownattackClip);
	m_playerSecondAttackEffect[2]->SetAnimationClip(playersecondupattackClip);
	m_playerSecondAttackEffect[3]->SetAnimationClip(playersecondleftattackClip);

	m_playerAttackEffect[0]->SetAnimationClip(playerrightattackClip);
	m_playerAttackEffect[1]->SetAnimationClip(playerdownattackClip);
	m_playerAttackEffect[2]->SetAnimationClip(playerupattackClip);
	m_playerAttackEffect[3]->SetAnimationClip(playerleftattackClip);
#pragma endregion

#pragma region Sheet 9 Super Mode
	// 플레이어 필살기 시작 이펙트
	playersuperattack = LoadSpriteFormData(9, 15, CVector2D(0, 0), 0, 399, 399, CVector2D(0.f, 0.f), 0.3f);
	// 플레이어 필살기 이펙트
	playerrightsuperattack = LoadSpriteFormData(9, 5, CVector2D(0, 416), 0, 399, 399, CVector2D(0.f, 0.f), 0.04f);			// right
	playerdownsuperattack = LoadSpriteFormData(9, 5, CVector2D(0, 816), 0, 399, 399, CVector2D(0.f, 0.f), 0.04f);			// down
	playerupsuperattack = LoadSpriteFormData(9, 5, CVector2D(0, 1216), 0, 399, 399, CVector2D(0.f, 0.f), 0.04f);			// up
	playerleftsuperattack = LoadSpriteFormData(9, 5, CVector2D(0, 4467), 0, 399, 399, CVector2D(0.f, 0.f), 0.04f);			// left
	// 플레이어 검기 이펙트
	playersuperlefteffect = LoadSpriteFormData(9, 7, CVector2D(0, 4257), 0, 199, 209, CVector2D(-0.15f, 0.15f), 0.17f);			// 검기 left + up
	playersuperupeffect = LoadSpriteFormData(9, 7, CVector2D(0, 4257), 0, 199, 209, CVector2D(-0.155f, 0.09f), 0.17f);			// 검기 left + up
	playersuperdowneffect = LoadSpriteFormData(9, 7, CVector2D(0, 4047), 0, 199, 209, CVector2D(-0.015f, 0.15f), 0.17f);		// 검기 right + down
	playersuperrighteffect = LoadSpriteFormData(9, 7, CVector2D(0, 4047), 0, 199, 209, CVector2D(0.06f, 0.06f), 0.17f);
	// 검기 right + down
	// 플레이어 필살기 두번째 이펙트
	playersupersecondrightattack = LoadSpriteFormData(9, 4, CVector2D(0, 1632), 0, 799, 199, CVector2D(0.f, 0.f), 0.04f);	// right
	playersuperseconddownattack = LoadSpriteFormData(9, 4, CVector2D(0, 1832), 0, 199, 799, CVector2D(0.f, 0.f), 0.04f);	// down
	playersupersecondupattack = LoadSpriteFormData(9, 4, CVector2D(0, 2632), 0, 199, 799, CVector2D(0.f, 0.f), 0.04f);		// up
	playersupersecondleftattack = LoadSpriteFormData(9, 4, CVector2D(0, 4867), 0, 799, 199, CVector2D(0.f, 0.f), 0.04f);	// left
	// 몬스터 히트 이펙트
	monstersuperrighthit = LoadSpriteFormData(9, 6, CVector2D(0, 3440), 0, 399, 599, CVector2D(0.f, 0.f), 0.05f);
	monstersuperlefthit = LoadSpriteFormData(9, 6, CVector2D(0, 5067), 0, 399, 599, CVector2D(0.f, 0.f), 0.05f);

	CAnimationClip* playersuperattackClip = new CAnimationClip(playersuperattack, eMyStatus::SUPERUSE);

	CAnimationClip* playerrightsuperattackClip = new CAnimationClip(playerrightsuperattack, eMyStatus::SATTACKRIGHT);
	CAnimationClip* playerdownsuperattackClip = new CAnimationClip(playerdownsuperattack, eMyStatus::SATTACKDOWN);
	CAnimationClip* playerupsuperattackClip = new CAnimationClip(playerupsuperattack, eMyStatus::SATTACKUP);
	CAnimationClip* playerleftsuperattackClip = new CAnimationClip(playerleftsuperattack, eMyStatus::SATTACKLEFT);

	CAnimationClip* playersuperrighteffectClip = new CAnimationClip(playersuperrighteffect, eMyStatus::IDLERIGHT);
	CAnimationClip* playersuperdowneffectClip = new CAnimationClip(playersuperdowneffect, eMyStatus::IDLEDOWN);
	CAnimationClip* playersuperupeffectClip = new CAnimationClip(playersuperupeffect, eMyStatus::IDLEUP);
	CAnimationClip* playersuperlefteffectClip = new CAnimationClip(playersuperlefteffect, eMyStatus::IDLELEFT);

	CAnimationClip* playersupersecondrightattackClip = new CAnimationClip(playersupersecondrightattack, eMyStatus::SDASHATTACKRIGHT);
	CAnimationClip* playersuperseconddownattackClip = new CAnimationClip(playersuperseconddownattack, eMyStatus::SDASHATTACKDOWN);
	CAnimationClip* playersupersecondupattackClip = new CAnimationClip(playersupersecondupattack, eMyStatus::SDASHATTACKUP);
	CAnimationClip* playersupersecondleftattackClip = new CAnimationClip(playersupersecondleftattack, eMyStatus::SDASHATTACKLEFT);

	m_monsterSuperHitEffect.push_back(new CAnimationClip(monstersuperrighthit, eMyStatus::HITRIGHT));
	m_monsterSuperHitEffect.push_back(new CAnimationClip(monstersuperlefthit, eMyStatus::HITLEFT));

	m_playerSuperUse = new CAnimator(playersuperattackClip);

	m_playerSuperAttackEffect.push_back(new CAnimator(playerrightsuperattackClip));
	m_playerSuperAttackEffect.push_back(new CAnimator(playerdownsuperattackClip));
	m_playerSuperAttackEffect.push_back(new CAnimator(playerupsuperattackClip));
	m_playerSuperAttackEffect.push_back(new CAnimator(playerleftsuperattackClip));

	m_playerSuperEffect.push_back(new CAnimator(playersuperrighteffectClip));
	m_playerSuperEffect.push_back(new CAnimator(playersuperdowneffectClip));
	m_playerSuperEffect.push_back(new CAnimator(playersuperupeffectClip));
	m_playerSuperEffect.push_back(new CAnimator(playersuperlefteffectClip));

	m_playerSuperSecondAttackEffect.push_back(new CAnimator(playersupersecondrightattackClip));
	m_playerSuperSecondAttackEffect.push_back(new CAnimator(playersuperseconddownattackClip));
	m_playerSuperSecondAttackEffect.push_back(new CAnimator(playersupersecondupattackClip));
	m_playerSuperSecondAttackEffect.push_back(new CAnimator(playersupersecondleftattackClip));

	m_playerSuperUse->SetAnimationClip(playersuperattackClip);

	m_playerSuperAttackEffect[0]->SetAnimationClip(playerrightsuperattackClip);
	m_playerSuperAttackEffect[1]->SetAnimationClip(playerdownsuperattackClip);
	m_playerSuperAttackEffect[2]->SetAnimationClip(playerupsuperattackClip);
	m_playerSuperAttackEffect[3]->SetAnimationClip(playerleftsuperattackClip);

	m_playerSuperEffect[0]->SetAnimationClip(playersuperrighteffectClip);
	m_playerSuperEffect[1]->SetAnimationClip(playersuperdowneffectClip);
	m_playerSuperEffect[2]->SetAnimationClip(playersuperupeffectClip);
	m_playerSuperEffect[3]->SetAnimationClip(playersuperlefteffectClip);

	m_playerSuperSecondAttackEffect[0]->SetAnimationClip(playersupersecondrightattackClip);
	m_playerSuperSecondAttackEffect[1]->SetAnimationClip(playersuperseconddownattackClip);
	m_playerSuperSecondAttackEffect[2]->SetAnimationClip(playersupersecondupattackClip);
	m_playerSuperSecondAttackEffect[3]->SetAnimationClip(playersupersecondleftattackClip);

#pragma  endregion Sheet 9 Super Mode

#pragma region sheet 10 Move
	// 플레이어 걷는 이펙트
	playerrightwalk = LoadSpriteFormData(10, 4, CVector2D(0, 0), 0, 199, 199, CVector2D(-0.3f, 0.f), 0.3f);
	playerdownwalk = LoadSpriteFormData(10, 4, CVector2D(0, 201), 0, 199, 207, CVector2D(0.1f, -0.2f), 0.3f);
	playerupwalk = LoadSpriteFormData(10, 4, CVector2D(0, 410), 0, 199, 215, CVector2D(-0.1f, 0.1f), 0.3f);
	playerleftwalk = LoadSpriteFormData(10, 4, CVector2D(0, 1362), 0, 199, 199, CVector2D(0.3f, 0.f), 0.3f);
	// 플레이어 필살기일때 걷는 이펙트
	playersuperrightwalk = LoadSpriteFormData(10, 4, CVector2D(0, 0), 0, 199, 199, CVector2D(-0.3f, 0.f), 0.1f);
	playersuperdownwalk = LoadSpriteFormData(10, 4, CVector2D(0, 201), 0, 199, 207, CVector2D(0.1f, -0.2f), 0.1f);
	playersuperupwalk = LoadSpriteFormData(10, 4, CVector2D(0, 410), 0, 199, 215, CVector2D(-0.1f, 0.1f), 0.1f);
	playersuperleftwalk = LoadSpriteFormData(10, 4, CVector2D(0, 1362), 0, 199, 199, CVector2D(0.3f, 0.f), 0.1f);
	// 플레이어 대쉬 이펙트
	playerrightdash = LoadSpriteFormData(10, 5, CVector2D(0, 627), 0, 255, 111, CVector2D(-0.8f, 0.3f), 0.12f);
	playerdowndash = LoadSpriteFormData(10, 5, CVector2D(0, 740), 0, 92, 252, CVector2D(0.1f, -0.95f), 0.12f);
	playerupdash = LoadSpriteFormData(10, 5, CVector2D(0, 993), 0, 99, 255, CVector2D(-0.3f, 0.8f), 0.12f);
	playerleftdash = LoadSpriteFormData(10, 5, CVector2D(0, 1249), 0, 239, 111, CVector2D(1.f, 0.3f), 0.12f);

	CAnimationClip* playerrightwalkClip = new CAnimationClip(playerrightwalk, eMyStatus::MOVERIGHT);
	CAnimationClip* playerdownwalkClip = new CAnimationClip(playerdownwalk, eMyStatus::MOVEDOWN);
	CAnimationClip* playerupwalkClip = new CAnimationClip(playerupwalk, eMyStatus::MOVEUP);
	CAnimationClip* playerleftwalkClip = new CAnimationClip(playerleftwalk, eMyStatus::MOVELEFT);

	CAnimationClip* playersuperrightwalkClip = new CAnimationClip(playersuperrightwalk, eMyStatus::SMOVERIGHT);
	CAnimationClip* playersuperdownwalkClip = new CAnimationClip(playersuperdownwalk, eMyStatus::SMOVEDOWN);
	CAnimationClip* playersuperupwalkClip = new CAnimationClip(playersuperupwalk, eMyStatus::SMOVEUP);
	CAnimationClip* playersuperleftwalkClip = new CAnimationClip(playersuperleftwalk, eMyStatus::SMOVELEFT);

	CAnimationClip* playerrightdashClip = new CAnimationClip(playerrightdash, eMyStatus::DASHRIGHT);
	CAnimationClip* playerdowndashClip = new CAnimationClip(playerdowndash, eMyStatus::DASHDOWN);
	CAnimationClip* playerupdashClip = new CAnimationClip(playerupdash, eMyStatus::DASHUP);
	CAnimationClip* playerleftdashClip = new CAnimationClip(playerleftdash, eMyStatus::DASHLEFT);

	m_playerWalkEffect.push_back(new CAnimator(playerrightwalkClip));
	m_playerWalkEffect.push_back(new CAnimator(playerdownwalkClip));
	m_playerWalkEffect.push_back(new CAnimator(playerupwalkClip));
	m_playerWalkEffect.push_back(new CAnimator(playerleftwalkClip));

	m_playerSuperWalkEffect.push_back(new CAnimator(playersuperrightwalkClip));
	m_playerSuperWalkEffect.push_back(new CAnimator(playersuperdownwalkClip));
	m_playerSuperWalkEffect.push_back(new CAnimator(playersuperupwalkClip));
	m_playerSuperWalkEffect.push_back(new CAnimator(playersuperleftwalkClip));

	m_playerDashEffect.push_back(new CAnimator(playerrightdashClip));
	m_playerDashEffect.push_back(new CAnimator(playerdowndashClip));
	m_playerDashEffect.push_back(new CAnimator(playerupdashClip));
	m_playerDashEffect.push_back(new CAnimator(playerleftdashClip));

	m_playerWalkEffect[0]->SetAnimationClip(playerrightwalkClip);
	m_playerWalkEffect[1]->SetAnimationClip(playerdownwalkClip);
	m_playerWalkEffect[2]->SetAnimationClip(playerupwalkClip);
	m_playerWalkEffect[3]->SetAnimationClip(playerleftwalkClip);

	m_playerSuperWalkEffect[0]->SetAnimationClip(playersuperrightwalkClip);
	m_playerSuperWalkEffect[1]->SetAnimationClip(playersuperdownwalkClip);
	m_playerSuperWalkEffect[2]->SetAnimationClip(playersuperupwalkClip);
	m_playerSuperWalkEffect[3]->SetAnimationClip(playersuperleftwalkClip);

	m_playerDashEffect[0]->SetAnimationClip(playerrightdashClip);
	m_playerDashEffect[1]->SetAnimationClip(playerdowndashClip);
	m_playerDashEffect[2]->SetAnimationClip(playerupdashClip);
	m_playerDashEffect[3]->SetAnimationClip(playerleftdashClip);
#pragma endregion sheet 10 Move

#pragma region sheet 11 Effect
	// 근접 몬스터 공격 이펙트
	monsterAtkRight = LoadSpriteFormData(11, 3, CVector2D(0, 0), 0, 399, 399, CVector2D(0.f, 0.f), 0.3f);
	monsterAtkLeft = LoadSpriteFormData(11, 3, CVector2D(0, 900), 0, 199, 199, CVector2D(0.f, 0.f), 0.3f);
	// 화살 터지는 이펙트
	monsterBoomRight = LoadSpriteFormData(11, 4, CVector2D(0, 500), 0, 199, 199, CVector2D(0.4f, 0.1f), 0.05f);
	monsterBoomLeft = LoadSpriteFormData(11, 4, CVector2D(0, 1400), 0, 199, 199, CVector2D(-0.4f, 0.1f), 0.05f);
	// 플레이어 피격 이펙트
	playerBoomRight = LoadSpriteFormData(11, 4, CVector2D(0, 700), 0, 199, 199, CVector2D(0.f, 0.f), 0.1f);
	playerBoomLeft = LoadSpriteFormData(11, 4, CVector2D(0, 1600), 0, 199, 199, CVector2D(0.f, 0.f), 0.1f);

	/*m_monsterAttackEffect.push_back(new CAnimationClip(monsterAtkRight, eMyStatus::ATTACKRIGHT));
	m_monsterAttackEffect.push_back(new CAnimationClip(monsterAtkLeft, eMyStatus::ATTACKLEFT));*/

	m_monsterArrowBoomEffect.push_back(new CAnimationClip(monsterBoomRight, eMyStatus::ATTACKRIGHT));
	m_monsterArrowBoomEffect.push_back(new CAnimationClip(monsterBoomLeft, eMyStatus::ATTACKLEFT));

	CAnimationClip* playerBoomRightClip = new CAnimationClip(playerBoomRight, eMyStatus::HITRIGHT);
	CAnimationClip* playerBoomDownClip = new CAnimationClip(playerBoomLeft, eMyStatus::HITDOWN);
	CAnimationClip* playerBoomUpClip = new CAnimationClip(playerBoomLeft, eMyStatus::HITUP);
	CAnimationClip* playerBoomLeftClip = new CAnimationClip(playerBoomLeft, eMyStatus::HITLEFT);

	m_playerHitEffect.push_back(new CAnimator(playerBoomRightClip));
	m_playerHitEffect.push_back(new CAnimator(playerBoomDownClip));
	m_playerHitEffect.push_back(new CAnimator(playerBoomUpClip));
	m_playerHitEffect.push_back(new CAnimator(playerBoomLeftClip));

	m_playerHitEffect[0]->SetAnimationClip(playerBoomRightClip);
	m_playerHitEffect[1]->SetAnimationClip(playerBoomDownClip);
	m_playerHitEffect[2]->SetAnimationClip(playerBoomUpClip);
	m_playerHitEffect[3]->SetAnimationClip(playerBoomLeftClip);

#pragma endregion sheet 11 Effect

	bossJumpShadow = LoadSpriteFormData(12, 4, CVector2D(0, 200), 0, 249, 249, CVector2D(0.f, 0.f), 0.3f);
	bossStompShadow = LoadSpriteFormData(12, 4, CVector2D(0, 500), 0, 249, 249, CVector2D(0.f, 0.f), 0.3f);

	m_BossJumpShadowEffect.push_back(new CAnimationClip(bossJumpShadow, eMyStatus::DASHRIGHT));
	m_BossJumpShadowEffect.push_back(new CAnimationClip(bossJumpShadow, eMyStatus::DASHLEFT));
	m_BossStompShadowEffect.push_back(new CAnimationClip(bossStompShadow, eMyStatus::AFTERDASHRIGHT));
	m_BossStompShadowEffect.push_back(new CAnimationClip(bossStompShadow, eMyStatus::AFTERDASHLEFT));
}
#pragma endregion Init

// 오브젝트, 투명도, 카메라
void AnimationManager::DrawSprite(CObjectBase* object, float opacity, CVector2D cvector)
{
	if (object == nullptr)
		return;
	CSprite* sprite = totalAnimClip[(static_cast<int>(object->objectKind))].at(static_cast<int>(object->m_status))->GetFram(object->m_animator->GetCurrentIdx());
	CVector2D printpos;
	printpos.x = object->m_pos.x - (sprite->m_sheetWidth / 2) - cvector.x;
	printpos.y = object->m_pos.y - (sprite->m_sheetHeight / 2) - cvector.y;
	m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, printpos, opacity, object->m_transform->TransformMatrix(), cvector);

	if (object->objectKind == eObjectKind::BOSS)
	{
		if (object->m_status == eMyStatus::DASHLEFT || object->m_status == eMyStatus::DASHRIGHT || object->m_status == eMyStatus::ATTACKLEFT || object->m_status == eMyStatus::ATTACKRIGHT
			|| object->m_status == eMyStatus::DIELEFT || object->m_status == eMyStatus::DIERIGHT)
		{
			object->m_animator->LastPlay();
		}
		else
			object->m_animator->Play();
	}

	else if (object->m_totalStatus == eToTalStatus::DIE)
	{
		object->m_animator->LastPlay();
	}

	else
		object->m_animator->Play();


}

void AnimationManager::SetStatus(CObjectBase* object)
{
	object->m_animator->SetAnimationClip(totalAnimClip[static_cast<int>(object->objectKind)].at(static_cast<int>(object->GetStatus())));
	object->m_animator->ResetCurrentIdx();
	object->m_animator->ResetLoadingTime();
}


CAnimationClip* AnimationManager::GetAnimationClip(CObjectBase* object)
{
	return totalAnimClip[static_cast<int>(object->objectKind)].at(static_cast<int>(object->GetStatus()));
}

std::vector<CSprite*> AnimationManager::LoadSpriteFormData(int idx, int count, CVector2D firstsheetpos, float spacegap, int width, int height, CVector2D pivot, float delaytime)
{
	std::vector <CSprite*> Anim;
	CVector2D pos;
	for (int i = 0; i < count; i++)
	{
		pos.x = firstsheetpos.x + (width * i) + (spacegap * i);

		pos.y = firstsheetpos.y;
		Anim.push_back(m_pEngine->LoadSpriteFromData(idx, pos, width, height, pivot, delaytime));
	}
	if (Anim.size() == 0)
		return std::vector<CSprite*>();
	return Anim;
}

CVector2D AnimationManager::GetSpriteHalfSize(CObjectBase* object)
{
	CSprite* newSprite = totalAnimClip[(static_cast<int>(object->objectKind))].at(static_cast<int>(object->m_status))->GetFram(0);
	CVector2D spritesize;
	spritesize.x = newSprite->m_sheetWidth / 2;
	spritesize.y = newSprite->m_sheetHeight / 2;

	//어떤 오브젝트인지 확인해서 clip을 받아와야함 
	return spritesize;
}

void AnimationManager::OneFrameSprite(CSprite* sprite, Transform* transform, CVector2D cvector)
{
	m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(0, 0), 1, transform->TransformMatrix(), cvector);
}

void AnimationManager::BossShadowEffect(CObjectBase* object, CVector2D printfpos, CVector2D cvector)
{
	//if (object == nullptr)
	//	return;

	//CSprite* sprite;
	//switch (object->GetStatus())
	//{
	//	case eMyStatus::DASHLEFT:

	//}
	////totalAnimClip[(static_cast<int>(object->objectKind))].at(static_cast<int>(object->m_status))->GetFram(object->m_animator->GetCurrentIdx());

	//m_pEngine->DrawSprite(sprite, printfpos.x, printfpos.y, 0, 0, 1, cvector);

	//object->m_animator->Play();

	//if (object == nullptr)
	//	return;

	//CSprite* sprite;
	//switch (object->GetStatus())
	//{
	//	case eMyStatus::DASHLEFT:
	//	{
	//		sprite = m_BossJumpShadowEffect[0]->GetFram(m_BossJumpShadowEffect[0]->GetCurrentIdx());
	//		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
	//		m_playerWalkEffect[0]->Play();
	//	}
	//	break;
	//	case eMyStatus::MOVEDOWN:
	//	{
	//		sprite = m_playerWalkEffect[1]->GetAnimationClip()->GetFram(m_playerWalkEffect[1]->GetCurrentIdx());
	//		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
	//		m_playerWalkEffect[1]->Play();
	//	}
	//	break;
	//	case eMyStatus::MOVEUP:
	//	{
	//		sprite = m_playerWalkEffect[2]->GetAnimationClip()->GetFram(m_playerWalkEffect[2]->GetCurrentIdx());
	//		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
	//		m_playerWalkEffect[2]->Play();
	//	}
	//	break;
	//	case eMyStatus::MOVELEFT:
	//	{
	//		sprite = m_playerWalkEffect[3]->GetAnimationClip()->GetFram(m_playerWalkEffect[3]->GetCurrentIdx());
	//		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
	//		m_playerWalkEffect[3]->Play();
	//	}
	//	break;
	//  }
}

void AnimationManager::UI()
{

	CSprite* sprite;
	if (SceneManager::GetInstance()->m_sceneNumber != 0&& SceneManager::GetInstance()->m_sceneNumber != 5)
	{
		sprite = m_playerHpAnim->GetAnimationClip()->GetFram(m_playerHpAnim->GetCurrentIdx());
		for (int i = 0; i < CPlayerObject::GetInstance()->GetHp(); i++)
		{
			m_pEngine->DrawSprite(sprite, 0, 0, sprite->m_sheetWidth * (i + 1) - 50, sprite->m_sheetHeight - 100, 1);
			m_playerHpAnim->Play();
		}
		sprite = m_playerSuperAnim->GetAnimationClip()->GetFram(m_playerSuperAnim->GetCurrentIdx());
		// super max =50

		if (0 <= CPlayerObject::GetInstance()->GetSuper() && CPlayerObject::GetInstance()->GetSuper() < 5)
		{
			m_playerSuperAnim->m_currentIdx = 0;
		}
		else if (5 <= CPlayerObject::GetInstance()->GetSuper() && CPlayerObject::GetInstance()->GetSuper() < 10)
		{
			m_playerSuperAnim->m_currentIdx = 1;
		}
		else if (10 <= CPlayerObject::GetInstance()->GetSuper() && CPlayerObject::GetInstance()->GetSuper() < 15)
		{
			m_playerSuperAnim->m_currentIdx = 2;
		}
		else if (15 <= CPlayerObject::GetInstance()->GetSuper() && CPlayerObject::GetInstance()->GetSuper() < 20)
		{
			m_playerSuperAnim->m_currentIdx = 3;

		}
		else if (20 <= CPlayerObject::GetInstance()->GetSuper() && CPlayerObject::GetInstance()->GetSuper() < 25)
		{
			m_playerSuperAnim->m_currentIdx = 4;


		}
		else if (25 <= CPlayerObject::GetInstance()->GetSuper() && CPlayerObject::GetInstance()->GetSuper() < 30)
		{
			m_playerSuperAnim->m_currentIdx = 5;


		}
		else if (30 <= CPlayerObject::GetInstance()->GetSuper() && CPlayerObject::GetInstance()->GetSuper() < 35)
		{
			m_playerSuperAnim->m_currentIdx = 6;


		}
		else if (35 <= CPlayerObject::GetInstance()->GetSuper() && CPlayerObject::GetInstance()->GetSuper() < 40)
		{
			m_playerSuperAnim->m_currentIdx = 7;

		}
		else if (40 <= CPlayerObject::GetInstance()->GetSuper() && CPlayerObject::GetInstance()->GetSuper() < 45)
		{
			m_playerSuperAnim->m_currentIdx = 8;

		}
		else if (45 <= CPlayerObject::GetInstance()->GetSuper() && CPlayerObject::GetInstance()->GetSuper() < 50)
		{
			m_playerSuperAnim->m_currentIdx = 9;

		}
		else
			m_playerSuperAnim->m_currentIdx = 10;

		m_pEngine->DrawSprite(sprite, 0, 0, 0, 30, 1);

	}

}

void AnimationManager::FrameResetEffect()
{
	// 플레이어 관련 리셋
	// 공격 리셋
	for (int i = 0; i < m_playerAttackEffect.size(); i++)
	{
		m_playerAttackEffect[i]->ResetCurrentIdx();
		m_playerAttackEffect[i]->ResetLoadingTime();
	}
	// 대쉬 공격 리셋
	for (int i = 0; i < m_playerSecondAttackEffect.size(); i++)
	{
		m_playerSecondAttackEffect[i]->ResetCurrentIdx();
		m_playerSecondAttackEffect[i]->ResetLoadingTime();
	}
	// 필살기 시작 애니메이션 리셋
	m_playerSuperUse->ResetCurrentIdx();
	m_playerSuperUse->ResetLoadingTime();
	// 필살기 공격 리셋
	for (int i = 0; i < m_playerSuperAttackEffect.size(); i++)
	{
		m_playerSuperAttackEffect[i]->ResetCurrentIdx();
		m_playerSuperAttackEffect[i]->ResetLoadingTime();
	}
	// 필살기 대쉬 공격 리셋
	for (int i = 0; i < m_playerSuperSecondAttackEffect.size(); i++)
	{
		m_playerSuperSecondAttackEffect[i]->ResetCurrentIdx();
		m_playerSuperSecondAttackEffect[i]->ResetLoadingTime();
	}
	// 플레이어 피격 박스 이펙트 리셋
	for (int i = 0; i < m_playerHitEffect.size(); i++)
	{
		m_playerHitEffect[i]->ResetCurrentIdx();
		m_playerHitEffect[i]->ResetLoadingTime();
	}
	// 플레이어 대쉬 이펙트 리셋
	for (int i = 0; i < m_playerDashEffect.size(); i++)
	{
		m_playerDashEffect[i]->ResetCurrentIdx();
		m_playerDashEffect[i]->ResetLoadingTime();
	}
	//// 몬스터 히트 공격 초기화
	//for (int i = 0; i < m_monsterHitEffect.size(); i++)
	//{
	//	m_monsterHitEffect[i]->ResetCurrentIdx();
	//	m_monsterHitEffect[i]->ResetLoadingTime();
	//}
	//// 몬스터 필살기 히드 공격 초기화
	//for (int i = 0; i < m_monsterSuperHitEffect.size(); i++)
	//{
	//	m_monsterSuperHitEffect[i]->ResetCurrentIdx();
	//	m_monsterSuperHitEffect[i]->ResetLoadingTime();
	//}

}

// 플레이어 공격
void AnimationManager::PlayerAttackEffect(CObjectBase* object, CVector2D cvector)
{
	if (object == nullptr)
		return;

	CSprite* sprite;

	switch (object->GetStatus())
	{
	case eMyStatus::ATTACKRIGHT:
	{
		sprite = m_playerAttackEffect[0]->GetAnimationClip()->GetFram(m_playerAttackEffect[0]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerAttackEffect[0]->Play();
	}
	break;
	case eMyStatus::ATTACKDOWN:
	{
		sprite = m_playerAttackEffect[1]->GetAnimationClip()->GetFram(m_playerAttackEffect[1]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerAttackEffect[1]->Play();
	}
	break;
	case eMyStatus::ATTACKUP:
	{
		sprite = m_playerAttackEffect[2]->GetAnimationClip()->GetFram(m_playerAttackEffect[2]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerAttackEffect[2]->Play();
	}
	break;
	case eMyStatus::ATTACKLEFT:
	{
		sprite = m_playerAttackEffect[3]->GetAnimationClip()->GetFram(m_playerAttackEffect[3]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerAttackEffect[3]->Play();
	}
	break;
	default:
		break;
	}

}

void AnimationManager::PlayerDashAttackEffect(CObjectBase* object, CVector2D cvector)
{
	if (object == nullptr)
		return;

	CSprite* sprite;

	switch (object->GetStatus())
	{
	case eMyStatus::DASHATTACKRIGHT:
	{
		sprite = m_playerSecondAttackEffect[0]->GetAnimationClip()->GetFram(m_playerSecondAttackEffect[0]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSecondAttackEffect[0]->Play();
	}
	break;
	case eMyStatus::DASHATTACKDOWN:
	{
		sprite = m_playerSecondAttackEffect[1]->GetAnimationClip()->GetFram(m_playerSecondAttackEffect[1]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSecondAttackEffect[1]->Play();
	}
	break;
	case eMyStatus::DASHATTACKUP:
	{
		sprite = m_playerSecondAttackEffect[2]->GetAnimationClip()->GetFram(m_playerSecondAttackEffect[2]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSecondAttackEffect[2]->Play();
	}
	break;
	case eMyStatus::DASHATTACKLEFT:
	{
		sprite = m_playerSecondAttackEffect[3]->GetAnimationClip()->GetFram(m_playerSecondAttackEffect[3]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSecondAttackEffect[3]->Play();
	}
	break;
	default:
		break;
	}
}

// 
void AnimationManager::PlayerIDLEEffect(CObjectBase* object, CVector2D cvector)
{
	if (object == nullptr)
		return;

	CSprite* sprite;
	if (CPlayerObject::GetInstance()->m_isSuper)
	{
		switch (object->GetStatus())
		{
		case eMyStatus::IDLERIGHT:
		{
			sprite = m_playerSuperEffect[0]->GetAnimationClip()->GetFram(m_playerSuperEffect[0]->GetCurrentIdx());
			m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
			m_playerSuperEffect[0]->Play();
		}
		break;
		case eMyStatus::IDLEDOWN:
		{
			sprite = m_playerSuperEffect[1]->GetAnimationClip()->GetFram(m_playerSuperEffect[1]->GetCurrentIdx());
			m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
			m_playerSuperEffect[1]->Play();
		}
		break;
		case eMyStatus::IDLEUP:
		{
			sprite = m_playerSuperEffect[2]->GetAnimationClip()->GetFram(m_playerSuperEffect[2]->GetCurrentIdx());
			m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
			m_playerSuperEffect[2]->Play();
		}
		break;
		case eMyStatus::IDLELEFT:
		{
			sprite = m_playerSuperEffect[3]->GetAnimationClip()->GetFram(m_playerSuperEffect[3]->GetCurrentIdx());
			m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
			m_playerSuperEffect[3]->Play();
		}
		break;
		default:
			break;
		}
	}
}

// 플레이어가 필살기를 쓰면 사용되는 이펙트 (_팀장님의 수정이 필요합니다)
void AnimationManager::PlayerSuperStartEffect(CObjectBase* object, CVector2D cvector)
{
	if (object == nullptr)
		return;

	CSprite* sprite = m_playerSuperUse->GetAnimationClip()->GetFram(m_playerSuperUse->GetCurrentIdx());
	m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
	m_playerSuperUse->Play();
}

void AnimationManager::PlayerSuperAttackEffect(CObjectBase* object, CVector2D cvector)
{
	if (object == nullptr)
		return;
	CSprite* sprite;

	switch (object->GetStatus())
	{
	case eMyStatus::SATTACKRIGHT:
	{
		sprite = m_playerSuperAttackEffect[0]->GetAnimationClip()->GetFram(m_playerSuperAttackEffect[0]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSuperAttackEffect[0]->Play();
	}
	break;
	case eMyStatus::SATTACKDOWN:
	{
		sprite = m_playerSuperAttackEffect[1]->GetAnimationClip()->GetFram(m_playerSuperAttackEffect[1]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSuperAttackEffect[1]->Play();
	}
	break;
	case eMyStatus::SATTACKUP:
	{
		sprite = m_playerSuperAttackEffect[2]->GetAnimationClip()->GetFram(m_playerSuperAttackEffect[2]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSuperAttackEffect[2]->Play();
	}
	break;
	case eMyStatus::SATTACKLEFT:
	{
		sprite = m_playerSuperAttackEffect[3]->GetAnimationClip()->GetFram(m_playerSuperAttackEffect[3]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSuperAttackEffect[3]->Play();
	}
	break;
	default:
		break;
	}
}

void AnimationManager::PlayerSuperDashAttackEffect(CObjectBase* object, CVector2D cvector)
{
	if (object == nullptr)
		return;

	CSprite* sprite;

	switch (object->GetStatus())
	{
	case eMyStatus::SDASHATTACKRIGHT:
	{
		sprite = m_playerSuperSecondAttackEffect[0]->GetAnimationClip()->GetFram(m_playerSuperSecondAttackEffect[0]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSuperSecondAttackEffect[0]->Play();
	}
	break;
	case eMyStatus::SDASHATTACKDOWN:
	{
		sprite = m_playerSuperSecondAttackEffect[1]->GetAnimationClip()->GetFram(m_playerSuperSecondAttackEffect[1]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSuperSecondAttackEffect[1]->Play();
	}
	break;
	case eMyStatus::SDASHATTACKUP:
	{
		sprite = m_playerSuperSecondAttackEffect[2]->GetAnimationClip()->GetFram(m_playerSuperSecondAttackEffect[2]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSuperSecondAttackEffect[2]->Play();
	}
	break;
	case eMyStatus::SDASHATTACKLEFT:
	{
		sprite = m_playerSuperSecondAttackEffect[3]->GetAnimationClip()->GetFram(m_playerSuperSecondAttackEffect[3]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSuperSecondAttackEffect[3]->Play();
	}
	break;
	default:
		break;
	}
}

void AnimationManager::PlayerHitEffect(CObjectBase* object, CVector2D cvector)
{
	if (object == nullptr)
		return;

	CSprite* sprite;

	switch (object->GetStatus())
	{
	case eMyStatus::HITRIGHT:
	{
		sprite = m_playerHitEffect[0]->GetAnimationClip()->GetFram(m_playerHitEffect[0]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerHitEffect[0]->Play();
	}
	break;
	case eMyStatus::HITDOWN:
	{
		sprite = m_playerHitEffect[1]->GetAnimationClip()->GetFram(m_playerHitEffect[1]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerHitEffect[1]->Play();
	}
	break;
	case eMyStatus::HITUP:
	{
		sprite = m_playerHitEffect[2]->GetAnimationClip()->GetFram(m_playerHitEffect[2]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerHitEffect[2]->Play();
	}
	break;
	case eMyStatus::HITLEFT:
	{
		sprite = m_playerHitEffect[3]->GetAnimationClip()->GetFram(m_playerHitEffect[3]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerHitEffect[3]->Play();
	}
	break;
	default:
		break;
	}
}

void AnimationManager::PlayerDashEffect(CObjectBase* object, CVector2D cvector)
{
	if (object == nullptr)
		return;

	CSprite* sprite;

	switch (object->GetStatus())
	{
		// 플레이어 기본일때
	case eMyStatus::AFTERDASHRIGHT:
	{
		sprite = m_playerDashEffect[0]->GetAnimationClip()->GetFram(m_playerDashEffect[0]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[0]->Play();
	}
	break;
	case eMyStatus::AFTERDASHDOWN:
	{
		sprite = m_playerDashEffect[1]->GetAnimationClip()->GetFram(m_playerDashEffect[1]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[1]->Play();
	}
	break;
	case eMyStatus::AFTERDASHUP:
	{
		sprite = m_playerDashEffect[2]->GetAnimationClip()->GetFram(m_playerDashEffect[2]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[2]->Play();
	}
	break;
	case eMyStatus::AFTERDASHLEFT:
	{
		sprite = m_playerDashEffect[3]->GetAnimationClip()->GetFram(m_playerDashEffect[3]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[3]->Play();
	}
	break;
	case eMyStatus::AFTERDASHDOWNLEFT:
	{
		sprite = m_playerDashEffect[3]->GetAnimationClip()->GetFram(m_playerDashEffect[3]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[3]->Play();
	}
	break;
	case eMyStatus::AFTERDASHDOWNRIGHT:
	{
		sprite = m_playerDashEffect[1]->GetAnimationClip()->GetFram(m_playerDashEffect[1]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[1]->Play();
	}
	break;
	case eMyStatus::AFTERDASHUPLEFT:
	{
		sprite = m_playerDashEffect[2]->GetAnimationClip()->GetFram(m_playerDashEffect[2]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[2]->Play();
	}
	break;
	case eMyStatus::AFTERDASHUPRIGHT:
	{
		sprite = m_playerDashEffect[0]->GetAnimationClip()->GetFram(m_playerDashEffect[0]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[0]->Play();
	}
	break;
	// 플레이어 필살기일때
	case eMyStatus::SAFTERDASHRIGHT:
	{
		sprite = m_playerDashEffect[0]->GetAnimationClip()->GetFram(m_playerDashEffect[0]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[0]->Play();
	}
	break;
	case eMyStatus::SAFTERDASHDOWN:
	{
		sprite = m_playerDashEffect[1]->GetAnimationClip()->GetFram(m_playerDashEffect[1]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[1]->Play();
	}
	break;
	case eMyStatus::SAFTERDASHUP:
	{
		sprite = m_playerDashEffect[2]->GetAnimationClip()->GetFram(m_playerDashEffect[2]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[2]->Play();
	}
	break;
	case eMyStatus::SAFTERDASHLEFT:
	{
		sprite = m_playerDashEffect[3]->GetAnimationClip()->GetFram(m_playerDashEffect[3]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[3]->Play();
	}
	break;
	case eMyStatus::SAFTERDASHDOWNLEFT:
	{
		sprite = m_playerDashEffect[3]->GetAnimationClip()->GetFram(m_playerDashEffect[3]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[3]->Play();
	}
	break;
	case eMyStatus::SAFTERDASHDOWNRIGHT:
	{
		sprite = m_playerDashEffect[1]->GetAnimationClip()->GetFram(m_playerDashEffect[1]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[1]->Play();
	}
	break;
	case eMyStatus::SAFTERDASHUPLEFT:
	{
		sprite = m_playerDashEffect[2]->GetAnimationClip()->GetFram(m_playerDashEffect[2]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[2]->Play();
	}
	break;
	case eMyStatus::SAFTERDASHUPRIGHT:
	{
		sprite = m_playerDashEffect[0]->GetAnimationClip()->GetFram(m_playerDashEffect[0]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerDashEffect[0]->Play();
	}
	break;
	default:
		break;
	}
}

void AnimationManager::PlayerWalkEffect(CObjectBase* object, CVector2D cvector)
{
	if (object == nullptr)
		return;

	CSprite* sprite;
	switch (object->GetStatus())
	{
	case eMyStatus::MOVERIGHT:
	{
		sprite = m_playerWalkEffect[0]->GetAnimationClip()->GetFram(m_playerWalkEffect[0]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerWalkEffect[0]->Play();
	}
	break;
	case eMyStatus::MOVEDOWN:
	{
		sprite = m_playerWalkEffect[1]->GetAnimationClip()->GetFram(m_playerWalkEffect[1]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerWalkEffect[1]->Play();
	}
	break;
	case eMyStatus::MOVEUP:
	{
		sprite = m_playerWalkEffect[2]->GetAnimationClip()->GetFram(m_playerWalkEffect[2]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerWalkEffect[2]->Play();
	}
	break;
	case eMyStatus::MOVELEFT:
	{
		sprite = m_playerWalkEffect[3]->GetAnimationClip()->GetFram(m_playerWalkEffect[3]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerWalkEffect[3]->Play();
	}
	break;
	case eMyStatus::SMOVERIGHT:
	{
		sprite = m_playerSuperWalkEffect[0]->GetAnimationClip()->GetFram(m_playerSuperWalkEffect[0]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSuperWalkEffect[0]->Play();
	}
	break;
	case eMyStatus::SMOVEDOWN:
	{
		sprite = m_playerSuperWalkEffect[1]->GetAnimationClip()->GetFram(m_playerSuperWalkEffect[1]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSuperWalkEffect[1]->Play();
	}
	break;
	case eMyStatus::SMOVEUP:
	{
		sprite = m_playerSuperWalkEffect[2]->GetAnimationClip()->GetFram(m_playerSuperWalkEffect[2]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSuperWalkEffect[2]->Play();
	}
	break;
	case eMyStatus::SMOVELEFT:
	{
		sprite = m_playerSuperWalkEffect[3]->GetAnimationClip()->GetFram(m_playerSuperWalkEffect[3]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		m_playerSuperWalkEffect[3]->Play();
	}
	break;

	default:
		break;
	}
}

void AnimationManager::CloseHitEffect(CObjectBase* object, CObjectBase* monster, CVector2D cvector)
{
	if (object == nullptr || monster == nullptr)
		return;
	CSprite* sprite;
	CCloseObject* closeobject = dynamic_cast<CCloseObject*>(monster);

	if (object->GetStatus() == eMyStatus::ATTACKRIGHT || object->GetStatus() == eMyStatus::ATTACKDOWN
		|| object->GetStatus() == eMyStatus::ATTACKUP || object->GetStatus() == eMyStatus::ATTACKLEFT)
	{
		switch (object->GetStatus())
		{
		case eMyStatus::ATTACKRIGHT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->HitEffect[0]->GetAnimationClip()->GetFram(closeobject->HitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->HitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::ATTACKDOWN:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->HitEffect[1]->GetAnimationClip()->GetFram(closeobject->HitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->HitEffect[1]->Play();
			}
		}
		break;
		case eMyStatus::ATTACKUP:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->HitEffect[0]->GetAnimationClip()->GetFram(closeobject->HitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->HitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::ATTACKLEFT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->HitEffect[1]->GetAnimationClip()->GetFram(closeobject->HitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->HitEffect[1]->Play();
			}
		}
		break;
		default:
			break;
		}
	}

	else if (object->GetStatus() == eMyStatus::SATTACKRIGHT || object->GetStatus() == eMyStatus::SATTACKDOWN
		|| object->GetStatus() == eMyStatus::SATTACKUP || object->GetStatus() == eMyStatus::SATTACKLEFT)
	{
		switch (object->GetStatus())
		{
		case eMyStatus::SATTACKRIGHT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(closeobject->SuperHitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->SuperHitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::SATTACKDOWN:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->SuperHitEffect[1]->GetAnimationClip()->GetFram(closeobject->SuperHitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->SuperHitEffect[1]->Play();
			}
		}
		break;
		case eMyStatus::SATTACKUP:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(closeobject->SuperHitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->SuperHitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::SATTACKLEFT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->SuperHitEffect[1]->GetAnimationClip()->GetFram(closeobject->SuperHitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->SuperHitEffect[1]->Play();
			}
		}
		break;



		default:
			break;
		}
	}

	else if (object->GetStatus() == eMyStatus::SDASHATTACKRIGHT || object->GetStatus() == eMyStatus::SDASHATTACKDOWN
		|| object->GetStatus() == eMyStatus::SDASHATTACKUP || object->GetStatus() == eMyStatus::SDASHATTACKLEFT)
	{
		switch (object->GetStatus())
		{
		case eMyStatus::SDASHATTACKRIGHT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(closeobject->SuperHitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->SuperHitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::SDASHATTACKDOWN:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->SuperHitEffect[1]->GetAnimationClip()->GetFram(closeobject->SuperHitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->SuperHitEffect[1]->Play();
			}
		}
		break;
		case eMyStatus::SDASHATTACKUP:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(closeobject->SuperHitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->SuperHitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::SDASHATTACKLEFT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->SuperHitEffect[1]->GetAnimationClip()->GetFram(closeobject->SuperHitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->SuperHitEffect[1]->Play();
			}
		}
		break;



		default:
			break;
		}
	}

	else if (object->GetStatus() == eMyStatus::DASHATTACKRIGHT || object->GetStatus() == eMyStatus::DASHATTACKDOWN
		|| object->GetStatus() == eMyStatus::DASHATTACKUP || object->GetStatus() == eMyStatus::DASHATTACKLEFT)
	{
		switch (object->GetStatus())
		{
		case eMyStatus::DASHATTACKRIGHT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->HitEffect[0]->GetAnimationClip()->GetFram(closeobject->HitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->HitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::DASHATTACKDOWN:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->HitEffect[1]->GetAnimationClip()->GetFram(closeobject->HitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->HitEffect[1]->Play();
			}
		}
		break;
		case eMyStatus::DASHATTACKUP:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->HitEffect[0]->GetAnimationClip()->GetFram(closeobject->HitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->HitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::DASHATTACKLEFT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = closeobject->HitEffect[1]->GetAnimationClip()->GetFram(closeobject->HitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				closeobject->HitEffect[1]->Play();
			}
		}
		break;
		default:
			break;
		}

	}
}

void AnimationManager::RangeHitEffect(CObjectBase* object, CObjectBase* monster, CVector2D cvector)
{
	if (object == nullptr || monster == nullptr)
		return;
	CSprite* sprite;
	CRangeObject* rangeobject = dynamic_cast<CRangeObject*>(monster);

	if (object->GetStatus() == eMyStatus::ATTACKRIGHT || object->GetStatus() == eMyStatus::ATTACKDOWN
		|| object->GetStatus() == eMyStatus::ATTACKUP || object->GetStatus() == eMyStatus::ATTACKLEFT)
	{
		switch (object->GetStatus())
		{
		case eMyStatus::ATTACKRIGHT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->HitEffect[0]->GetAnimationClip()->GetFram(rangeobject->HitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->HitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::ATTACKDOWN:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->HitEffect[1]->GetAnimationClip()->GetFram(rangeobject->HitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->HitEffect[1]->Play();
			}
		}
		break;
		case eMyStatus::ATTACKUP:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->HitEffect[0]->GetAnimationClip()->GetFram(rangeobject->HitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->HitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::ATTACKLEFT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->HitEffect[1]->GetAnimationClip()->GetFram(rangeobject->HitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->HitEffect[1]->Play();
			}
		}
		break;
		default:
			break;
		}

	}
	else if (object->GetStatus() == eMyStatus::SATTACKRIGHT || object->GetStatus() == eMyStatus::SATTACKDOWN
		|| object->GetStatus() == eMyStatus::SATTACKUP || object->GetStatus() == eMyStatus::SATTACKLEFT)
	{
		switch (object->GetStatus())
		{
		case eMyStatus::SATTACKRIGHT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(rangeobject->SuperHitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->SuperHitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::SATTACKDOWN:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->SuperHitEffect[1]->GetAnimationClip()->GetFram(rangeobject->SuperHitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->SuperHitEffect[1]->Play();
			}
		}
		break;
		case eMyStatus::SATTACKUP:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(rangeobject->SuperHitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->SuperHitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::SATTACKLEFT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->SuperHitEffect[1]->GetAnimationClip()->GetFram(rangeobject->SuperHitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->SuperHitEffect[1]->Play();
			}
		}
		break;
		default:
			break;
		}
	}

	else if (object->GetStatus() == eMyStatus::SDASHATTACKRIGHT || object->GetStatus() == eMyStatus::SDASHATTACKDOWN
		|| object->GetStatus() == eMyStatus::SDASHATTACKUP || object->GetStatus() == eMyStatus::SDASHATTACKLEFT)
	{
		switch (object->GetStatus())
		{
		case eMyStatus::SDASHATTACKRIGHT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(rangeobject->SuperHitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->SuperHitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::SDASHATTACKDOWN:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->SuperHitEffect[1]->GetAnimationClip()->GetFram(rangeobject->SuperHitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->SuperHitEffect[1]->Play();
			}
		}
		break;
		case eMyStatus::SDASHATTACKUP:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(rangeobject->SuperHitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->SuperHitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::SDASHATTACKLEFT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->SuperHitEffect[1]->GetAnimationClip()->GetFram(rangeobject->SuperHitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->SuperHitEffect[1]->Play();
			}
		}
		break;



		default:
			break;
		}
	}

	else if (object->GetStatus() == eMyStatus::DASHATTACKRIGHT || object->GetStatus() == eMyStatus::DASHATTACKDOWN
		|| object->GetStatus() == eMyStatus::DASHATTACKUP || object->GetStatus() == eMyStatus::DASHATTACKLEFT)
	{
		switch (object->GetStatus())
		{
		case eMyStatus::DASHATTACKRIGHT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->HitEffect[0]->GetAnimationClip()->GetFram(rangeobject->HitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->HitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::DASHATTACKDOWN:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->HitEffect[1]->GetAnimationClip()->GetFram(rangeobject->HitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->HitEffect[1]->Play();
			}
		}
		break;
		case eMyStatus::DASHATTACKUP:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->HitEffect[0]->GetAnimationClip()->GetFram(rangeobject->HitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->HitEffect[0]->Play();
			}
		}
		break;
		case eMyStatus::DASHATTACKLEFT:
		{
			if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
			{
				sprite = rangeobject->HitEffect[1]->GetAnimationClip()->GetFram(rangeobject->HitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				rangeobject->HitEffect[1]->Play();
			}
		}
		break;
		default:
			break;
		}
	}
}

void AnimationManager::BossHitEffect(CObjectBase* object, CObjectBase* monster, CVector2D cvector)
{
	if (object == nullptr || monster == nullptr)
		return;
	CSprite* sprite;
	CBossObject* bossobject = dynamic_cast<CBossObject*>(monster);

	if (bossobject->m_isHit)
	{
		if (object->GetStatus() == eMyStatus::ATTACKRIGHT || object->GetStatus() == eMyStatus::ATTACKDOWN
			|| object->GetStatus() == eMyStatus::ATTACKUP || object->GetStatus() == eMyStatus::ATTACKLEFT)
		{
			switch (object->GetStatus())
			{
			case eMyStatus::ATTACKRIGHT:
			{
				sprite = bossobject->HitEffect[0]->GetAnimationClip()->GetFram(bossobject->HitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->HitEffect[0]->Play();
			}
			break;
			case eMyStatus::ATTACKDOWN:
			{
				sprite = bossobject->HitEffect[1]->GetAnimationClip()->GetFram(bossobject->HitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->HitEffect[1]->Play();
			}
			break;
			case eMyStatus::ATTACKUP:
			{
				sprite = bossobject->HitEffect[0]->GetAnimationClip()->GetFram(bossobject->HitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->HitEffect[0]->Play();
			}
			break;
			case eMyStatus::ATTACKLEFT:
			{
				sprite = bossobject->HitEffect[1]->GetAnimationClip()->GetFram(bossobject->HitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->HitEffect[1]->Play();
			}
			break;
			default:
				break;
			}

		}
		else if (object->GetStatus() == eMyStatus::SATTACKRIGHT || object->GetStatus() == eMyStatus::SATTACKDOWN
			|| object->GetStatus() == eMyStatus::SATTACKUP || object->GetStatus() == eMyStatus::SATTACKLEFT)
		{
			switch (object->GetStatus())
			{
			case eMyStatus::SATTACKRIGHT:
			{
				sprite = bossobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(bossobject->SuperHitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->SuperHitEffect[0]->Play();
			}
			break;
			case eMyStatus::SATTACKDOWN:
			{
				switch (object->GetStatus())
				{
				case eMyStatus::SATTACKRIGHT:
				{
					sprite = bossobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(bossobject->SuperHitEffect[0]->GetCurrentIdx());
					m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
					bossobject->SuperHitEffect[0]->Play();
				}
				break;
				case eMyStatus::SATTACKDOWN:
				{
					sprite = bossobject->SuperHitEffect[1]->GetAnimationClip()->GetFram(bossobject->SuperHitEffect[1]->GetCurrentIdx());
					m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
					bossobject->SuperHitEffect[1]->Play();
				}
				break;
				case eMyStatus::SATTACKUP:
				{
					sprite = bossobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(bossobject->SuperHitEffect[0]->GetCurrentIdx());
					m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
					bossobject->SuperHitEffect[0]->Play();
				}
				break;
				case eMyStatus::SATTACKLEFT:
				{
					sprite = bossobject->SuperHitEffect[1]->GetAnimationClip()->GetFram(bossobject->SuperHitEffect[1]->GetCurrentIdx());
					m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
					bossobject->SuperHitEffect[1]->Play();
				}
				break;
				default:
					break;
				}
			}
			break;
			case eMyStatus::SATTACKUP:
			{
				sprite = bossobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(bossobject->SuperHitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->SuperHitEffect[0]->Play();
			}
			break;
			case eMyStatus::SATTACKLEFT:
			{
				sprite = bossobject->SuperHitEffect[1]->GetAnimationClip()->GetFram(bossobject->SuperHitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->SuperHitEffect[1]->Play();
			}
			break;
			default:
				break;
			}
		}

		else if (object->GetStatus() == eMyStatus::SDASHATTACKRIGHT || object->GetStatus() == eMyStatus::SDASHATTACKDOWN
			|| object->GetStatus() == eMyStatus::SDASHATTACKUP || object->GetStatus() == eMyStatus::SDASHATTACKLEFT)
		{
			switch (object->GetStatus())
			{
			case eMyStatus::SDASHATTACKRIGHT:
			{
				sprite = bossobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(bossobject->SuperHitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->SuperHitEffect[0]->Play();
			}
			break;
			case eMyStatus::SDASHATTACKDOWN:
			{
				sprite = bossobject->SuperHitEffect[1]->GetAnimationClip()->GetFram(bossobject->SuperHitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->SuperHitEffect[1]->Play();
			}
			break;
			case eMyStatus::SDASHATTACKUP:
			{
				sprite = bossobject->SuperHitEffect[0]->GetAnimationClip()->GetFram(bossobject->SuperHitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->SuperHitEffect[0]->Play();
			}
			break;
			case eMyStatus::SDASHATTACKLEFT:
			{
				if (monster->GetStatus() == eMyStatus::HITRIGHT || monster->GetStatus() == eMyStatus::HITDOWN || monster->GetStatus() == eMyStatus::HITUP || monster->GetStatus() == eMyStatus::HITLEFT)
				{
					sprite = bossobject->SuperHitEffect[1]->GetAnimationClip()->GetFram(bossobject->SuperHitEffect[1]->GetCurrentIdx());
					m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
					bossobject->SuperHitEffect[1]->Play();
				}
			}
			break;



			default:
				break;
			}
		}

		else if (object->GetStatus() == eMyStatus::DASHATTACKRIGHT || object->GetStatus() == eMyStatus::DASHATTACKDOWN
			|| object->GetStatus() == eMyStatus::DASHATTACKUP || object->GetStatus() == eMyStatus::DASHATTACKLEFT)
		{
			switch (object->GetStatus())
			{
			case eMyStatus::DASHATTACKRIGHT:
			{
				sprite = bossobject->HitEffect[0]->GetAnimationClip()->GetFram(bossobject->HitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->HitEffect[0]->Play();
			}
			break;
			case eMyStatus::DASHATTACKDOWN:
			{

				sprite = bossobject->HitEffect[1]->GetAnimationClip()->GetFram(bossobject->HitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->HitEffect[1]->Play();
			}
			break;
			case eMyStatus::DASHATTACKUP:
			{
				sprite = bossobject->HitEffect[0]->GetAnimationClip()->GetFram(bossobject->HitEffect[0]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->HitEffect[0]->Play();
			}
			break;
			case eMyStatus::DASHATTACKLEFT:
			{
				sprite = bossobject->HitEffect[1]->GetAnimationClip()->GetFram(bossobject->HitEffect[1]->GetCurrentIdx());
				m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, monster->m_transform->TransformMatrix(), cvector);
				bossobject->HitEffect[1]->Play();
			}
			break;
			default:
				break;
			}
		}
	}
}

void AnimationManager::RangeArrowEffect(CArrowObject* object, CVector2D cvector)
{
	if (object == nullptr)
		return;

	CSprite* sprite;
	if (object->m_isBreak == true)
	{
		sprite = object->AttackEffect[0]->GetAnimationClip()->GetFram(object->AttackEffect[0]->GetCurrentIdx());
		m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		object->AttackEffect[0]->ArrowPlay(object);

		//sprite = object->AttackEffect[1]->GetAnimationClip()->GetFram(object->AttackEffect[1]->GetCurrentIdx());
		//m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
		//object->AttackEffect[1]->Play();
	}
}

//}
//
//void AnimationManager::MonsterAttackEffect(CObjectBase* object, CVector2D cvector)
//{
//	if (object == nullptr)
//		return;
//
//	CSprite* sprite;
//
//	if (object->m_isBreak == true)
//	{
//		/*if ()
//		{*/
//			sprite = object->AttackEffect[0]->GetAnimationClip()->GetFram(object->AttackEffect[0]->GetCurrentIdx());
//			m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
//			monster->AttackEffect[0]->LastPlay();
//		/*}
//		else if ()
//		{
//			sprite = monster->AttackEffect[1]->GetAnimationClip()->GetFram(monster->AttackEffect[1]->GetCurrentIdx());
//			m_pEngine->DrawSprite(sprite, sprite->m_sheetPos, CVector2D(1, 1), 1, object->m_transform->TransformMatrix(), cvector);
//			monster->AttackEffect[1]->LastPlay();
//		}*/
//	}
//}

