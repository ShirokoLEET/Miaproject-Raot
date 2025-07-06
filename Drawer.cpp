#include "Drawer.h"
#include "CheatBase.h"
#include "UnityResolve.hpp"
void Drawer::RenderPlayers() {
    auto camera = UnityResolve::UnityType::Camera::GetMain();
    if (!camera) return;

    auto positions = GetCachedPlayerPositions();
    int windowWidth, windowHeight;
    ImGuiIO& io = ImGui::GetIO();
    windowWidth = (int)io.DisplaySize.x;
    windowHeight = (int)io.DisplaySize.y;

    for (const auto& pos : positions) {
        auto screen = camera->WorldToScreenPoint(pos);
        if (screen.z <= 0) continue;    
        float flippedY = windowHeight - screen.y;
        ImVec2 drawPos(screen.x, flippedY);
        ImGui::GetForegroundDrawList()->AddText(drawPos, IM_COL32(255, 255, 0, 255), "Player");
    }
}