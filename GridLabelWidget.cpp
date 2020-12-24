#include "GridLabelWidget.h"

GridLabelWidget::GridLabelWidget(std::array<std::array<int, 10>, 10> field, const QSize & size, QWidget * parent) :
    QWidget(parent),
    fields_count(10),
    size(size)
{
    this->setFixedSize(size.width() * 10, size.height() * 10);
    grid = new QGridLayout(this);
    setLabelsStyle(field, size);
    setLabel();
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

void GridLabelWidget::setBombHit(const QPair<int, int> & coordinate) {
    l_fields[coordinate.second][coordinate.first]->setStyleSheet("background-color : red;\
                                                                  border : 2px solid white;\
                                                                  border-radius : 5px;");
}

void GridLabelWidget::setBombMiss(const QPair<int, int> & coordinate) {
    l_fields[coordinate.second][coordinate.first]->setStyleSheet("background-color : orange;\
                                                                  border : 2px solid white;\
                                                                  border-radius : 5px;");
}
