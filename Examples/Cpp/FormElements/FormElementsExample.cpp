#include "example_setup.h"

using namespace gooey;

int main() {
    UIApplication* app    = create_gooey_application();
    UIWindow*      window = app->add_window();
    window->set_title("Form Elements");
    window->show();

    // app->get_defaults()->

    auto* label1 = window->add_label("ONE");
    label1->set_background_color({255, 0, 0});
    auto* text_input1 = window->add_text_input();

    auto* label2      = window->add_label("TWO");
    auto* text_input2 = window->add_text_input();
    text_input2->set_background_color({0, 255, 0});

    auto* label3 = window->add_label("THREE");
    label3->set_background_color({0, 0, 255});
    auto* text_input3 = window->add_text_input();

    app->run_blocking();
    return 0;
}
