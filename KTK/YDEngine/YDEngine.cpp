#include "YDEngine.h"
#include "CVector2D.h"
#include "CSprite.h"
#include "Camera.h"

YDEngine::YDEngine()
	:_hWnd(nullptr), _IsDDResReady(S_FALSE), _pFactory(nullptr), _pRenderTarget(nullptr),
	_pRenderTargetSize(D2D1_SIZE_F())
{
}

YDEngine::~YDEngine()
{
}

void YDEngine::Initialize(HWND hWnd)
{
	HRESULT _hResult = CoInitialize(NULL);

	_hWnd = hWnd;

	HRESULT hr = S_OK;

	static const WCHAR _fontName[] = L"굴림";
	static const FLOAT _fontSize = 20;

	//Factory를 만들어준다.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_pFactory);
	//WIC 객체를 생성하기 위한 Factory 객체를 생성한다. 
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_pWicFactory));

	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(_pWriteFactory),
			reinterpret_cast<IUnknown**>(&_pWriteFactory)
		);
	}
	if (SUCCEEDED(hr))
	{
		hr = _pWriteFactory->CreateTextFormat(
			_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			_fontSize,
			L"",
			&_pTextFormat
		);
	}
	if (SUCCEEDED(hr))
	{
		//Text 정렬
		_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		//레이아웃 상자의 위쪽 및 아래쪽 가장자리를 기준으로 단락의 정렬옵션을 설정?
		//?
		_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}
	CreateDeviceResources();
	hr = S_OK;

	//파일 경로에 있는 sheet를 newsheet에 넣어준다.
	hr = LoadBitmapFromFile(2309, 1176, L"../Resourse/SpriteSheet/Black.png", &BlackBitmap);

}

void YDEngine::BeginRender()
{
	_IsDDResReady = CreateDeviceResources();

	if (SUCCEEDED(_IsDDResReady))
	{
		_pRenderTargetSize = _pRenderTarget->GetSize();

		_pRenderTarget->BeginDraw();
		_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	}
}

void YDEngine::EndRender()
{
	if (SUCCEEDED(_IsDDResReady))
	{
		HRESULT hr = _pRenderTarget->EndDraw();

		//자원을 복구하는 경우라고 하는데 정확히 몰?루
		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			DiscardDeviceResources();
		}
	}
}

HRESULT YDEngine::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!_pRenderTarget)
	{
		RECT rc;
		GetClientRect(_hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		// Create a Direct2D render target.
		hr = _pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(_hWnd, size),
			&_pRenderTarget
		);
		if (SUCCEEDED(hr))
		{
			hr = _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &_pNowBrush);
		}
	}

	return hr;;
}
/// <summary>
/// 
/// GetFrame함수로 얻은 이미지는 WIC형식의 비트맵이기 때문에 d2d에서는 바로 사용하기 어려움
/// IWICBitmap 형식의 비트맵을 D2D에서 바로 사용할수 있도록 
/// ID2D1Bitmap 형식의 비트맵으로 변환해야함
/// </summary>
HRESULT YDEngine::LoadBitmapFromFile(UINT _destWidth, UINT _destHeight, const wchar_t* filepath, ID2D1Bitmap** bitmap)
{
	HRESULT hr = S_OK;
	//압축된 이미지를 해제할 객체
	//PNG 파일은 압축되있어서 비트맵 형식으로 압축을 해제하는 디코더를 만듬
	IWICBitmapDecoder* pDecoder = nullptr;
	//특정 그림을 선택한 객체 (여러 개의 그림이 하나의 파일에 저장된경우 어떤 그림을 사용할지에 대해 선택)
	IWICBitmapFrameDecode* pFrame = nullptr;
	//이미지 변환 객체
	IWICFormatConverter* pConverter = nullptr;
	//D2D의 기본 render target에서 사용가능한 기본 비트맵 객체
	//ID2D1Bitmap* pBitmap;
	IWICBitmapScaler* pScaler = NULL;

	//WIC용 Factory 객체를 사용하여 이미지 압축 해제를 위한 객체 생성
	hr = _pWicFactory->CreateDecoderFromFilename(filepath, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);

	if (SUCCEEDED(hr))
	{
		//파일을 구성하는 이미지 중에서 첫번째 이미지를 선택한다. 
		hr = pDecoder->GetFrame(0, &pFrame);
	}
	if (SUCCEEDED(hr))
	{
		//IWICBitmap형식의 비트맵을 ID2D1Bitmap형식으로 변환하기 위한 객체 생성
		hr = _pWicFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		if (_destWidth != 0 || _destHeight != 0)
		{
			UINT oriWidth, oriHeight;
			hr = pFrame->GetSize(&oriWidth, &oriHeight);
			if (SUCCEEDED(hr))
			{
				if (_destWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(_destHeight) / static_cast<FLOAT>(oriHeight);
					_destWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(oriWidth));
				}
				else if (_destHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(_destWidth) / static_cast<FLOAT>(oriWidth);
					_destHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(oriHeight));
				}

				hr = _pWicFactory->CreateBitmapScaler(&pScaler);

				if (SUCCEEDED(hr))
				{
					// 이미지를 조절한다.
					hr = pScaler->Initialize(
						pFrame,
						_destWidth,
						_destHeight,
						WICBitmapInterpolationModeCubic
					);
				}

				if (SUCCEEDED(hr))
				{
					// 이미지를 변환할 준비를 한다.
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else
		{
			hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
		}
	}

	if (SUCCEEDED(hr))
	{
		// IWICBitmap 형식의 이미지를 ID2D1Bitmap 객체로 변환하여 생성한다.
		hr = _pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, bitmap);
	}

	SafeRelease(&pConverter);
	SafeRelease(&pFrame);
	SafeRelease(&pDecoder);
	SafeRelease(&pScaler);

	return hr;
}

