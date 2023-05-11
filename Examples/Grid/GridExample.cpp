#include "example_setup.h"

using namespace gooey;

int main() {
    UIApplication* app    = create_gooey_application();
    UIWindow*      window = app->add_window();
    window->set_title("Button Grid");
    window->show();

    // Create a cell grid
    auto* grid = window->add_grid(8, 4);

    app->run_blocking();
    return 0;
}
