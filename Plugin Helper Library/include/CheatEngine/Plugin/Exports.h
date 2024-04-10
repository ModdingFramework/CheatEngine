#pragma once

#include <CheatEngine/SDK.h>
#include <_Log_.h>

#include "Plugin.h"

namespace CheatEngine::Plugin::Exports {

    SDK::ExportedFunctions* exportedFunctions = nullptr;

    extern "C" int __declspec(dllexport) CEPlugin_GetVersion(CheatEngine::SDK::PluginVersion* pluginVersion, int) {
        _Log_("CEPlugin_GetVersion");
        auto& plugin              = CheatEngine::Plugin::GetPlugin();
        pluginVersion->version    = CheatEngine::SDK::SDK_VERSION;
        pluginVersion->pluginName = plugin.GetPluginName().data();
        return plugin.Initialize();
    }

    extern "C" int __declspec(dllexport)
        CEPlugin_InitializePlugin(CheatEngine::SDK::ExportedFunctions* exportedFunctions, int pluginId) {
        _Log_("CEPlugin_InitializePlugin");
        auto& plugin = CheatEngine::Plugin::GetPlugin();
        plugin.SetPluginId(pluginId);
        Exports::exportedFunctions = exportedFunctions;
        return plugin.Enable();
    }

    extern "C" int __declspec(dllexport) CEPlugin_DisablePlugin() {
        _Log_("CEPlugin_DisablePlugin");
        return CheatEngine::Plugin::GetPlugin().Disable();
    }
}