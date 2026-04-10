set_project("JaJaLys-Artifacts-Client")
set_version("99.99.99")

add_rules("mode.debug", "mode.release")

add_requires("cpp-httplib  0.22.0", {config = {ssl=true}})
add_requires("nlohmann_json")
add_requires("fmt")


set_languages("c++20")

target("logic")
    set_kind("static")
    add_files("ammo-logic/**.cpp")
    add_packages("cpp-httplib", "nlohmann_json", "fmt", {public = true})
    add_includedirs("ammo-logic/", {public = true})

target("client")
    set_kind("binary")
    add_files("ammo-client/**.cpp")
    add_deps("logic")

    set_rundir("$(projectdir)")
