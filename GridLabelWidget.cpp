#include "GridLabelWidget.h"
#include <QDebug>

GridLabelWidget::GridLabelWidget(std::array<std::array<int, 10>, 10> field, const QSize & size, QWidget * parent) :
    QWidget(parent),
    grid(new QGridLayout(this)),
    fields_count(10),
    size(size)
{
    this->setFixedSize(size.width() * 10, size.height() * 10);
    setLabelsStyle(field, size);
    setLabel();
}

void GridLabelWidget::setFieldsAroundDestroyededShipInGridLabel(const QVector<QPair<int, int>> & coordinates) {
    for (const auto& i : coordinates) {
        l_fields[i.second][i.first]->setStyleSheet("background-color : grey;\
                                                    border : 2px solid white;\
                                                    border-radius : 5px;");
    }
}

void GridLabelWidget::setLabel() {
    for (int i = 0; i < fields_count; ++i) {
        for (int j = 0; j < fields_count; ++j) {
            grid->addWidget(l_fields[i][j], i, j);
        }
    }
}

void GridLabelWidget::setLabelsStyle(std::array<std::array<int, 10>, 10> field, const QSize & size) {
    for (int i = 0; i < fields_count; ++i) {
        for (int j = 0; j < fields_count; ++j) {
            l_fields[i][j] = new QLabel;
            l_fields[i][j]->setFixedSize(size);
            if (field[i][j])
                l_fields[i][j]->setStyleSheet("background-color : black;\
                                               border : 2px solid white;\
                                               border-radius : 5px;");
            else
                l_fields[i][j]->setStyleSheet("background-color : blue;\
                                               border : 2px solid white;\
                                               border-radius : 5px;");

        }
    }
}

void GridLabelWidget::setBombHitOnLabelGrid(const QPair<int, int> & coordinate) {
    //qDebug() << "setBombHitOnLabelGrid";
//    l_fields[coordinate.second][coordinate.first]->setStyleSheet("background-color : red;\
//                                                                  border : 2px solid white;\
//                                                                  border-radius : 5px;");
    QImage("/home/vitaly/QtProject/BattleShips/images/GridLabelImages/x.png").scaled(size).
            save("/home/vitaly/QtProject/BattleShips/images/GridLabelImages/x.png");
    l_fields[coordinate.second][coordinate.first]->setPixmap(QPixmap("/home/vitaly/QtProject/BattleShips/images/GridLabelImages/x.png"));
}

void GridLabelWidget::setBombMissOnLabelGrid(const QPair<int, int> & coordinate) {
    //qDebug() << "setBombMissOnLabelGrid";
//    l_fields[coordinate.second][coordinate.first]->setStyleSheet("background-color : orange;\
//                                                                  border : 2px solid white;\
//                                                                  border-radius : 5px;");
    QImage("/home/vitaly/QtProject/BattleShips/images/GridLabelImages/miss.png").scaled(size).
            save("/home/vitaly/QtProject/BattleShips/images/GridLabelImages/miss.png");
    l_fields[coordinate.second][coordinate.first]->setPixmap(QPixmap("/home/vitaly/QtProject/BattleShips/images/GridLabelImages/miss.png"));
}

GridLabelWidget::~GridLabelWidget() {
    delete grid;
    for (int i = 0; i < fields_count; ++i) {
        for (int j = 0; j < fields_count; ++j) {
            delete l_fields[i][j];
        }
    }
}
