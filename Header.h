#pragma once
#include <iostream>
#include <vector>
#include <utility>

#define TotalShipsCount 10


using namespace std;

enum class GamerType
{
    Random = 1,
    Optimal = 2,
    Interactive = 3
};

enum class ShipType
{
    TorpedoBoat = 1,
    Destroyer = 2,
    Cruiser = 3,
    BattleShip = 4
};
enum class PointState
{
    Empty = 0,
    Ship = 1,
    Hit = 2,
    Miss = 3,
    Destroyed = 4
};

class Point
{
public:
    int x;
    int y;

    Point();

    Point& operator = (const Point other);      

};

class Gamer
{
    friend class Referee;
protected:
    bool HitOnPreviousTurn = false;

    bool ShipWasDestroyedOnPreviousTurn = false;

    vector<vector<PointState>> field;

    bool IsCorrectShip(Point point, bool horizontal, ShipType type);

    void SetShip(Point point, bool horizontal, ShipType type);

    void FillField();

    void FillFieldRandom();
public:
    Gamer();

    void SetHitOnPreviousTurn(bool val);

    void SetDestroyShipOnPreviousTurn(bool val);

    static shared_ptr<Gamer> MakeGamer(GamerType type);

    virtual Point NextTurn() = 0;

    virtual ~Gamer()
    {

    };
};

class ConsoleGamer : public Gamer
{
public:
    Point NextTurn() override;

    ConsoleGamer();
};

class RandomGamer : public Gamer
{
public:
    Point NextTurn() override;

    RandomGamer();
};

class OptimalGamer :public Gamer
{
private:
    int HitDirection = 0;

    vector<Point> HitPoints;

    Point point;

    Point RandomTurn();
public:
    Point NextTurn() override;

    OptimalGamer();
};

class Referee
{
private:
    vector<vector<PointState>> FirstGamerField;

    vector<vector<PointState>> SecondGamerField;

    size_t FirstGamerShipsDestroyedCount;

    size_t SecondGamerShipsDestroyedCount;
public:
    Referee(shared_ptr<Gamer> FirstGamer, shared_ptr<Gamer> SecondGamer);

    void IncGamerDestroyed(bool isFirst);

    bool IsCorrectField(vector<vector<PointState>> field);

    bool IsCorrectTurn(Point point, bool isFirst);

    PointState Step(Point point, bool isFirst);

    friend void play(int rounds, GamerType FirstGamerType, GamerType SecondGamerType);
};

void play(int rounds, GamerType FirstGamerType, GamerType SecondGamerType);
