set_languages("c++20")
add_rules("mode.debug")
set_toolchains("msvc")

-- Bring your own GUI library
-- Uncomment the one that you want!
add_requires("nana")
-- add_requires("wxwidgets")

target("UserInterface")
    set_kind("headeronly")
    add_headerfiles("include/(**.h)")
    add_includedirs("include", {public = true})
    add_packages("nana")

target("Example")
    set_kind("binary")
    add_ldflags("/subsystem:windows")
    set_policy("check.auto_ignore_flags", false)
    add_ldflags("/entry:WinMainCRTStartup")
    add_files("Example.cpp")
    add_deps("UserInterface")
    -- Swap out with the GUI library you want to use!
    add_packages("nana")
    -- add_packages("wxwidgets")
