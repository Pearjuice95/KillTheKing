#pragma once

/// <summary>
/// �� Ŭ������ �������̽�
/// </summary>
enum eSceneState
{
	TITLE,STAGE1,STAGE2,STAGE3,ENDING,
};


class CScene
{
public:
	CScene();
	~CScene();


public:
	virtual void InitScenen() = 0;
	virtual void UpdateScene() = 0;
	virtual void RenderScene() = 0;
	virtual void ReleaseScene() = 0;
	
};

