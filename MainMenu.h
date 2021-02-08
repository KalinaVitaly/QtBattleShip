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
    QPixmap *background_ships;
    QPushButton *start_game;
    QPushButton *settings;
    QPushButton *exit;
    QLabel *game_name;
    QVBoxLayout *layout;

    void setButtons(QPushButton *&button, const QSize &size, const QString &str);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void startGameClicked();
    void settingsClicked();
    void exitClicked();
};
#endif // MAINMENU_H
