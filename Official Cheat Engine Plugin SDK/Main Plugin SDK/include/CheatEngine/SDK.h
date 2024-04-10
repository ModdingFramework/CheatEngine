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

    Original type names have been preserved in the CheatEngine::SDK::Compat namespace.

    To use the original type names:
    - #include <CheatEngine/SDK/Compat.h>
    - using namespace CheatEngine::SDK::Compat;

    Note: `char*` have been converted to `const char*` so Compat is not 100% compatible.

    If you want the original SDK.h, you can #include <CheatEngine/SDK/Official.h>
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

#define CESDK_VERSION 6

namespace CheatEngine::SDK {

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

    typedef enum { aaInitialize = 0, aaPhase1 = 1, aaPhase2 = 2, aaFinalize = 3 } AutoAssemblerPhase;

    struct PluginVersion {
        unsigned int version;  // write here the minimum version this dll is compatible with (Current supported version:
                               // 1 and 2: this SDK only describes 2)
        const char* pluginName;  // make this point to a 0-terminated string (allocated memory or static addressin your
                                 // dll, not stack)
    };

    struct AddressListRecord {
        char*          interpretedaddress;  // pointer to a 255 bytes long string (0 terminated)
        std::uintptr_t address;    // this is a read-only representaion of the address. Change interpretedaddress if you
                                   // want to change this
        int            ispointer;  // readonly
        int            countoffsets;  // readonly
        std::uint32_t* offsets;       // array of dwords ranging from 0 to countoffsets-1 (readonly)
        char*          description;   // pointer to a 255 bytes long string
        char           valuetype;     // 0=byte, 1=word, 2=dword, 3=float, 4=double, 5=bit, 6=int64, 7=string
        char           size;          // stringlength or bitlength;
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

    typedef struct _REGISTERMODIFICATIONINFO {
        std::uintptr_t address;  // addres to break on
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
    } REGISTERMODIFICATIONINFO, *PREGISTERMODIFICATIONINFO;

    // the __stdcall stuff isn't really needed since I've set compiler options to force stdcall, but this makes it clear
    // that stdcall is used to the reader
    typedef void(__stdcall* CEP_SHOWMESSAGE)(char* message);
    typedef int(__stdcall* CEP_REGISTERFUNCTION)(int pluginid, PluginType functiontype, void* init);
    typedef int(__stdcall* CEP_UNREGISTERFUNCTION)(int pluginid, int functionid);
    typedef void*(__stdcall* CEP_GETMAINWINDOWHANDLE)(void);
    typedef int(__stdcall* CEP_AUTOASSEMBLE)(char* script);
    typedef int(__stdcall* CEP_ASSEMBLER)(
        std::uintptr_t address, char* instruction, std::uint8_t* output, int maxlength, int* returnedsize
    );
    typedef int(__stdcall* CEP_DISASSEMBLER)(std::uintptr_t address, char* output, int maxsize);
    typedef int(__stdcall* CEP_CHANGEREGATADDRESS)(std::uintptr_t address, PREGISTERMODIFICATIONINFO changereg);
    typedef int(__stdcall* CEP_INJECTDLL)(char* dllname, char* functiontocall);
    typedef int(__stdcall* CEP_FREEZEMEM)(std::uintptr_t address, int size);
    typedef int(__stdcall* CEP_UNFREEZEMEM)(int freezeID);
    typedef int(__stdcall* CEP_FIXMEM)(void);
    typedef int(__stdcall* CEP_PROCESSLIST)(char* listbuffer, int listsize);
    typedef int(__stdcall* CEP_RELOADSETTINGS)(void);
    typedef std::uintptr_t(__stdcall* CEP_GETADDRESSFROMPOINTER)(
        std::uintptr_t baseaddress, int offsetcount, int* offsets
    );
    typedef int(__stdcall* CEP_GENERATEAPIHOOKSCRIPT)(
        char* address, char* addresstojumpto, char* addresstogetnewcalladdress, char* script, int maxscriptsize
    );
    typedef int(__stdcall* CEP_ADDRESSTONAME)(std::uintptr_t address, char* name, int maxnamesize);
    typedef int(__stdcall* CEP_NAMETOADDRESS)(char* name, std::uintptr_t* address);

    typedef void(__stdcall* CEP_LOADDBK32)(void);
    typedef int(__stdcall* CEP_LOADDBVMIFNEEDED)(void);
    typedef std::uint32_t(__stdcall* CEP_PREVIOUSOPCODE)(std::uintptr_t address);
    typedef std::uint32_t(__stdcall* CEP_NEXTOPCODE)(std::uintptr_t address);
    typedef int(__stdcall* CEP_LOADMODULE)(char* modulepath, char* exportlist, int* maxsize);
    typedef int(__stdcall* CEP_DISASSEMBLEEX)(std::uintptr_t address, char* output, int maxsize);
    typedef void(__stdcall* CEP_AA_ADDCOMMAND)(char* command);
    typedef void(__stdcall* CEP_AA_DELCOMMAND)(char* command);

