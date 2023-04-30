local function require_wx()
    local vcpkg_root = os.getenv("VCPKG_ROOT")
    if vcpkg_root and has_config("arch") then
        local vcpkg_triplet = get_config("arch") .. "-windows-static"
        add_requires("vcpkg::wxwidgets", { system = false, configs = { triplet = vcpkg_triplet } })
    end
end

require_wx()

function add_wx()
    local vcpkg_root = os.getenv("VCPKG_ROOT")
    if vcpkg_root and has_config("arch") then
        local vcpkg_triplet = get_config("arch") .. "-windows-static"
        add_packages("vcpkg::wxwidgets", { public = true })
        add_includedirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "include"))
        add_linkdirs(path.join(vcpkg_root, "installed", vcpkg_triplet, "lib"))
        add_links("kernel32", "user32", "gdi32", "comdlg32", "winspool", "winmm", "shell32", "comctl32", "ole32", "oleaut32", "uuid", "rpcrt4", "advapi32", "wsock32", "wininet", "libpng16", "nanosvg", "nanosvgrast", "zlib")
    end
end

target("Gooey.wxWidgets")
    set_kind("headeronly") -- TODO: provide a static library as well
    add_headerfiles("include/(**.h)")
    add_includedirs("include", { public = true })
    add_deps("Gooey")
    add_wx()
