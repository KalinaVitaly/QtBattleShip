#include "ComputerPlayer.h"
#include <QDebug>

ComputerPlayer::ComputerPlayer(QObject *parent) : QObject(parent),
                                                  status(Search)
{

}

void ComputerPlayer::setPlayerStatus(int _status) {
    if (_status == 1)
        status = Search;
    else if (_status == 2)
        status = SearchNextField;
    else if (_status == 3)
        status = Finish;
}

QPair<int, int> ComputerPlayer::Shooting() {
    QPair<int, int> field_coordinate;
    std::random_device rd;
    std::mt19937 mersenne(rd());

    if (status == Search) {
        do {
//            field_coordinate.first = mersenne() % 10;
//            field_coordinate.second = mersenne() % 10;
            field_coordinate.first = 2;
            field_coordinate.second = 2;
        } while (coordinates_destroyeded_fields.contains(field_coordinate));


    }
    else if (status == SearchNextField) {

    }
    else if (status == Finish) {

    }

    coordinates_destroyeded_fields.push_back(field_coordinate);
    qDebug() << "Normal";
    return field_coordinate;
}
