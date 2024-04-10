#pragma once

#include <CheatEngine/SDK.h>

#include "Plugin.h"

namespace CheatEngine::Plugin::Exports {

    inline SDK::ExportedFunctions* ExportedCheatEngineFunctions = nullptr;

    extern "C" int __declspec(dllexport) CEPlugin_GetVersion(CheatEngine::SDK::PluginVersion* pluginVersion, int) {
        auto& plugin              = CheatEngine::Plugin::GetPlugin();
        pluginVersion->version    = CheatEngine::SDK::SDK_VERSION;
        pluginVersion->pluginName = plugin.GetPluginName().data();
        return plugin.Initialize();
    }

    extern "C" int __declspec(dllexport)
        CEPlugin_InitializePlugin(CheatEngine::SDK::ExportedFunctions* exportedFunctions, int pluginId) {
        auto& plugin = CheatEngine::Plugin::GetPlugin();
        plugin.SetPluginId(pluginId);
        ExportedCheatEngineFunctions = exportedFunctions;
        return plugin.Enable();
    }

    extern "C" int __declspec(dllexport) CEPlugin_DisablePlugin() { return CheatEngine::Plugin::GetPlugin().Disable(); }
}