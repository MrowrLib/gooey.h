#include "example_setup.h"

using namespace gooey;

int main() {
    UIApplication* app    = create_gooey_application();
    UIWindow*      window = app->add_window();
    window->set_title("Empty Window");
    window->set_size(640, 480);
    window->set_position(100, 100);
    window->show();
    //

    // Use alignments and anchoring and shit...

    // But I think #1 is: make the vertical space assignment = the size of the element,
    // proportionally

    auto* element1 = window->add_label("Hello, world");
    // element1->set_size() <--- TODO

    auto* element2 = window->add_label("Goodnight, moon");

    //
    app->run_blocking();
    return 0;
}
