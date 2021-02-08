#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class Button : public QWidget
{
    Q_OBJECT

public:
    Button(QWidget *parent = nullptr);
    ~Button() override;

    void setButtonState(const QString &);
    QSize sizeHint() const override;

private:
    enum buttonState {
        EMPTY_FIELD = 1,
        SHIP_FIELD,
        UNKNOWN_FIELD,
        MISS_FIELD,
        DESTROYEDED_FIELD
    };

    buttonState state;


    void setButtonStyleSheet();

protected:
    void enterEvent(QEvent* _event) override;
    void leaveEvent(QEvent* _event) override;
    //Собственная отрисовка
    void paintEvent(QPaintEvent* _event) override;
    //Нажатие на клавишу
    void mousePressEvent(QMouseEvent* _event) override;

signals:
    void signalClicked();
};
#endif // BUTTON_H
