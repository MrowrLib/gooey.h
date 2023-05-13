#include "Example - Empty Window.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    QWidget      window;
    QVBoxLayout* layout = new QVBoxLayout(&window);

    QGraphicsScene scene;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            CustomRectItem* rect  = new CustomRectItem(i * 10, j * 10, 9, 9);  // , &scene);
            int             hue   = (i + j) % 360;
            QColor          color = QColor::fromHsv(hue, 255, 255);
            rect->setBrush(color);
            scene.addItem(rect);
        }
    }

    GameView* view = new GameView();
    view->setScene(&scene);
    layout->addWidget(view, 9);

    QHBoxLayout* panelLayout = new QHBoxLayout();
    for (int i = 0; i < 4; i++) {
        QPushButton* button = new QPushButton(QString("Button %1").arg(i + 1));
        panelLayout->addWidget(button);
    }
    QWidget* panel = new QWidget();
    panel->setLayout(panelLayout);
    layout->addWidget(panel, 1);

    window.show();

    return a.exec();
}

///////////////////////////////////////

// #include <QApplication>
// #include <QGraphicsRectItem>
// #include <QGraphicsScene>
// #include <QGraphicsSceneMouseEvent>
// #include <QGraphicsView>
// #include <QPen>

// class CustomRectItem : public QGraphicsRectItem {
// public:
//     CustomRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr)
//         : QGraphicsRectItem(x, y, w, h, parent) {}

// protected:
//     void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
//         if (event->button() == Qt::LeftButton) {
//             this->scene()->removeItem(
//                 this->scene()->property("highlight").value<QGraphicsRectItem*>()
//             );
//             delete this->scene()->property("highlight").value<QGraphicsRectItem*>();

//             QGraphicsRectItem* highlight =
//                 this->scene()->addRect(this->rect(), QPen(Qt::blue, 5), Qt::NoBrush);
//             highlight->setPos(this->pos());
//             highlight->setZValue(1);  // Ensure highlight is always on top
//             this->scene()->setProperty("highlight", QVariant::fromValue(highlight));
//         }
//         QGraphicsRectItem::mousePressEvent(event);
//     }

//     void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override {
//         // do nothing
//     }
// };

// int main(int argc, char** argv) {
//     QApplication app(argc, argv);

//     QGraphicsScene scene;
//     for (int i = 0; i < 10; ++i) {
//         for (int j = 0; j < 10; ++j) {
//             CustomRectItem* rect = new CustomRectItem(i * 20, j * 20, 19, 19);
//             scene.addItem(rect);
//         }
//     }

//     QGraphicsView view(&scene);
//     view.show();

//     return app.exec();
// }

// ////////////////////////////////////////

// // // #include "example_setup.h"

// // // using namespace gooey;

// // // int main() {
// // //     int            x   = 69;
// // //     UIApplication* app = create_gooey_application();
// // //     // UIWindow*      window = app->add_window();
// // //     // window->set_title("Empty Window");
// // //     // window->set_size(640, 480);
// // //     // window->set_position(100, 100);
// // //     // window->show();
// // //     app->run_blocking();
// // //     return 0;
// // // }

// // //////////////////////
// // //////////////////////
// // //////////////////////
// // //////////////////////
// // //////////////////////

// // // #include <QApplication>
// // // #include <QGraphicsOpacityEffect>
// // // #include <QLabel>
// // // #include <QPushButton>
// // // #include <QStackedLayout>
// // // #include <QVBoxLayout>

// // // int main(int argc, char** argv) {
// // //     QApplication app(argc, argv);

// // //     QWidget         window;
// // //     QStackedLayout* stackLayout = new QStackedLayout(&window);

// // //     // This is your main content
// // //     QPushButton* mainContent = new QPushButton("Main Content");
// // //     mainContent->setStyleSheet("background-color: rgba(255, 0, 255);");  // opaque white
// // //     // mainContent->setAlignment(Qt::AlignCenter);
// // //     stackLayout->addWidget(mainContent);