//Sprite를 불러온다.
void YDEngine::LoadSpriteSheet(const wchar_t* filepath)
{
	HRESULT hr = S_OK;
	ID2D1Bitmap* newSheet = nullptr;

	//파일 경로에 있는 sheet를 newsheet에 넣어준다.
	hr = LoadBitmapFromFile(0, 0, filepath, &newSheet);

	//newsheet에 들어있는 sprite를 spritesheet에 넣어준다.
	if (SUCCEEDED(hr))
		spriteSheets.push_back(newSheet); //이걸 나중에 MAP 으로 바꿔서 Sprite idx와 연동가능할듯
}

void YDEngine::LoadMapSpriteSheet(const wchar_t* filepath)
{
	HRESULT hr = S_OK;
	ID2D1Bitmap* newSheet = nullptr;

	//파일 경로에 있는 sheet를 newsheet에 넣어준다.
	hr = LoadBitmapFromFile(0, 0, filepath, &newSheet);

	//newsheet에 들어있는 sprite를 spritesheet에 넣어준다.
	if (SUCCEEDED(hr))
		spriteMapSheets.push_back(newSheet); //이걸 나중에 MAP 으로 바꿔서 Sprite idx와 연동가능할듯
}

CSprite* YDEngine::LoadSpriteFromData(int sheetidx, CVector2D sheetpos, int width, int height, CVector2D pivot, float delaytime)
{
	CSprite* newSprite = new CSprite(sheetidx, sheetpos, width, height, pivot, delaytime);

	return newSprite;
}

CSprite* YDEngine::LoadMapSpriteFromData(int sheetidx, int width = 171, int height = 171)
{
	CSprite* newSprite = new CSprite(sheetidx, CVector2D(0.f, 0.f), width, height, CVector2D(0.f, 0.f), 0);

	return newSprite;
}

void YDEngine::SetBrush(int r, int g, int b, int a)
{
	SafeRelease(&_pNowBrush); //일단 먼저 해제를 해줘야한다.

	_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(r, g, b, a)), &_pNowBrush);
}

