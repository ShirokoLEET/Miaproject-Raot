#include <Windows.h>
#include <thread>
#include "Menu.h"
#include <tchar.h>
#include <iostream>
#include "kiero.h"
#include "MinHook.h"
#include "CheatBase.h"

void OpenConsole() {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONOUT$", "w", stderr);
    freopen_s(&f, "CONIN$", "r", stdin);
    SetConsoleTitleA("Injected Console Debug");
    std::cout << "[+] Console attached!\n";
}


DWORD WINAPI HackThread(HMODULE hModule) {
    OpenConsole();
    auto status = kiero::init(kiero::RenderType::D3D11);
    std::cout << "[~] Kiero init status = " << status << std::endl;

    switch (status) {
    case kiero::Status::Success:
        std::cout << "[+] Kiero initialized successfully." << std::endl;
        break;
    case kiero::Status::UnknownError:
        std::cerr << "[!] UnknownError: Kiero failed. Maybe DirectX not loaded yet?" << std::endl;
        break;
    case kiero::Status::ModuleNotFoundError:
        std::cerr << "[!] ModuleNotFoundError: Could not find target module (e.g., dxgi.dll)." << std::endl;
        break;
    default:
        std::cerr << "[!] Unknown failure from kiero::init." << std::endl;
        break;
    }

    if (status == kiero::Status::Success) {
        if (MH_Initialize() == MH_OK) {
            void** pPresent = (void**)kiero::getMethodsTable()[8];
            if (MH_CreateHook(pPresent, hkPresent, reinterpret_cast<void**>(&oPresent)) == MH_OK) {
                if (MH_EnableHook(pPresent) == MH_OK) {
                    std::cout << "[+] Hooked Present successfully.\n";
					CheatInit(); 

                }
                else {
                    std::cerr << "[!] Failed to enable Present hook.\n";
                }
            }
            else {
                std::cerr << "[!] Failed to create Present hook.\n";
            }
        }
        else {
            std::cerr << "[!] Failed to initialize MinHook.\n";
        }
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr);
    }
    return TRUE;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;
    return DefWindowProc(hWnd, msg, wParam, lParam);
}