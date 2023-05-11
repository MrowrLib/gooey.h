#include "example_setup.h"

using namespace gooey;

int main() {
    UIApplication* app    = create_gooey_application();
    UIWindow*      window = app->add_window();
    window->set_title("Form Elements");
    window->show();
    // window->set_background_color({0, 0, 0});
    window->add_background_image(ExampleImagePaths::Monster1.string().c_str());

    auto* label1 = window->add_label("Label 1");
    // label1->set_background_color({255, 0, 0});

    auto* textInput1 = window->add_text_input();
    textInput1->set_background_color({0, 0, 255});

    auto* label2 = window->add_label("Label 2");
    // label2->set_background_color({0, 255, 0});

    // auto* mainVertical = window->add_horizontal_panel(false);
    // mainVertical->set_background_color({255, 150, 50});

    // auto* leftBox = mainVertical->add_label("LEFT");
    // leftBox->set_background_color({255, 0, 255});

    // auto middleGroup = mainVertical->add_vertical_panel(false);
    // middleGroup->set_background_color({0, 255, 200});

    // auto* l1 = middleGroup->add_label("MIDDLE 1");
    // l1->set_background_color({100, 255, 0});

    // auto* middleHorizontal = middleGroup->add_horizontal_panel(false);
    // middleHorizontal->set_background_color({255, 255, 0});

    // auto* l3 = middleHorizontal->add_label("MIDDLE L");
    // l3->set_background_color({255, 0, 100});

    // auto* l4 = middleHorizontal->add_label("MIDDLE R");
    // l4->set_background_color({255, 0, 100});

    // auto* l2 = middleGroup->add_label("MIDDLE 2");
    // l2->set_background_color({10, 255, 50});

    // auto* rightBox = mainVertical->add_label("RIGHT");
    // rightBox->set_background_color({0, 255, 255});

    // auto* horizontal_panel = mainVertical->add_horizontal_panel(false);
    // horizontal_panel->set_background_color({0, 0, 0});
    // auto* label1 = horizontal_panel->add_label("H ONE");
    // label1->set_background_color({255, 0, 0});
    // auto* label2 = horizontal_panel->add_label("H TWO");
    // label2->set_background_color({0, 255, 0});

    // auto* vertical_panel = mainVertical->add_vertical_panel(false);
    // vertical_panel->set_background_color({255, 255, 255});
    // auto* label11 = vertical_panel->add_label("V ONE");
    // label11->set_background_color({255, 0, 0});
    // auto* label22 = vertical_panel->add_label("V TWO");
    // label22->set_background_color({0, 255, 0});

    // Then absolute

    // And images in all of them

    app->run_blocking();
    return 0;
}
