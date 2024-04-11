#include <CheatEngine/SDK.h>

#include <string>
#include <vector>

using namespace std;

extern "C" int __declspec(dllexport) CEPlugin_GetVersion(CheatEngine::SDK::PPluginVersion pluginVersion, int) {
    string       pluginName = "Using official SDK without Lua";
    vector<char> pluginNameChars(pluginName.begin(), pluginName.end());

    pluginVersion->version    = 1;
    pluginVersion->pluginname = pluginNameChars.data();
    return 1;
}

extern "C" int __declspec(dllexport)
    CEPlugin_InitializePlugin(CheatEngine::SDK::PExportedFunctions exportedFunctions, int pluginId) {
    string       message = "Hello from plugin using official SDK without Lua!";
    vector<char> messageChars(message.begin(), message.end());

    exportedFunctions->ShowMessage(messageChars.data());

    return 1;
}

extern "C" int __declspec(dllexport) CEPlugin_DisablePlugin() { return 1; }