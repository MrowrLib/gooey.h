set_languages("c++20")
add_rules("mode.debug")
set_toolchains("msvc")

set_arch("x86")
set_defaultplat("windows")
set_defaultmode("x86")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")
add_requires("StringFormatting")

-- [wxWidgets]
-- local vcpkg_triplet = "x86-windows-static"
-- local vcpkg_root = os.getenv("VCPKG_ROOT")
-- add_requires("vcpkg::wxwidgets", {system = false, configs = {triplet = vcpkg_triplet}})

-- [Qt]
local vcpkg_triplet = "x86-windows-static"
local vcpkg_root = os.getenv("VCPKG_ROOT")
add_requires("vcpkg::qtbase", {system = false, configs = {triplet = vcpkg_triplet}})
add_requires("vcpkg::qtdeclarative", {system = false, configs = {triplet = vcpkg_triplet}})
add_cxflags("/Zc:__cplusplus")
add_defines(_CRT_SECURE_NO_WARNINGS)

target("UserInterface")
    set_kind("headeronly")
    add_headerfiles("include/(**.h)")
    add_includedirs("include", {public = true})

target("Example")
    set_kind("binary")
    -- add_ldflags("/subsystem:windows")
    -- set_policy("check.auto_ignore_flags", false)
    -- add_ldflags("/entry:WinMainCRTStartup")
    add_files("Example.cpp")
    add_deps("UserInterface")
    add_packages("StringFormatting")
    add_packages("vcpkg::qtbase")

    -- [wxWidgets]
    -- add_packages("vcpkg::wxwidgets")
    -- add_includedirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "include"))
    -- add_linkdirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "lib"))
    -- add_links("kernel32", "user32", "gdi32", "comdlg32", "winspool", "winmm", "shell32", "comctl32", "ole32", "oleaut32", "uuid", "rpcrt4", "advapi32", "wsock32", "wininet", "libpng16", "nanosvg", "nanosvgrast", "zlib")

    -- [Qt]
    add_packages("vcpkg::qtbase")
    add_packages("vcpkg::qtdeclarative")
    add_includedirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "include"))
    add_includedirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "include", "Qt6"))
    add_includedirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "include", "Qt6", "QtGui"))
    add_includedirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "include", "Qt6", "QtWidgets"))
    add_linkdirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "lib"))
    add_linkdirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "Qt6", "plugins", "platforms"))
    -- add_links("qwindows", "zstd", "synchronization", "netapi32", "authz", "dwrite", "zlib", "pcre2-8", "pcre2-16", "pcre2-32", "libpng16", "harfbuzz", "double-conversion", "icuuc", "icudt", "icuin", "Qt6Core", "Qt6Gui", "Qt6Widgets", "kernel32", "user32", "gdi32", "winspool", "shell32", "ole32", "oleaut32", "uuid", "comdlg32", "advapi32", "ws2_32", "userenv", "shell32", "shlwapi", "rpcrt4", "oleaut32", "ole32", "uuid", "comdlg32", "advapi32", "winspool", "gdi32", "user32", "kernel32", "opengl32", "dwmapi", "imm32", "winmm", "version", "uxtheme", "d3d9", "d3d11", "dxgi", "dxguid", "dinput8")
    add_files(path.join(vcpkg_root, "installed", vcpkg_triplet, "debug", "lib", "objects-Debug", "Widgets_resources_1", ".rcc", "qrc_qstyle.cpp.obj"))
    add_files(path.join(vcpkg_root, "installed", vcpkg_triplet, "debug", "lib", "objects-Debug", "Widgets_resources_3", ".rcc", "qrc_qmessagebox.cpp.obj"))

    add_links(
        "qwindows",
        "dwmapi",
        "imm32",
        "oleaut32",
        "shlwapi",
        "winspool",
        "wtsapi32",
        "shcore",
        "comdlg32",
        "d3d9",
        "Qt6OpenGL",
        "Qt6Gui",
        "Qt6Core",
        "synchronization",
        "mpr",
        "userenv",
        "authz",
        "kernel32",
        "netapi32",
        "uuid",
        "version",
        "winmm",
        "ws2_32",
        "double-conversion",
        "runtimeobject",
        "icuin",
        "icuuc",
        "icudt",
        "pcre2-16",
        "zstd",
        "d3d11",
        "dxgi",
        "dxguid",
        "advapi32",
        "gdi32",
        "ole32",
        "shell32",
        "user32",
        "libpng16",
        "harfbuzz",
        "freetype",
        "bz2",
        "zlib",
        "brotlidec-static",
        "brotlicommon-static",
        "d2d1",
        "dwrite"
    )

    local qt_plugin_path = path.join(vcpkg_root, "installed", vcpkg_triplet, "Qt6", "plugins/")
    add_runenvs("QT_PLUGIN_PATH", qt_plugin_path)
    add_runenvs("QT_DEBUG_PLUGINS", "1")

    -- after_build(function (target)
        -- local build_dir = target:targetdir()
        -- os.cp(path.join(vcpkg_root, "installed", vcpkg_triplet, "Qt6", "plugins", "platforms", "qwindows.*"), build_dir)
    -- end)

    -- after_build(function (target)
    --     import("core.project.config")
    --     config.set_runenv("QT_PLUGIN_PATH", qt_plugin_path)
    -- end)