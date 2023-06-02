#include <windows.h>
#include "GameProcess.h"
#include "CInput.h"

/// <summary>
/// ¤·¤· ¾ËÁö
/// </summary>
/// <returns></returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	/// MK.3
	GameProcess* pGameAPP = new GameProcess();
	CInput* _pInput = new CInput();

	pGameAPP->Initialize();

	pGameAPP->Process();

	pGameAPP->Finalize();

	delete pGameAPP;

	return 0;
}