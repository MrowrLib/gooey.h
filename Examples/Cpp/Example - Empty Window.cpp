// #include "example_setup.h"

// using namespace gooey;

// int main() {
//     int            x   = 69;
//     UIApplication* app = create_gooey_application();
//     // UIWindow*      window = app->add_window();
//     // window->set_title("Empty Window");
//     // window->set_size(640, 480);
//     // window->set_position(100, 100);
//     // window->show();
//     app->run_blocking();
//     return 0;
// }

// #include <QtWidgets>

// int main(int argc, char** argv) {
//     QApplication app(argc, argv);

//     QWidget window;

//     QVBoxLayout* vLayout    = new QVBoxLayout();  // Vertical Box Layout
//     QHBoxLayout* hLayout    = new QHBoxLayout();  // Horizontal Box Layout
//     QGridLayout* gridLayout = new QGridLayout();  // Grid Layout
//     QFormLayout* formLayout = new QFormLayout();  // Form Layout

//     // For QVBoxLayout and QHBoxLayout
//     QPushButton* button1 = new QPushButton("Button 1");
//     QPushButton* button2 = new QPushButton("Button 2");

//     vLayout->addWidget(button1);
//     hLayout->addWidget(button2);

//     // For QGridLayout
//     QPushButton* button3 = new QPushButton("Button 3");
//     QPushButton* button4 = new QPushButton("Button 4");

//     gridLayout->addWidget(button3, 0, 0);  // 0 row, 0 column
//     gridLayout->addWidget(button4, 0, 1);  // 0 row, 1 column

//     // For QFormLayout
//     QLineEdit* lineEdit1 = new QLineEdit();
//     QLineEdit* lineEdit2 = new QLineEdit();

//     formLayout->addRow("Label 1", lineEdit1);
//     formLayout->addRow("Label 2", lineEdit2);

//     // Creating QWidgets to hold the layouts
//     QWidget* vLayoutWidget    = new QWidget;
//     QWidget* hLayoutWidget    = new QWidget;
//     QWidget* gridLayoutWidget = new QWidget;
//     QWidget* formLayoutWidget = new QWidget;

//     // Setting the layouts of the widgets
//     vLayoutWidget->setLayout(vLayout);
//     hLayoutWidget->setLayout(hLayout);
//     gridLayoutWidget->setLayout(gridLayout);
//     formLayoutWidget->setLayout(formLayout);

//     // Using QStackedLayout to switch between different layouts
//     QStackedLayout* stackedLayout = new QStackedLayout();
//     stackedLayout->addWidget(vLayoutWidget);
//     stackedLayout->addWidget(hLayoutWidget);
//     stackedLayout->addWidget(gridLayoutWidget);
//     stackedLayout->addWidget(formLayoutWidget);

//     // Set the layout of the window to the stacked layout
//     window.setLayout(stackedLayout);

//     stackedLayout->setCurrentIndex(2);

//     window.show();

//     return app.exec();
// }

// #include <QtWidgets>

// int main(int argc, char** argv) {
//     QApplication app(argc, argv);

//     // Main window and layout
//     QWidget      window;
//     QVBoxLayout* vLayout = new QVBoxLayout();  // Vertical Box Layout

//     QPushButton* button1 = new QPushButton("xxxx HELLO xxxx");
//     vLayout->addWidget(button1);
//     window.setLayout(vLayout);

//     // Create a modal dialog
//     QDialog*     dialog       = new QDialog(&window);
//     QVBoxLayout* dialogLayout = new QVBoxLayout();  // Dialog layout

//     QPushButton* button2 = new QPushButton("Close Modal");
//     dialogLayout->addWidget(button2);
//     dialog->setLayout(dialogLayout);

//     // Connect the button click signal to show the modal dialog
//     QObject::connect(button1, &QPushButton::clicked, [&]() {
//         dialog->exec();  // This will block input to the main window until the dialog is closed
//     });

//     // Connect the button click signal to close the modal dialog
//     QObject::connect(button2, &QPushButton::clicked, [&]() { dialog->close(); });

//     window.show();

//     return app.exec();
// }

// #include <QtWidgets>

// int main(int argc, char** argv) {
//     QApplication app(argc, argv);

//     // Main window and layout
//     QWidget      mainWindow;
//     QVBoxLayout* mainLayout = new QVBoxLayout(&mainWindow);

//     QPushButton* button1 = new QPushButton("Open Modal");
//     mainLayout->addWidget(button1);

//     // Create an overlay QWidget
//     QWidget      overlay(&mainWindow);
//     QVBoxLayout* overlayLayout = new QVBoxLayout(&overlay);

//     QPushButton* button2 = new QPushButton("Close Modal");
//     overlayLayout->addWidget(button2);

//     // Initially hide the overlay
//     overlay.hide();

