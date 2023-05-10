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

// #include <Windows.h>

// #include "icon.h"

// void SetProgramIcon(HINSTANCE hInstance, HWND hwndMain) {
//     // Load the icon from the resource file
//     // HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
//     // HICON hicon = (HICON)LoadImage(NULL, icon_path, IMAGE_ICON, 0, 0, LR_LOADFROMFILE |
//     // LR_DEFAULTSIZE | LR_SHARED);

//     // Set the icon for the main window
//     SendMessage(hwndMain, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
//     SendMessage(hwndMain, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
// }

// void set_window_icon(Fl_Window* window, const char* icon_path) {
//     // Get the window handle
//     HWND hwnd = fl_xid(window);

//     // Load the icon from the file
//     HICON hicon = (HICON)LoadImage(NULL, icon_path, IMAGE_ICON, 0, 0, LR_LOADFROMFILE |
//     LR_DEFAULTSIZE | LR_SHARED);

//     if (hicon) {
//         // Set the window icon
//         SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hicon);
//         SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hicon);
//     }
// }