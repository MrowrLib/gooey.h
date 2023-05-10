#include "example_setup.h"

using namespace gooey;

int main() {
    UIApplication* app    = create_gooey_application();
    UIWindow*      window = app->add_window();
    window->set_title("Form Elements");
    window->show();

    auto* label1      = window->add_label("ONE");
    auto* text_input1 = window->add_text_input();

    auto* label2      = window->add_label("TWO");
    auto* text_input2 = window->add_text_input();

    auto* label3      = window->add_label("THREE");
    auto* text_input3 = window->add_text_input();

    return app->run_blocking();
}