//     // Connect the button click signal to show the overlay widget
//     QObject::connect(button1, &QPushButton::clicked, [&]() {
//         overlay.setGeometry(mainWindow.rect()
//         );                // Make the overlay the same size as the main window
//         overlay.raise();  // Bring the overlay to the top
//         overlay.show();   // Show the overlay
//     });

//     // Connect the button click signal to hide the overlay widget
//     QObject::connect(button2, &QPushButton::clicked, [&]() {
//         overlay.hide();  // Hide the overlay
//     });

//     mainWindow.show();

//     return app.exec();
// }

// #include <QApplication>
// #include <QPushButton>
// #include <QVBoxLayout>
// #include <QWidget>

// int main(int argc, char** argv) {
//     QApplication app(argc, argv);
//     QWidget      window;

//     QVBoxLayout layout(&window);

//     QPushButton button1("Button 1");
//     button1.setStyleSheet(
//         "QPushButton {"
//         "background-color: #C0C0C0;"
//         "border-style: outset;"
//         "border-width: 2px;"
//         "border-color: black;"
//         "}"
//         "QPushButton:pressed {"
//         "background-color: #808080;"
//         "border-style: inset;"
//         "}"
//     );
//     layout.addWidget(&button1);

//     QPushButton button2("Button 2");
//     button2.setStyleSheet(
//         "QPushButton {"
//         "background-color: #C0C0C0;"
//         "border-style: outset;"
//         "border-width: 2px;"
//         "border-color: black;"
//         "}"
//         "QPushButton:pressed {"
//         "background-color: #808080;"
//         "border-style: inset;"
//         "}"
//     );
//     layout.addWidget(&button2);

//     window.show();

//     return app.exec();
// }

// #include <QApplication>
// #include <QFile>
// #include <QFileSystemWatcher>
// #include <QPushButton>
// #include <QTextStream>
// #include <QVBoxLayout>
// #include <QWidget>

// // Function to load QSS
// QString loadQSS(const QString& path) {
//     QFile file(path);
//     file.open(QFile::ReadOnly | QFile::Text);
//     QTextStream stream(&file);
//     return stream.readAll();
// }

// #include <filesystem>
// #include <iostream>

// int main(int argc, char** argv) {
//     // print current directory path
//     std::cout << "Current path is " << std::filesystem::current_path() << '\n';

//     QApplication app(argc, argv);
//     QWidget      window;

//     QVBoxLayout layout(&window);

//     QPushButton button1("Button 1");
//     layout.addWidget(&button1);

//     QPushButton button2("Button 2");
//     layout.addWidget(&button2);

//     window.show();

//     // Load the QSS
//     QString qss = loadQSS("../../../../Examples/Cpp/styles.qss");
//     app.setStyleSheet(qss);

//     // Watch for changes in the QSS file
//     QFileSystemWatcher watcher;
//     watcher.addPath("../../../../Examples/Cpp/styles.qss");

//     QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, [&]() {
//         QString newQss = loadQSS("../../../../Examples/Cpp/styles.qss");
//         app.setStyleSheet(newQss);
//     });

//     return app.exec();
// }

// #include <QApplication>
// #include <QPropertyAnimation>
// #include <QPushButton>
// #include <QWidget>

// int main(int argc, char* argv[]) {
//     QApplication a(argc, argv);

//     QWidget widget;
//     widget.setFixedSize(1920, 1080);
//     QPushButton button("Moving Button", &widget);

//     QPropertyAnimation animation(&button, "geometry");
//     animation.setDuration(1000);  // 1 second
//     animation.setStartValue(QRect(0, 0, 100, 30));
//     animation.setEndValue(QRect(1000, 1000, 600, 400));

//     widget.show();
//     animation.start();

//     return a.exec();
// }

#include <QApplication>
#include <QBrush>
// #include <QDesktopWidget>
#include <QMainWindow>
#include <QPalette>
#include <QPixmap>
#include <QPushButton>
#include <QStyle>
#include <QVBoxLayout>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;

    // QScreen *screen = QGuiApplication::primaryScreen();
    // QRect  screenGeometry = screen->geometry();
    // int height = screenGeometry.height();
    // int width = screenGeometry.width();
    // window.setFixedSize(QApplication::desktop()->size());  // Full screen
    window.setFixedSize(1920, 1080);

    // Set background image
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/Resources/Images/grass_background.png")));
    window.setPalette(palette);

    // Create buttons
    QPushButton* newGameButton  = new QPushButton("New Game");
    QPushButton* exitGameButton = new QPushButton("Exit Game");

    // Create layout
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(newGameButton, 0, Qt::AlignCenter);
    layout->addWidget(exitGameButton, 0, Qt::AlignCenter);

    // Create a central widget to hold the layout
    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(layout);
    window.setCentralWidget(centralWidget);

    // Connect button signals to slots
    QObject::connect(newGameButton, &QPushButton::clicked, &app, [&]() {
        // Code to start new game goes here
    });
    QObject::connect(exitGameButton, &QPushButton::clicked, &app, &QApplication::quit);

    window.show();

    return app.exec();
}