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
    QLabel *resultLabel;
    QPushButton *exitButton;
    QPushButton *retryGameButton;
    QPushButton *continueGameButton;
    QVBoxLayout *mainLayout;

public:
    explicit GameMenu(const QString & result_information, QWidget *parent = nullptr);
    //explicit GameMenu(QWidget *parent = nullptr);
    ~GameMenu() override;

    QPushButton*& getButtonExit();
    QPushButton*& getButtonRetryGame();

    void setResultMenuStyle(const QString &);

private slots:
    void slotContinueClicked();
};

#endif // RESULTMENU_H
