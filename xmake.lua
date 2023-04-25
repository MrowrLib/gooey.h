add_rules("mode.debug", "mode.release")

set_languages("c++20")
set_toolchains("msvc")

option("toolkit")
    set_default("nana")
    set_showmenu(true)
    set_values("nana", "wx")
    set_description("Select UI Toolkit (nana or wx)")
option_end()

if has_config("arch") then
    vcpkg_triplet = get_config("arch") .. "-windows-static"
    vcpkg_root = os.getenv("VCPKG_ROOT")
end

add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")
add_requires("string_format")

if get_config("toolkit") == "nana" then
    add_requires("nana")
end

if get_config("toolkit") == "wx" then
    add_requires("vcpkg::wxwidgets", { system = false, configs = { triplet = vcpkg_triplet } })
end

if get_config("toolkit") == "" then
    print("Must choose a toolkit with `xmake configure --toolkit=<nana|wx>`")
    return
elseif not get_config("toolkit") == nil then
    print(string.format("Selected UI toolkit: '%s'", get_config("toolkit")))
end

target("MicroUI")
    set_kind("headeronly")
    add_headerfiles("include/(**.h)")
    add_includedirs("include", { public = true })
target_end()

target("Example")
    set_kind("binary")
    add_files("Example.cpp")
    add_deps("MicroUI")
    add_packages("string_format")
    add_ldflags("/subsystem:windows")
    add_ldflags("/entry:WinMainCRTStartup", { force = true })

if get_config("toolkit") == "nana" then
    add_packages("nana")
end

if get_config("toolkit") == "wx" then
    add_packages("vcpkg::wxwidgets")
    add_includedirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "include"))
    add_linkdirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "lib"))
    add_links("kernel32", "user32", "gdi32", "comdlg32", "winspool", "winmm", "shell32", "comctl32", "ole32", "oleaut32", "uuid", "rpcrt4", "advapi32", "wsock32", "wininet", "libpng16", "nanosvg", "nanosvgrast", "zlib")
end

