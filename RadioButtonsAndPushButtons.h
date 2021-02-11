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
    QPushButton *automaticPlacementShips;
    QRadioButton *horizontalRadioButton;
    QRadioButton *verticalRadioButton;
    QVBoxLayout *verticalLayout;

    void setStyleSheets();
    
public:
    RadioButtonsAndPushButtons(QWidget * parent = nullptr);
    ~RadioButtonsAndPushButtons() override;

    QPushButton*& getStart();
    QPushButton*& getAutoPlacementShips();
    QRadioButton*& getHorizantal();
    QRadioButton*& getVertical();
};

#endif // RADIOBUTTONSANDPUSHBUTTONS_H
