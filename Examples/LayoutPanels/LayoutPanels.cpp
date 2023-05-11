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

    auto* mainVertical = horizontal->add_vertical_panel(true, false);
    mainVertical->set_background_color({0, 10, 200});

    auto* l33 = mainVertical->add_label("MIDDLE middle");
    l33->set_background_color({69, 255, 69});

    auto* l3 = mainVertical->add_label("MIDDLE top");
    l3->set_background_color({69, 0, 69});

    // auto* middleHorizontal = mainVertical->add_horizontal_panel(true, false);
    // middleHorizontal->set_background_color({255, 69, 0});

    // auto* l4 = middleHorizontal->add_label("MIDDLE L");
    // l4->set_background_color({69, 0, 100});

    // auto* middleVertical = middleHorizontal->add_vertical_panel(false, false);

    // auto* l7 = middleVertical->add_label("MIDDLE top 2");
    // l7->set_background_color({255, 69, 2});

    // auto* l8 = middleVertical->add_label("MIDDLE bottom 2");
    // l8->set_background_color({255, 69, 100});

    // auto* l6 = middleHorizontal->add_label("MIDDLE R");
    // l6->set_background_color({69, 255, 69});

    // auto* anotherPanel = mainVertical->add_horizontal_panel(false, false);

    // auto* l9 = anotherPanel->add_label("MIDDLE top 3");
    // l9->set_background_color({15, 69, 200});

    // auto* l10 = anotherPanel->add_label("MIDDLE bottom 3");
    // l10->set_background_color({155, 155, 100});

    // auto* l5 = mainVertical->add_label("MIDDLE bottom");
    auto* l5 = mainVertical->add_horizontal_panel(true, false);
    l5->set_background_color({255, 69, 100});

    auto* l6 = l5->add_label("<left>");
    l6->set_background_color({0, 100, 189});

    auto* l7 = l5->add_label("<right>");
    l7->set_background_color({189, 20, 189});

    auto* middleBottom = mainVertical->add_label("MIDDLE bottom");
    middleBottom->set_background_color({76, 69, 1});

    // auto* l2 = horizontal->add_label("RIGHT");
    // l2->set_background_color({200, 176, 20});
    auto* l2 = horizontal->add_vertical_panel(true, false);
    l2->set_background_color({200, 176, 20});

    auto* l22 = l2->add_label("up");
    l22->set_background_color({50, 116, 20});

    auto* l23 = l2->add_label("down");
    l23->set_background_color({200, 100, 200});

    auto* rightBox = window->add_label("BOTTOM");
    rightBox->set_background_color({0, 255, 255});

    // Then absolute

    // And images in all of them

    app->run_blocking();
    return 0;
}
