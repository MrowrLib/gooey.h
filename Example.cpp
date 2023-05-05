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
    // window->SetBackgroundColor(0, 0, 0);

    auto* panel = window->AddHorizontalPanel();
    panel->AddButton("Hello, panel");

    panel->AddBackgroundImage("Cleric.png", UIBackgroundImageStyle::Fill);

    // ALIGN IMAGE TO TOP LEFT, TOP RIGHT, BOTTOM LEFT, BOTTOM RIGHT, CENTER, or STRETCH

    // window->SetBackgroundImage("Logo.png");

    // window->AddLabel("ONE (label)")->SetBackgroundColor(255, 0, 255);
    // window->AddButton("TWO (button)")->SetBackgroundColor(0, 255, 255);

    // auto* panel1 = window->AddHorizontalPanel();
    // panel1->AddLabel("Label 1");
    // panel1->AddLabel("Label 2");
    // panel1->AddLabel("Label 3");

    // auto* panel2 = window->AddVerticalPanel();
    // panel2->AddButton("A");
    // panel2->AddButton("B");
    // panel2->AddButton("C");
    // panel2->SetBackgroundColor(123, 20, 222);

    // window->AddLabel("THREE (label)")->SetBackgroundColor(255, 255, 0);

    window->Show();
    app->Start();
    return 0;
}
