install_ui_library_global_dependency()

    target("HelloWorld")
        set_kind("binary")
        add_files("Example - Empty Window.cpp")
        setup_target_for_ui_library()
        add_includedirs(".")

-- for _, file_path in ipairs(os.files(os.scriptdir() .. "/*.cpp")) do
--     local cpp = path.filename(file_path)
--     local target_name = path.basename(cpp, ".cpp")
--     target(target_name)
--         set_kind("binary")
--         add_files(cpp)
--         setup_target_for_ui_library()
--         add_includedirs(".")
-- end
