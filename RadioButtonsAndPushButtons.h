#ifndef RADIOBUTTONSANDPUSHBUTTONS_H
#define RADIOBUTTONSANDPUSHBUTTONS_H

#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>

class RadioButtonsAndPushButtons : public QWidget
{
    Q_OBJECT
    
private:
    QPushButton *start;
    QRadioButton *horizontal;
    QRadioButton *vertical;
    QVBoxLayout *vertical_layout;
    
public:
    RadioButtonsAndPushButtons(QWidget * parent = nullptr);

    QPushButton*& getStart();
    QRadioButton*& getHorizantal();
    QRadioButton*& getVertical();
};

#endif // RADIOBUTTONSANDPUSHBUTTONS_H
