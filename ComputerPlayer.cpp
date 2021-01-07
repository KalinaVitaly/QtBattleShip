#include "ComputerPlayer.h"
#include <QDebug>

ComputerPlayer::ComputerPlayer(QObject *parent) : QObject(parent),
                                                  status(PlayerStatus::Search) {}

int ComputerPlayer::getPlayerStatus() const {
    if (status == PlayerStatus::Search) {
        return 1;
    }
    else if (status == PlayerStatus::SearchNextField) {
        return 2;
    }
    else if (status == PlayerStatus::Finish) {
        return 3;
    }
    else if (status == PlayerStatus::FinishRemainingShipPart) {
        return 4;
    }
    return -1;
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
//    for (auto i : possible_fields_with_ships_part)
//        qDebug() << "Coordinates possible fields: " << i.first << " " << i.second;
}

void ComputerPlayer::setPlayerStatus(int _status) {
    if (_status == 1) {
        status = PlayerStatus::Search;
        qDebug() << "PlayerStatus::Search";
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
    else if (_status == 4) {
        status = PlayerStatus::FinishRemainingShipPart;
        dx = -dx;
        dy = -dy;
        qDebug() << "PlayerStatus::FinishAnotherPart";
    }
}

void ComputerPlayer::addDestroyededFields(const QVector<QPair<int, int>> & coordinates) {
    coordinates_destroyeded_fields.append(coordinates);
}

void ComputerPlayer::searchShip(QPair<int, int> & field_coordinate) {
    coordinates_injured_ship_fields.clear();
    std::random_device rd;
    std::mt19937 mersenne(rd());
    do {
        field_coordinate.first = mersenne() % 10;
        field_coordinate.second = mersenne() % 10;
    } while (coordinates_destroyeded_fields.contains(field_coordinate));
}

void ComputerPlayer::searchNextField(QPair<int, int> & field_coordinate) {
    if (!coordinates_injured_ship_fields.size())
        coordinates_injured_ship_fields.push_back(coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1]);

    if (possible_fields_with_ships_part.size() - 1 >= 0) {
        //проверка ограждает от проблемы если корабль был ранен в середину
        field_coordinate.first = possible_fields_with_ships_part[possible_fields_with_ships_part.size() - 1].first;
        field_coordinate.second = possible_fields_with_ships_part[possible_fields_with_ships_part.size() - 1].second;
        possible_fields_with_ships_part.remove(possible_fields_with_ships_part.size() - 1);
    }
}

void ComputerPlayer::finishShip(QPair<int, int> & field_coordinate) {
    if (coordinates_injured_ship_fields.size() == 1) {
        coordinates_injured_ship_fields.push_back(coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1]);

        dx = coordinates_injured_ship_fields[coordinates_injured_ship_fields.size() - 1].first -
                coordinates_injured_ship_fields[coordinates_injured_ship_fields.size() - 2].first;
        dy = coordinates_injured_ship_fields[coordinates_injured_ship_fields.size() - 1].second -
                coordinates_injured_ship_fields[coordinates_injured_ship_fields.size() - 2].second;

        qDebug() << "dX = " << dx << " dY = " << dy;
    }

    if (coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].first + dx >= 0 &&
            coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].first + dx < 10 &&
            coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].second + dy >= 0 &&
            coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].second + dy < 10) {
        field_coordinate.first = coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].first + dx;
        field_coordinate.second = coordinates_destroyeded_fields[coordinates_destroyeded_fields.size() - 1].second + dy;
    }
}

void ComputerPlayer::finishRemainingShipPart(QPair<int, int> & field_coordinate) {
    if (coordinates_injured_ship_fields[0].first + dx >= 0 &&
            coordinates_injured_ship_fields[0].first + dx < 10 &&
            coordinates_injured_ship_fields[0].second + dy >= 0 &&
            coordinates_injured_ship_fields[0].second + dy < 10) {
        field_coordinate.first = coordinates_injured_ship_fields[0].first + dx;
        field_coordinate.second = coordinates_injured_ship_fields[0].second + dy;

        coordinates_injured_ship_fields[0].first = coordinates_injured_ship_fields[0].first + dx;
        coordinates_injured_ship_fields[0].second = coordinates_injured_ship_fields[0].second + dy;
    }
}

QPair<int, int> ComputerPlayer::Shooting() {
    QPair<int, int> field_coordinate;

    if (status == PlayerStatus::Search) {
        searchShip(field_coordinate);
    }
    else if (status == PlayerStatus::SearchNextField) {
        searchNextField(field_coordinate);
    }
    else if (status == PlayerStatus::Finish) {
        finishShip(field_coordinate);
    }
    else if (status == PlayerStatus::FinishRemainingShipPart) {
        finishRemainingShipPart(field_coordinate);
    }

    coordinates_destroyeded_fields.push_back(field_coordinate);
    return field_coordinate;
}
