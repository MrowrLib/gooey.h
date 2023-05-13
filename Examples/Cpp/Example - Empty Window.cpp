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
