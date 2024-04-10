#pragma once

#include <CheatEngine/SDK.h>

#include "Exports.h"
#include "Functions.h"  // IWYU pragma: keep

inline CheatEngine::SDK::ExportedFunctions* GetCheatEngineFunctions() {
    return CheatEngine::Plugin::Exports::ExportedCheatEngineFunctions;
}

namespace CheatEngineFunctions = CheatEngine::Plugin::Functions;  // NOLINT
namespace CE                   = CheatEngine::Plugin::Functions;  // NOLINT
