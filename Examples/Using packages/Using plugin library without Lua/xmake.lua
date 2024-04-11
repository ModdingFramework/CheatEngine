add_requires("cheat-engine-plugin", { configs = { includes_lua = false }})

target("Example - Using plugin library without Lua")
  set_kind("shared")
  add_files("*.cpp")
  add_packages("cheat-engine-plugin")
