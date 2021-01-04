#ifndef GRIDLABELWIDGET_H
#define GRIDLABELWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <array>

class GridLabelWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *grid;
    const int fields_count;
    QLabel *l_fields[10][10];
    QSize size;

    void setLabelsStyle(std::array<std::array<int, 10>, 10> field, const QSize & size);
    void setLabel();
public:
    GridLabelWidget(std::array<std::array<int, 10>, 10> field, const QSize & size, QWidget * parent = nullptr);

public slots:
    void setBombHitOnLabelGrid(const QPair<int, int> &);
    void setBombMissOnLabelGrid(const QPair<int, int> &);
    void setFieldsAroundDestroyededShipInGridLabel(const QVector<QPair<int, int>> &);
};

#endif // GRIDLABELWIDGET_H
