// Original header:
/*
 cepluginsdk.h
 Updated July 4, 2017

 v5.0.0
*/

// Notes about what has been changed:
/*
    To remove dependency <windows.h> aliases such as int have been replaced with int, etc.

    Lua headers and types have been wrapped with #ifdef CHEATENGINE_USE_LUA
    which allows loading the SDK without automatically including CE's Lua headers.

    > This is important if you want to use your own Lua headers, e.g. to bring your own Lua.

    The changes below are C++ specific, as this version is exclusively being used from C++:

    - Structures have been wrapped in the CheatEngine::SDK namespace.
    - `typedef enum` has been replaced with `enum class`.
    - `typedef struct` has been replaced with `struct`.
    - `typedef` for function pointers has been replaced with `using`.

    For clarity in the SDK.h, types such as `PLUGINTYPE0_RECORD` have been replaced
    with `AddressListRecord` to make it more readable and C++-like.

    If you want the original C SDK.h, you can #include <CheatEngine/SDK/Official/v6.h>
*/

#pragma once

#include <cstdint>

#ifdef CHEATENGINE_USE_LUA
    #include "lauxlib.h"  // IWYU pragma: keep
    #include "lua.h"      // IWYU pragma: keep
    #include "lualib.h"   // IWYU pragma: keep
#endif

#ifdef CHEATENGINE_INCLUDE_WINDOWS
    #include <windows.h>
#endif

namespace CheatEngine::SDK {

    inline int SDK_VERSION = 6;

    enum class PluginType {
        AddressList,
        MemoryView,
        OnDebugEvent,
        ProcessWatcherEvent,
        FunctionPointerChange,
        MainMenu,
        DisassemblerContext,
        DisassemblerRenderLine,
        AutoAssembler
    };

    enum class AutoAssemblerPhase { Initialize = 0, Phase1 = 1, Phase2 = 2, Finalize = 3 };

    struct PluginVersion {
        unsigned int version;  // write here the minimum version this dll is compatible with (Current supported version:
                               // 1 and 2: this SDK only describes 2)
        const char* pluginName;  // make this point to a 0-terminated string (allocated memory or static addressin your
                                 // dll, not stack)
    };

    enum class AddressListRecordType { Byte, Word, DWord, Float, Double, Bit, Int64, String };

    struct AddressListRecord {
        char*          interpretedAddress;  // pointer to a 255 bytes long string (0 terminated)
        std::uintptr_t address;    // this is a read-only representaion of the address. Change interpretedaddress if you
                                   // want to change this
        int            isPointer;  // readonly
        int            countOffsets;  // readonly
        std::uint32_t* offsets;       // array of dwords ranging from 0 to countoffsets-1 (readonly)
        char*          description;   // pointer to a 255 bytes long string
        char           valueTypeId;   // 0=byte, 1=word, 2=dword, 3=float, 4=double, 5=bit, 6=int64, 7=string
        char           size;          // stringlength or bitlength;

        AddressListRecordType ValueType() const { return static_cast<AddressListRecordType>(valueTypeId); }
    };

    /* Registered Function Types */

    // 0 = AddressList

    using AddressListPluginCallback = int(__stdcall*)(AddressListRecord* selectedRecord);

    struct AddressListPluginInit {
        const char*               name;      // 0 terminated string describing the name for the user's menu item
        AddressListPluginCallback callback;  // pointer to a callback routine of the type 0 plugin
    };

    // 1 = MemoryView

    using MemoryViewPluginCallback = int(__stdcall*)(
        std::uintptr_t* disassemblerAddress, std::uintptr_t* selectedDisassemblerAddress, std::uintptr_t* hexviewAddress
    );

    struct MemoryViewPluginInit {
        const char*              name;      // 0 terminated string describing the name for the user's menu item
        MemoryViewPluginCallback callback;  // pointer to a callback routine of the type 1 plugin
        const char* shortcut;  // 0 terminated string containing the shortcut in textform. CE will try it's best to
                               // parse it to a valid shortcut
    };