//Sprite를 그려준다.
void YDEngine::DrawSprite(CSprite* sprite, CVector2D pos, CVector2D printpos, float opacity, D2D1_MATRIX_3X2_F transformMatrix, CVector2D cameraPosition)
{
	///test
	/*RECT r;
	GetClientRect(_hWnd, &r);
	imageRect.right = (float)r.right;
	imageRect.bottom = (float)r.bottom;*/

	//잘라야할 Sprite Sheet를 가져온다.(통짜 이미지를 가져옴)
	ID2D1Bitmap* _SpriteSheet = spriteSheets[sprite->m_spriteSheetIdx];

	float xsize = sprite->m_sheetWidth / 10;
	float ysize = sprite->m_sheetHeight / 10;

	if (_SpriteSheet != NULL)
	{
		// transform에 카메라 좌표를 넣어줘야한다. 
		D2D1_MATRIX_3X2_F _temp = transformMatrix;
		_temp.dx -= cameraPosition.x;
		_temp.dy -= cameraPosition.y;

		_pRenderTarget->SetTransform(_temp);
		// LoadSpriteSheet(filepath);
		// 어디다 출력할지 , sheet 원본 좌표 순이다.
		/*_pRenderTarget->DrawBitmap(_SpriteSheet, D2D1::RectF(5 * xsize * sprite->m_sheetPivot.x, 5 * ysize * sprite->m_sheetPivot.y, static_cast<float>(sprite->m_sheetWidth) + (5 * xsize * sprite->m_sheetPivot.x), static_cast<float>(sprite->m_sheetHeight) + (5 * ysize * sprite->m_sheetPivot.y)),
			opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(static_cast<float>(sprite->m_sheetPos.x), static_cast<float>(sprite->m_sheetPos.y), static_cast<float>(sprite->m_sheetPos.x + sprite->m_sheetWidth), static_cast<float>(sprite->m_sheetPos.y + sprite->m_sheetHeight)));*/

			// pivot 적용한 버전
			//_pRenderTarget->DrawBitmap(_SpriteSheet, D2D1::RectF(printpos.x + (5 * xsize * sprite->m_sheetPivot.x), printpos.y + (5 * ysize * sprite->m_sheetPivot.y), printpos.x + static_cast<float>(sprite->m_sheetWidth) + (5 * xsize * sprite->m_sheetPivot.x), printpos.y + static_cast<float>(sprite->m_sheetHeight) + (5 * ysize * sprite->m_sheetPivot.y)),
			//	opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			//	D2D1::RectF(static_cast<float>(sprite->m_sheetPos.x), static_cast<float>(sprite->m_sheetPos.y), static_cast<float>(sprite->m_sheetPos.x + sprite->m_sheetWidth), static_cast<float>(sprite->m_sheetPos.y + sprite->m_sheetHeight)));

		const float _spriteHalfWidth = sprite->m_sheetWidth / 2;
		const float _spriteHalfHeight = sprite->m_sheetHeight / 2;

		_pRenderTarget->DrawBitmap(_SpriteSheet,
			D2D1::RectF(-_spriteHalfWidth + (5 * xsize * sprite->m_sheetPivot.x), -_spriteHalfHeight + (5 * ysize * sprite->m_sheetPivot.y), _spriteHalfWidth + (5 * xsize * sprite->m_sheetPivot.x), _spriteHalfHeight + (5 * ysize * sprite->m_sheetPivot.y)),
			opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(static_cast<float>(sprite->m_sheetPos.x), static_cast<float>(sprite->m_sheetPos.y), static_cast<float>(sprite->m_sheetPos.x + sprite->m_sheetWidth), static_cast<float>(sprite->m_sheetPos.y + sprite->m_sheetHeight)));

		//* pivot 적용안한 버전
		//	_pRenderTarget->DrawBitmap(_SpriteSheet, D2D1::RectF(printpos.x, printpos.y, printpos.x + static_cast<float>(sprite->m_sheetWidth) , printpos.y + static_cast<float>(sprite->m_sheetHeight)),
		//	opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		//	D2D1::RectF(static_cast<float>(sprite->m_sheetPos.x), static_cast<float>(sprite->m_sheetPos.y), static_cast<float>(sprite->m_sheetPos.x + sprite->m_sheetWidth), static_cast<float>(sprite->m_sheetPos.y + sprite->m_sheetHeight))); 
		_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		//	DrawTextFormat(100, 100, "printx : %d, printy : %d", static_cast<int>(printpos.x), static_cast<int>(printpos.y));
	}
	//_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void YDEngine::DrawSprite(CSprite* sprite, float posx, float posy, float printposx, float printposy, float opacity)
{
	ID2D1Bitmap* _SpriteSheet = spriteSheets[sprite->m_spriteSheetIdx];

	if (_SpriteSheet != NULL)
	{
		_pRenderTarget->DrawBitmap(_SpriteSheet, D2D1::RectF(printposx, printposy, printposx + sprite->m_sheetWidth, printposy + sprite->m_sheetHeight),
			opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(sprite->m_sheetPos.x, sprite->m_sheetPos.y, sprite->m_sheetPos.x + sprite->m_sheetWidth, sprite->m_sheetPos.y + sprite->m_sheetHeight));
	}
}

void YDEngine::DrawSprite(CSprite* sprite, float posx, float posy, float printposx, float printposy, float opacity,CVector2D cameraPosition)
{
	ID2D1Bitmap* _SpriteSheet = spriteSheets[sprite->m_spriteSheetIdx];

	if (_SpriteSheet != NULL)
	{
		// transform에 카메라 좌표를 넣어줘야한다. 
		D2D1_MATRIX_3X2_F _temp = D2D1::Matrix3x2F::Identity();
		_temp.dx -= cameraPosition.x;
		_temp.dy -= cameraPosition.y;

		_pRenderTarget->SetTransform(_temp);

		_pRenderTarget->DrawBitmap(_SpriteSheet, D2D1::RectF(printposx, printposy, printposx + sprite->m_sheetWidth, printposy + sprite->m_sheetHeight),
			opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(sprite->m_sheetPos.x, sprite->m_sheetPos.y, sprite->m_sheetPos.x + sprite->m_sheetWidth, sprite->m_sheetPos.y + sprite->m_sheetHeight));

		_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	}
}

void YDEngine::DrawSprite(CSprite* sprite, float posx, float posy, float opacity, CVector2D cameraPosition)
{
	LoadBitmapFromFile(211, 462, L"../Resourse/SpriteSheet/Gate/GateOpen.png", &spritesample);
	ID2D1Bitmap** _SpriteSheet = &spritesample;

	if (_SpriteSheet != NULL)
	{
		// transform에 카메라 좌표를 넣어줘야한다. 
		D2D1_MATRIX_3X2_F _temp = D2D1::Matrix3x2F::Identity();
		_temp.dx -= cameraPosition.x;
		_temp.dy -= cameraPosition.y;

		_pRenderTarget->SetTransform(_temp);

		_pRenderTarget->DrawBitmap(*_SpriteSheet, D2D1::RectF(posx, posy, posx + sprite->m_sheetWidth, posy + sprite->m_sheetHeight),
			opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(sprite->m_sheetPos.x, sprite->m_sheetPos.y, sprite->m_sheetPos.x + sprite->m_sheetWidth, sprite->m_sheetPos.y + sprite->m_sheetHeight));


		_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	}
}

void YDEngine::DrawMapSprite(CSprite* sprite, float posx, float posy, float printposx, float printposy, float opacity, CVector2D cameraPosition)
{
	ID2D1Bitmap* _SpriteSheet = spriteMapSheets[sprite->m_spriteSheetIdx];

	if (_SpriteSheet != NULL)
	{
		// transform에 카메라 좌표를 넣어줘야한다. 
		D2D1_MATRIX_3X2_F _temp = D2D1::Matrix3x2F::Identity();
		_temp.dx -= cameraPosition.x;
		_temp.dy -= cameraPosition.y;

		_pRenderTarget->SetTransform(_temp);

		_pRenderTarget->DrawBitmap(_SpriteSheet,
			D2D1::RectF(0, 0, sprite->m_sheetWidth, sprite->m_sheetHeight),
			opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(static_cast<float>(sprite->m_sheetPos.x), static_cast<float>(sprite->m_sheetPos.y), static_cast<float>(sprite->m_sheetPos.x + sprite->m_sheetWidth), static_cast<float>(sprite->m_sheetPos.y + sprite->m_sheetHeight)));

		_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}

/// <summary>
/// 
/// (x,y)좌표와 가변함수를 인자로 받는다.
/// 그냥 printf()처럼 사용하면 됨.
/// </summary>
void YDEngine::DrawTextFormat(int x, int y, const char* pch, ...)
{
	char* buffer;
	va_list ap; //가변 인자 목록 포인터 (첫번째 가변인자 주소를 받아옴)
	va_start(ap, pch); //ap 포인터가 가변인자의 첫번째 가변인수 주소를 가리키도록 초기화

	unsigned int length = _vscprintf(pch, ap) + 1;
	buffer = new char[length];

	vsprintf_s(buffer, length, pch, ap);
	va_end(ap); //포인터를 NUll로 만들어준다. va_start, va_copy 로 초기화된 각 인수 목록에 대해 va_end을 호출해줘야한다. 

	//ANSI 코드 -> Unicode로 변환하는 APU루틴 
	int len = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
	BSTR unicodester = SysAllocStringLen(NULL, len);

	MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), unicodester, len);

	if (unicodester)
	{
		_pRenderTarget->DrawText(unicodester, wcslen(unicodester), _pTextFormat, D2D1::RectF((float)x, (float)y, (float)(x + 800), (float)(y + 40)), _pNowBrush);
	}

	//free BSTR
	SysFreeString(unicodester);

	delete[] buffer;
}

void YDEngine::DrawRect(RECT rect, int r, int g, int b)
{
	SetBrush(r, g, b, 1);
	D2D1_RECT_F _rectangle = D2D1::RectF(rect.left - Camera::GetInsance()->GetCameraVector().x, rect.top - Camera::GetInsance()->GetCameraVector().y, rect.right - Camera::GetInsance()->GetCameraVector().x, rect.bottom - Camera::GetInsance()->GetCameraVector().y);
	_pRenderTarget->DrawRectangle(&_rectangle, _pNowBrush);
}

void YDEngine::FadeInOut(float opacity)
{
	if (BlackBitmap != NULL)
	{
		_pRenderTarget->DrawBitmap(BlackBitmap, D2D1::RectF(0, 0, 2309, 1176), opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 2309, 1176));
	}
}

void YDEngine::DiscardDeviceResources()
{
	SafeRelease(&_pRenderTarget);
	SafeRelease(&_pWicFactory);
}