    typedef void*(__stdcall* CEP_CREATETABLEENTRY)(void);
    typedef void*(__stdcall* CEP_GETTABLEENTRY)(char* description);
    typedef int(__stdcall* CEP_MEMREC_SETDESCRIPTION)(void* memrec, char* description);
    typedef const char*(__stdcall* CEP_MEMREC_GETDESCRIPTION)(void* memrec);
    typedef int(__stdcall* CEP_MEMREC_GETADDRESS)(
        void* memrec, std::uintptr_t* address, std::uint32_t* offsets, int maxoffsets, int* neededOffsets
    );
    typedef int(__stdcall* CEP_MEMREC_SETADDRESS)(void* memrec, char* address, std::uint32_t* offsets, int offsetcount);
    typedef int(__stdcall* CEP_MEMREC_GETTYPE)(void* memrec);
    typedef int(__stdcall* CEP_MEMREC_SETTYPE)(void* memrec, int vtype);
    typedef int(__stdcall* CEP_MEMREC_GETVALUETYPE)(void* memrec, char* value, int maxsize);
    typedef int(__stdcall* CEP_MEMREC_SETVALUETYPE)(void* memrec, char* value);
    typedef char*(__stdcall* CEP_MEMREC_GETSCRIPT)(void* memrec);
    typedef int(__stdcall* CEP_MEMREC_SETSCRIPT)(void* memrec, char* script);
    typedef int(__stdcall* CEP_MEMREC_ISFROZEN)(void* memrec);
    typedef int(__stdcall* CEP_MEMREC_FREEZE)(void* memrec, int direction);
    typedef int(__stdcall* CEP_MEMREC_UNFREEZE)(void* memrec);
    typedef int(__stdcall* CEP_MEMREC_SETCOLOR)(void* memrec, std::uint32_t color);
    typedef int(__stdcall* CEP_MEMREC_APPENDTOENTRY)(void* memrec1, void* memrec2);
    typedef int(__stdcall* CEP_MEMREC_DELETE)(void* memrec);

    typedef std::uint32_t(__stdcall* CEP_GETPROCESSIDFROMPROCESSNAME)(char* name);
    typedef std::uint32_t(__stdcall* CEP_OPENPROCESS)(std::uint32_t pid);
    typedef std::uint32_t(__stdcall* CEP_DEBUGPROCESS)(int debuggerinterface);
    typedef void(__stdcall* CEP_PAUSE)(void);
    typedef void(__stdcall* CEP_UNPAUSE)(void);
    typedef int(__stdcall* CEP_DEBUG_SETBREAKPOINT)(std::uintptr_t address, int size, int trigger);
    typedef int(__stdcall* CEP_DEBUG_REMOVEBREAKPOINT)(std::uintptr_t address);
    typedef int(__stdcall* CEP_DEBUG_CONTINUEFROMBREAKPOINT)(int continueoption);

    typedef void(__stdcall* CEP_CLOSECE)(void);
    typedef void(__stdcall* CEP_HIDEALLCEWINDOWS)(void);
    typedef void(__stdcall* CEP_UNHIDEMAINCEWINDOW)(void);

    typedef void*(__stdcall* CEP_CREATEFORM)(void);
    typedef void(__stdcall* CEP_FORM_CENTERSCREEN)(void* form);
    typedef void(__stdcall* CEP_FORM_HIDE)(void* form);
    typedef void(__stdcall* CEP_FORM_SHOW)(void* form);
    typedef void(__stdcall* CEP_FORM_ONCLOSE)(void* form, void* function);

    typedef void*(__stdcall* CEP_CREATEPANEL)(void* owner);
    typedef void*(__stdcall* CEP_CREATEGROUPBOX)(void* owner);
    typedef void*(__stdcall* CEP_CREATEBUTTON)(void* owner);
    typedef void*(__stdcall* CEP_CREATEIMAGE)(void* owner);

    typedef int(__stdcall* CEP_IMAGE_LOADIMAGEFROMFILE)(void* image, char* filename);
    typedef void(__stdcall* CEP_IMAGE_TRANSPARENT)(void* image, int transparent);
    typedef void(__stdcall* CEP_IMAGE_STRETCH)(void* image, int stretch);

    typedef void*(__stdcall* CEP_CREATELABEL)(void* owner);
    typedef void*(__stdcall* CEP_CREATEEDIT)(void* owner);
    typedef void*(__stdcall* CEP_CREATEMEMO)(void* owner);
    typedef void*(__stdcall* CEP_CREATETIMER)(void* owner);