    // 2 = OnDebugEvent

#ifdef CHEATENGINE_INCLUDE_WINDOWS
    using OnDebugEventPluginCallback = int(__stdcall*)(LPDEBUG_EVENT DebugEvent);
#else
    using OnDebugEventPluginCallback = int(__stdcall*)(void* DebugEvent);
#endif

    struct OnDebugEventPluginInit {
        OnDebugEventPluginCallback callback;  // pointer to a callback routine of the type 2 plugin
    };

    // 3 = ProcessWatcherEvent

    using ProcessWatcherEventPluginCallback =
        void(__stdcall*)(std::uint32_t processid, std::uint32_t peprocess, int Created);

    struct ProcessWatcherEventPluginInit {
        ProcessWatcherEventPluginCallback callback;  // pointer to a callback routine of the type 3 plugin
    };

    // 4 = FunctionPointerChange

    using FunctionPointerChangePluginCallback = void(__stdcall*)(int reserved);

    struct FunctionPointerChangePluginInit {
        FunctionPointerChangePluginCallback callback;  // pointer to a callback routine of the type 4 plugin
    };

    // 5 = MainMenu

    using MainMenuPluginCallback = void(__stdcall*)(void);

    struct MainMenuPluginInit {
        const char*            name;  // 0 terminated string describing the name for the user's menu item
        MainMenuPluginCallback callback;
        const char* shortcut;  // 0 terminated string containing the shortcut in textform. CE will try it's best to
                               // parse it to a valid shortcut
    };

    // 6 = DisassemblerContext

    using DisassemblerContextPluginCallback = int(__stdcall*)(std::uintptr_t* selectedAddress);
    using DisassemblerContextPluginOnPopupCallback =
        int(__stdcall*)(std::uintptr_t selectedAddress, char** addressofname, int* show);

    struct DisassemblerContextPluginInit {
        const char*                       name;  // 0 terminated string describing the name for the user's menu item
        DisassemblerContextPluginCallback callback;
        DisassemblerContextPluginOnPopupCallback callbackOnPopup;
        const char* shortcut;  // 0 terminated string containing the shortcut in textform. CE will try it's best to
                               // parse it to a valid shortcut
    };

    // 7 = DisassemblerRenderLine

    using DisassemblerRenderLinePluginCallback = void(__stdcall*)(
        std::uintptr_t address, char** addressStringPointer, char** byteStringPointer, char** opCodeStringPointer,
        char** specialStringpointer, std::uint32_t* textcolor
    );

    struct DisassemblerRenderLinePluginInit {
        DisassemblerRenderLinePluginCallback callback;  // pointer to a callback routine of the type 7 plugin
    };

    // 8 = AutoAssembler

    using AutoAssemblerPluginCallback = void(__stdcall*)(char** line, AutoAssemblerPhase phase, int id);

    struct AutoAssemblerPluginInit {
        AutoAssemblerPluginCallback callback;  // pointer to a callback routine of the type 8 plugin
    };

    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    struct RegisterModificationInfo {
        std::uintptr_t address;  // address to break on
        int            change_eax;
        int            change_ebx;
        int            change_ecx;
        int            change_edx;
        int            change_esi;
        int            change_edi;
        int            change_ebp;
        int            change_esp;
        int            change_eip;
#ifdef _AMD64_
        int change_r8;
        int change_r9;
        int change_r10;
        int change_r11;
        int change_r12;
        int change_r13;
        int change_r14;
        int change_r15;
#endif
        int            change_cf;
        int            change_pf;
        int            change_af;
        int            change_zf;
        int            change_sf;
        int            change_of;
        std::uintptr_t new_eax;
        std::uintptr_t new_ebx;
        std::uintptr_t new_ecx;
        std::uintptr_t new_edx;
        std::uintptr_t new_esi;
        std::uintptr_t new_edi;
        std::uintptr_t new_ebp;
        std::uintptr_t new_esp;
        std::uintptr_t new_eip;
#ifdef _AMD64_
        std::uintptr_t new_r8;
        std::uintptr_t new_r9;
        std::uintptr_t new_r10;
        std::uintptr_t new_r11;
        std::uintptr_t new_r12;
        std::uintptr_t new_r13;
        std::uintptr_t new_r14;
        std::uintptr_t new_r15;
#endif

        int new_cf;
        int new_pf;
        int new_af;
        int new_zf;
        int new_sf;
        int new_of;
    };

