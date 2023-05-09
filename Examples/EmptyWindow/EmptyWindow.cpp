#include "gooey_loader.h"

using namespace gooey;

int main() {
    UIApplication* app = create_gooey_application();

    app->add_window()
        ->set_title("Empty Window")
        ->set_size(640, 480)
        ->set_position(100, 100)
        ->show()
        ->apply();

    app->run_blocking();

    return 0;
}
