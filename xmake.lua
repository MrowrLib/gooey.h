add_rules("mode.debug", "mode.release")

set_languages("c++20")
set_toolchains("msvc")

option("nana")
    set_default(false)
    set_showmenu(true)
    set_description("Build Nana Example")
option_end()

option("wx")
    set_default(false)
    set_showmenu(true)
    set_description("Build wxWidgets Example")
option_end()

add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")
add_requires("string_format")

target("MicroUI")
    set_kind("headeronly")
    add_headerfiles("include/(**.h)")
    add_includedirs("include", { public = true })
target_end()

local function example_target(name)
    target(name)
        set_kind("binary")
        add_files("Example.cpp")
        add_deps("MicroUI")
        add_packages("string_format")
        add_ldflags("/subsystem:windows")
        add_ldflags("/entry:WinMainCRTStartup", { force = true })
end

if get_config("nana") == true then
    add_requires("nana")
    example_target("nana_Example")
        add_packages("nana")
    target_end()
end

if get_config("wx") == true then
    local vcpkg_triplet = get_config("arch") .. "-windows-static"
    local vcpkg_root = os.getenv("VCPKG_ROOT")
    add_requires("vcpkg::wxwidgets", { system = false, configs = { triplet = vcpkg_triplet } })
    example_target("wx_Example")
        add_packages("vcpkg::wxwidgets")
        add_includedirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "include"))
        add_linkdirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "lib"))
        add_links("kernel32", "user32", "gdi32", "comdlg32", "winspool", "winmm", "shell32", "comctl32", "ole32", "oleaut32", "uuid", "rpcrt4", "advapi32", "wsock32", "wininet", "libpng16", "nanosvg", "nanosvgrast", "zlib")
    target_end()
end

