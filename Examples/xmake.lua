-- option("ui_library")
--     set_showmenu(true)
--     set_default("fltk")
--     set_values("fltk")
--     set_description("Select UI Library (fltk/...)")
-- option_end()

-- if get_config("ui_library") == "<something>" then
--     -- wx or qt or ...
-- else
    -- includes("../xmake/fltk.lua")
includes("../xmake/fltk.lua")
-- end

includes("Cpp/xmake.lua")
includes("Rust/CppRustLibraryLoader/xmake.lua")
