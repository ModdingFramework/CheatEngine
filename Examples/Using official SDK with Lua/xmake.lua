add_requires("cheat-engine-sdk", { configs = { includes_lua = true }})
add_requires("sol2", { configs = { includes_lua = false }})

target("Example - Using official SDK with Lua")
  set_kind("shared")
  add_files("*.cpp")
  add_packages("cheat-engine-sdk", "sol2")
