#pragma once
#include "Stage00.h"
#include "Stage01.h"
#include "SceneBase.h"
#include "enum.h"
#include "CSprite.h"
#include <vector>

class YDEngine;
class CBackGroundObject;
class CTitle;
class Stage00;
class Stage01;
class Stage02;
class Stage03;
class CEnding;

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

	YDEngine* m_pEngine;
	CBackGroundObject* m_pBackGround;

	eScene m_prevStage;
	//SceneBase* m_curScene;
	bool m_isLoad;			// 씬을 로드할 때 로드되었는지 확인하는 용도
	bool m_isEnd;			//
	bool m_isNextScene;		// 다음 씬을 로드해야하는지 여부 결정

	bool m_isStage1Clear;	// 스테이지 1이 깨졌는지 저장용 데이터
	bool m_isStage2clear;	// 스테이지 2가 깨졌는지 저장용 데이터

	//std::vector<SceneBase*> m_scenePool;
	CTitle* m_TitleStage; // 타이틀 화면
	Stage00* m_stage00; // 튜톨리얼 씬
	Stage01* m_stage01; // LV.1 씬
	Stage02* m_stage02; // LV.2 씬
	Stage03* m_stage03; // BOSS 씬
	CEnding* m_EndingStage; // 엔딩 씬

	// 페이드 인 아웃 관련 변수
	bool m_isFadein;
	bool m_wait;
	bool m_ready;
	float m_fadeinTime;
	float m_fadeinCount;
	float m_timer;


	int test = 0;

	std::vector<CSprite*> GateOpen;

public:
	void Initialize(YDEngine* engine);
	void Update();
	void Render();

	void SceneStatus();
	void NextScene();

	// 타이틀
	void LoadTitle();
	void EndTitle();

	// 스테이지 1
	void LoadStage00();
	void LoadStage01();
	void LoadStage02();
	void LoadStage03();
	void EndStage00();
	void EndStage01();
	void EndStage02();
	void EndStage03();
	void ReStart();
	void LoadTitleScene();
	void LoadDieScene();
	void LoadEndingScene();

	void FadeInOut();

	int m_sceneNumber;
};

