add_rules("mode.debug", "mode.release")

set_languages("c++20")

add_repositories("ModdingFramework https://github.com/ModdingFramework/Packages.git")

includes("Official SDK/**/xmake.lua")
includes("Plugin Helper Library/**/xmake.lua")
includes("Examples/**/xmake.lua")
