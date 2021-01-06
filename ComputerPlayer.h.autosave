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
    QVector<QPair<int, int>> possible_fields_with_ships_part;
    QVector<QPair<int, int>> coordinates_injured_ship_fields;
    int dx;
    int dy;
    enum class PlayerStatus {
        Search,              //1
        SearchNextField,     //2
        Finish,              //3
        FinishAnotherPart    //4
    };
    PlayerStatus status;

    void  findPossibleFieldsWithShipsParts();

public:
    explicit ComputerPlayer(QObject *parent = nullptr);

    QPair<int, int> Shooting();
    void setPlayerStatus(int);
    int getPlayerStatus() const;

signals:

};

#endif // COMPUTERPLAYER_H
