#pragma once
#include <cstdint>
#include "UnityResolve.hpp"

void Debug();
void UpdatePlayerPositions();
std::vector<UnityResolve::UnityType::Vector3> GetCachedPlayerPositions();
void CheatInit();

class CheatBase
{
};