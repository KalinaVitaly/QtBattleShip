#include "Button.h"
#include <QDebug>

Button::Button(QWidget *parent)
    : QWidget(parent),
      state(EMPTY_FIELD)
{}

void Button::enterEvent(QEvent* _event) {
    Q_UNUSED(_event);
    update();
}

void Button::leaveEvent(QEvent* _event) {
    Q_UNUSED(_event);
    update();
}

QSize Button::sizeHint() const { return QSize(width(), height()); }

void Button::setButtonState(const QString & _state) {
    if (_state == "EMPTY_FIELD") {
        state = EMPTY_FIELD;
    } else if (_state == "SHIP_FIELD") {
        state = SHIP_FIELD;
    } else if (_state == "UNKNOWN_FIELD") {
        state = UNKNOWN_FIELD;
    } else if (_state == "MISS_FIELD") {
        qDebug() << "Miss Field!";
        state = MISS_FIELD;
    } else if (_state == "DESTROYEDED_FIELD") {
        qDebug() << "DESTROYEDED Field!";
        state = DESTROYEDED_FIELD;
    }

    update();
}

void Button::setButtonStyleSheet() {

}

void Button::paintEvent(QPaintEvent* _event) {
    Q_UNUSED(_event)

    QPainter painter(this);
    QRect backgroundRect(0, 0, width(), height());
    painter.setRenderHint(QPainter::Antialiasing);

    //
    // Заливаем фон
    //
    QColor backgroundColor;

    if (underMouse()
         && state == EMPTY_FIELD) {
        backgroundColor = Qt::yellow;
    } else if (state == SHIP_FIELD) {
        backgroundColor = Qt::black;
    } else if (state == EMPTY_FIELD
               || state == DESTROYEDED_FIELD
               || state == MISS_FIELD) {
        backgroundColor = Qt::blue;
    } else if (state == UNKNOWN_FIELD) {
        backgroundColor = Qt::gray;
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundColor);
    painter.drawRect(backgroundRect);

    //
    // Рисование поверх фона
    //
    if (state == DESTROYEDED_FIELD) {
        QPen pen(Qt::red, 20, Qt::SolidLine);
        painter.setPen(pen);
        painter.drawLine(0, 0, width(), height());
        painter.drawLine(0, height(), width(), 0);
    } else if (state == MISS_FIELD) {
        QPen pen(Qt::gray, width() / 10, Qt::SolidLine);
        painter.setPen(pen);
        painter.drawEllipse(QPointF(width() / 2, height() / 2), width() / 4, height() / 4);
    }

    //
    // Рисуем рамку
    //
    QPen pen(Qt::white, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    QRectF rectangle(0, 0, width(), height());
    painter.drawRect(rectangle);

}

void Button::mousePressEvent(QMouseEvent* _event) {
    Q_UNUSED(_event);

    emit signalClicked();
}

int Button::getButtonState() {
    return state;
}

Button::~Button() {}
