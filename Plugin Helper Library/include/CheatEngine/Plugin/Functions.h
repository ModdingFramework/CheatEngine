#pragma once

#include <string_view>

#include "Exports.h"

namespace CheatEngine::Plugin::Functions {

    namespace {
        inline CheatEngine::SDK::ExportedFunctions* CEFunctions() {
            return CheatEngine::Plugin::Exports::ExportedCheatEngineFunctions;
        }
    }

    inline void ShowMessage(std::string_view message) { CEFunctions()->ShowMessage(message.data()); }
}
