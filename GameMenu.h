#ifndef RESULTMENU_H
#define RESULTMENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class GameMenu : public QWidget
{
    Q_OBJECT

private:
    QLabel *label_result;
    QPushButton *button_exit;
    QPushButton *button_retry_game;
    QPushButton *continue_game;
    QVBoxLayout *vertical_layout;

public:
    explicit GameMenu(const QString & result_information, QWidget *parent = nullptr);
    //explicit GameMenu(QWidget *parent = nullptr);
    ~GameMenu();

    QPushButton*& getButtonExit();
    QPushButton*& getButtonRetryGame();

    void setResultMenuStyle(const QString &);

signals:

private slots:

};

#endif // RESULTMENU_H
