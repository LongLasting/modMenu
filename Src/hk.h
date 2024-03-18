#pragma once
#include "ImGui/imconfig.h"
#include "menu/menu.h"
#include "d3d11.h"
#include "Kiero/kiero.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

namespace DirectX11 {
	typedef HRESULT(_stdcall* Present)(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT Flags);

	Present g_pD3D11oPresent;

	ID3D11Device* g_pD3D11Device = NULL;
	ID3D11RenderTargetView* g_pD3D11MainRenderTargetView;
	ID3D11DeviceContext* g_pD3D11Context = NULL;

	HWND MainWindow = NULL;
	WNDPROC oWndProc;

	LRESULT WINAPI myWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		if (msg == WM_KEYDOWN) {

			if (wParam == 106) {
				Menu::Visible = !Menu::Visible;
				return true;
			}

			if (Menu::Visible) {
				if (wParam == 96) {
					if (Menu::g_pRendering != Menu::g_pRoot) {
						Menu::g_pRendering = Menu::g_pRendering->getParent();
					}
					return true;
				}

				if (wParam == 98) {
					Menu::g_pRendering->moveDown();
					return true;
				}

				if (wParam == 100) {
					Menu::g_pRendering->stepOff();
					return true;
				}

				if (wParam == 101) {
					Menu::g_pRendering->keyeventCall();
					return true;
				}

				if (wParam == 102) {
					Menu::g_pRendering->stepOn();
					return true;
				}

				if (wParam == 104) {
					Menu::g_pRendering->moveUp();
					return true;
				}

			}
		}

		return oWndProc(hWnd, msg, wParam, lParam);
	}

	bool hooked = false;

	HRESULT _stdcall hk(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT Flag) {
		if (!hooked) {
			if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pD3D11Device))) {
				g_pD3D11Device->GetImmediateContext(&g_pD3D11Context);
				DXGI_SWAP_CHAIN_DESC scDesc;
				pSwapChain->GetDesc(&scDesc);
				MainWindow = scDesc.OutputWindow;
				ID3D11Texture2D* Buffer = nullptr;
				pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&Buffer);
				if (Buffer == nullptr) {
					return g_pD3D11oPresent(pSwapChain, syncInterval, Flag);
				}
				g_pD3D11Device->CreateRenderTargetView(Buffer, NULL, &g_pD3D11MainRenderTargetView);
				Buffer->Release();
				/****/
				oWndProc = (WNDPROC)GetWindowLongPtrW(MainWindow, GWLP_WNDPROC);
				SetWindowLongPtr(MainWindow, GWLP_WNDPROC, (LONG_PTR)myWndProc);

				ImGui::CreateContext();
				ImGui_ImplWin32_Init(MainWindow);
				ImGui_ImplDX11_Init(g_pD3D11Device, g_pD3D11Context);
				ImGuiIO& io = ImGui::GetIO();
				ImFont* Font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Deng.ttf", 35.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
				Menu::init();
				hooked = true;
			}
			else {
				return g_pD3D11oPresent(pSwapChain, syncInterval, Flag);
			}
		}
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		/*   now here to render imgui or your own stuff   */
		Menu::Render();
		ImGui::Render();
		g_pD3D11Context->OMSetRenderTargets(1, &g_pD3D11MainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		return g_pD3D11oPresent(pSwapChain, syncInterval, Flag);
	}

	bool Done = false;
	DWORD WINAPI kieroDx11(LPVOID lpParams) {
		AllocConsole();
		FILE* consoleOut;
		freopen_s(&consoleOut, "CONOUT$", "w", stdout);
		SetConsoleTitle(TEXT("Debug"));

		do {
			if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
				kiero::bind(8, (void**)&g_pD3D11oPresent, hk);
				Done = true;
			}
		} while (!Done);
		return 0L;
	}
}