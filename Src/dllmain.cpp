#include "hk.h"
static BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		CreateThread(nullptr, 0, DirectX11::kieroDx11, nullptr, 0, nullptr);
	}
	return TRUE;
}