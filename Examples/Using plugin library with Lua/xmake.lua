add_requires("cheat-engine-plugin")
add_requires("sol2", { configs = { includes_lua = false }})

target("Example - Using plugin library with Lua")
  set_kind("shared")
  add_files("*.cpp")
  add_packages("cheat-engine-plugin", "sol2")
