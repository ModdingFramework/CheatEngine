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
    using CEP_PLUGINTYPE0         = AddressListPluginCallback;
    using _PLUGINTYPE0_INIT       = AddressListPluginInit;
    using PLUGINTYPE0_INIT        = AddressListPluginInit;
    using PPLUGINTYPE0_INIT       = AddressListPluginInit*;
    using ADDRESSLISTPLUGIN_INIT  = AddressListPluginInit;
    using PADDRESSLISTPLUGIN_INIT = AddressListPluginInit*;

    // 1 = MemoryView
    using CEP_PLUGINTYPE1        = MemoryViewPluginCallback;
    using _PLUGINTYPE1_INIT      = MemoryViewPluginInit;
    using PLUGINTYPE1_INIT       = MemoryViewPluginInit;
    using PPLUGINTYPE1_INIT      = MemoryViewPluginInit*;
    using MEMORYVIEWPLUGIN_INIT  = MemoryViewPluginInit;
    using PMEMORYVIEWPLUGIN_INIT = MemoryViewPluginInit*;

    // 2 = OnDebugEvent

    using CEP_PLUGINTYPE2        = OnDebugEventPluginCallback;
    using _PLUGINTYPE2_INIT      = OnDebugEventPluginInit;
    using PLUGINTYPE2_INIT       = OnDebugEventPluginInit;
    using PPLUGINTYPE2_INIT      = OnDebugEventPluginInit*;
    using DEBUGEVENTPLUGIN_INIT  = OnDebugEventPluginInit;
    using PDEBUGEVENTPLUGIN_INIT = OnDebugEventPluginInit*;

    // 3 = ProcessWatcherEvent

    using CEP_PLUGINTYPE3            = ProcessWatcherEventPluginCallback;
    using _PLUGINTYPE3_INIT          = ProcessWatcherEventPluginInit;
    using PLUGINTYPE3_INIT           = ProcessWatcherEventPluginInit;
    using PPLUGINTYPE3_INIT          = ProcessWatcherEventPluginInit*;
    using PROCESSWATCHERPLUGIN_INIT  = ProcessWatcherEventPluginInit;
    using PPROCESSWATCHERPLUGIN_INIT = ProcessWatcherEventPluginInit*;

    // 4 = FunctionPointerChange

    using CEP_PLUGINTYPE4                 = FunctionPointerChangePluginCallback;
    using _PLUGINTYPE4_INIT               = FunctionPointerChangePluginInit;
    using PLUGINTYPE4_INIT                = FunctionPointerChangePluginInit;
    using POINTERREASSIGNMENTPLUGIN_INIT  = FunctionPointerChangePluginInit;
    using PPLUGINTYPE4_INIT               = FunctionPointerChangePluginInit*;
    using PPOINTERREASSIGNMENTPLUGIN_INIT = FunctionPointerChangePluginInit*;

    // 5 = MainMenu

    using CEP_PLUGINTYPE5      = MainMenuPluginCallback;
    using _PLUGINTYPE5_INIT    = MainMenuPluginInit;
    using PLUGINTYPE5_INIT     = MainMenuPluginInit;
    using PPLUGINTYPE5_INIT    = MainMenuPluginInit*;
    using MAINMENUPLUGIN_INIT  = MainMenuPluginInit;
    using PMAINMENUPLUGIN_INIT = MainMenuPluginInit*;

    // 6 = DisassemblerContext

    using CEP_PLUGINTYPE6           = DisassemblerContextPluginCallback;
    using CEP_PLUGINTYPE6ONPOPUP    = DisassemblerContextPluginOnPopupCallback;
    using _PLUGINTYPE6_INIT         = DisassemblerContextPluginInit;
    using PLUGINTYPE6_INIT          = DisassemblerContextPluginInit;
    using PPLUGINTYPE6_INIT         = DisassemblerContextPluginInit*;
    using DISASSEMBLERCONTEXT_INIT  = DisassemblerContextPluginInit;
    using PDISASSEMBLERCONTEXT_INIT = DisassemblerContextPluginInit*;

    // 7 = DisassemblerRenderLine

    using CEP_PLUGINTYPE7              = DisassemblerRenderLinePluginCallback;
    using _PLUGINTYPE7_INIT            = DisassemblerRenderLinePluginInit;
    using PLUGINTYPE7_INIT             = DisassemblerRenderLinePluginInit;
    using PPLUGINTYPE7_INIT            = DisassemblerRenderLinePluginInit*;
    using DISASSEMBLERLINEPLUGIN_INIT  = DisassemblerRenderLinePluginInit;
    using PDISASSEMBLERLINEPLUGIN_INIT = DisassemblerRenderLinePluginInit*;

    // 8 = AutoAssembler

    using CEP_PLUGINTYPE8           = AutoAssemblerPluginCallback;
    using _PLUGINTYPE8_INIT         = AutoAssemblerPluginInit;
    using PLUGINTYPE8_INIT          = AutoAssemblerPluginInit;
    using PPLUGINTYPE8_INIT         = AutoAssemblerPluginInit*;
    using AUTOASSEMBLERPLUGIN_INIT  = AutoAssemblerPluginInit;
    using PAUTOASSEMBLERPLUGIN_INIT = AutoAssemblerPluginInit*;
}