// // //     // This is your "modal"
// // //     QWidget* modalOverlay = new QWidget();
// // //     modalOverlay->setStyleSheet("background-color: rgba(0, 0, 0, 50); width: 50%;"
// // //     );  // semi-transparent black
// // //     QVBoxLayout* modalLayout      = new QVBoxLayout(modalOverlay);
// // //     QLabel*      modalLabel       = new QLabel("Modal Content");
// // //     QPushButton* closeModalButton = new QPushButton("Close");
// // //     modalLabel->setAlignment(Qt::AlignCenter);
// // //     modalLayout->addWidget(modalLabel);
// // //     modalLayout->addWidget(closeModalButton);
// // //     stackLayout->addWidget(modalOverlay);

// // //     // Switch to the modal when the main content is clicked
// // //     // QObject::connect(mainContent, &QLabel::linkActivated, [&]() {
// // //     //     stackLayout->setCurrentWidget(modalOverlay);
// // //     // });
// // //     QObject::connect(mainContent, &QPushButton::clicked, [&]() {
// // //         stackLayout->setCurrentWidget(modalOverlay);
// // //     });

// // //     // Switch back to the main content when the close button is clicked
// // //     QObject::connect(closeModalButton, &QPushButton::clicked, [&]() {
// // //         stackLayout->setCurrentWidget(mainContent);
// // //     });

// // //     window.show();
// // //     return app.exec();
// // // }

// // // #include <QtWidgets>

// // // int main(int argc, char** argv) {
// // //     QApplication app(argc, argv);

// // //     QWidget window;

// // //     QVBoxLayout* vLayout    = new QVBoxLayout();  // Vertical Box Layout
// // //     QHBoxLayout* hLayout    = new QHBoxLayout();  // Horizontal Box Layout
// // //     QGridLayout* gridLayout = new QGridLayout();  // Grid Layout
// // //     QFormLayout* formLayout = new QFormLayout();  // Form Layout

// // //     // For QVBoxLayout and QHBoxLayout
// // //     QPushButton* button1 = new QPushButton("Button 1");
// // //     QPushButton* button2 = new QPushButton("Button 2");

// // //     vLayout->addWidget(button1);
// // //     hLayout->addWidget(button2);

// // //     // For QGridLayout
// // //     QPushButton* button3 = new QPushButton("Button 3");
// // //     QPushButton* button4 = new QPushButton("Button 4");

// // //     gridLayout->addWidget(button3, 0, 0);  // 0 row, 0 column
// // //     gridLayout->addWidget(button4, 0, 1);  // 0 row, 1 column

// // //     // For QFormLayout
// // //     QLineEdit* lineEdit1 = new QLineEdit();
// // //     QLineEdit* lineEdit2 = new QLineEdit();

// // //     formLayout->addRow("Label 1", lineEdit1);
// // //     formLayout->addRow("Label 2", lineEdit2);

// // //     // Creating QWidgets to hold the layouts
// // //     QWidget* vLayoutWidget    = new QWidget;
// // //     QWidget* hLayoutWidget    = new QWidget;
// // //     QWidget* gridLayoutWidget = new QWidget;
// // //     QWidget* formLayoutWidget = new QWidget;

// // //     // Setting the layouts of the widgets
// // //     vLayoutWidget->setLayout(vLayout);
// // //     hLayoutWidget->setLayout(hLayout);
// // //     gridLayoutWidget->setLayout(gridLayout);
// // //     formLayoutWidget->setLayout(formLayout);

// // //     // Using QStackedLayout to switch between different layouts
// // //     QStackedLayout* stackedLayout = new QStackedLayout();
// // //     stackedLayout->addWidget(vLayoutWidget);
// // //     stackedLayout->addWidget(hLayoutWidget);
// // //     stackedLayout->addWidget(gridLayoutWidget);
// // //     stackedLayout->addWidget(formLayoutWidget);

// // //     // Set the layout of the window to the stacked layout
// // //     window.setLayout(stackedLayout);

// // //     stackedLayout->setCurrentIndex(2);

