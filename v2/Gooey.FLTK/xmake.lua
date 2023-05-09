add_requires("fltk")

target("Gooey.FLTK")
    set_kind("headeronly")
    add_headerfiles("include/(**.h)")
    add_includedirs("include", { public = true })
    add_deps("Gooey")
    add_packages("fltk", { public = true })
