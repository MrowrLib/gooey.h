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
    add_deps("gooey-fltk")
    add_defines("GOOEY_USE_FLTK")

    -- ...
    add_packages("brew::fltk")
end
