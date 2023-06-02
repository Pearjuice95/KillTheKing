#pragma once

// MSDN에도 있는 macro
// MSDN 예제와 교수님 헤더파일은 템플릿이 아닌 Interface로 되어있긴함.
// 이 밑에는 뭐 안전하게 메모리를 해제하는게 아닐까 (아님 말구) 
template <class Interface>
inline void SafeRelease(Interface** ppT)
{
	if (*ppT != NULL)
	{
		(*ppT)->Release();
		(*ppT) = NULL;
	}
}
/// 이 밑에는 음.. 디버그 할때 음.. 
#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG)
#define Assert(b) if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}
#else
#define Assert(b)
#endif
#endif

//#ifndef HINST_THISCOMPONENT
//EXTERN_C IMAGE_DOS_HEADER __ImageBase;
//#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
//#endif