#include <_Log_.h>
_LogToFile_("C:/Temp/CEPlugin_Example_UsingPluginLibraryWithLua.log");

//

#include <CheatEngine/Plugin.h>
// ...

CEPlugin("My Plugin Name");

CEPlugin_OnInit { _Log_("CEPlugin_OnInit"); }

CEPlugin_OnEnable {
    CE::ShowMessage("Hello!");
    _Log_("CEPlugin_Enable");
}

CEPlugin_OnDisable { _Log_("CEPlugin_Disable"); }
