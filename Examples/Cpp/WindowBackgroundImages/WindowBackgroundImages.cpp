#include "example_setup.h"

using namespace gooey;

int main() {
    UIApplication* app    = create_gooey_application();
    UIWindow*      window = app->add_window();
    window->set_title("Background Images");
    window->add_background_image(ExampleImagePaths::GrassBackground.string().c_str());
    window->add_background_image(ExampleImagePaths::Castle.string().c_str());
    window->show();
    app->run_blocking();
    return 0;
}