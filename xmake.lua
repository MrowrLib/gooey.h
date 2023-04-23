set_languages("c++20")
add_rules("mode.debug")
set_toolchains("msvc")
set_arch("x86")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")
add_requires("string_format")

target("MicroUI")
    set_kind("headeronly")
    add_headerfiles("include/(**.h)")
    add_includedirs("include", {public = true})
target_end()

local function example_target(name)
    target(name)
        set_kind("binary")
        add_files("Example.cpp")
        add_deps("MicroUI")
        add_packages("string_format")
        add_ldflags("/subsystem:windows")
        add_ldflags("/entry:WinMainCRTStartup", {force = true})
end

-- [wxWidgets]
local vcpkg_triplet = "x86-windows-static"
local vcpkg_root = os.getenv("VCPKG_ROOT")
add_requires("vcpkg::wxwidgets", {system = false, configs = {triplet = vcpkg_triplet}})
example_target("wx Example")
    add_packages("vcpkg::wxwidgets")
    add_includedirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "include"))
    add_linkdirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "lib"))
    add_links("kernel32", "user32", "gdi32", "comdlg32", "winspool", "winmm", "shell32", "comctl32", "ole32", "oleaut32", "uuid", "rpcrt4", "advapi32", "wsock32", "wininet", "libpng16", "nanosvg", "nanosvgrast", "zlib")
target_end()

-- [nana]
add_requires("nana")
example_target("nana Example")
    add_packages("nana")
target_end()
