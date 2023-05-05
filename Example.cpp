#include <Windows.h>
#include <gooey/FLTK.h>

// TODO
// 1. Fix Window name
// 2. [Panel] Align image to top left, top right, bottom left, bottom right, center, or stretch
// 3. [Button] and [Window] and [Label] background image alignment too
// 4. Can stack multiple images on top of each other (by name [*ordered* map] rather than push/pop)
// 5. GRID
// 6. Tabs
// 7. Menu Dropdowns
// 8. Status Bar
// 9. Popup Dialogs (need the folder chooser, for example!)

using namespace gooey;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    FLTKAdapter::Defaults::ButtonHeight = 50;

    /*
        TODO: AddBackgroundImage() RemoveBackgroundImage()
    */

    auto* app    = GetUIApplication();
    auto* window = app->AddWindow();
    window->SetTitle("OGRE");
    window->SetBackgroundColor(0, 0, 0);

    auto* board = window->AddGrid(8, 4);
    // board->AddButton("0,0 2,2", 0, 0, 2, 2);

    window->Show();
    app->Start();
    return 0;
}
