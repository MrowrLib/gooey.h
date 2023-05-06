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
    FLTKAdapter::Defaults::ButtonHeight   = 30;
    FLTKAdapter::Defaults::GridCellHeight = 25;
    FLTKAdapter::Defaults::GridCellWidth  = 25;
    FLTKAdapter::Defaults::GridPadding    = 5;
    FLTKAdapter::Defaults::WindowWidth    = 1800;
    FLTKAdapter::Defaults::WindowHeight   = 600;
    FLTKAdapter::Defaults::PanelWidth     = 100;

    auto* app    = GetUIApplication();
    auto* window = app->AddWindow();
    window->SetTitle("OGRE");
    window->SetBackgroundColor(0, 0, 0);

    auto* topLevelGrid = window->AddGrid(4, 8);

    // auto* columns = window->AddHorizontalPanel();
    // columns->SetBackgroundColor(255, 0, 255);

    // columns->AddButton("LEFT");

    // auto* column1 = columns->AddVerticalPanel();
    // column1->SetBackgroundColor(255, 0, 0);
    // column1->AddButton("LEFT");

    // auto* column2 = columns->AddVerticalPanel();
    // column2->SetBackgroundColor(0, 255, 0);
    // column2->AddButton("TOP");

    // auto* grid = column2->AddGrid(8, 8);

    // column2->AddButton("BOTTOM");

    // auto* column3 = columns->AddVerticalPanel();
    // column3->SetBackgroundColor(0, 0, 255);
    // column3->AddButton("RIGHT");

    // columns->AddButton("RIGHT");

    // auto* column4 = columns->AddVerticalPanel();
    // column4->SetBackgroundColor(255, 50, 255);
    // column4->AddButton("Again...");

    // auto* board2 = column4->AddGrid(3, 3);

    window->Show();
    app->Start();
    return 0;
}
