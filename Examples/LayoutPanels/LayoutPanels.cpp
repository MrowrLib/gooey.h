#include "example_setup.h"

using namespace gooey;

int main() {
    UIApplication* app    = create_gooey_application();
    UIWindow*      window = app->add_window();
    window->set_title("Layout Panels");
    window->show();
    // window->set_background_color({0, 0, 0});
    window->add_background_image(ExampleImagePaths::Monster1.string().c_str());

    auto* leftBox = window->add_label("TOP");
    leftBox->set_background_color({255, 0, 255});

    auto* horizontal = window->add_horizontal_panel(true, false);
    horizontal->set_background_color({255, 150, 50});

    auto* l1 = horizontal->add_label("LEFT");
    l1->set_background_color({255, 0, 0});

    auto* mainVertical = horizontal->add_vertical_panel(false, false);
    mainVertical->set_background_color({0, 255, 255});

    auto* l3 = mainVertical->add_label("MIDDLE 1");
    l3->set_background_color({255, 0, 100});

    auto* l4 = mainVertical->add_label("MIDDLE 2");
    l4->set_background_color({255, 0, 100});

    auto* l2 = horizontal->add_label("RIGHT");
    l2->set_background_color({0, 255, 0});

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

    auto* rightBox = window->add_label("BOTTOM");
    rightBox->set_background_color({0, 255, 255});

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
