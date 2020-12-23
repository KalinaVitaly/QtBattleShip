#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <QObject>
#include <ctime>
#include <random>

class ComputerPlayer : public QObject
{
    Q_OBJECT

private:
    QVector<QPair<int, int>> coordinates_destroyeded_fields;
    enum PlayerStatus {
        Search,              //1
        SearchNextField,     //2
        Finish               //3
    };
    PlayerStatus status;


public:
    explicit ComputerPlayer(QObject *parent = nullptr);

    QPair<int, int> Shooting();
    void setPlayerStatus(int);

signals:

};

#endif // COMPUTERPLAYER_H
