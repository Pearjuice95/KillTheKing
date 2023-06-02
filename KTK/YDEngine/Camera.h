#pragma once
#include "CVector2D.h"
#include <d2d1.h>
#include <d2d1helper.h>

class CObjectBase;
class Transform;

class Camera
{
private:
	Camera();
	~Camera();

private:
	CObjectBase* m_object;
	CVector2D m_cameraPosition;
	CVector2D m_size;
	float m_top;
	float m_right;
	float m_left;
	float m_bottom;

public:
	static Camera* GetInsance()
	{
		static Camera instance;
		return &instance;
	}

public:
	void Initialize(CObjectBase* object);
	CVector2D GetCameraVector() { return m_cameraPosition; }
	void Update(int x, int y);
	void SetCameraSize(int x, int y);
	void ChangeObject(CObjectBase* object);
	void WallException(int stage);
};