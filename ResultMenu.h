#ifndef RESULTMENU_H
#define RESULTMENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class ResultMenu : public QWidget
{
    Q_OBJECT

private:
    QLabel *label_result;
    QPushButton *button_exit;
    QPushButton *button_retry_game;
    QVBoxLayout *vertical_layout;

    void connectButtons();

public:
    explicit ResultMenu(const QString & result_information, QWidget *parent = nullptr);

signals:

private slots:
    void exitButtonClicked();
    void retryButtonClicked();

};

#endif // RESULTMENU_H
