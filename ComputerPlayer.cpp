#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(QObject *parent) : QObject(parent),
                                                  status(Search)
{

}

QPair<int, int> ComputerPlayer::Shooting() {
    QPair<int, int> field_coordinate;
    std::random_device rd;
    std::mt19937 mersenne(rd());

    if (status == Search) {
        do {
        field_coordinate.first = mersenne() % 10;
        field_coordinate.second = mersenne() % 10;
        } while (!coordinates_destroyeded_fields.contains(field_coordinate));


    }
    else if (status == SearchNextField) {

    }
    else if (status == Finish) {

    }

    coordinates_destroyeded_fields.push_back(field_coordinate);
    return field_coordinate;
}
