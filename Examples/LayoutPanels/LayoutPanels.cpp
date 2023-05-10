#include "example_setup.h"

using namespace gooey;

int main() {
    UIApplication* app    = create_gooey_application();
    UIWindow*      window = app->add_window();
    window->set_title("Form Elements");
    window->show();
    window->set_background_color({100, 200, 255});

    auto* mainVertical = window->add_horizontal_panel(false);
    mainVertical->set_background_color({255, 150, 50});

    auto* leftBox = mainVertical->add_label("LEFT");
    leftBox->set_background_color({255, 0, 255});

    auto middleGroup = mainVertical->add_vertical_panel(false);
    middleGroup->set_background_color({0, 255, 200});

    auto* l1 = middleGroup->add_label("MIDDLE 1");
    l1->set_background_color({100, 255, 0});

    auto* l2 = middleGroup->add_label("MIDDLE 2");
    l2->set_background_color({10, 255, 50});

    auto* rightBox = mainVertical->add_label("RIGHT");
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

    return app->run_blocking();
}

// #include <FL/Fl.H>
// #include <FL/Fl_Box.H>
// #include <FL/Fl_Group.H>
// #include <FL/Fl_Input.H>
// #include <FL/Fl_Pack.H>
// #include <FL/Fl_Window.H>

// #include <cmath>
// #include <vector>

// class AspectRatioGroup : public Fl_Group {
//     double aspect_ratio;

// public:
//     AspectRatioGroup(int X, int Y, int W, int H, const char* L = 0)
//         : Fl_Group(X, Y, W, H, L), aspect_ratio(static_cast<double>(W) / H) {}

//     void resize(int X, int Y, int W, int H) override {
//         double new_aspect_ratio = static_cast<double>(W) / H;
//         if (abs(new_aspect_ratio - aspect_ratio) > 0.01) {
//             if (H * aspect_ratio <= W) {
//                 Fl_Group::resize(X, Y, static_cast<int>(H * aspect_ratio), H);
//             } else {
//                 Fl_Group::resize(X, Y, W, static_cast<int>(W / aspect_ratio));
//             }
//         } else {
//             Fl_Group::resize(X, Y, W, H);
//         }
//     }
// };

// class ProportionalGroup : public Fl_Group {
//     std::vector<double> proportions;

// public:
//     ProportionalGroup(
//         int X, int Y, int W, int H, const std::vector<double>& proportions, const char* L = 0
//     )
//         : Fl_Group(X, Y, W, H, L), proportions(proportions) {}

//     void resize(int X, int Y, int W, int H) override {
//         Fl_Group::resize(X, Y, W, H);
//         int num_children = children();

//         int cur_x = X;
//         int cur_y = Y;
//         for (int i = 0; i < num_children; ++i) {
//             Fl_Widget* child_widget = this->child(i);
//             int        child_width  = static_cast<int>(W * proportions[i]);

//             child_widget->resize(cur_x, cur_y, child_width, H);

//             cur_x += child_width;
//         }
//     }
// };

// class AutoProportionalGroup : public Fl_Group {
//     bool manage_width;
//     bool manage_height;

// public:
//     AutoProportionalGroup(
//         int X, int Y, int W, int H, bool manage_width = true, bool manage_height = false,
//         const char* L = 0
//     )
//         : Fl_Group(X, Y, W, H, L), manage_width(manage_width), manage_height(manage_height) {}

//     void resize(int X, int Y, int W, int H) override {
//         Fl_Group::resize(X, Y, W, H);
//         int num_children = children();

//         int total_width  = 0;
//         int total_height = 0;
//         for (int i = 0; i < num_children; ++i) {
//             Fl_Widget* child_widget = child(i);
//             total_width += child_widget->w();
//             total_height += child_widget->h();
//         }

//         int cur_x = X;
//         int cur_y = Y;
//         for (int i = 0; i < num_children; ++i) {
//             Fl_Widget* child_widget = child(i);
//             int        child_width  = child_widget->w();
//             int        child_height = child_widget->h();

//             if (manage_width) {
//                 child_width =
//                     static_cast<int>(W * (static_cast<double>(child_widget->w()) / total_width));
//             }

//             if (manage_height) {
//                 child_height =
//                     static_cast<int>(H * (static_cast<double>(child_widget->h()) /
//                     total_height));
//             }

//             child_widget->resize(cur_x, cur_y, child_width, child_height);

//             if (manage_width) {
//                 cur_x += child_width;
//             }
//             if (manage_height) {
//                 cur_y += child_height;
//             }
//         }
//     }
// };

// int main(int argc, char** argv) {
//     Fl_Window* window = new Fl_Window(800, 600, "FLTK AutoProportionalGroup Example");
//     window->color(FL_GRAY);

//     Fl_Pack* v_pack = new Fl_Pack(0, 0, window->w(), window->h());
//     v_pack->type(Fl_Pack::VERTICAL);

//     // First row
//     AutoProportionalGroup* row1 = new AutoProportionalGroup(0, 0, v_pack->w(), 200, true, false);

//     Fl_Box* blue_box = new Fl_Box(0, 0, 100, row1->h(), "");
//     blue_box->box(FL_FLAT_BOX);
//     blue_box->color(FL_BLUE);
//     row1->add(blue_box);

//     AutoProportionalGroup* nested_v_group =
//         new AutoProportionalGroup(0, 0, 200, row1->h(), false, true);
//     Fl_Box* red_box = new Fl_Box(0, 0, nested_v_group->w(), 50, "");
//     red_box->box(FL_FLAT_BOX);
//     red_box->color(FL_RED);
//     nested_v_group->add(red_box);

//     Fl_Box* green_box = new Fl_Box(0, 0, nested_v_group->w(), 150, "");
//     green_box->box(FL_FLAT_BOX);
//     green_box->color(FL_GREEN);
//     nested_v_group->add(green_box);

//     row1->add(nested_v_group);

//     Fl_Box* magenta_box = new Fl_Box(0, 0, 100, row1->h(), "");
//     magenta_box->box(FL_FLAT_BOX);
//     magenta_box->color(FL_MAGENTA);
//     row1->add(magenta_box);

//     // Add row1 to vertical layout
//     v_pack->add(row1);
//     // v_pack->resizable(row1);

//     v_pack->end();
//     window->resizable(v_pack);
//     window->end();
//     window->show(argc, argv);

//     return Fl::run();
// }