add_requires("_Log_")

target("Plugin Helper Library")
  set_kind("headeronly")
  add_includedirs("include", {public = true})
  add_deps("Official Cheat Engine Plugin SDK", { public = true })
  add_deps("Official Cheat Engine Plugin SDK - Lua Support", { public = true })
  add_defines("CHEATENGINE_USE_LUA", "CHEATENGINE_INCLUDE_WINDOWS")
  add_packages("_Log_")