    namespace ExportedFunctionSignatures {
        typedef void(__stdcall* ShowMessage)(const char* message);
        typedef int(__stdcall* RegisterFunction)(int pluginid, PluginType functiontype, void* init);
        typedef int(__stdcall* UnregisterFunction)(int pluginid, int functionid);
        typedef void*(__stdcall* GetMainWindowHandle)(void);
        typedef int(__stdcall* AutoAssemble)(const char* script);
        typedef int(__stdcall* Assembler)(
            std::uintptr_t address, const char* instruction, std::uint8_t* output, int maxlength, int* returnedsize
        );
        typedef int(__stdcall* Dissassembler)(std::uintptr_t address, const char* output, int maxsize);
        typedef int(__stdcall* ChangeRegistersAtAddress)(std::uintptr_t address, RegisterModificationInfo* changereg);
        typedef int(__stdcall* InjectDLL)(const char* pathToDLL, const char* functionToCall);
        typedef int(__stdcall* FreezeMem)(std::uintptr_t address, int size);
        typedef int(__stdcall* UnfreezeMem)(int freezeID);
        typedef int(__stdcall* FixMem)(void);
        typedef int(__stdcall* ProcessList)(char* listbuffer, int listsize);
        typedef int(__stdcall* ReloadSettings)(void);
        typedef std::uintptr_t(__stdcall* GetAddressFromPointer)(
            std::uintptr_t baseaddress, int offsetcount, int* offsets
        );
        typedef int(__stdcall* GenerateAPIHookScript)(
            const char* address, const char* addresstojumpto, const char* addresstogetnewcalladdress,
            const char* script, int maxscriptsize
        );
        typedef int(__stdcall* AddressToName)(std::uintptr_t address, const char* name, int maxnamesize);
        typedef int(__stdcall* NameToAddress)(const char* name, std::uintptr_t* address);

        typedef void(__stdcall* LoadDBK32)(void);
        typedef int(__stdcall* LoadDBVMIfNeeded)(void);
        typedef std::uint32_t(__stdcall* PreviousOpCode)(std::uintptr_t address);
        typedef std::uint32_t(__stdcall* NextOpCode)(std::uintptr_t address);
        typedef int(__stdcall* LoadModule)(const char* modulepath, char* exportlist, int* maxsize);
        typedef int(__stdcall* CEP_DISASSEMBLEEX)(std::uintptr_t address, char* output, int maxsize);
        typedef void(__stdcall* CEP_AA_ADDCOMMAND)(const char* command);
        typedef void(__stdcall* CEP_AA_DELCOMMAND)(const char* command);

        typedef void*(__stdcall* CreateTableEntry)(void);
        typedef void*(__stdcall* GetTableEntry)(const char* description);

        typedef int(__stdcall* MemoryRecord_SetDescription)(void* memrec, const char* description);
        typedef const char*(__stdcall* MemoryRecord_GetDescription)(void* memrec);
        typedef int(__stdcall* MemoryRecord_GetAddress)(
            void* memrec, std::uintptr_t* address, std::uint32_t* offsets, int maxoffsets, int* neededOffsets
        );
        typedef int(__stdcall* MemoryRecord_SetAddress)(
            void* memrec, char* address, std::uint32_t* offsets, int offsetcount
        );
        typedef int(__stdcall* MemoryRecord_GetType)(void* memrec);
        typedef int(__stdcall* MemoryRecord_SetType)(void* memrec, int vtype);
        typedef int(__stdcall* MemoryRecord_GetValueType)(void* memrec, const char* value, int maxsize);
        typedef int(__stdcall* MemoryRecord_SetValueType)(void* memrec, const char* value);
        typedef char*(__stdcall* MemoryRecord_GetScript)(void* memrec);
        typedef int(__stdcall* MemoryRecord_SetScript)(void* memrec, const char* script);
        typedef int(__stdcall* MemoryRecord_IsFrozen)(void* memrec);
        typedef int(__stdcall* MemoryRecord_Freeze)(void* memrec, int direction);
        typedef int(__stdcall* MemoryRecord_Unfreeze)(void* memrec);
        typedef int(__stdcall* MemoryRecord_SetColor)(void* memrec, std::uint32_t color);
        typedef int(__stdcall* MemoryRecord_AppendToEntry)(void* memrec1, void* memrec2);
        typedef int(__stdcall* MemoryRecord_Delete)(void* memrec);