// // //     window.show();

// // //     return app.exec();
// // // }

// // // #include <QtWidgets>

// // // int main(int argc, char** argv) {
// // //     QApplication app(argc, argv);

// // //     // Main window and layout
// // //     QWidget      window;
// // //     QVBoxLayout* vLayout = new QVBoxLayout();  // Vertical Box Layout

// // //     QPushButton* button1 = new QPushButton("xxxx HELLO xxxx");
// // //     vLayout->addWidget(button1);
// // //     window.setLayout(vLayout);

// // //     // Create a modal dialog
// // //     QDialog*     dialog       = new QDialog(&window);
// // //     QVBoxLayout* dialogLayout = new QVBoxLayout();  // Dialog layout

// // //     QPushButton* button2 = new QPushButton("Close Modal");
// // //     dialogLayout->addWidget(button2);
// // //     dialog->setLayout(dialogLayout);

// // //     // Connect the button click signal to show the modal dialog
// // //     QObject::connect(button1, &QPushButton::clicked, [&]() {
// // //         dialog->exec();  // This will block input to the main window until the dialog is
// // closed
// // //     });

// // //     // Connect the button click signal to close the modal dialog
// // //     QObject::connect(button2, &QPushButton::clicked, [&]() { dialog->close(); });

// // //     window.show();

// // //     return app.exec();
// // // }

// // // #include <QtWidgets>

// // // int main(int argc, char** argv) {
// // //     QApplication app(argc, argv);

// // //     // Main window and layout
// // //     QWidget      mainWindow;
// // //     QVBoxLayout* mainLayout = new QVBoxLayout(&mainWindow);

// // //     QPushButton* button1 = new QPushButton("Open Modal");
// // //     mainLayout->addWidget(button1);

// // //     // Create an overlay QWidget
// // //     QWidget      overlay(&mainWindow);
// // //     QVBoxLayout* overlayLayout = new QVBoxLayout(&overlay);

// // //     QPushButton* button2 = new QPushButton("Close Modal");
// // //     overlayLayout->addWidget(button2);

// // //     // Initially hide the overlay
// // //     overlay.hide();

// // //     // Connect the button click signal to show the overlay widget
// // //     QObject::connect(button1, &QPushButton::clicked, [&]() {
// // //         overlay.setGeometry(mainWindow.rect()
// // //         );                // Make the overlay the same size as the main window
// // //         overlay.raise();  // Bring the overlay to the top
// // //         overlay.show();   // Show the overlay
// // //     });

// // //     // Connect the button click signal to hide the overlay widget
// // //     QObject::connect(button2, &QPushButton::clicked, [&]() {
// // //         overlay.hide();  // Hide the overlay
// // //     });

// // //     mainWindow.show();

// // //     return app.exec();
// // // }

// // // #include <QApplication>
// // // #include <QPushButton>
// // // #include <QVBoxLayout>
// // // #include <QWidget>

// // // int main(int argc, char** argv) {
// // //     QApplication app(argc, argv);
// // //     QWidget      window;

// // //     QVBoxLayout layout(&window);

// // //     QPushButton button1("Button 1");
// // //     button1.setStyleSheet(
// // //         "QPushButton {"
// // //         "background-color: #C0C0C0;"
// // //         "border-style: outset;"
// // //         "border-width: 2px;"
// // //         "border-color: black;"
// // //         "}"
// // //         "QPushButton:pressed {"
// // //         "background-color: #808080;"
// // //         "border-style: inset;"
// // //         "}"
// // //     );
// // //     layout.addWidget(&button1);

// // //     QPushButton button2("Button 2");
// // //     button2.setStyleSheet(
// // //         "QPushButton {"
// // //         "background-color: #C0C0C0;"
// // //         "border-style: outset;"
// // //         "border-width: 2px;"
// // //         "border-color: black;"
// // //         "}"
// // //         "QPushButton:pressed {"
// // //         "background-color: #808080;"
// // //         "border-style: inset;"
// // //         "}"
// // //     );
// // //     layout.addWidget(&button2);

