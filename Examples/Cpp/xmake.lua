install_ui_library_global_dependency()

function example_target(target_name)
    target("Example - " .. target_name)
        set_kind("binary")
        add_files("*.cpp")
        setup_target_for_ui_library()
        add_includedirs("..")

        -- Windows stuff:
        -- add_files("*.cpp", "../icon.rc")
        -- add_ldflags("/subsystem:windows")
        -- add_ldflags("/entry:WinMainCRTStartup", { force = true })
end

includes("*/xmake.lua")