        typedef std::uint32_t(__stdcall* GetProcessIdFromProcessName)(const char* name);
        typedef std::uint32_t(__stdcall* OpenProcess)(std::uint32_t pid);
        typedef std::uint32_t(__stdcall* DebugProcess)(int debuggerinterface);
        typedef void(__stdcall* Pause)(void);
        typedef void(__stdcall* Unpause)(void);
        typedef int(__stdcall* SetBreakpoint)(std::uintptr_t address, int size, int trigger);
        typedef int(__stdcall* RemoveBreakpoint)(std::uintptr_t address);
        typedef int(__stdcall* ContinueFromBreakpoint)(int continueoption);

        typedef void(__stdcall* CloseCheatEngine)(void);
        typedef void(__stdcall* HideAllCheatEngineWindows)(void);
        typedef void(__stdcall* UnhideMainCheatEngineWindow)(void);

        typedef void*(__stdcall* CreateForm)(void);
        typedef void(__stdcall* CenterFormOnScreen)(void* form);
        typedef void(__stdcall* HideForm)(void* form);
        typedef void(__stdcall* ShowForm)(void* form);
        typedef void(__stdcall* OnFormClose)(void* form, void* function);

        typedef void*(__stdcall* CreatePanel)(void* owner);
        typedef void*(__stdcall* CreateGroupBox)(void* owner);
        typedef void*(__stdcall* CreateButton)(void* owner);
        typedef void*(__stdcall* CreateImage)(void* owner);

        typedef int(__stdcall* LoadImageFromFile)(void* image, const char* filename);
        typedef void(__stdcall* SetImageTransparent)(void* image, int transparent);
        typedef void(__stdcall* SetImageStretch)(void* image, int stretch);

        typedef void*(__stdcall* CreateLabel)(void* owner);
        typedef void*(__stdcall* CreateEdit)(void* owner);
        typedef void*(__stdcall* CreateMemo)(void* owner);
        typedef void*(__stdcall* CreateTimer)(void* owner);

        typedef void(__stdcall* SetTimerInterval)(void* timer, int interval);
        typedef void(__stdcall* OnTimer)(void* timer, void* function);

        typedef void(__stdcall* SetControlCaption)(void* control, const char* caption);
        typedef int(__stdcall* GetControlCaption)(void* control, const char* caption, int maxsize);

        typedef void(__stdcall* SetControlPosition)(void* control, int x, int y);
        typedef int(__stdcall* GetControlX)(void* control);
        typedef int(__stdcall* GetControlY)(void* control);

        typedef void(__stdcall* SetControlSize)(void* control, int width, int height);
        typedef int(__stdcall* GetControlWidth)(void* control);
        typedef int(__stdcall* GetControlHeight)(void* control);

        typedef void(__stdcall* SetControlAlign)(void* control, int align);
        typedef void(__stdcall* SetControlOnClickFunction)(void* control, void* function);

        typedef void(__stdcall* DestroyObject)(void* object);

        typedef int(__stdcall* MessageDialog)(const char* massage, int messagetype, int buttoncombination);
        typedef int(__stdcall* SpeecHackSetSpeed)(float speed);

#ifdef CHEATENGINE_USE_LUA
        typedef lua_State*(__fastcall* GetLuaState)();
#else
        typedef void*(__fastcall* GetLuaState)();
#endif

        typedef int(__stdcall** ReadProcessMemory)(
            void* hProcess, const void* lpBaseAddress, void* lpBuffer, size_t nSize, size_t* lpNumberOfBytesRead
        );
    }