// // //     window.show();

// // //     return app.exec();
// // // }

// // // #include <QApplication>
// // // #include <QFile>
// // // #include <QFileSystemWatcher>
// // // #include <QPushButton>
// // // #include <QTextStream>
// // // #include <QVBoxLayout>
// // // #include <QWidget>

// // // // Function to load QSS
// // // QString loadQSS(const QString& path) {
// // //     QFile file(path);
// // //     file.open(QFile::ReadOnly | QFile::Text);
// // //     QTextStream stream(&file);
// // //     return stream.readAll();
// // // }

// // // #include <filesystem>
// // // #include <iostream>

// // // int main(int argc, char** argv) {
// // //     // print current directory path
// // //     std::cout << "Current path is " << std::filesystem::current_path() << '\n';

// // //     QApplication app(argc, argv);
// // //     QWidget      window;

// // //     QVBoxLayout layout(&window);

// // //     QPushButton button1("Button 1");
// // //     layout.addWidget(&button1);

// // //     QPushButton button2("Button 2");
// // //     layout.addWidget(&button2);

// // //     window.show();

// // //     // Load the QSS
// // //     QString qss = loadQSS("../../../../Examples/Cpp/styles.qss");
// // //     app.setStyleSheet(qss);

// // //     // Watch for changes in the QSS file
// // //     QFileSystemWatcher watcher;
// // //     watcher.addPath("../../../../Examples/Cpp/styles.qss");

// // //     QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, [&]() {
// // //         QString newQss = loadQSS("../../../../Examples/Cpp/styles.qss");
// // //         app.setStyleSheet(newQss);
// // //     });

// // //     return app.exec();
// // // }

// // // #include <QApplication>
// // // #include <QPropertyAnimation>
// // // #include <QPushButton>
// // // #include <QWidget>

// // // int main(int argc, char* argv[]) {
// // //     QApplication a(argc, argv);

// // //     QWidget widget;
// // //     widget.setFixedSize(1920, 1080);
// // //     QPushButton button("Moving Button", &widget);

// // //     QPropertyAnimation animation(&button, "geometry");
// // //     animation.setDuration(1000);  // 1 second
// // //     animation.setStartValue(QRect(0, 0, 100, 30));
// // //     animation.setEndValue(QRect(1000, 1000, 600, 400));

// // //     widget.show();
// // //     animation.start();

// // //     return a.exec();
// // // }

// // // #include <QApplication>
// // // #include <QBrush>
// // // // #include <QDesktopWidget>
// // // #include <QMainWindow>
// // // #include <QPalette>
// // // #include <QPixmap>
// // // #include <QPushButton>
// // // #include <QStyle>
// // // #include <QVBoxLayout>

// // // int main(int argc, char* argv[]) {
// // //     QApplication app(argc, argv);

// // //     QMainWindow window;

// // //     // QScreen *screen = QGuiApplication::primaryScreen();
// // //     // QRect  screenGeometry = screen->geometry();
// // //     // int height = screenGeometry.height();
// // //     // int width = screenGeometry.width();
// // //     // window.setFixedSize(QApplication::desktop()->size());  // Full screen
// // //     window.setFixedSize(1920, 1080);

// // //     // Set background image
// // //     QPalette palette;
// // //     palette.setBrush(QPalette::Window,
// // //     QBrush(QPixmap(":/Resources/Images/grass_background.png")));
// window.setPalette(palette);

// // //     // Create buttons
// // //     QPushButton* newGameButton  = new QPushButton("New Game");
// // //     QPushButton* exitGameButton = new QPushButton("Exit Game");

// // //     // Create layout
// // //     QVBoxLayout* layout = new QVBoxLayout();
// // //     layout->addWidget(newGameButton, 0, Qt::AlignCenter);
// // //     layout->addWidget(exitGameButton, 0, Qt::AlignCenter);

// // //     // Create a central widget to hold the layout
// // //     QWidget* centralWidget = new QWidget();
// // //     centralWidget->setLayout(layout);
// // //     window.setCentralWidget(centralWidget);

