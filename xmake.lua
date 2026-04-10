set_project("JaJaLys-Artifacts-Client")
set_version("99.99.99")

add_rules("mode.debug", "mode.release")

add_requires("cpp-httplib", {config = {ssl=true}})
add_requires("nlohmann_json")
add_requires("fmt")


set_languages("c++20")

target("client")
    set_kind("binary")
    add_files("Sources/**.cpp")

    add_packages("cpp-httplib", "nlohmann_json", "fmt")

    add_includedirs("Sources/")

    --on_run(function(target)
    --    print(target:targetdir())
    --end)