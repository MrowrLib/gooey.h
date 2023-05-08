#include <Windows.h>
#include <gooey/Qt.h>

using namespace gooey;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    auto* app    = GetUIApplication();
    auto* window = app->AddWindow();
    window->SetTitle("OGRE");

    window->Show();
    app->Start();
    return 0;
}