// // //     // Connect button signals to slots
// // //     QObject::connect(newGameButton, &QPushButton::clicked, &app, [&]() {
// // //         // Code to start new game goes here
// // //     });
// // //     QObject::connect(exitGameButton, &QPushButton::clicked, &app, &QApplication::quit);

// // //     window.show();

// // //     return app.exec();
// // // }

// // #include <QApplication>
// // #include <QGraphicsRectItem>
// // #include <QGraphicsScene>
// // #include <QGraphicsSceneMouseEvent>
// // #include <QGraphicsView>
// // #include <QPushButton>
// // #include <QScrollBar>
// // #include <QVBoxLayout>
// // #include <QWheelEvent>

// // class CustomRectItemObject : public QObject {
// //     Q_OBJECT
// // public:
// //     CustomRectItemObject(QObject* parent = nullptr) : QObject(parent) {}

// // signals:
// //     void leftClicked();
// // };

// // //

// // class CustomRectItem : public QGraphicsObject {
// //     Q_OBJECT
// //     QGraphicsRectItem* rectItem;

// // public:
// //     CustomRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr)
// //         : QGraphicsObject(parent), rectItem(new QGraphicsRectItem(x, y, w, h, this)) {}

// //     ~CustomRectItem() { delete rectItem; }

// //     QGraphicsRectItem* getRect() { return rectItem; }

// //     QRectF boundingRect() const override { return rectItem->boundingRect(); }

//     void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
//         override {
//         rectItem->paint(painter, option, widget);
//     }

//     void setBrush(const QBrush& brush) { rectItem->setBrush(brush); }

// signals:
//     void leftClicked();

// protected:
//     void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
//         if (event->button() == Qt::LeftButton) {
//             emit leftClicked();
//         }
//     }
// };

// class CustomScene : public QGraphicsScene {
//     Q_OBJECT
//     QGraphicsRectItem* highlight = nullptr;

// public:
//     CustomScene(QObject* parent = nullptr) : QGraphicsScene(parent) {}

//     Q_INVOKABLE void updateHighlight() {
//         if (highlight != nullptr) {
//             this->removeItem(highlight);
//             delete highlight;
//         }

//         CustomRectItem* senderItem = qobject_cast<CustomRectItem*>(sender());
//         if (senderItem != nullptr) {
//             highlight =
//                 this->addRect(senderItem->getRect()->rect(), QPen(Qt::black, 1), Qt::NoBrush);
//             highlight->setZValue(1);  // Ensure highlight is always on top
//         }
//     }
// };

// class GameView : public QGraphicsView {
//     qreal   _totalScaleFactor = 1;
//     qreal   _lastScaleFactor  = 1;
//     bool    _mousePressed     = false;
//     QPointF _lastMousePos;

// public:
//     GameView() {
//         setRenderHint(QPainter::Antialiasing);
//         setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//         setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//         setAttribute(Qt::WA_AcceptTouchEvents);
//     }

// protected:
//     void wheelEvent(QWheelEvent* event) override {
//         setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//         double scaleFactor = 1.15;
//         if (event->angleDelta().y() > 0) {
//             // Zoom in
//             scale(scaleFactor, scaleFactor);
//         } else {
//             // Zooming out
//             scale(1 / scaleFactor, 1 / scaleFactor);
//         }
//     }

//     void mousePressEvent(QMouseEvent* event) override {
//         if (event->button() == Qt::RightButton) {
//             _mousePressed = true;
//             _lastMousePos = event->globalPosition();
//         }
//     }

//     void mouseMoveEvent(QMouseEvent* event) override {
//         if (_mousePressed) {
//             QPointF delta    = event->globalPosition() - _lastMousePos;
//             _lastMousePos    = event->globalPosition();
//             QScrollBar* hBar = horizontalScrollBar();
//             QScrollBar* vBar = verticalScrollBar();
//             hBar->setValue(hBar->value() - delta.x());
//             vBar->setValue(vBar->value() - delta.y());
//         }
//     }

