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

// #include "example_setup.h"

// using namespace gooey;

// int main() {
//     UIApplication* app    = create_gooey_application();
//     UIWindow*      window = app->add_window();
//     window->set_title("Background Images");
//     window->show();
//     return app->run_blocking();
// }

// #include <FL/Fl.H>
// #include <FL/Fl_Box.H>
// #include <FL/Fl_Check_Button.H>
// #include <FL/Fl_Input.H>
// #include <FL/Fl_Menu_Bar.H>
// #include <FL/Fl_Menu_Item.H>
// #include <FL/Fl_Multiline_Input.H>
// #include <FL/Fl_PNG_Image.H>
// #include <FL/Fl_Round_Button.H>
// #include <FL/Fl_Window.H>
// #include <FL/fl_ask.H>

// void about_cb(Fl_Widget* w, void* data) {
//     fl_message("About: This is a minimal FLTK application.");
// }

// int main(int argc, char** argv) {
//     Fl::scheme("none");
//     // Fl::scheme("plastic");
//     // Fl::scheme("gtk+");
//     // Fl::scheme("gleam");
//     // Fl::scheme("oxy");

//     Fl_Window* window = new Fl_Window(400, 400, "FLTK Application");

//     Fl_Menu_Item menu_items[] = {
//         {"&File", 0, 0, 0, FL_SUBMENU},
//         {"&About", 0, about_cb, 0},
//         {0},
//         {0}
//     };

//     Fl_Menu_Bar* menu_bar = new Fl_Menu_Bar(0, 0, 400, 20);
//     menu_bar->menu(menu_items);

//     Fl_Box* label = new Fl_Box(20, 30, 100, 20, "Label:");
//     label->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);

//     Fl_Input* single_line_input = new Fl_Input(120, 50, 200, 20);

//     Fl_Round_Button* radio_button = new Fl_Round_Button(20, 80, 100, 20, "Radio button");

//     Fl_Check_Button* check_button = new Fl_Check_Button(20, 100, 100, 20, "Check button");

//     Fl_Choice* dropdown_chooser = new Fl_Choice(120, 200, 200, 20, "Chooser:");
//     dropdown_chooser->add("Option 1");
//     dropdown_chooser->add("Option 2");
//     dropdown_chooser->add("Option 3");
//     dropdown_chooser->value(0);

//     Fl_Multiline_Input* multiline_input = new Fl_Multiline_Input(20, 140, 200, 80);

//     // Fl_PNG_Image* image     = new
//     // Fl_PNG_Image("../../../../Examples/Resources/Images/castle.png"); Fl_Box*       image_box
//     =
//     // new Fl_Box(240, 50, image->w(), image->h()); image_box->image(image);

//     window->end();
//     window->show(argc, argv);

//     return Fl::run();
// }

// #include <FL/Fl.H>
// #include <FL/Fl_Box.H>
// #include <FL/Fl_Button.H>
// #include <FL/Fl_Check_Button.H>
// #include <FL/Fl_Choice.H>
// #include <FL/Fl_Group.H>
// #include <FL/Fl_Input.H>
// #include <FL/Fl_Menu_Bar.H>
// #include <FL/Fl_Menu_Item.H>
// #include <FL/Fl_PNG_Image.H>
// #include <FL/Fl_Pack.H>
// #include <FL/Fl_Round_Button.H>
// #include <FL/Fl_Window.H>

// class Icon_Menu_Item : public Fl_Menu_Item {
// public:
//     Icon_Menu_Item(
//         const char* label, int shortcut, Fl_Callback* callback, Fl_Image* icon = nullptr,
//         int flags = 0
//     )
//         : Fl_Menu_Item{label, shortcut, callback, nullptr, flags}, icon_(icon) {}

//     void draw(int x, int y, int w, int h, const Fl_Menu_* menu, int selected = 0) const {
//         if (icon_) {
//             icon_->draw(x + 5, y + (h - icon_->h()) / 2);
//             Fl_Menu_Item::draw(x + icon_->w() + 10, y, w - icon_->w() - 10, h, menu, selected);
//         } else {
//             Fl_Menu_Item::draw(x, y, w, h, menu, selected);
//         }
//     }

// private:
//     Fl_Image* icon_;
// };

// void click_me_cb(Fl_Widget* w, void* data) {
//     Fl_Box* status_bar = static_cast<Fl_Box*>(data);
//     status_bar->label("You clicked me");
//     status_bar->redraw();
// }

