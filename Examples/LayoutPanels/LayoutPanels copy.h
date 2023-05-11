#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Window.H>

#include <cmath>






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
