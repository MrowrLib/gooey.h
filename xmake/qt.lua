-- export VCPKG_ROOT="$HOME/Code/vcpkg"
-- export FLTK_INCLUDE_DIR=$(brew --prefix fltk)/include
-- export FLTK_LIB_DIR=$(brew --prefix fltk)/lib

function install_ui_library_global_dependency()
    -- I can't get any of these to work on Mac yet
    -- add_requires("fltk")
    -- add_requires("vcpkg::fltk")
    add_requires("brew::fltk")
end

function setup_target_for_ui_library()
    add_deps("gooey-qt")
    add_defines("GOOEY_USE_QT")

    -- ...
    local qt_dir = path.join(os.getenv("QTROOT"), "macos")
    local qt_lib_dir = path.join(qt_dir, "lib")

    add_includedirs(path.join(qt_dir, "include"))
    add_includedirs(path.join(qt_lib_dir, "QtCore.framework", "Headers"))
    add_includedirs(path.join(qt_lib_dir, "QtGui.framework", "Headers"))
    add_includedirs(path.join(qt_lib_dir, "QtWidgets.framework", "Headers"))

    add_linkdirs(path.join(qt_lib_dir, "QtCore.framework"))
    add_linkdirs(path.join(qt_lib_dir, "QtGui.framework"))
    add_linkdirs(path.join(qt_lib_dir, "QtWidgets.framework"))

    -- add_rules("qt.shared")
    -- add_rules("qt.quickapp")
    add_rules("qt.application")
    add_ldflags("-F" .. qt_lib_dir)
    add_frameworks("QtCore", "QtGui", "QtWidgets")
end
