#include <QApplication>
#include <QGridLayout>
#include <QIcon>
#include <QLabel>
#include <QMap>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QStyleOptionButton>
#include <QVBoxLayout>
#include <QWidget>
#include <functional>

enum class CellBorder { None, Raised };

class Grid;

class Cell : public QPushButton {
public:
    explicit Cell(Grid* grid, QWidget* parent = nullptr) : QPushButton(parent), m_grid(grid) {
        setMouseTracking(true);

        m_layout = new QVBoxLayout(this);
        m_layout->setContentsMargins(0, 0, 0, 0);
        setLayout(m_layout);

        m_label = new QLabel(this);
        m_layout->addWidget(m_label);
    }

    void setLabel(const QString& text) { m_label->setText(text); }

    void addBackgroundImage(const QString& imagePath) {
        QPixmap image(imagePath);
        m_backgroundImages.insert(imagePath, image);
        updateBackground();
    }

    void removeBackgroundImage(const QString& imagePath) {
        m_backgroundImages.remove(imagePath);
        updateBackground();
    }

    void removeAllBackgroundImages() {
        m_backgroundImages.clear();
        updateBackground();
    }

    void setBackgroundColor(const QColor& color) {
        m_backgroundColor = color;
        updateBackground();
    }

    void unsetBackgroundColor() {
        m_backgroundColor = QColor();
        updateBackground();
    }

    void setBorderType(CellBorder borderType) {
        m_borderType = borderType;
        updateBorder();
    }

    void reset() {
        m_label->clear();  //
        setText("");       //

        m_backgroundImages.clear();
        m_backgroundColor = QColor();
        m_borderType      = CellBorder::None;
        updateBackground();
        updateBorder();
    }

    void destroy() {
        // if (m_grid) {
        //     m_grid->destroyCell(this); // <----- TRICKY!
        // }
    }

    void enterEvent(QEnterEvent* event) override {
        // mouseEntered(); // ????
        QWidget::enterEvent(event);
    }

private:
    void updateBackground() {
        QPixmap combinedBackground(size());
        combinedBackground.fill(m_backgroundColor);
        QPainter painter(&combinedBackground);

        for (const QPixmap& image : m_backgroundImages.values()) {
            painter.drawPixmap(0, 0, width(), height(), image);
        }

        QPalette palette;
        palette.setBrush(QPalette::Window, combinedBackground);
        setAutoFillBackground(true);
        setPalette(palette);
    }

    void updateBorder() {
        switch (m_borderType) {
            case CellBorder::None:
                setStyleSheet("border: none;");
                break;
            case CellBorder::Raised:
                setStyleSheet("border: 2px outset #CCCCCC;");
                break;
        }
    }

    Grid*                  m_grid;
    QVBoxLayout*           m_layout;
    QLabel*                m_label;
    QMap<QString, QPixmap> m_backgroundImages;
    QColor                 m_backgroundColor;
    CellBorder             m_borderType;
};

class Grid : public QWidget {
public:
    Grid(int columnCount, int rowCount, int cellWidth, int cellHeight, QWidget* parent = nullptr)
        : QWidget(parent), m_cellWidth(cellWidth), m_cellHeight(cellHeight) {
        m_layout = new QGridLayout(this);
        m_layout->setSpacing(0);
        m_layout->setContentsMargins(0, 0, 0, 0);
        setLayout(m_layout);

        initializeCells(columnCount, rowCount);
    }

    void createCell(
        int x, int y, int cellWidth, int cellHeight, const QString& labelText,
        const QStringList& imagePaths, const QColor& backgroundColor, CellBorder borderType
    ) {
        auto cell = new Cell(this);
        cell->setFixedSize(cellWidth, cellHeight);

        // You can implement the missing methods for the Cell class and customize the cell here.
        // e.g., cell->setLabel(labelText);

        m_layout->addWidget(cell, y, x, cellHeight, cellWidth);
    }

    Cell* cellAt(int x, int y) {
        return static_cast<Cell*>(m_layout->itemAtPosition(y, x)->widget());
    }

    void destroyCell(Cell* cell) {
        int index = m_layout->indexOf(cell);
        int row, column, rowSpan, colSpan;
        m_layout->getItemPosition(index, &row, &column, &rowSpan, &colSpan);
        m_layout->removeWidget(cell);
        cell->setParent(nullptr);

        for (int r = row; r < row + rowSpan; ++r) {
            for (int c = column; c < column + colSpan; ++c) {
                Cell* newCell = new Cell(this);
                m_layout->addWidget(newCell, r, c);
            }
        }
    }

    void onMouseEnter(int x, int y, std::function<void()> callback) {
        // Cell* cell = cellAt(x, y);
        // if (cell) {
        //     connect(cell, &Cell::enterEvent, callback);
        // }
    }

private:
    void initializeCells(int columnCount, int rowCount) {
        for (int y = 0; y < rowCount; ++y) {
            for (int x = 0; x < columnCount; ++x) {
                auto cell = new Cell(this);
                cell->setFixedSize(m_cellWidth, m_cellHeight);
                m_layout->addWidget(cell, y, x);
            }
        }
    }

    QGridLayout* m_layout;
    int          m_cellWidth;
    int          m_cellHeight;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QWidget     mainWindow;
    QVBoxLayout mainLayout(&mainWindow);
    Grid        grid(10, 8, 50, 50);
    mainLayout.addWidget(&grid);

    // Add labels to a couple of cells
    grid.cellAt(1, 1)->setLabel("Cell 1");
    grid.cellAt(2, 3)->setLabel("Cell 2");

    // Set different border styles
    grid.cellAt(1, 1)->setBorderType(CellBorder::None);
    grid.cellAt(2, 3)->setBorderType(CellBorder::Raised);

    // Set image backgrounds
    grid.cellAt(3, 1)->addBackgroundImage("image1.png");
    grid.cellAt(4, 2)->addBackgroundImage("image2.png");

    // Set background colors
    grid.cellAt(0, 0)->setBackgroundColor(QColor(255, 0, 0));
    grid.cellAt(0, 1)->setBackgroundColor(QColor(0, 255, 0));
    grid.cellAt(0, 2)->setBackgroundColor(QColor(0, 0, 255));

    mainWindow.show();
    return app.exec();
}
