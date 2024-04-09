#pragma once

#include "../SDK.h"

namespace CheatEngine::SDK::Compat {

    // PluginVersion
    using _PluginVersion = PluginVersion;
    using PPluginVersion = PluginVersion*;

    // AddressListRecord
    using _PLUGINTYPE0_RECORD = AddressListRecord;
    using PLUGINTYPE0_RECORD  = AddressListRecord;
    using ADDRESSLIST_RECORD  = AddressListRecord;
    using PPLUGINTYPE0_RECORD = AddressListRecord*;
    using PADDRESSLIST_RECORD = AddressListRecord*;

    // ExportedFunctions
    using _ExportedFunctions = ExportedFunctions;
    using PExportedFunctions = ExportedFunctions*;

    // Plugin Types:

    // 0 = AddressList
    using CEP_PLUGINTYPE0         = AddressListCallback;
    using _PLUGINTYPE0_INIT       = AddressListPluginInit;
    using PLUGINTYPE0_INIT        = AddressListPluginInit;
    using ADDRESSLISTPLUGIN_INIT  = AddressListPluginInit;
    using PPLUGINTYPE0_INIT       = AddressListPluginInit*;
    using PADDRESSLISTPLUGIN_INIT = AddressListPluginInit*;

    // 1 = MemoryView
    using CEP_PLUGINTYPE1        = MemoryViewCallback;
    using _PLUGINTYPE1_INIT      = MemoryViewPluginInit;
    using PLUGINTYPE1_INIT       = MemoryViewPluginInit;
    using MEMORYVIEWPLUGIN_INIT  = MemoryViewPluginInit;
    using PPLUGINTYPE1_INIT      = MemoryViewPluginInit*;
    using PMEMORYVIEWPLUGIN_INIT = MemoryViewPluginInit*;

    // 2 = OnDebugEvent

    using CEP_PLUGINTYPE2        = OnDebugEventCallback;
    using _PLUGINTYPE2_INIT      = OnDebugEventPluginInit;
    using PLUGINTYPE2_INIT       = OnDebugEventPluginInit;
    using DEBUGEVENTPLUGIN_INIT  = OnDebugEventPluginInit;
    using PPLUGINTYPE2_INIT      = OnDebugEventPluginInit*;
    using PDEBUGEVENTPLUGIN_INIT = OnDebugEventPluginInit*;

    // 3 = ProcessWatcherEvent

    // 4 = FunctionPointerChange

    // 5 = MainMenu

    // 6 = DisassemblerContext

    // 7 = DisassemblerRenderLine

    // 8 = AutoAssembler
}
