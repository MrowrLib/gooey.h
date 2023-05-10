#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Window.H>

#include <cmath>

// #include "example_setup.h"

// using namespace gooey;

// int main() {
//     UIApplication* app    = create_gooey_application();
//     UIWindow*      window = app->add_window();
//     window->set_title("Form Elements");
//     window->show();
//     window->set_background_color({0, 0, 0});

//     auto* label1 = window->add_label("Label 1");
//     label1->set_background_color({255, 0, 0});

//     auto* label2 = window->add_label("Label 2");
//     label2->set_background_color({0, 255, 0});

//     // auto* mainVertical = window->add_horizontal_panel(false);
//     // mainVertical->set_background_color({255, 150, 50});

//     // auto* leftBox = mainVertical->add_label("LEFT");
//     // leftBox->set_background_color({255, 0, 255});

//     // auto middleGroup = mainVertical->add_vertical_panel(false);
//     // middleGroup->set_background_color({0, 255, 200});

//     // auto* l1 = middleGroup->add_label("MIDDLE 1");
//     // l1->set_background_color({100, 255, 0});

//     // auto* middleHorizontal = middleGroup->add_horizontal_panel(false);
//     // middleHorizontal->set_background_color({255, 255, 0});

//     // auto* l3 = middleHorizontal->add_label("MIDDLE L");
//     // l3->set_background_color({255, 0, 100});

//     // auto* l4 = middleHorizontal->add_label("MIDDLE R");
//     // l4->set_background_color({255, 0, 100});

//     // auto* l2 = middleGroup->add_label("MIDDLE 2");
//     // l2->set_background_color({10, 255, 50});

//     // auto* rightBox = mainVertical->add_label("RIGHT");
//     // rightBox->set_background_color({0, 255, 255});

//     // auto* horizontal_panel = mainVertical->add_horizontal_panel(false);
//     // horizontal_panel->set_background_color({0, 0, 0});
//     // auto* label1 = horizontal_panel->add_label("H ONE");
//     // label1->set_background_color({255, 0, 0});
//     // auto* label2 = horizontal_panel->add_label("H TWO");
//     // label2->set_background_color({0, 255, 0});

//     // auto* vertical_panel = mainVertical->add_vertical_panel(false);
//     // vertical_panel->set_background_color({255, 255, 255});
//     // auto* label11 = vertical_panel->add_label("V ONE");
//     // label11->set_background_color({255, 0, 0});
//     // auto* label22 = vertical_panel->add_label("V TWO");
//     // label22->set_background_color({0, 255, 0});

//     // Then absolute

//     // And images in all of them

//     return app->run_blocking();
// }

// #include <cmath>
// #include <vector>

class AspectRatioGroup : public Fl_Group {
    double aspect_ratio;

public:
    AspectRatioGroup(int X, int Y, int W, int H, const char* L = 0)
        : Fl_Group(X, Y, W, H, L), aspect_ratio(static_cast<double>(W) / H) {}

    void resize(int X, int Y, int W, int H) override {
        Fl::lock();
        double new_aspect_ratio = static_cast<double>(W) / H;
        if (abs(new_aspect_ratio - aspect_ratio) > 0.01) {
            if (H * aspect_ratio <= W) {
                Fl_Group::resize(X, Y, static_cast<int>(H * aspect_ratio), H);
            } else {
                Fl_Group::resize(X, Y, W, static_cast<int>(W / aspect_ratio));
            }
        } else {
            Fl_Group::resize(X, Y, W, H);
        }
        Fl::unlock();
        Fl::awake();
    }
};

class AutoProportionalGroup : public Fl_Group {
    bool manage_width;
    bool manage_height;

public:
    AutoProportionalGroup(
        int X, int Y, int W, int H, bool manage_width = true, bool manage_height = false,
        const char* L = 0
    )
        : Fl_Group(X, Y, W, H, L), manage_width(manage_width), manage_height(manage_height) {}

