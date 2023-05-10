add_rules("mode.debug", "mode.release")

set_languages("c++20")

if is_host("windows") then
    set_toolchains("msvc")
elseif is_host("macosx") then
    set_toolchains("clang")
elseif is_host("linux") then
    -- TODO
end

includes("gooey*/xmake.lua")
includes("Examples/xmake.lua")
