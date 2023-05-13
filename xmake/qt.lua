function install_ui_library_global_dependency()
    --
end

function setup_target_for_ui_library()
    add_deps("gooey-qt")
    add_defines("GOOEY_USE_QT")
    add_rules("qt.qrc")
    add_files("../*.qrc")

    if is_host("windows") then
        add_cxflags("/Zc:__cplusplus")

        local qt_dir = path.join(os.getenv("QTROOT"), "msvc2019_64")
        local qt_lib_dir = path.join(qt_dir, "lib")
        local qt_include_dir = path.join(qt_dir, "include")

        add_includedirs(path.join(qt_include_dir, "QtCore"))
        add_includedirs(path.join(qt_include_dir, "QtGui"))
        add_includedirs(path.join(qt_include_dir, "QtWidgets"))

        add_linkdirs(qt_lib_dir)
        add_links("Qt6Core", "Qt6Gui", "Qt6Widgets")

        add_rules("qt.application")
    elseif is_host("macosx") then
        local qt_dir = path.join(os.getenv("QTROOT"), "macos")
        local qt_lib_dir = path.join(qt_dir, "lib")

        add_includedirs(path.join(qt_dir, "include"))
        add_includedirs(path.join(qt_lib_dir, "QtCore.framework", "Headers"))
        add_includedirs(path.join(qt_lib_dir, "QtGui.framework", "Headers"))
        add_includedirs(path.join(qt_lib_dir, "QtWidgets.framework", "Headers"))

        add_linkdirs(path.join(qt_lib_dir, "QtCore.framework"))
        add_linkdirs(path.join(qt_lib_dir, "QtGui.framework"))
        add_linkdirs(path.join(qt_lib_dir, "QtWidgets.framework"))

        add_rules("qt.application")
        add_ldflags("-F" .. qt_lib_dir)
        add_frameworks("QtCore", "QtGui", "QtWidgets")
    elseif is_host("linux") then
        -- TODO
    end
end