    typedef void(__stdcall* CEP_TIMER_SETINTERVAL)(void* timer, int interval);
    typedef void(__stdcall* CEP_TIMER_ONTIMER)(void* timer, void* function);

    typedef void(__stdcall* CEP_CONTROL_SETCAPTION)(void* control, char* caption);
    typedef int(__stdcall* CEP_CONTROL_GETCAPTION)(void* control, char* caption, int maxsize);

    typedef void(__stdcall* CEP_CONTROL_SETPOSITION)(void* control, int x, int y);
    typedef int(__stdcall* CEP_CONTROL_GETX)(void* control);
    typedef int(__stdcall* CEP_CONTROL_GETY)(void* control);

    typedef void(__stdcall* CEP_CONTROL_SETSIZE)(void* control, int width, int height);
    typedef int(__stdcall* CEP_CONTROL_GETWIDTH)(void* control);
    typedef int(__stdcall* CEP_CONTROL_GETHEIGHT)(void* control);

    typedef void(__stdcall* CEP_CONTROL_SETALIGN)(void* control, int align);
    typedef void(__stdcall* CEP_CONTROL_ONCLICK)(void* control, void* function);

    typedef void(__stdcall* CEP_OBJECT_DESTROY)(void* object);

    typedef int(__stdcall* CEP_MESSAGEDIALOG)(char* massage, int messagetype, int buttoncombination);
    typedef int(__stdcall* CEP_SPEEDHACK_SETSPEED)(float speed);

#ifdef CHEATENGINE_USE_LUA
    typedef lua_State*(__fastcall* CEP_GETLUASTATE)();
#else
    typedef void*(__fastcall* CEP_GETLUASTATE)();
#endif

    typedef int(__stdcall** CEP_READPROCESSMEMORY)(
        void* hProcess, const void* lpBaseAddress, void* lpBuffer, size_t nSize, size_t* lpNumberOfBytesRead
    );

    /*
    function ce_messageDialog(message: pchar; messagetype: integer; buttoncombination: integer): integer; stdcall;
    function ce_speedhack_setSpeed(speed: single): int; stdcall;
    */

    struct ExportedFunctions {
        int                    sizeofExportedFunctions;
        CEP_SHOWMESSAGE        ShowMessage;          // Pointer to the ce showmessage function
        CEP_REGISTERFUNCTION   RegisterFunction;     // Use this to register a specific type of plugin
        CEP_UNREGISTERFUNCTION UnregisterFunction;   // unregisters a function registered with registerfunction
        std::uint32_t*         OpenedProcessID;      // pointer to the currently selected processid
        void**                 OpenedProcessHandle;  // pointer to the currently selected processhandle

        CEP_GETMAINWINDOWHANDLE
        GetMainWindowHandle;                  // returns the handle of the main window (for whatever reason, it is
                                              // recommended to use delphi to make a real userinterface upgrade)
        CEP_AUTOASSEMBLE       AutoAssemble;  // Pointer to the AutoAssemble function
        CEP_ASSEMBLER          Assembler;     // pointer to the assembler function
        CEP_DISASSEMBLER       Disassembler;  // pointer to the disassembler function
        CEP_CHANGEREGATADDRESS ChangeRegistersAtAddress;  // pointer to the ChangeRegAtBP function
        CEP_INJECTDLL          InjectDLL;                 // pointer to ce's Inject DLL function
        CEP_FREEZEMEM          FreezeMem;                 // pointer to the FreezeMem routine
        CEP_UNFREEZEMEM    UnfreezeMem;  // pointer to the UnfreezeMem routine (use this to undo freezes with FreezeMem)
        CEP_FIXMEM         FixMem;       // pointer to the fixmem routine
        CEP_PROCESSLIST    ProcessList;  // pointer to the processlist routine
        CEP_RELOADSETTINGS ReloadSettings;                // pointer to the ReloadSettings routine
        CEP_GETADDRESSFROMPOINTER GetAddressFromPointer;  // pointer to the GetAddressFromPointer routine

        // pointers to the address that contains the pointers to the functions
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        CEP_READPROCESSMEMORY ReadProcessMemory;  // pointer to the pointer of ReadProcessMemory (Change it to hook that
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
        void* mainform;       // pointer to the Tmainform object.
        void* memorybrowser;  // pointer to the TMemoryBrowser object (memory view windows), same as mainform

        // Plugin Version 2+
        CEP_NAMETOADDRESS         sym_nameToAddress;
        CEP_ADDRESSTONAME         sym_addressToName;
        CEP_GENERATEAPIHOOKSCRIPT sym_generateAPIHookScript;

