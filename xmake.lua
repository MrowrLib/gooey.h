add_rules("mode.debug", "mode.release")

set_languages("c++20")
set_toolchains("msvc")

includes("gooey*/xmake.lua")
includes("Examples/xmake.lua")
