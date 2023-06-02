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
	bool m_isLoad;			// ���� �ε��� �� �ε�Ǿ����� Ȯ���ϴ� �뵵
	bool m_isEnd;			//
	bool m_isNextScene;		// ���� ���� �ε��ؾ��ϴ��� ���� ����

	bool m_isStage1Clear;	// �������� 1�� �������� ����� ������
	bool m_isStage2clear;	// �������� 2�� �������� ����� ������

	//std::vector<SceneBase*> m_scenePool;
	CTitle* m_TitleStage; // Ÿ��Ʋ ȭ��
	Stage00* m_stage00; // Ʃ�縮�� ��
	Stage01* m_stage01; // LV.1 ��
	Stage02* m_stage02; // LV.2 ��
	Stage03* m_stage03; // BOSS ��
	CEnding* m_EndingStage; // ���� ��

	// ���̵� �� �ƿ� ���� ����
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

	// Ÿ��Ʋ
	void LoadTitle();
	void EndTitle();

	// �������� 1
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

