#include <CheatEngine/SDK.h>

#include <memory>
#include <sol/sol.hpp>
#include <string>
#include <vector>

using namespace std;

unique_ptr<sol::state_view> ceLuaState = nullptr;

void CallMeFromLua() {
    auto print = ceLuaState->get<sol::function>("print");
    print("Hello from C++!");
}

extern "C" int __declspec(dllexport) CEPlugin_GetVersion(CheatEngine::SDK::PPluginVersion pluginVersion, int) {
    string       pluginName = "Using official SDK with Lua";
    vector<char> pluginNameChars(pluginName.begin(), pluginName.end());

    pluginVersion->version    = 1;
    pluginVersion->pluginname = pluginNameChars.data();

    return 1;
}

extern "C" int __declspec(dllexport)
    CEPlugin_InitializePlugin(CheatEngine::SDK::ExportedFunctions* exportedFunctions, int pluginId) {
    string       message = "Hello from plugin using official SDK with Lua!";
    vector<char> messageChars(message.begin(), message.end());
    messageChars.push_back('\0');

    exportedFunctions->ShowMessage(messageChars.data());

    ceLuaState = make_unique<sol::state_view>(exportedFunctions->GetLuaState());
    ceLuaState->set_function("CallMeFromLua", CallMeFromLua);

    return 1;
}

extern "C" int __declspec(dllexport) CEPlugin_DisablePlugin() { return 1; }