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
    // auto* x       = window->add_label("x");
    leftBox->set_background_color({255, 0, 255});

    auto* horizontal = window->add_horizontal_panel();
    horizontal->set_background_color({255, 150, 50});

    auto* l1 = horizontal->add_label("LEFT");
    l1->set_background_color({255, 0, 0});

    auto* mainVertical = horizontal->add_vertical_panel();
    mainVertical->set_background_color({0, 10, 200});

    auto* l33 = mainVertical->add_label("MIDDLE middle");
    l33->set_background_color({69, 255, 69});

    auto* l3 = mainVertical->add_label("MIDDLE top");
    l3->set_background_color({69, 0, 69});

    auto* l5 = mainVertical->add_horizontal_panel();
    l5->set_background_color({255, 69, 100});

    auto* l6 = l5->add_label("<left>");
    l6->set_background_color({0, 100, 189});

    auto* l7 = l5->add_label("<right>");
    l7->set_background_color({189, 20, 189});

    auto* middleBottom = mainVertical->add_label("MIDDLE bottom");
    middleBottom->set_background_color({76, 69, 1});

    auto* l2 = horizontal->add_vertical_panel();
    l2->set_background_color({200, 176, 20});

    auto* l22 = l2->add_label("up");
    l22->set_background_color({50, 116, 20});

    auto* l23 = l2->add_label("down");
    l23->set_background_color({200, 100, 200});

    auto* rightBox = window->add_label("BOTTOM");
    rightBox->set_background_color({0, 255, 255});

    // Then absolute!

    auto* absolutePanel = window->add_vertical_panel(true);
    absolutePanel->set_background_color({30, 30, 30});

    absolutePanel->add_label("<top spacer>");
    auto* absoluteHorizontal = absolutePanel->add_horizontal_panel();
    absoluteHorizontal->add_label("<left spacer>");

    // CONTENT HERE
    auto* absoluteLabel = absoluteHorizontal->add_label("Absolute");
    // auto* absoluteLabel = absolutePanel->add_label("Absolute");
    absoluteLabel->set_background_color({255, 0, 200});

    absoluteHorizontal->add_label("<left Right>");
    absolutePanel->add_label("<bottom spacer>");

    // absolutePanel->set_visible(false);

    // Then hide/show toggle visibility

    // And images in all of them

    app->run_blocking();
    return 0;
}
