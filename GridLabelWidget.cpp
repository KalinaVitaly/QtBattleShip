#include "GridLabelWidget.h"
#include <QDebug>

GridLabelWidget::GridLabelWidget(std::array<std::array<int, 10>, 10> field, const QSize & size, QWidget * parent) :
    QWidget(parent),
    grid(new QGridLayout(this)),
    fieldsCount(10),
    size(size)
{
    this->setFixedSize(size.width() * 10, size.height() * 10);
    setLabelsStyle(field, size);
    setLabel();
}

void GridLabelWidget::slotSetFieldsAroundDestroyededShipInGridLabel(const QVector<QPair<int, int>> & coordinates) {
    for (const auto& i : coordinates) {
        fieldsLabel[i.second][i.first]->setStyleSheet("background-color : grey;\
                                                    border : 2px solid white;\
                                                    border-radius : 5px;");
    }
}

void GridLabelWidget::setLabel() {
    for (int i = 0; i < fieldsCount; ++i) {
        for (int j = 0; j < fieldsCount; ++j) {
            grid->addWidget(fieldsLabel[i][j], i, j);
        }
    }
}

void GridLabelWidget::setLabelsStyle(std::array<std::array<int, 10>, 10> field, const QSize & size) {
    for (int i = 0; i < fieldsCount; ++i) {
        for (int j = 0; j < fieldsCount; ++j) {
            fieldsLabel[i][j] = new QLabel;
            fieldsLabel[i][j]->setFixedSize(size);
            if (field[i][j])
                fieldsLabel[i][j]->setStyleSheet("background-color : black;\
                                               border : 2px solid white;\
                                               border-radius : 5px;");
            else
                fieldsLabel[i][j]->setStyleSheet("background-color : blue;\
                                               border : 2px solid white;\
                                               border-radius : 5px;");

        }
    }
}

void GridLabelWidget::slotSetBombHitOnLabelGrid(const QPair<int, int> & coordinate) {
//    QImage(":/images/x.png").scaled(size).
//            save(":/images/x.png");
    fieldsLabel[coordinate.second][coordinate.first]->setPixmap(QPixmap(":/images/GridLabelImages/x.png"));
}

void GridLabelWidget::slotSetBombMissOnLabelGrid(const QPair<int, int> & coordinate) {
//    QImage(":/images/miss.png").scaled(size).
//            save(":/images/miss.png");
    fieldsLabel[coordinate.second][coordinate.first]->setPixmap(QPixmap(":/images/GridLabelImages/miss.png"));
}

GridLabelWidget::~GridLabelWidget() {
    delete grid;
    for (int i = 0; i < fieldsCount; ++i) {
        for (int j = 0; j < fieldsCount; ++j) {
            delete fieldsLabel[i][j];
        }
    }
}