// int main(int argc, char** argv) {
//     fl_register_images();

//     Fl_Window*   window   = new Fl_Window(400, 300, "FLTK Application");
//     Fl_Menu_Bar* menu_bar = new Fl_Menu_Bar(0, 0, window->w(), 20);

//     Fl_PNG_Image icon1("../../../../Examples/Resources/Images/castle.png");
//     Fl_PNG_Image icon2("../../../../Examples/Resources/Images/knight.png");

//     Icon_Menu_Item menu_items[] = {
//         Icon_Menu_Item("&File", 0, 0, &icon1, FL_SUBMENU),
//         Icon_Menu_Item("&New", 0, 0, &icon2),
//         Icon_Menu_Item("&Open", 0, 0, nullptr),
//         Icon_Menu_Item("&Save", 0, 0, nullptr),
//         Icon_Menu_Item("&Quit", FL_COMMAND + 'q', 0, nullptr),
//         Icon_Menu_Item("&Edit", 0, 0, nullptr, FL_SUBMENU),
//         Icon_Menu_Item("&Cut", FL_COMMAND + 'x', 0, nullptr),
//         Icon_Menu_Item("&Copy", FL_COMMAND + 'c', 0, nullptr),
//         Icon_Menu_Item("&Paste", FL_COMMAND + 'v', 0, nullptr)};

//     menu_bar->menu(menu_items);

//     Fl_Box* status_bar = new Fl_Box(0, window->h() - 20, window->w(), 20, "This is the status
//     bar"); status_bar->box(FL_FLAT_BOX); status_bar->color(FL_GRAY);

//     Fl_Pack* v_pack = new Fl_Pack(20, 30, 360, 200);
//     v_pack->spacing(10);
//     v_pack->type(Fl_Pack::VERTICAL);

//     Fl_Box*   input_label = new Fl_Box(0, 0, 100, 20, "Name:");
//     Fl_Input* input_field = new Fl_Input(0, 0, 100, 20);

//     Fl_Button*       submit_button    = new Fl_Button(0, 0, 100, 20, "Submit");
//     Fl_Round_Button* radio_button     = new Fl_Round_Button(0, 0, 100, 20, "Radio button");
//     Fl_Check_Button* check_button     = new Fl_Check_Button(0, 0, 100, 20, "Check button");
//     Fl_Choice*       dropdown_chooser = new Fl_Choice(120, 200, 200, 20);
//     dropdown_chooser->add("Choose an option");
//     dropdown_chooser->add("Option 2");
//     dropdown_chooser->add("Option 3");
//     dropdown_chooser->value(0);

//     Fl_Group* red_group = new Fl_Group(0, 0, 360, 40);
//     // red_group->color(FL_RED);
//     red_group->box(FL_FLAT_BOX);

//     Fl_Pack* h_pack = new Fl_Pack(0, 0, 360, 40);
//     h_pack->spacing(10);
//     h_pack->type(Fl_Pack::HORIZONTAL);

//     Fl_Button* button_a = new Fl_Button(0, 0, 50, 20, "A");
//     Fl_Button* button_b = new Fl_Button(0, 0, 50, 20, "B");
//     Fl_Button* button_c = new Fl_Button(0, 0, 50, 20, "C");

//     h_pack->end();
//     red_group->end();

//     v_pack->end();

//     window->end();
//     window->resizable(window);
//     window->show(argc, argv);

//     return Fl::run();
// }

// #include <FL/Fl.H>
// #include <FL/Fl_Box.H>
// #include <FL/Fl_Group.H>
// #include <FL/Fl_Pack.H>
// #include <FL/Fl_Window.H>

// int main(int argc, char** argv) {
//     Fl_Window* window = new Fl_Window(400, 300, "FLTK Application");
//     window->color(FL_GREEN);

//     Fl_Pack* v_pack = new Fl_Pack(0, 0, window->w(), window->h());
//     v_pack->type(Fl_Pack::VERTICAL);

//     Fl_Box* row_a = new Fl_Box(0, 0, v_pack->w(), 20, "A");
//     row_a->box(FL_FLAT_BOX);
//     row_a->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
//     row_a->color(FL_YELLOW);

