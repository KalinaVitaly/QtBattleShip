#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QVBoxLayout>
#include "PreparationGameWidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QPixmap *backgroundShipPixmap;
    QPushButton *startGameButton;
    QPushButton *settingsButton;
    QPushButton *exitButton;
    QLabel *gameNameLabel;
    QVBoxLayout *mainLayout;

    //
    // Установка параметров кнопок
    //
    void setButtons(QPushButton *&button, const QSize &size, const QString &str);
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private slots:
    void startGameClicked();
    void settingsClicked();
    void exitClicked();
};
#endif // MAINMENU_H
