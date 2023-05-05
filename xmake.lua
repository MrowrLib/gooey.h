add_rules("mode.debug", "mode.release")

set_languages("c++20")
set_toolchains("msvc")

includes("**/xmake.lua")

target("Example")
    set_kind("binary")
    add_files("Example.cpp")
    add_deps("Gooey", "Gooey.FLTK")