//     Fl_Group* row_b_and_c = new Fl_Group(0, 0, v_pack->w(), v_pack->h() - 40);
//     {
//         Fl_Pack* h_pack = new Fl_Pack(0, 0, row_b_and_c->w(), row_b_and_c->h());
//         h_pack->type(Fl_Pack::HORIZONTAL);

//         Fl_Box* row_b =
//             new Fl_Box(0, 0, static_cast<int>(row_b_and_c->w() * 0.6666), row_b_and_c->h(), "B");
//         row_b->box(FL_FLAT_BOX);
//         row_b->color(FL_BLUE);

//         Fl_Box* row_c =
//             new Fl_Box(0, 0, static_cast<int>(row_b_and_c->w() * 0.3333), row_b_and_c->h(), "C");
//         row_c->box(FL_FLAT_BOX);
//         row_c->color(FL_RED);

//         h_pack->resizable(row_b_and_c);
//         h_pack->end();
//     }
//     row_b_and_c->resizable(row_b_and_c);
//     row_b_and_c->end();

//     Fl_Box* row_d = new Fl_Box(0, 0, v_pack->w(), 20, "D");
//     row_d->box(FL_FLAT_BOX);
//     row_d->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
//     row_d->color(FL_CYAN);

//     v_pack->resizable(row_b_and_c);
//     v_pack->end();

//     window->resizable(v_pack);
//     window->end();
//     window->show(argc, argv);

//     return Fl::run();
// }

// Fl_Group* panel = new Fl_Group((window->w() - 200) / 2, (window->h() - 100) / 2, 200, 100);
// Fl_Box*   panel_label = new Fl_Box(
//     panel->x(), panel->y(), panel->w(), panel->h(), "I am an absolutely positioned panel"
// );
// panel_label->box(FL_FLAT_BOX);
// panel_label->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER);
// panel->end();
// panel->hide();

// Fl_Button* toggle_button =
//     new Fl_Button(10, window->h() - 30, 200, 20, "Show/hide absolute panel");
//
// void resize(int X, int Y, int W, int H) override {
//     float x_scale = static_cast<float>(W) / static_cast<float>(w());
//     float y_scale = static_cast<float>(H) / static_cast<float>(h());

//     for (int i = 0; i < children(); ++i) {
//         Fl_Widget* child = this->child(i);
//         int        new_x = X + static_cast<int>((child->x() - x()) * x_scale);
//         int        new_y = Y + static_cast<int>((child->y() - y()) * y_scale);
//         int        new_w = static_cast<int>(child->w() * x_scale);
//         int        new_h = static_cast<int>(child->h() * y_scale);
//         child->resize(new_x, new_y, new_w, new_h);
//     }

//     Fl_Widget::resize(X, Y, W, H);
// }/ toggle_button->callback(toggle_panel, panel);

// #include <FL/Fl.H>
// #include <FL/Fl_Box.H>
// #include <FL/Fl_Group.H>
// #include <FL/Fl_Pack.H>
// #include <FL/Fl_Window.H>

// class ResizingGroup : public Fl_Group {
// public:
//     ResizingGroup(int X, int Y, int W, int H, const char* L = 0) : Fl_Group(X, Y, W, H, L) {}

//     void resize(int X, int Y, int W, int H) override {
//         Fl_Group::resize(X, Y, W, H);
//         Fl_Widget* row_b = child(0);
//         Fl_Widget* row_c = child(1);

//         int row_b_width = static_cast<int>(W * 0.6666);
//         int row_c_width = W - row_b_width;

//         row_b->size(row_b_width, H);
//         row_c->resize(X + row_b_width, Y, row_c_width, H);
//     }
// };

// int main(int argc, char** argv) {
//     Fl_Window* window = new Fl_Window(400, 300, "FLTK Application");
//     window->color(FL_GREEN);

//     Fl_Pack* v_pack = new Fl_Pack(0, 0, window->w(), window->h());
//     v_pack->type(Fl_Pack::VERTICAL);

//     Fl_Box* row_a = new Fl_Box(0, 0, v_pack->w(), 20, "A");
//     row_a->box(FL_FLAT_BOX);
//     row_a->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
//     row_a->color(FL_YELLOW);

//     ResizingGroup* row_b_and_c = new ResizingGroup(0, 0, v_pack->w(), v_pack->h() - 40);
//     {
//         Fl_Box* row_b =
//             new Fl_Box(0, 0, static_cast<int>(row_b_and_c->w() * 0.6666), row_b_and_c->h(), "B");
//         row_b->box(FL_FLAT_BOX);
//         row_b->color(FL_BLUE);

