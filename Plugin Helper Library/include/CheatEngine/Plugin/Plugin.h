#pragma once

#include "CheatEnginePlugin.h"

namespace CheatEngine::Plugin {

    inline CheatEnginePlugin& GetPlugin() {
        static CheatEnginePlugin plugin;
        return plugin;
    }
}
