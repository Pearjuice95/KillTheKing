#pragma once

// MSDN���� �ִ� macro
// MSDN ������ ������ ��������� ���ø��� �ƴ� Interface�� �Ǿ��ֱ���.
// �� �ؿ��� �� �����ϰ� �޸𸮸� �����ϴ°� �ƴұ� (�ƴ� ����) 
template <class Interface>
inline void SafeRelease(Interface** ppT)
{
	if (*ppT != NULL)
	{
		(*ppT)->Release();
		(*ppT) = NULL;
	}
}
/// �� �ؿ��� ��.. ����� �Ҷ� ��.. 
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