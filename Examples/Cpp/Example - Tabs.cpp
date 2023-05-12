// #include "example_setup.h"

// using namespace gooey;

// int main() {
//     UIApplication* app    = create_gooey_application();
//     UIWindow*      window = app->add_window();
//     window->set_title("Form Elements");
//     window->show();

//     // app->get_defaults()->

//     auto* label1 = window->add_label("ONE");
//     label1->set_background_color({255, 0, 0});
//     auto* text_input1 = window->add_text_input();

//     auto* label2      = window->add_label("TWO");
//     auto* text_input2 = window->add_text_input();
//     text_input2->set_background_color({0, 255, 0});

//     auto* label3 = window->add_label("THREE");
//     label3->set_background_color({0, 0, 255});
//     auto* text_input3 = window->add_text_input();

//     app->run_blocking();
//     return 0;
// }

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Window.H>

int main() {
    Fl_Window window(300, 200, "FLTK Tabs Example");

    Fl_Tabs tabs(0, 0, 300, 200);
    tabs.color(FL_RED, FL_BLUE);

    // Tab 1
    Fl_Group group1(0, 30, 300, 170, "Tab 1");
    Fl_Box   box1(100, 100, 100, 50, "Hi from tab 1");
    group1.end();

    // Tab 2
    Fl_Group group2(0, 30, 300, 170, "Tab 2");
    Fl_Box   box2(100, 100, 100, 50, "Hi from tab 2");
    group2.end();

    tabs.end();
    window.end();

    group1.copy_label("CHANGED");
    group1.labelcolor(FL_MAGENTA);

    Fl_Group* thirdTab = new Fl_Group(0, 30, 300, 170, "Tab 3");
    Fl_Box*   box3     = new Fl_Box(100, 100, 100, 50, "Hi from tab 3");
    thirdTab->end();
    tabs.add(thirdTab);

    tabs.remove(&group2);

    window.show();
    return Fl::run();
}
