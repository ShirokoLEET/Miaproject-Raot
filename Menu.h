#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>

// Global variables
extern ID3D11Device* g_pd3dDevice;
extern ID3D11DeviceContext* g_pd3dDeviceContext;
extern ID3D11RenderTargetView* g_mainRenderTargetView;
extern IDXGISwapChain* g_pSwapChain;
extern bool menu_open;
extern HWND hwnd;

// Function pointer type
typedef HRESULT(__stdcall* Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
extern Present oPresent;

// Function declarations
void RenderMenu();
void InitImGui();
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

class Menu
{
};