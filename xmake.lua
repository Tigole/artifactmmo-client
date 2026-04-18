set_project("JaJaLys-Artifacts-Client")
set_version("99.99.99")

add_rules("mode.debug", "mode.release")

add_requires("cpp-httplib  0.22.0", {configs = {ssl=true}})
add_requires("nlohmann_json", "fmt", "raylib", "clay")
--add_requires()


set_languages("c++20")

target("logic")
    set_kind("static")
    add_files("ammo-logic/**.cpp")
    add_packages("cpp-httplib", "nlohmann_json", "fmt", {public = true})
    add_includedirs("ammo-logic/", {public = true})

target("ui")
    set_kind("static")
    add_files("ammo-ui/**.cpp")
    add_deps("logic")
    add_packages("raylib", "clay")
    add_includedirs("ammo-ui/", {public = true})

target("client")
    set_kind("binary")
    add_files("ammo-client/**.cpp")
    add_deps("logic")
    add_deps("ui")

    set_rundir("$(projectdir)")