//         Fl_Box* row_c = new Fl_Box(
//             row_b->w(), 0, static_cast<int>(row_b_and_c->w() * 0.3333), row_b_and_c->h(), "C"
//         );
//         row_c->box(FL_FLAT_BOX);
//         row_c->color(FL_RED);

//         row_b_and_c->end();
//     }

//     Fl_Box* row_d = new Fl_Box(0, 0, v_pack->w(), 20, "D");
//     row_d->box(FL_FLAT_BOX);
//     row_d->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
//     row_d->color(FL_CYAN);

//     v_pack->resizable(row_b_and_c);
//     v_pack->end();

//     window->resizable(v_pack);
//     window->end();
//     window->show(argc, argv);

//     return Fl::run();
// }

// #include <FL/Fl.H>
// #include <FL/Fl_Box.H>
// #include <FL/Fl_Group.H>
// #include <FL/Fl_Pack.H>
// #include <FL/Fl_Window.H>

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
//             Fl_Widget* child_widget = child(i);
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

// int main__x(int argc, char** argv) {
//     Fl_Window* window = new Fl_Window(800, 600, "FLTK Proportional Group Example");
//     window->color(FL_GREEN);

//     AspectRatioGroup* ar_group = new AspectRatioGroup(0, 0, window->w(), window->h());
//     // Create vertical layout
//     Fl_Pack* v_pack = new Fl_Pack(0, 0, window->w(), window->h());
//     v_pack->type(Fl_Pack::VERTICAL);
//     //
//     ar_group->add(v_pack);
//     ar_group->resizable(v_pack);
//     ar_group->end();

//     // First row
//     Fl_Box* row_a = new Fl_Box(0, 0, v_pack->w(), 100, "A");
//     row_a->box(FL_FLAT_BOX);
//     row_a->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
//     row_a->color(FL_YELLOW);

//     // Second row
//     std::vector<double> proportions = {0.4, 0.6};
//     ProportionalGroup*  row_b_and_c = new ProportionalGroup(0, 0, v_pack->w(), 400, proportions);
//     Fl_Box*             row_b       = new Fl_Box(
//         0, 0, static_cast<int>(row_b_and_c->w() * proportions[0]), row_b_and_c->h(), "B"
//     );
//     row_b->box(FL_FLAT_BOX);
//     row_b->color(FL_BLUE);
//     row_b_and_c->add(row_b);

//     std::vector<double> nested_proportions = {0.3, 0.7};
//     ProportionalGroup*  nested_group       = new ProportionalGroup(
//         0, 0, row_b_and_c->w() - row_b->w(), row_b_and_c->h(), nested_proportions
//     );
//     {
//         Fl_Box* row_c = new Fl_Box(
//             0, 0, static_cast<int>(nested_group->w() * nested_proportions[0]), nested_group->h(),
//             "C"
//         );
//         row_c->box(FL_FLAT_BOX);
//         row_c->color(FL_RED);
//         nested_group->add(row_c);

//         Fl_Box* row_d = new Fl_Box(
//             0, 0, static_cast<int>(nested_group->w() * nested_proportions[1]), nested_group->h(),
//             "D"
//         );
//         row_d->box(FL_FLAT_BOX);
//         row_d->color(FL_CYAN);
//         nested_group->add(row_d);
//     }
//     row_b_and_c->add(nested_group);

//     // Third row
//     Fl_Box* row_e = new Fl_Box(0, 0, v_pack->w(), 100, "E");
//     row_e->box(FL_FLAT_BOX);
//     row_e->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
//     row_e->color(FL_MAGENTA);

//     // Add rows to vertical layout
//     v_pack->add(row_a);
//     v_pack->add(row_b_and_c);
//     v_pack->add(row_e);

//     // Set resizable elements
//     v_pack->resizable(row_b_and_c);
//     row_b_and_c->resizable(nested_group);

//     // Finish and show the window
//     v_pack->end();
//     // window->resizable(v_pack);
//     window->resizable(ar_group);
//     window->end();
//     window->show(argc, argv);

//     return Fl::run();
// }

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
//     v_pack->resizable(row1);

//     v_pack->end();
//     window->resizable(v_pack);
//     window->end();
//     window->show(argc, argv);

//     return Fl::run();
// }