set_languages("c++20")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")

add_requires("cheat-engine-sdk", { configs = { includes_lua = true }})
add_requires("sol2", { configs = { includes_lua = false }})
add_requires("_Log_", "spdlog")

target("Example - Using plugin library with Lua")
  set_kind("shared")
  add_files("*.cpp")
  -- add_packages("cheat-engine-sdk", "sol2")
  add_deps("Official Cheat Engine Plugin SDK", { public = true })
  add_deps("Official Cheat Engine Plugin SDK - Lua Support", { public = true })
  add_deps("Plugin Helper Library")
  add_packages("_Log_", "spdlog")