    /*
    function ce_messageDialog(message: pchar; messagetype: integer; buttoncombination: integer): integer; stdcall;
    function ce_speedhack_setSpeed(speed: single): int; stdcall;
    */

    struct ExportedFunctions {
        int _sizeOfExportedFunctions;

        ExportedFunctionSignatures::ShowMessage ShowMessage;  // Pointer to the ce showmessage function
        ExportedFunctionSignatures::RegisterFunction
            RegisterFunction;  // Use this to register a specific type of plugin
        ExportedFunctionSignatures::UnregisterFunction
                       UnregisterFunction;   // unregisters a function registered with registerfunction
        std::uint32_t* OpenedProcessID;      // pointer to the currently selected processid
        void**         OpenedProcessHandle;  // pointer to the currently selected processhandle

        ExportedFunctionSignatures::GetMainWindowHandle
            GetMainWindowHandle;  // returns the handle of the main window (for whatever reason, it is
                                  // recommended to use delphi to make a real userinterface upgrade)
        ExportedFunctionSignatures::AutoAssemble  AutoAssemble;  // Pointer to the AutoAssemble function
        ExportedFunctionSignatures::Assembler     Assembler;     // pointer to the assembler function
        ExportedFunctionSignatures::Dissassembler Disassembler;  // pointer to the disassembler function
        ExportedFunctionSignatures::ChangeRegistersAtAddress
                                              ChangeRegistersAtAddress;  // pointer to the ChangeRegAtBP function
        ExportedFunctionSignatures::InjectDLL InjectDLL;                 // pointer to ce's Inject DLL function
        ExportedFunctionSignatures::FreezeMem FreezeMem;                 // pointer to the FreezeMem routine
        ExportedFunctionSignatures::UnfreezeMem
            UnfreezeMem;  // pointer to the UnfreezeMem routine (use this to undo freezes with FreezeMem)
        ExportedFunctionSignatures::FixMem         FixMem;          // pointer to the fixmem routine
        ExportedFunctionSignatures::ProcessList    ProcessList;     // pointer to the processlist routine
        ExportedFunctionSignatures::ReloadSettings ReloadSettings;  // pointer to the ReloadSettings routine
        ExportedFunctionSignatures::GetAddressFromPointer
            GetAddressFromPointer;  // pointer to the GetAddressFromPointer routine

        // pointers to the address that contains the pointers to the functions
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        ExportedFunctionSignatures::ReadProcessMemory
            ReadProcessMemory;     // pointer to the pointer of ReadProcessMemory (Change it to hook that
                                   // api, or use it yourself)
        void* WriteProcessMemory;  // pointer to the pointer of WriteProcessMemory (Change it to hook that api, or use
                                   // it yourself)
        void* GetThreadContext;    //   ...
        void* SetThreadContext;    //   ...
        void* SuspendThread;       //   ...
        void* ResumeThread;        //   ...
        void* OpenProcess;         //   ...
        void* WaitForDebugEvent;   //   ...
        void* ContinueDebugEvent;  //   ...
        void* DebugActiveProcess;  //   ...
        void* StopDebugging;       //   ...
        void* StopRegisterChange;  //   ...
        void* VirtualProtect;      //   ...
        void* VirtualProtectEx;    //   ...
        void* VirtualQueryEx;      //   ...
        void* VirtualAllocEx;      //   ...
        void* CreateRemoteThread;  //   ...
        void* OpenThread;          //   ...
        void* GetPEProcess;        //   ...
        void* GetPEThread;         //   ...
        void* GetThreadsProcessOffset;      //   ...
        void* GetThreadListEntryOffset;     //   ...
        void* GetProcessnameOffset;         //   ...
        void* GetDebugportOffset;           //   ...
        void* GetPhysicalAddress;           //   ...
        void* ProtectMe;                    //   ...
        void* GetCR4;                       //   ...
        void* GetCR3;                       //   ...
        void* SetCR3;                       //   ...
        void* GetSDT;                       //   ...
        void* GetSDTShadow;                 //   ...
        void* setAlternateDebugMethod;      //   ...
        void* getAlternateDebugMethod;      //   ...
        void* DebugProcess;                 //   ...
        void* ChangeRegOnBP;                //   ...
        void* RetrieveDebugData;            //   ...
        void* StartProcessWatch;            //   ...
        void* WaitForProcessListData;       //   ...
        void* GetProcessNameFromID;         //   ...
        void* GetProcessNameFromPEProcess;  //   ...
        void* KernelOpenProcess;            //   ...
        void* KernelReadProcessMemory;      //   ...
        void* KernelWriteProcessMemory;     //   ...
        void* KernelVirtualAllocEx;         //   ...
        void* IsValidHandle;                //   ...
        void* GetIDTCurrentThread;          //   ...
        void* GetIDTs;                      //   ...
        void* MakeWritable;                 //   ...
        void* GetLoadedState;               //   ...
        void* DBKSuspendThread;             //   ...
        void* DBKResumeThread;              //   ...
        void* DBKSuspendProcess;            //   ...
        void* DBKResumeProcess;             //   ...
        void* KernelAlloc;                  //   ...
        void* GetKProcAddress;              //   ...
        void* CreateToolhelp32Snapshot;     //   ...
        void* Process32First;               //   ...
        void* Process32Next;                //   ...
        void* Thread32First;                //   ...
        void* Thread32Next;                 //   ...
        void* Module32First;                //   ...
        void* Module32Next;                 //   ...
        void* Heap32ListFirst;              //   ...
        void* Heap32ListNext;               //   ...
        //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