        // Plugin version 3+
        CEP_LOADDBK32        loadDBK32;
        CEP_LOADDBVMIFNEEDED loaddbvmifneeded;
        CEP_PREVIOUSOPCODE   previousOpcode;
        CEP_NEXTOPCODE       nextOpcode;
        CEP_DISASSEMBLEEX    disassembleEx;
        CEP_LOADMODULE       loadModule;
        CEP_AA_ADDCOMMAND    aa_AddExtraCommand;
        CEP_AA_DELCOMMAND    aa_RemoveExtraCommand;

        // version 4 extension
        CEP_CREATETABLEENTRY      createTableEntry;
        CEP_GETTABLEENTRY         getTableEntry;
        CEP_MEMREC_SETDESCRIPTION memrec_setDescription;
        CEP_MEMREC_GETDESCRIPTION memrec_getDescription;
        CEP_MEMREC_GETADDRESS     memrec_getAddress;
        CEP_MEMREC_SETADDRESS     memrec_setAddress;
        CEP_MEMREC_GETTYPE        memrec_getType;
        CEP_MEMREC_SETTYPE        memrec_setType;
        CEP_MEMREC_GETVALUETYPE   memrec_getValue;
        CEP_MEMREC_SETVALUETYPE   memrec_setValue;
        CEP_MEMREC_GETSCRIPT      memrec_getScript;
        CEP_MEMREC_SETSCRIPT      memrec_setScript;
        CEP_MEMREC_ISFROZEN       memrec_isfrozen;
        CEP_MEMREC_FREEZE         memrec_freeze;
        CEP_MEMREC_UNFREEZE       memrec_unfreeze;
        CEP_MEMREC_SETCOLOR       memrec_setColor;
        CEP_MEMREC_APPENDTOENTRY  memrec_appendtoentry;
        CEP_MEMREC_DELETE         memrec_delete;

        CEP_GETPROCESSIDFROMPROCESSNAME getProcessIDFromProcessName;
        CEP_OPENPROCESS                 openProcessEx;
        CEP_DEBUGPROCESS                debugProcessEx;
        CEP_PAUSE                       pause;
        CEP_UNPAUSE                     unpause;

        CEP_DEBUG_SETBREAKPOINT          debug_setBreakpoint;
        CEP_DEBUG_REMOVEBREAKPOINT       debug_removeBreakpoint;
        CEP_DEBUG_CONTINUEFROMBREAKPOINT debug_continueFromBreakpoint;

        CEP_CLOSECE            closeCE;
        CEP_HIDEALLCEWINDOWS   hideAllCEWindows;
        CEP_UNHIDEMAINCEWINDOW unhideMainCEwindow;
        CEP_CREATEFORM         createForm;
        CEP_FORM_CENTERSCREEN  form_centerScreen;
        CEP_FORM_HIDE          form_hide;
        CEP_FORM_SHOW          form_show;
        CEP_FORM_ONCLOSE       form_onClose;

        CEP_CREATEPANEL             createPanel;
        CEP_CREATEGROUPBOX          createGroupBox;
        CEP_CREATEBUTTON            createButton;
        CEP_CREATEIMAGE             createImage;
        CEP_IMAGE_LOADIMAGEFROMFILE image_loadImageFromFile;
        CEP_IMAGE_TRANSPARENT       image_transparent;
        CEP_IMAGE_STRETCH           image_stretch;

        CEP_CREATELABEL         createLabel;
        CEP_CREATEEDIT          createEdit;
        CEP_CREATEMEMO          createMemo;
        CEP_CREATETIMER         createTimer;
        CEP_TIMER_SETINTERVAL   timer_setInterval;
        CEP_TIMER_ONTIMER       timer_onTimer;
        CEP_CONTROL_SETCAPTION  control_setCaption;
        CEP_CONTROL_GETCAPTION  control_getCaption;
        CEP_CONTROL_SETPOSITION control_setPosition;
        CEP_CONTROL_GETX        control_getX;
        CEP_CONTROL_GETY        control_getY;
        CEP_CONTROL_SETSIZE     control_setSize;
        CEP_CONTROL_GETWIDTH    control_getWidth;
        CEP_CONTROL_GETHEIGHT   control_getHeight;
        CEP_CONTROL_SETALIGN    control_setAlign;
        CEP_CONTROL_ONCLICK     control_onClick;

        CEP_OBJECT_DESTROY     object_destroy;
        CEP_MESSAGEDIALOG      messageDialog;
        CEP_SPEEDHACK_SETSPEED speedhack_setSpeed;

        // V5: Todo, implement function declarations
        void*           ExecuteKernelCode;
        void*           UserdefinedInterruptHook;
        CEP_GETLUASTATE GetLuaState;
        void*           MainThreadCall;
    };
}