//     void mouseReleaseEvent(QMouseEvent* event) override {
//         if (event->button() == Qt::RightButton) {
//             _mousePressed = false;
//         }
//     }

//     bool viewportEvent(QEvent* event) override {
//         switch (event->type()) {
//             case QEvent::TouchBegin:
//             case QEvent::TouchUpdate:
//             case QEvent::TouchEnd: {
//                 QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);

//                 QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->points();
//                 if (touchPoints.count() == 2) {
//                     // Determine scale factor
//                     const QTouchEvent::TouchPoint& touchPoint0 = touchPoints.first();
//                     const QTouchEvent::TouchPoint& touchPoint1 = touchPoints.last();

//                     qreal currentScaleFactor =
//                         QLineF(touchPoint0.position(), touchPoint1.position()).length() /
//                         QLineF(touchPoint0.pressPosition(),
//                         touchPoint1.pressPosition()).length();
//                     if (touchEvent->touchPointStates() & Qt::TouchPointReleased) {
//                         // If one of the fingers is released, remember the last scale factor so
//                         that
//                         // adding another finger later will continue zooming by adding new scale
//                         // factor to the existing remembered value.
//                         _lastScaleFactor = _totalScaleFactor;
//                         _totalScaleFactor *= currentScaleFactor;
//                     } else {
//                         setTransformationAnchor(QGraphicsView::NoAnchor);
//                         setTransform(QTransform::fromScale(
//                             _totalScaleFactor * currentScaleFactor,
//                             _totalScaleFactor * currentScaleFactor
//                         ));
//                     }
//                 } else if (touchPoints.count() == 1) {
//                     // Pan
//                     if (touchEvent->touchPointStates() & Qt::TouchPointMoved) {
//                         QScrollBar* hBar = horizontalScrollBar();
//                         QScrollBar* vBar = verticalScrollBar();
//                         QPointF     delta =
//                             touchPoints.first().position() - touchPoints.first().pressPosition();

//                         qreal scaleFactor = transform().m11();

//                         // Change this value to adjust the panning speed
//                         qreal speedAdjustment = 0.1;

//                         hBar->setValue(
//                             hBar->value() + speedAdjustment * (delta.x() > 0 ? -1 : 1) *
//                                                 qAbs(delta.x()) / scaleFactor
//                         );
//                         vBar->setValue(
//                             vBar->value() + speedAdjustment * (delta.y() > 0 ? -1 : 1) *
//                                                 qAbs(delta.y()) / scaleFactor
//                         );
//                     }
//                 }
//                 return true;
//             }
//             default:
//                 return QGraphicsView::viewportEvent(event);
//         }
//     }
// };

// int main(int argc, char* argv[]) {
//     QApplication a(argc, argv);

//     QWidget      window;
//     QVBoxLayout* layout = new QVBoxLayout(&window);

//     CustomScene scene;
//     for (int i = 0; i < 100; i++) {
//         for (int j = 0; j < 100; j++) {
//             CustomRectItem* rect = new CustomRectItem(i * 10, j * 10, 9, 9);

//             int    hue   = (i + j) % 360;
//             QColor color = QColor::fromHsv(hue, 255, 255);
//             rect->setBrush(color);

//             QObject::connect(
//                 rect, &CustomRectItem::leftClicked, &scene, &CustomScene::updateHighlight
//             );

//             scene.addItem(rect);
//         }
//     }

//     GameView* view = new GameView();
//     view->setScene(&scene);
//     layout->addWidget(view, 9);

//     QHBoxLayout* panelLayout = new QHBoxLayout();
//     for (int i = 0; i < 4; i++) {
//         QPushButton* button = new QPushButton(QString("Button %1").arg(i + 1));
//         panelLayout->addWidget(button);
//     }
//     QWidget* panel = new QWidget();
//     panel->setLayout(panelLayout);
//     layout->addWidget(panel, 1);

//     window.show();

//     return a.exec();
// }
