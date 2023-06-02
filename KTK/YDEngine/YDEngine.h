#pragma once

#pragma comment(lib, "d2d1.lib")	// Direct2D API를 사용하기 위해서 참조해야 하는 라이브러리
#pragma comment(lib, "dwrite.lib")	// writefactory를 쓰기 위해 참조해야하는 라이브러리
#pragma comment(lib, "windowscodecs.lib") // WIC를 쓰기 위해 참조해야하는 라이브러리

#include <windows.h>

#include <stdio.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <cstring>
#include "DRMacro.h"
#include <vector> //원래 안해도 돌아가지 않나? 모르겠네

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
	//이 메서드는 창의 장치 종속 리소스, 렌더링 대상 및 브러시를 만든다. 
	HRESULT CreateDeviceResources();

	//CreateDeviceResources에서 만든 렌더링 대상과 브러시를 해제해줌
	void DiscardDeviceResources();

private:
	HWND _hWnd;
	//DeviceResources를 가져오는 변수
	HRESULT _IsDDResReady;
	ID2D1Factory* _pFactory;		// Direct2D 리소스를 만드는 Factory
	ID2D1HwndRenderTarget* _pRenderTarget;	// 그림을 그릴 렌더타겟
	D2D1_SIZE_F _pRenderTargetSize;

	//텍스트관련 변수
	IDWriteFactory* _pWriteFactory; //텍스트를 그리기위한 팩토리
	IDWriteTextFormat* _pTextFormat;
	const WCHAR* wszText_;

	//WIC관련 객체(이미지)를 생성하기 위한 Factory 객체 선언
	IWICImagingFactory* _pWicFactory;
	//테스트용으로 render target에서 사용가능한 기본 비트맵 객체
	ID2D1Bitmap* pBitMap;
	D2D1_RECT_F imageRect; //PNG이미지를 출력할 좌표
	//Sprite Sheet를 저장해놓고 여기서 잘라서 사용
	std::vector<ID2D1Bitmap*> spriteSheets;
	std::vector<ID2D1Bitmap*> spriteMapSheets;
	ID2D1Bitmap* BlackBitmap;
	ID2D1Bitmap* spritesample;
	ID2D1SolidColorBrush* _pNowBrush;

public:
	// WIC(windows imaging component)
	// 이미지나 영상을 압축하거나 해제,변환하는 컴포넌트이고 이미지 정보를 읽어서 Direct2D에서 사용 가능한 형식으로 변환
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


	//텍스트 출력 함수
	void DrawTextFormat(int x, int y, const char* pch, ...);

	//DrawRect를 그려주는 함수
	void DrawRect(RECT rect, int r, int g, int b);

	void FadeInOut(float opacity);


	D2D1_SIZE_F GetRenderTargetSize() const { return _pRenderTargetSize; }
};