option("ui_library")
    set_showmenu(true)
    set_default("fltk")
    set_values("fltk")
    set_description("Select UI Library (fltk/...)")
option_end()

if get_config("ui_library") == "<something>" then
    -- wx or qt or ...
else
    includes("../xmake/fltk.lua")
end

install_ui_library_global_dependency()

function example_target(target_name)
    target("Example - " .. target_name)
        set_kind("binary")
        add_files("*.cpp")
        -- add_files("*.cpp", "../icon.rc")
        setup_target_for_ui_library()
        add_includedirs("..")
        add_headerfiles("../gooey_loader.h")
        -- add_ldflags("/subsystem:windows")
        -- add_ldflags("/entry:WinMainCRTStartup", { force = true })
end

includes("*/xmake.lua")
