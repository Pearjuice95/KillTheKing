#pragma once

#pragma comment(lib, "d2d1.lib")	// Direct2D API�� ����ϱ� ���ؼ� �����ؾ� �ϴ� ���̺귯��
#pragma comment(lib, "dwrite.lib")	// writefactory�� ���� ���� �����ؾ��ϴ� ���̺귯��
#pragma comment(lib, "windowscodecs.lib") // WIC�� ���� ���� �����ؾ��ϴ� ���̺귯��

#include <windows.h>

#include <stdio.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <cstring>
#include "DRMacro.h"
#include <vector> //���� ���ص� ���ư��� �ʳ�? �𸣰ڳ�

#include "CVector2D.h"

class CSprite;
class CVector2D;

class YDEngine
{
public:
	YDEngine();
	~YDEngine();

public:
	void Initialize(HWND hWnd);

	void BeginRender();
	void EndRender();

private:
	//�� �޼���� â�� ��ġ ���� ���ҽ�, ������ ��� �� �귯�ø� �����. 
	HRESULT CreateDeviceResources();

	//CreateDeviceResources���� ���� ������ ���� �귯�ø� ��������
	void DiscardDeviceResources();

private:
	HWND _hWnd;
	//DeviceResources�� �������� ����
	HRESULT _IsDDResReady;
	ID2D1Factory* _pFactory;		// Direct2D ���ҽ��� ����� Factory
	ID2D1HwndRenderTarget* _pRenderTarget;	// �׸��� �׸� ����Ÿ��
	D2D1_SIZE_F _pRenderTargetSize;

	//�ؽ�Ʈ���� ����
	IDWriteFactory* _pWriteFactory; //�ؽ�Ʈ�� �׸������� ���丮
	IDWriteTextFormat* _pTextFormat;
	const WCHAR* wszText_;

	//WIC���� ��ü(�̹���)�� �����ϱ� ���� Factory ��ü ����
	IWICImagingFactory* _pWicFactory;
	//�׽�Ʈ������ render target���� ��밡���� �⺻ ��Ʈ�� ��ü
	ID2D1Bitmap* pBitMap;
	D2D1_RECT_F imageRect; //PNG�̹����� ����� ��ǥ
	//Sprite Sheet�� �����س��� ���⼭ �߶� ���
	std::vector<ID2D1Bitmap*> spriteSheets;
	std::vector<ID2D1Bitmap*> spriteMapSheets;
	ID2D1Bitmap* BlackBitmap;
	ID2D1Bitmap* spritesample;
	ID2D1SolidColorBrush* _pNowBrush;

public:
	// WIC(windows imaging component)
	// �̹����� ������ �����ϰų� ����,��ȯ�ϴ� ������Ʈ�̰� �̹��� ������ �о Direct2D���� ��� ������ �������� ��ȯ
	HRESULT LoadBitmapFromFile(UINT _width, UINT _Height, const wchar_t* filepath, ID2D1Bitmap** bitmap);

	void LoadSpriteSheet(const wchar_t* filepath);

	void LoadMapSpriteSheet(const wchar_t* filepath);

	CSprite* LoadSpriteFromData(int sheetidx, CVector2D sheetpos, int width, int height, CVector2D pivot, float delaytime);

	CSprite* LoadMapSpriteFromData(int sheetidx, int width, int height);


	void SetBrush(int r, int g, int b, int a);

	void DrawSprite(CSprite* sprite, CVector2D pos, CVector2D printpos, float opacity, D2D1_MATRIX_3X2_F transformMatrix, CVector2D cameraPosition = CVector2D(0.f, 0.f));

	void DrawSprite(CSprite* sprite, float posx, float posy, float printposx, float printposy, float opacity);
	void DrawSprite(CSprite* sprite, float posx, float posy, float printposx, float printposy, float opacity, CVector2D camera);
	void DrawSprite(CSprite* sprite, float posx, float posy,float opacity, CVector2D camera);

	void DrawMapSprite(CSprite* sprite, float posx, float posy, float printposx, float printposy, float opacity,CVector2D cvector);


	//�ؽ�Ʈ ��� �Լ�
	void DrawTextFormat(int x, int y, const char* pch, ...);

	//DrawRect�� �׷��ִ� �Լ�
	void DrawRect(RECT rect, int r, int g, int b);

	void FadeInOut(float opacity);


	D2D1_SIZE_F GetRenderTargetSize() const { return _pRenderTargetSize; }
};