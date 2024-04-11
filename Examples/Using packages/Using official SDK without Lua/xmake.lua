add_requires("cheat-engine-sdk", { configs = { includes_lua = false }})

target("Example - Using official SDK without Lua")
  set_kind("shared")
  add_files("*.cpp")
  add_packages("cheat-engine-sdk")
