#include "Menu.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include "CheatBase.h"
#include <Windows.h>
#include "Drawer.h"
#pragma comment(lib, "d3d11.lib")

ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;
LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
WNDPROC oWndProc = nullptr;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool menu_open = true;

HWND hwnd = nullptr;
typedef HRESULT(__stdcall* Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
Present oPresent = nullptr;

LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, msg, wParam, lParam);
}

void RenderMenu() {
    if (!menu_open) return;

    ImGui::Begin("IL2CPP Hack Menu", &menu_open);
    ImGui::Text("Welcome to the menu!");
    if (ImGui::Button("Aimbot")){
            
    }

    if (ImGui::Button("Click Me")) {
        std::cout << "Button clicked!" << std::endl;
		Debug();
    }
    

    ImGui::End();
}


void InitImGui() {
    DXGI_SWAP_CHAIN_DESC sd;
    g_pSwapChain->GetDesc(&sd);
    hwnd = sd.OutputWindow;

    g_pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pd3dDevice);
    g_pd3dDevice->GetImmediateContext(&g_pd3dDeviceContext);

    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();

    oWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

    ImGui::CreateContext();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    static bool initialized = false;
    if (!initialized) {
        g_pSwapChain = pSwapChain;
        UnityResolve::ThreadAttach();
        InitImGui();
        initialized = true;
    }

    if (GetAsyncKeyState(VK_INSERT) & 1) {
        menu_open = !menu_open;
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    RenderMenu();
	UpdatePlayerPositions();
	Drawer::RenderPlayers();






    ImGui::Render();
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(pSwapChain, SyncInterval, Flags);
}


