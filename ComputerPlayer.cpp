#include "ComputerPlayer.h"
#include <QDebug>

ComputerPlayer::ComputerPlayer(QObject *parent) : QObject(parent),
                                                  status(PlayerStatus::Search)
{

}

void ComputerPlayer::setPlayerStatus(int _status) {
    if (_status == 1)
        status = PlayerStatus::Search;
    else if (_status == 2)
        status = PlayerStatus::SearchNextField;
    else if (_status == 3)
        status = PlayerStatus::Finish;
}

QPair<int, int> ComputerPlayer::Shooting() {
    QPair<int, int> field_coordinate;
    std::random_device rd;
    std::mt19937 mersenne(rd());

    if (status == PlayerStatus::Search) {
        do {
            field_coordinate.first = mersenne() % 10;
            field_coordinate.second = mersenne() % 10;
//            field_coordinate.first = 2;
//            field_coordinate.second = 2;
        } while (coordinates_shooting_fields.contains(field_coordinate));
    }
    else if (status == PlayerStatus::SearchNextField) {

    }
    else if (status == PlayerStatus::Finish) {

    }

    coordinates_shooting_fields.push_back(field_coordinate);
    qDebug() << "Normal";
    return field_coordinate;
}
