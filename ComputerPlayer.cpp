#include "ComputerPlayer.h"
#include <QDebug>

ComputerPlayer::ComputerPlayer(QObject *parent) : QObject(parent),
                                                  status(PlayerStatus::Search)
{

}

void  ComputerPlayer::findPossibleFieldsWithShipsParts() {
    possible_fields_with_ships_part.clear();

    if (coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].first - 1 >= 0 &&
            !coordinates_destroyeded_fields.contains(
                QPair<int, int>(coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].first - 1,
                                coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].second))) {

        possible_fields_with_ships_part.push_back(QPair<int, int>(coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].first - 1,
                                                  coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].second));
    }

    if (coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].second - 1 >= 0 &&
            !coordinates_destroyeded_fields.contains(
                QPair<int, int>(coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].first,
                                coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].second - 1))) {

        possible_fields_with_ships_part.push_back(QPair<int, int>(coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].first,
                                                  coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].second - 1));
    }

    if (coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].first + 1 <= 9 &&
            !coordinates_destroyeded_fields.contains(
                QPair<int, int>(coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].first + 1,
                                coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].second))) {

        possible_fields_with_ships_part.push_back(QPair<int, int>(coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].first + 1,
                                                  coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].second));
    }

    if (coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].second + 1 <= 9 &&
            !coordinates_destroyeded_fields.contains(
                QPair<int, int>(coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].first,
                                coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].second + 1))) {

        possible_fields_with_ships_part.push_back(QPair<int, int>(coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].first,
                                                  coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].second + 1));
    }
    for (auto i : possible_fields_with_ships_part)
        qDebug() << "Coordinates possible fields: " << i.first << " " << i.second;
}

void ComputerPlayer::setPlayerStatus(int _status) {
    if (_status == 1) {
        status = PlayerStatus::Search;
    }
    else if (_status == 2) {
        status = PlayerStatus::SearchNextField;
        findPossibleFieldsWithShipsParts();
        qDebug() << "PlayerStatus::SearchNextField";
    }
    else if (_status == 3) {
        status = PlayerStatus::Finish;
        qDebug() << "PlayerStatus::Finish";
    }
}

QPair<int, int> ComputerPlayer::Shooting() {
    QPair<int, int> field_coordinate;
    std::random_device rd;
    std::mt19937 mersenne(rd());

    if (status == PlayerStatus::Search) {
        do {
            field_coordinate.first = mersenne() % 10;
            field_coordinate.second = mersenne() % 10;
        } while (coordinates_destroyeded_fields.contains(field_coordinate));
    }
    else if (status == PlayerStatus::SearchNextField) {
        field_coordinate.first = possible_fields_with_ships_part[possible_fields_with_ships_part.size() - 1].first;
        field_coordinate.second = possible_fields_with_ships_part[possible_fields_with_ships_part.size() - 1].second;
        possible_fields_with_ships_part.remove(possible_fields_with_ships_part.size() - 1);
    }
    else if (status == PlayerStatus::Finish) {

    }

    coordinates_destroyeded_fields.push_back(field_coordinate);
    return field_coordinate;
}