        // advanced for delphi 7 enterprise dll programmers only
        void* MainForm;           // pointer to the Tmainform object.
        void* MemoryBrowserForm;  // pointer to the TMemoryBrowser object (memory view windows), same as mainform

        // Plugin Version 2+
        ExportedFunctionSignatures::NameToAddress         NameToAddress;
        ExportedFunctionSignatures::AddressToName         AddressToName;
        ExportedFunctionSignatures::GenerateAPIHookScript GenerateAPIHookScript;

        // Plugin version 3+
        ExportedFunctionSignatures::LoadDBK32         LoadDBK32;
        ExportedFunctionSignatures::LoadDBVMIfNeeded  LoadDBVMIfneeded;
        ExportedFunctionSignatures::PreviousOpCode    PreviousOpcode;
        ExportedFunctionSignatures::NextOpCode        NextOpcode;
        ExportedFunctionSignatures::CEP_DISASSEMBLEEX DisassembleEx;
        ExportedFunctionSignatures::LoadModule        LoadModule;
        ExportedFunctionSignatures::CEP_AA_ADDCOMMAND aa_AddExtraCommand;
        ExportedFunctionSignatures::CEP_AA_DELCOMMAND aa_RemoveExtraCommand;

        // version 4 extension
        ExportedFunctionSignatures::CreateTableEntry            CreateTableEntry;
        ExportedFunctionSignatures::GetTableEntry               GetTableEntry;
        ExportedFunctionSignatures::MemoryRecord_SetDescription MemoryRecord_SetDescription;
        ExportedFunctionSignatures::MemoryRecord_GetDescription MemoryRecord_GetDescription;
        ExportedFunctionSignatures::MemoryRecord_GetAddress     MemoryRecord_GetAddress;
        ExportedFunctionSignatures::MemoryRecord_SetAddress     MemoryRecord_SetAddress;
        ExportedFunctionSignatures::MemoryRecord_GetType        MemoryRecord_GetType;
        ExportedFunctionSignatures::MemoryRecord_SetType        MemoryRecord_SetType;
        ExportedFunctionSignatures::MemoryRecord_GetValueType   MemoryRecord_GetValue;
        ExportedFunctionSignatures::MemoryRecord_SetValueType   MemoryRecord_SetValue;
        ExportedFunctionSignatures::MemoryRecord_GetScript      MemoryRecord_GetScript;
        ExportedFunctionSignatures::MemoryRecord_SetScript      MemoryRecord_SetScript;
        ExportedFunctionSignatures::MemoryRecord_IsFrozen       MemoryRecord_Isfrozen;
        ExportedFunctionSignatures::MemoryRecord_Freeze         MemoryRecord_Freeze;
        ExportedFunctionSignatures::MemoryRecord_Unfreeze       MemoryRecord_Unfreeze;
        ExportedFunctionSignatures::MemoryRecord_SetColor       MemoryRecord_SetColor;
        ExportedFunctionSignatures::MemoryRecord_AppendToEntry  MemoryRecord_Appendtoentry;
        ExportedFunctionSignatures::MemoryRecord_Delete         MemoryRecord_Delete;

