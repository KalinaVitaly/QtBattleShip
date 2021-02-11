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
    const int fieldsCount;
    QLabel *fieldsLabel[10][10];
    QSize size;

    void setLabelsStyle(std::array<std::array<int, 10>, 10> field, const QSize & size);
    void setLabel();
public:
    GridLabelWidget(std::array<std::array<int, 10>, 10> field, const QSize & size, QWidget * parent = nullptr);
    ~GridLabelWidget() override;
public slots:
    void slotSetBombHitOnLabelGrid(const QPair<int, int> &);
    void slotSetBombMissOnLabelGrid(const QPair<int, int> &);
    void slotSetFieldsAroundDestroyededShipInGridLabel(const QVector<QPair<int, int>> &);
};

#endif // GRIDLABELWIDGET_H