    void resize(int X, int Y, int W, int H) override {
        Fl::lock();
        Fl_Group::resize(X, Y, W, H);
        int num_children = children();

        int total_width  = 0;
        int total_height = 0;
        for (int i = 0; i < num_children; ++i) {
            Fl_Widget* child_widget = child(i);
            total_width += child_widget->w();
            total_height += child_widget->h();
        }

        int cur_x = X;
        int cur_y = Y;
        for (int i = 0; i < num_children; ++i) {
            Fl_Widget* child_widget = child(i);
            int        child_width  = child_widget->w();
            int        child_height = child_widget->h();

            if (manage_width) {
                child_width =
                    static_cast<int>(W * (static_cast<double>(child_widget->w()) / total_width));
            }

            if (manage_height) {
                child_height =
                    static_cast<int>(H * (static_cast<double>(child_widget->h()) / total_height));
            }

            if (manage_width && manage_height) {
                child_widget->resize(X, cur_y, parent()->w(), child_height);
            } else {
                child_widget->resize(cur_x, cur_y, child_width, child_height);
            }

            if (manage_width && !manage_height) {
                cur_x += child_width;
            }
            if (manage_height) {
                cur_y += child_height;
            }
        }
        Fl::unlock();
        Fl::awake();
    }
};

//

class CustomWindow : public Fl_Window {
public:
    CustomWindow(int width, int height, const char* title = 0) : Fl_Window(width, height, title) {
        resizable(this);

        aspect_ratio_group = new AspectRatioGroup(0, 0, w(), h());
        full_size_group    = new AutoProportionalGroup(
            0, 0, aspect_ratio_group->w(), aspect_ratio_group->h(), true, true
        );

        aspect_ratio_group->add(full_size_group);
        aspect_ratio_group->end();

        resizable(aspect_ratio_group);
        end();
    }

    void add(Fl_Widget* widget) { full_size_group->add(widget); }

    void show() override {
        Fl_Window::show();
        aspect_ratio_group->resize(0, 0, w(), h());
    }

private:
    AspectRatioGroup*      aspect_ratio_group;
    AutoProportionalGroup* full_size_group;
};

int main(int argc, char** argv) {
    CustomWindow window(800, 600, "Custom Window with AutoProportionalGroup");

    Fl_Box* red_box = new Fl_Box(0, 0, 200, 200, "ONE");
    red_box->box(FL_FLAT_BOX);
    red_box->color(FL_RED);
    window.add(red_box);

    // Fl_Box* green_box = new Fl_Box(0, 0, 200, 200, "TWO");
    // green_box->box(FL_FLAT_BOX);
    // green_box->color(FL_GREEN);
    // window.add(green_box);
    auto* greenGroup = new AutoProportionalGroup(0, 0, 200, 200, false, true);

    Fl_Box* green_box = new Fl_Box(0, 0, 200, 100, "TWO");
    green_box->box(FL_FLAT_BOX);
    green_box->color(fl_rgb_color(255, 100, 50));
    greenGroup->add(green_box);

    // Fl_Box* green_box2 = new Fl_Box(0, 0, 200, 100, "TWO");
    // green_box2->box(FL_FLAT_BOX);
    // green_box2->color(fl_rgb_color(50, 255, 90));
    // greenGroup->add(green_box2);
    auto* subGroup = new AutoProportionalGroup(0, 0, 200, 100, true, false);
    subGroup->add(new Fl_Box(0, 0, 100, 100, "A"));

    auto* subSubGroup = new AutoProportionalGroup(0, 0, 100, 100, false, true);
    subSubGroup->add(new Fl_Box(0, 0, 100, 50, "x"));
    subSubGroup->add(new Fl_Box(0, 0, 100, 50, "y"));
    auto* subSubSubGroup = new AutoProportionalGroup(0, 0, 100, 50, true, false);
    subSubSubGroup->add(new Fl_Box(0, 0, 50, 50, "z"));
    subSubSubGroup->add(new Fl_Box(0, 0, 50, 50, "w"));
    auto* subSubSubSubGroup = new AutoProportionalGroup(0, 0, 50, 50, false, true);
    subSubSubSubGroup->add(new Fl_Box(0, 0, 50, 50, "1"));
    subSubSubSubGroup->add(new Fl_Box(0, 0, 50, 50, "2"));
    subSubSubGroup->add(subSubSubSubGroup);
    subSubGroup->add(subSubSubGroup);
    subGroup->add(subSubGroup);

    subGroup->add(new Fl_Box(0, 0, 100, 100, "B"));

    greenGroup->add(subGroup);

    window.add(greenGroup);

    Fl_Box* blue_box = new Fl_Box(0, 0, 200, 200, "THREE");
    blue_box->box(FL_FLAT_BOX);
    blue_box->color(FL_BLUE);
    window.add(blue_box);

    window.show();
    return Fl::run();
}
