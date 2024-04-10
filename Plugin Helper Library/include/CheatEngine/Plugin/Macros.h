#pragma once

#include <functional>

#include "Plugin.h"

namespace CheatEngine::Plugin::Macros {
    struct FunctionRunner {
        FunctionRunner(std::function<void()> function) { function(); }
    };
}

//

#ifdef CEPLUGIN_FILE
    #define _CEPlugin_CompilationUnitID CEPLUGIN_FILE
#endif

//

#define __CEPlugin_Stringize_Simple(symbol) #symbol
#define __CEPlugin_Stringize(symbol) __CEPlugin_Stringize_Simple(symbol)

#define __CEPlugin_Concat_Simple(a, b) a##b
#define __CEPlugin_Concat(a, b) __CEPlugin_Concat_Simple(a, b)

#define __CEPlugin_ConcatWithCompilationUnitID(prefix) __CEPlugin_Concat(prefix, _CEPlugin_CompilationUnitID)

#define __CEPlugin_ConcatWithCompilationUnitIDAndCounter(prefix, count) \
    __CEPlugin_ConcatWithCompilationUnitID(__CEPlugin_Concat(prefix, count))

//

#define __CEPlugin_SetName(pluginName, count)                                                      \
    CheatEngine::Plugin::Macros::FunctionRunner                                                    \
        __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_SET_PLUGIN_NAME_, count)([]() { \
            CheatEngine::Plugin::GetPlugin().SetPluginName(pluginName);                            \
        });

#define __CEPlugin_Init(count)                                                                              \
    inline bool __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_INIT_FN_, count)();              \
    CheatEngine::Plugin::Macros::FunctionRunner                                                             \
                __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_REGISTER_INIT_FN_, count)([]() { \
            CheatEngine::Plugin::GetPlugin().RegisterPluginInitCallback(                            \
                __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_INIT_FN_, count)         \
            );                                                                                      \
        });                                                                                         \
    inline bool __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_INIT_FN_, count)()

#define __CEPlugin_OnInit(count)                                                                               \
    inline void __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_ON_INIT_FN_, count)();              \
    CheatEngine::Plugin::Macros::FunctionRunner                                                                \
                __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_REGISTER_ON_INIT_FN_, count)([]() { \
            CheatEngine::Plugin::GetPlugin().RegisterOnPluginInitCallback(                             \
                __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_ON_INIT_FN_, count)         \
            );                                                                                         \
        });                                                                                            \
    inline void __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_ON_INIT_FN_, count)()

#define __CEPlugin_Enable(count)                                                                              \
    inline bool __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_ENABLE_FN_, count)();              \
    CheatEngine::Plugin::Macros::FunctionRunner                                                               \
                __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_REGISTER_ENABLE_FN_, count)([]() { \
            CheatEngine::Plugin::GetPlugin().RegisterPluginEnableCallback(                            \
                __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_ENABLE_FN_, count)         \
            );                                                                                        \
        });                                                                                           \
    inline bool __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_ENABLE_FN_, count)()

#define __CEPlugin_OnEnable(count)                                                                               \
    inline void __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_ON_ENABLE_FN_, count)();              \
    CheatEngine::Plugin::Macros::FunctionRunner                                                                  \
                __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_REGISTER_ON_ENABLE_FN_, count)([]() { \
            CheatEngine::Plugin::GetPlugin().RegisterOnPluginEnableCallback(                             \
                __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_ON_ENABLE_FN_, count)         \
            );                                                                                           \
        });                                                                                              \
    inline void __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_ON_ENABLE_FN_, count)()

#define __CEPlugin_Disable(count)                                                                              \
    inline bool __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_DISABLE_FN_, count)();              \
    CheatEngine::Plugin::Macros::FunctionRunner                                                                \
                __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_REGISTER_DISABLE_FN_, count)([]() { \
            CheatEngine::Plugin::GetPlugin().RegisterPluginDisableCallback(                            \
                __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_DISABLE_FN_, count)         \
            );                                                                                         \
        });                                                                                            \
    inline bool __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_DISABLE_FN_, count)()

#define __CEPlugin_OnDisable(count)                                                                               \
    inline void __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_ON_DISABLE_FN_, count)();              \
    CheatEngine::Plugin::Macros::FunctionRunner                                                                   \
                __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_REGISTER_ON_DISABLE_FN_, count)([]() { \
            CheatEngine::Plugin::GetPlugin().RegisterOnPluginDisableCallback(                             \
                __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_ON_DISABLE_FN_, count)         \
            );                                                                                            \
        });                                                                                               \
    inline void __CEPlugin_ConcatWithCompilationUnitIDAndCounter(_CEPLUGIN_ON_DISABLE_FN_, count)()

//

#define CEPlugin(pluginName) __CEPlugin_SetName(pluginName, __COUNTER__)
#define CEPlugin_Init __CEPlugin_Init(__COUNTER__)
#define CEPlugin_OnInit __CEPlugin_OnInit(__COUNTER__)
#define CEPlugin_Enable __CEPlugin_Enable(__COUNTER__)
#define CEPlugin_OnEnable __CEPlugin_OnEnable(__COUNTER__)
#define CEPlugin_Disable __CEPlugin_Disable(__COUNTER__)
#define CEPlugin_OnDisable __CEPlugin_OnDisable(__COUNTER__)
