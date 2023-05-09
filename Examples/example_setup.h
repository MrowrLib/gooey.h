#ifdef GOOEY_USE_FLTK
    #include <gooey/fltk.h>
#else
    #error "GOOEY_USE_<library> not defined"
#endif

#include <filesystem>

namespace ExampleImagePaths {
    std::filesystem::path Folder{"../../../../Examples/Resources/Images"};
    std::filesystem::path Castle{Folder / "castle.png"};
    std::filesystem::path GrassBackground{Folder / "grass_background.png"};
    std::filesystem::path Knight{Folder / "knight.png"};
    std::filesystem::path Monster1{Folder / "monster1.png"};
    std::filesystem::path Monster2{Folder / "monster2.png"};
}
