#pragma once
#include "Offsets.hpp"
#include "DMALibrary/Memory/Memory.h"
#include <unordered_map>

namespace LvMap
{
	inline bool m_mixtape;
}

struct Level {
    std::string Name;
    uint64_t gameModePtr;
    char NameBuffer[1024] = { 0 };
    bool m_mixtape;
    char gameMode[64] = { 0 };
    std::unordered_map<std::string, bool> mixtape = { {"control", true}, {"freedm", true}, {"arenas", true} };

    bool IsPlayable;
    bool IsFiringRange;

    void Read() {
        if (!NameBuffer) {
            Name = "Unknown";
        }
        else {
            Name = std::string(NameBuffer);
        }

        IsPlayable = !Name.empty() && Name != "mp_lobby" && Name != "Unknown";
        IsFiringRange = Name == "mp_rr_canyonlands_staging_mu1";
        if (gameModePtr) {
            mem.Read(gameModePtr, &gameMode, sizeof(gameMode), true);
            m_mixtape = mixtape[gameMode];
            LvMap::m_mixtape = m_mixtape;
        }
    }
};