        ExportedFunctionSignatures::GetProcessIdFromProcessName GetProcessIDFromProcessName;
        ExportedFunctionSignatures::OpenProcess                 OpenProcessEx;
        ExportedFunctionSignatures::DebugProcess                DebugProcessEx;
        ExportedFunctionSignatures::Pause                       Pause;
        ExportedFunctionSignatures::Unpause                     Unpause;

        ExportedFunctionSignatures::SetBreakpoint          SetBreakpoint;
        ExportedFunctionSignatures::RemoveBreakpoint       RemoveBreakpoint;
        ExportedFunctionSignatures::ContinueFromBreakpoint ContinueFromBreakpoint;

        ExportedFunctionSignatures::CloseCheatEngine            CloseCheatEngine;
        ExportedFunctionSignatures::HideAllCheatEngineWindows   HideAllCheatEngineWindows;
        ExportedFunctionSignatures::UnhideMainCheatEngineWindow UnhideMainCheatEngineWindow;
        ExportedFunctionSignatures::CreateForm                  CreateForm;
        ExportedFunctionSignatures::CenterFormOnScreen          CenterFormOnScreen;
        ExportedFunctionSignatures::HideForm                    HideForm;
        ExportedFunctionSignatures::ShowForm                    ShowForm;
        ExportedFunctionSignatures::OnFormClose                 OnFormClose;

        ExportedFunctionSignatures::CreatePanel         CreatePanel;
        ExportedFunctionSignatures::CreateGroupBox      CreateGroupBox;
        ExportedFunctionSignatures::CreateButton        CreateButton;
        ExportedFunctionSignatures::CreateImage         CreateImage;
        ExportedFunctionSignatures::LoadImageFromFile   LoadImageFromFile;
        ExportedFunctionSignatures::SetImageTransparent SetImageTransparent;
        ExportedFunctionSignatures::SetImageStretch     SetImageStretch;

        ExportedFunctionSignatures::CreateLabel               CreateLabel;
        ExportedFunctionSignatures::CreateEdit                CreateEdit;
        ExportedFunctionSignatures::CreateMemo                CreateMemo;
        ExportedFunctionSignatures::CreateTimer               CreateTimer;
        ExportedFunctionSignatures::SetTimerInterval          SetTimerInterval;
        ExportedFunctionSignatures::OnTimer                   OnTimer;
        ExportedFunctionSignatures::SetControlCaption         SetControlCaption;
        ExportedFunctionSignatures::GetControlCaption         GetControlCaption;
        ExportedFunctionSignatures::SetControlPosition        SetControlPosition;
        ExportedFunctionSignatures::GetControlX               GetControlX;
        ExportedFunctionSignatures::GetControlY               GetControlY;
        ExportedFunctionSignatures::SetControlSize            SetControlSize;
        ExportedFunctionSignatures::GetControlWidth           GetControlWidth;
        ExportedFunctionSignatures::GetControlHeight          GetControlHeight;
        ExportedFunctionSignatures::SetControlAlign           SetControlAlign;
        ExportedFunctionSignatures::SetControlOnClickFunction OnClickControl;

        ExportedFunctionSignatures::DestroyObject     DestroyObject;
        ExportedFunctionSignatures::MessageDialog     MessageDialog;
        ExportedFunctionSignatures::SpeecHackSetSpeed SpeedHackSetSpeed;

        // V5: Todo, implement function declarations
        void*                                   ExecuteKernelCode;
        void*                                   UserdefinedInterruptHook;
        ExportedFunctionSignatures::GetLuaState GetLuaState;
        void*                                   MainThreadCall;
    };
}
