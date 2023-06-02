#pragma once

/// <summary>
/// 씬매니저 싱글톤으로 만들어서 돌릴 거임
/// </summary>

class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	static CSceneManager* GetInstance()
	{
		return &m_instance;
	}

private:
	static CSceneManager m_instance;



};

