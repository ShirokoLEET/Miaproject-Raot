#include "CheatBase.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "UnityResolve.hpp"

static std::vector<UnityResolve::UnityType::Vector3> g_playerPositions;
static std::mutex g_playerMutex;
UnityResolve::Assembly* gameAssembly;
UnityResolve::Class* playerClass;
UnityResolve::Class* WeaponClass;

struct PlayerMain :UnityResolve::UnityType::MonoBehaviour {

    


};

struct vector3 {
    float x;
    float y;
    float z;
    vector3(float x, float y, float z) : x(x), y(y), z(z) {}
};

void Debug() {
    auto playerClass = gameAssembly->Get("PlayerMain", "Player");
	auto playerInstances = playerClass->FindObjectsByType<PlayerMain*>();
    if (playerInstances.empty()) {
        std::cout << "[Debug] No PlayerMain instances found!" << std::endl;
        return;
	}
	auto tpmethod = playerClass->Get<UnityResolve::Method>("Teleport");
    if (!tpmethod) {
        std::cout << "[Debug] Teleport method not found!" << std::endl;
        return;
    }
    auto localplayerinstance = playerInstances[0];
    UnityResolve::UnityType::Vector3 newPosition(0, 110, 0);
    tpmethod->Invoke<void>(localplayerinstance, newPosition);
	std::cout << "[Debug] Teleported player to (0, 0, 0)" << std::endl;








	

}
void UpdatePlayerPositions() {
    std::vector<UnityResolve::UnityType::Vector3> temp;
    playerClass = gameAssembly->Get("MirrorNetworkedPlayer", "AoTNetworking.Players");
    if (!playerClass) return;       
    std::vector<PlayerMain*> players = playerClass->FindObjectsByType<PlayerMain*>();
    for (auto player : players) {
        if (!player) continue;
        auto transform = player->GetTransform();
        if (!transform) continue;

        temp.push_back(transform->GetPosition());
    }
    std::scoped_lock lock(g_playerMutex);
    g_playerPositions = std::move(temp);
}

std::vector<UnityResolve::UnityType::Vector3> GetCachedPlayerPositions() {
    std::scoped_lock lock(g_playerMutex);
	//std::cout << "Cached player positions size: " << g_playerPositions.size() << std::endl;
    return g_playerPositions;
}
void CheatInit() {
	HMODULE gameAssemblyDLL = GetModuleHandle(L"GameAssembly.dll");
	std::cout << "GameAssembly addr: " << gameAssemblyDLL << std::endl;
    UnityResolve::Init(gameAssemblyDLL, UnityResolve::Mode::Il2Cpp);
    
	gameAssembly = UnityResolve::Get("Assembly-CSharp.dll");
    
}

