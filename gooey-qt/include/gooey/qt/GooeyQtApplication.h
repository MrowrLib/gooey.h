#pragma once

#include <gooey/base.h>

#include <QApplication>
#include <QMainWindow>

namespace gooey::Qt {

    class GooeyQtApplication : public UIApplicationBase {
    public:
        bool run_blocking() override {
            int          argc = 0;
            char**       argv = nullptr;
            QApplication app{argc, argv};
            QMainWindow  window;
            window.show();
            QApplication::exec();
            return true;
        }
    };
}
