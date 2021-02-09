#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <QObject>
#include <ctime>
#include <random>

class ComputerPlayer : public QObject
{
    Q_OBJECT

private:
    QVector<QPair<int, int>> coordinatesDestroyededFields;
    QVector<QPair<int, int>> possibleFieldsWithShipsPart;
    QVector<QPair<int, int>> coordinatesInjuredShipFields;
    int dx;
    int dy;

    //
    // Состояние компьютера во время игры
    //
    enum class PlayerStatus {
        Search,                    //1
        SearchNextField,           //2
        Finish,                    //3
        FinishRemainingShipPart    //4
    };
    PlayerStatus status;

    //
    // Поиск частей корабля
    //
    void findPossibleFieldsWithShipsParts();
    void searchShip(QPair<int, int> &);

    //
    // Поиск следующей части корабля после ранения
    //
    void searchNextField(QPair<int, int> &);

    //
    // Добивание корабля
    //
    void finishShip(QPair<int, int> &);

    //
    //
    //
    void finishRemainingShipPart(QPair<int, int> &);

public:
    explicit ComputerPlayer(QObject *parent = nullptr);

    QPair<int, int> Shooting();
    void setPlayerStatus(int);
    int getPlayerStatus() const;
    void addDestroyededFields(const QVector<QPair<int, int>> &);
};

#endif // COMPUTERPLAYER_H
