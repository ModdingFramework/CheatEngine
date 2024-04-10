#include <_Log_.h>
_LogToFile_("C:/Temp/CEPlugin_Example_UsingPluginLibraryWithLua.log");

//

#include <CheatEngine/Plugin.h>
// ...

CEPlugin("My Plugin Name");

CEPlugin_Init {
    _Log_("CEPlugin_Init");
    return true;
}

CEPlugin_OnInit { _Log_("CEPlugin_OnInit"); }

CEPlugin_Enable {
    _Log_("CEPlugin_Enable");
    return true;
}

CEPlugin_OnEnable { _Log_("CEPlugin_Enable"); }

CEPlugin_Disable {
    _Log_("CEPlugin_Disable");
    return true;
}

CEPlugin_OnDisable { _Log_("CEPlugin_Disable"); }
