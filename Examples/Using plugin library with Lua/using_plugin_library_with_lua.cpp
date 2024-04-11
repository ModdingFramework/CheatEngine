#include <CheatEngine/Plugin.h>

#include <memory>
#include <sol/sol.hpp>

using namespace std;

unique_ptr<sol::state_view> _luaState;

void CallThisFunctionFromLua() { _luaState->get<sol::function>("print")("Hello from C++!"); }

CEPlugin_OnEnable {
    _luaState = make_unique<sol::state_view>(GetCheatEngineFunctions()->GetLuaState());
    _luaState->set_function("CallThisFunctionFromLua", CallThisFunctionFromLua);
}
