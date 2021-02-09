#include "ComputerPlayer.h"
#include <QDebug>

ComputerPlayer::ComputerPlayer(QObject *parent)
    : QObject(parent),
      status(PlayerStatus::Search) {}

int ComputerPlayer::getPlayerStatus() const {
    if (status == PlayerStatus::Search) {
        return 1;
    } else if (status == PlayerStatus::SearchNextField) {
        return 2;
    } else if (status == PlayerStatus::Finish) {
        return 3;
    } else if (status == PlayerStatus::FinishRemainingShipPart) {
        return 4;
    }
    return -1;
}

void  ComputerPlayer::findPossibleFieldsWithShipsParts() {
    possibleFieldsWithShipsPart.clear();

    if (coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].first - 1 >= 0 &&
            !coordinatesDestroyededFields.contains(
                QPair<int, int>(coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].first - 1,
                                coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].second))) {

        possibleFieldsWithShipsPart.push_back(QPair<int, int>(coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].first - 1,
                                                  coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].second));
    }

    if (coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].second - 1 >= 0 &&
            !coordinatesDestroyededFields.contains(
                QPair<int, int>(coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].first,
                                coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].second - 1))) {

        possibleFieldsWithShipsPart.push_back(QPair<int, int>(coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].first,
                                                  coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].second - 1));
    }

    if (coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].first + 1 <= 9 &&
            !coordinatesDestroyededFields.contains(
                QPair<int, int>(coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].first + 1,
                                coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].second))) {

        possibleFieldsWithShipsPart.push_back(QPair<int, int>(coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].first + 1,
                                                  coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].second));
    }

    if (coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].second + 1 <= 9 &&
            !coordinatesDestroyededFields.contains(
                QPair<int, int>(coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].first,
                                coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].second + 1))) {

        possibleFieldsWithShipsPart.push_back(QPair<int, int>(coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].first,
                                                  coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].second + 1));
    }
//    for (auto i : possible_fields_with_ships_part)
//        qDebug() << "Coordinates possible fields: " << i.first << " " << i.second;
}

void ComputerPlayer::setPlayerStatus(int _status) {
    if (_status == 1) {
        status = PlayerStatus::Search;
    } else if (_status == 2) {
        status = PlayerStatus::SearchNextField;
        findPossibleFieldsWithShipsParts();
    } else if (_status == 3) {
        status = PlayerStatus::Finish;
    } else if (_status == 4) {
        status = PlayerStatus::FinishRemainingShipPart;
        dx = -dx;
        dy = -dy;
    }
}

void ComputerPlayer::addDestroyededFields(const QVector<QPair<int, int>> & coordinates) {
    coordinatesDestroyededFields.append(coordinates);
}

void ComputerPlayer::searchShip(QPair<int, int> & field_coordinate) {
    coordinatesDestroyededFields.clear();
    std::random_device rd;
    std::mt19937 mersenne(rd());
    do {
        field_coordinate.first = mersenne() % 10;
        field_coordinate.second = mersenne() % 10;
    } while (coordinatesDestroyededFields.contains(field_coordinate));
}

void ComputerPlayer::searchNextField(QPair<int, int> & field_coordinate) {
    if (!coordinatesDestroyededFields.size())
        coordinatesDestroyededFields.push_back(coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1]);

    if (possibleFieldsWithShipsPart.size() - 1 >= 0) {
        //проверка ограждает от проблемы если корабль был ранен в середину
        field_coordinate.first = possibleFieldsWithShipsPart[possibleFieldsWithShipsPart.size() - 1].first;
        field_coordinate.second = possibleFieldsWithShipsPart[possibleFieldsWithShipsPart.size() - 1].second;
        possibleFieldsWithShipsPart.remove(possibleFieldsWithShipsPart.size() - 1);
    }
}

void ComputerPlayer::finishShip(QPair<int, int> & field_coordinate) {
    if (coordinatesInjuredShipFields.size() == 1) {
        coordinatesInjuredShipFields.push_back(coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1]);

        dx = coordinatesInjuredShipFields[coordinatesInjuredShipFields.size() - 1].first -
                coordinatesInjuredShipFields[coordinatesInjuredShipFields.size() - 2].first;
        dy = coordinatesInjuredShipFields[coordinatesInjuredShipFields.size() - 1].second -
                coordinatesInjuredShipFields[coordinatesInjuredShipFields.size() - 2].second;

    }

    if (coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].first + dx >= 0 &&
            coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].first + dx < 10 &&
            coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].second + dy >= 0 &&
            coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].second + dy < 10) {
        field_coordinate.first  = coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].first + dx;
        field_coordinate.second = coordinatesDestroyededFields[coordinatesDestroyededFields.size() - 1].second + dy;
    }
}

void ComputerPlayer::finishRemainingShipPart(QPair<int, int> & field_coordinate) {
    if (coordinatesInjuredShipFields[0].first + dx >= 0 &&
            coordinatesInjuredShipFields[0].first + dx < 10 &&
            coordinatesInjuredShipFields[0].second + dy >= 0 &&
            coordinatesInjuredShipFields[0].second + dy < 10) {
        field_coordinate.first  = coordinatesInjuredShipFields[0].first + dx;
        field_coordinate.second = coordinatesInjuredShipFields[0].second + dy;

        coordinatesInjuredShipFields[0].first  = coordinatesInjuredShipFields[0].first + dx;
        coordinatesInjuredShipFields[0].second = coordinatesInjuredShipFields[0].second + dy;
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

    coordinatesDestroyededFields.push_back(field_coordinate);
    return field_coordinate;
}
