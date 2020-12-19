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
        Search,
        SearchNextField,
        Finish
    };
    PlayerStatus status;


public:
    explicit ComputerPlayer(QObject *parent = nullptr);

    QPair<int, int> Shooting();

signals:

};

#endif // COMPUTERPLAYER_H
