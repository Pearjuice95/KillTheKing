#pragma once

/// <summary>
/// ���Ŵ��� �̱������� ���� ���� ����
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

