#include "example_setup.h"

using namespace gooey;

int main() {
    UIApplication* app    = create_gooey_application();
    UIWindow*      window = app->add_window();
    window->set_title("Button Grid");
    window->show();

    window->add_label("Button 1");

    auto* row2   = window->add_horizontal_panel();
    auto* label1 = row2->add_label("x");
    auto* grid   = row2->add_grid(8, 4);
    auto* label2 = row2->add_label("y");

    window->add_label("Button 3");

    app->run_blocking();
    return 0;
}
