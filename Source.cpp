#include "Header.h"

Point::Point()
{
	this->x = 0;
	this->y = 0;
}

Point& Point::operator = (const Point other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

Gamer::Gamer()
{
	this->field.resize(10);
	for (int i = 0; i < field.size(); i++)
	{
		field[i].resize(10, PointState::Empty);
	}
}
bool Gamer::IsCorrectShip(Point point, bool horizontal, ShipType type)
{
	if (point.x > 9 || point.y > 9 || point.x < 0 || point.y < 0)
	{
		return false;
	}
	for (size_t i = 0; i < (int)type; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (point.y + j <= 9 && point.y + j >= 0)
			{
				for (int m = -1; m < 2; m++)
				{
					if (point.x + m <= 9 && point.x + m >= 0 && field[point.y + j][point.x + m] != PointState::Empty)
					{
						return false;
					}
				}
			}
		}
		if (horizontal)
		{
			point.x++;
		}
		else
		{
			point.y++;
		}

		if (point.x > 9 || point.y > 9)
		{
			return false;
		}

	}
	return true;
}

void Gamer::SetShip(Point point, bool horizontal, ShipType Type)
{
	if (horizontal)
		for (int i = 0; i < (int)Type; i++)
		{
			field[point.y][point.x + i] = PointState::Ship;
		}

	else
		for (int i = 0; i < (int)Type; i++)
		{
			field[point.y + i][point.x] = PointState::Ship;
		}
}

void Gamer::SetHitOnPreviousTurn(bool value)
{
	HitOnPreviousTurn = value;
}

void Gamer::SetDestroyShipOnPreviousTurn(bool value)
{
	ShipWasDestroyedOnPreviousTurn = value;
}

shared_ptr<Gamer> Gamer::MakeGamer(GamerType type)
{
	if (type == GamerType::Random)
	{
		return make_shared<RandomGamer>();
	}
	else if (type == GamerType::Optimal)
	{
		return make_shared<OptimalGamer>();
	}
	else
	{
		return make_shared<ConsoleGamer>();
	}
}
void Gamer::FillFieldRandom()
{
	bool IsHorizontal;
	Point point;
	do
	{
		IsHorizontal = (rand() % 2);
		point.x = rand() % 10;
		point.y = rand() % 10;
	} while (!IsCorrectShip(point, IsHorizontal, ShipType::BattleShip));
	SetShip(point, IsHorizontal, ShipType::BattleShip);

	for (int i = 0; i < 2; ++i)
	{
		do
		{
			IsHorizontal = (rand() % 2);
			point.x = rand() % 10;
			point.y = rand() % 10;
		} while (!IsCorrectShip(point, IsHorizontal, ShipType::Cruiser));
		SetShip(point, IsHorizontal, ShipType::Cruiser);
	}
	for (int i = 0; i < 3; ++i)
	{
		do
		{
			IsHorizontal = (rand() % 2);
			point.x = rand() % 10;
			point.y = rand() % 10;
		} while (!IsCorrectShip(point, IsHorizontal, ShipType::Destroyer));
		SetShip(point, IsHorizontal, ShipType::Destroyer);
	}
	for (int i = 0; i < 4; ++i)
	{
		do
		{
			IsHorizontal = (rand() % 2);
			point.x = rand() % 10;
			point.y = rand() % 10;
		} while (!IsCorrectShip(point, IsHorizontal, ShipType::TorpedoBoat));
		SetShip(point, IsHorizontal, ShipType::TorpedoBoat);
	}
}

void Gamer::FillField()
{
	bool IsHorizontal;
	Point point;
	int BattleShipAttempts = 0;
	do
	{
		if (BattleShipAttempts > 0)
		{
			cout << "Bad data, try again" << endl;
		}

		cout << "Enter information about BattleShip (4 cage ship) (x, y, IsHorizontal(y/n) )";
		char symb;
		cin >> point.x >> point.y >> symb;
		IsHorizontal = false;
		if (symb == 'y')
		{
			IsHorizontal = true;
		}
		point.x--;
		point.y--;

		BattleShipAttempts++;

	} while (!IsCorrectShip(point, IsHorizontal, ShipType::BattleShip));

	SetShip(point, IsHorizontal, ShipType::BattleShip);

	for (int i = 0; i < 2; ++i)
	{
		int CruiserAttempts = 0;
		do
		{
			if (CruiserAttempts > 0)
			{
				cout << "Bad data, try again" << endl;
			}

			cout << "Enter information about #" << i + 1 << " Cruiser (3 cage ship) (x, y, IsHorizontal(y/n) )";
			char symb;
			cin >> point.x >> point.y >> symb;
			IsHorizontal = false;
			if (symb == 'y')
			{
				IsHorizontal = true;
			}
			point.x--;
			point.y--;

			CruiserAttempts++;


		} while (!IsCorrectShip(point, IsHorizontal, ShipType::Cruiser));

		SetShip(point, IsHorizontal, ShipType::Cruiser);
	}
	for (int i = 0; i < 3; ++i)
	{
		int DestroyerAttempts = 0;
		do
		{
			if (DestroyerAttempts > 0)
			{
				cout << "Bad data, try again" << endl;
			}

			cout << "Enter information about #" << i + 1 << " Destroyer (2 cage ship) (x, y, IsHorizontal(y/n) )";
			char symb;
			cin >> point.x >> point.y >> symb;
			IsHorizontal = false;
			if (symb == 'y')
			{
				IsHorizontal = true;
			}
			point.x--;
			point.y--;

			DestroyerAttempts++;


		} while (!IsCorrectShip(point, IsHorizontal, ShipType::Destroyer));

		SetShip(point, IsHorizontal, ShipType::Destroyer);
	}
	for (int i = 0; i < 4; ++i)
	{
		int TorpedoBoatAttempts = 0;
		do
		{
			if (TorpedoBoatAttempts > 0)
			{
				cout << "Bad data, try again" << endl;
			}

			cout << "Enter information about #" << i + 1 << " Torpedo boat (1 cage ship)  (x, y, IsHorizontal(y/n) )";
			char symb;
			cin >> point.x >> point.y >> symb;
			IsHorizontal = false;
			if (symb == 'y')
			{
				IsHorizontal = true;
			}
			point.x--;
			point.y--;

			TorpedoBoatAttempts++;

		} while (!IsCorrectShip(point, IsHorizontal, ShipType::TorpedoBoat));

		SetShip(point, IsHorizontal, ShipType::TorpedoBoat);
	}
}

Point ConsoleGamer::NextTurn()
{
	cout << "Enter hit coordinates (x y)" << endl;

	Point point;
	cin >> point.x >> point.y;
	point.x--;
	point.y--;

	return point;
}

ConsoleGamer::ConsoleGamer()
{
	string str;
	int attempts = 0;
	do
	{
		if (attempts > 0)
		{
			cout << "Bad data, try again" << endl;
		}
		cout << "Do you want to set the ships yourself or random? me/random \n";
		cin >> str;
		attempts++;
	} while (str != "me" && str != "random");

	if (str == "random")
	{
		FillFieldRandom();
	}

	else
	{
		FillField();
	}
}

Point RandomGamer::NextTurn()
{
	Point point;
	point.x = rand() % 10;
	point.y = rand() % 10;

	return point;
}

RandomGamer::RandomGamer()
{
	FillFieldRandom();
}

Point OptimalGamer::RandomTurn()
{
	point.x = rand() % 10;
	point.y = rand() % 10;
	return point;
}

Point OptimalGamer::NextTurn()
{
	if (!HitOnPreviousTurn && HitPoints.empty())
	{
		return RandomTurn();
	}
	else if (!HitOnPreviousTurn && !HitPoints.empty())
	{
		while (HitPoints.size() > 1)
		{
			HitPoints.pop_back();
		}
		HitDirection = (HitDirection + 1) % 4;
	}
	else if (ShipWasDestroyedOnPreviousTurn)
	{
		HitPoints.clear();
		HitDirection = 0;
		return RandomTurn();
	}
	else if (HitOnPreviousTurn)
	{
		HitPoints.push_back(point);
	}

	if (HitDirection == 0)
	{
		point.x = HitPoints[HitPoints.size() - 1].x + 1;
		point.y = HitPoints[HitPoints.size() - 1].y;
	}

	else if (HitDirection == 1)
	{
		point.x = HitPoints[HitPoints.size() - 1].x - 1;
		point.y = HitPoints[HitPoints.size() - 1].y;
	}

	else if (HitDirection == 2)
	{
		point.x = HitPoints[HitPoints.size() - 1].x;
		point.y = HitPoints[HitPoints.size() - 1].y + 1;
	}
	if (HitDirection == 4)
	{
		point.x = HitPoints[HitPoints.size() - 1].x;
		point.y = HitPoints[HitPoints.size() - 1].y - 1;
	}

	return point;
}

OptimalGamer::OptimalGamer()
{
	FillFieldRandom();
}

Referee::Referee(shared_ptr<Gamer> FirstGamer, shared_ptr<Gamer> SecondGamer)
{
	this->FirstGamerShipsDestroyedCount = 0;
	this->SecondGamerShipsDestroyedCount = 0;

	this->FirstGamerField = FirstGamer->field;
	this->SecondGamerField = SecondGamer->field;


	if (!IsCorrectField(FirstGamerField) || !IsCorrectField(SecondGamerField))
	{
		throw("Invalid field");
	}
}

bool Referee::IsCorrectField(vector<vector<PointState>> field)
{
	size_t EmptyPointsCount = 0;
	size_t ShipsCount[4] = { 0 };

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (field[i][j] == PointState::Ship)
			{
				if (!(i - 1 >= 0 && field[i - 1][j] == PointState::Ship) && !(j - 1 >= 0 && field[i][j - 1] == PointState::Ship))
				{
					size_t length = 1,
						stepY = 0,
						stepX = 0;
					if (i + 1 < 10 && field[i + 1][j] == PointState::Ship)
						stepY = 1;
					else
						stepX = 1;
					while (i + stepY < 10 && j + stepX < 10 && field[i + stepY][j + stepX] == PointState::Ship)
					{
						length++;
						stepY ? stepY++ : stepX++;
					}

					if (length > 0 && length < 5)
					{
						ShipsCount[length - 1]++;
					}
					else
						return false;
				}
			}
			else
			{
				EmptyPointsCount++;
			}
		}
	}
	if ((ShipsCount[3] == 1) && (ShipsCount[2] == 2) && (ShipsCount[1] == 3) && (ShipsCount[0] == 4) &&
		EmptyPointsCount == (100 - 4 - 3 * 2 - 2 * 3 - 4))
	{
		return true;
	}

	return false;
}

bool Referee::IsCorrectTurn(Point point, bool isFirst)
{
	if (point.x < 0 || point.y < 0 || point.x > 9 || point.y > 9)
	{
		return false;
	}

	if (isFirst)
	{
		if (SecondGamerField[point.y][point.x] != PointState::Empty && SecondGamerField[point.y][point.x] != PointState::Ship)
		{
			return false;
		}
	}
	else
	{
		if (FirstGamerField[point.y][point.x] != PointState::Empty && FirstGamerField[point.y][point.x] != PointState::Ship)
		{
			return false;
		}
	}

	return true;
}

PointState Referee::Step(Point point, bool isFirst)
{
	if (isFirst)
	{
		if (SecondGamerField[point.y][point.x] == PointState::Empty)
		{
			SecondGamerField[point.y][point.x] = PointState::Miss;
			{
				return PointState::Miss;
			}
		}
		if (SecondGamerField[point.y][point.x] == PointState::Ship)
		{

			SecondGamerField[point.y][point.x] = PointState::Hit;

			int i = 1;
			for(int i = 1; point.y - i >= 0 && SecondGamerField[point.y - i][point.x] != PointState::Empty; i++)
			{
				if (SecondGamerField[point.y - i][point.x] == PointState::Ship)
				{
					return PointState::Hit;
				}
				i++;
			}

			for (int i = 1; point.y + i < 10 && SecondGamerField[point.y + i][point.x] != PointState::Empty; i++)
			{
				if (SecondGamerField[point.y + i][point.x] == PointState::Ship)
				{
					return PointState::Hit;
				}
			}

			for (int i = 1; point.x - i > -1 && SecondGamerField[point.y][point.x - i] != PointState::Empty; i++)
			{
				if (SecondGamerField[point.y][point.x - i] == PointState::Ship)
				{
					return PointState::Hit;
				}
			}

			for (int i = 1; point.x + i < 10 && SecondGamerField[point.y][point.x + i] != PointState::Empty; i++)
			{
				if (SecondGamerField[point.y][point.x + i] == PointState::Ship)
				{
					return PointState::Hit;
				}
			}

			int TurnY = 0;
			int	TurnX = 0;

			if (point.y - 1 >= 0 && SecondGamerField[point.y - 1][point.x] == PointState::Hit)
			{
				TurnY = -1;
			}
			else if (point.y + 1 < 10 && SecondGamerField[point.y + 1][point.x] == PointState::Hit)
			{
				TurnY = 1;
			}
			else if (point.x - 1 >= 0 && SecondGamerField[point.y][point.x - 1] == PointState::Hit)
			{
				TurnX = -1;
			}
			else if (point.x + 1 < 10 && SecondGamerField[point.y][point.x + 1] == PointState::Hit)
			{
				TurnX = 1;
			}

			do
			{
				for (int i = -1; i < 2; i++)
				{
					if (point.y + i < 10 && point.y + i >= 0)
					{
						for (int j = -1; j < 2; j++)
						{
							if (point.x + j < 10 && point.x + j >= 0 &&
								SecondGamerField[point.y + i][point.x + j] == PointState::Empty)
							{
								SecondGamerField[point.y + i][point.x + j] = PointState::Miss;
							}
						}
					}
				}
				point.y += TurnY;
				point.x += TurnX;
			} while ((TurnY != 0 || TurnX != 0) && point.y < 10 && point.x < 10 &&
				point.y >= 0 && point.x >= 0 && SecondGamerField[point.y][point.x] == PointState::Hit);

			return PointState::Destroyed;
		}
	}
	else
	{
		if (FirstGamerField[point.y][point.x] == PointState::Empty)
		{
			FirstGamerField[point.y][point.x] = PointState::Miss;
			{
				return PointState::Miss;
			}
		}
		if (FirstGamerField[point.y][point.x] == PointState::Ship)
		{
			FirstGamerField[point.y][point.x] = PointState::Hit;

			int i = 1;
			for (int i = 1; point.y - i >= 0 && FirstGamerField[point.y - i][point.x] != PointState::Empty; i++)
			{
				if (FirstGamerField[point.y - i][point.x] == PointState::Ship)
				{
					return PointState::Hit;
				}
				i++;
			}

			for (int i = 1; point.y + i < 10 && FirstGamerField[point.y + i][point.x] != PointState::Empty; i++)
			{
				if (FirstGamerField[point.y + i][point.x] == PointState::Ship)
				{
					return PointState::Hit;
				}
			}

			for (int i = 1; point.x - i > -1 && FirstGamerField[point.y][point.x - i] != PointState::Empty; i++)
			{
				if (FirstGamerField[point.y][point.x - i] == PointState::Ship)
				{
					return PointState::Hit;
				}
			}

			for (int i = 1; point.x + i < 10 && FirstGamerField[point.y][point.x + i] != PointState::Empty; i++)
			{
				if (FirstGamerField[point.y][point.x + i] == PointState::Ship)
				{
					return PointState::Hit;
				}
			}

			int TurnY = 0;
			int	TurnX = 0;

			if (point.y - 1 >= 0 && FirstGamerField[point.y - 1][point.x] == PointState::Hit)
			{
				TurnY = -1;
			}
			else if (point.y + 1 < 10 && FirstGamerField[point.y + 1][point.x] == PointState::Hit)
			{
				TurnY = 1;
			}
			else if (point.x - 1 >= 0 && FirstGamerField[point.y][point.x - 1] == PointState::Hit)
			{
				TurnX = -1;
			}
			else if (point.x + 1 < 10 && FirstGamerField[point.y][point.x + 1] == PointState::Hit)
			{
				TurnX = 1;
			}

			do
			{
				for (int i = -1; i < 2; i++)
				{
					if (point.y + i < 10 && point.y + i >= 0)
					{
						for (int j = -1; j < 2; j++)
						{
							if (point.x + j < 10 && point.x + j >= 0 &&
								FirstGamerField[point.y + i][point.x + j] == PointState::Empty)
							{
								FirstGamerField[point.y + i][point.x + j] = PointState::Miss;
							}
						}
					}
				}
				point.y += TurnY;
				point.x += TurnX;
			} while ((TurnY != 0 || TurnX != 0) && point.y < 10 && point.x < 10 &&
				point.y >= 0 && point.x >= 0 && FirstGamerField[point.y][point.x] == PointState::Hit);

			return PointState::Destroyed;
		}
	}
}

void play(int rounds, GamerType FirstGamerType, GamerType SecondGamerType)
{
	srand(time(NULL));

	int FirstGamerRoundsCount = 0;
	int SecondGamerRoundsCount = 0;

	for (size_t i = 0; i < rounds; i++)
	{
		shared_ptr<Gamer> FirstGamer = Gamer::MakeGamer(FirstGamerType);
		shared_ptr<Gamer> SecondGamer = Gamer::MakeGamer(SecondGamerType);

		Referee Ref(FirstGamer, SecondGamer);

		bool IsFirstGamerTurn = 1;

		while (Ref.FirstGamerShipsDestroyedCount != TotalShipsCount && Ref.SecondGamerShipsDestroyedCount != TotalShipsCount)
		{
			Point turn;
			do
			{
				if (IsFirstGamerTurn)
				{
					turn = FirstGamer->NextTurn();
				}
				else
				{
					turn = SecondGamer->NextTurn();
				}		
			} while (!Ref.IsCorrectTurn(turn, IsFirstGamerTurn));

			switch (Ref.Step(turn, IsFirstGamerTurn))
			{
			case PointState::Miss:
				if (IsFirstGamerTurn)
				{
					FirstGamer->SetHitOnPreviousTurn(0);
					FirstGamer->SetDestroyShipOnPreviousTurn(0);
					cout << "First gamer missed" << endl;
				}
				else
				{
					SecondGamer->SetHitOnPreviousTurn(0);
					SecondGamer->SetDestroyShipOnPreviousTurn(0);
					cout << "Second gamer missed" << endl;
				}
				IsFirstGamerTurn = !IsFirstGamerTurn;
				break;
			case PointState::Hit:
				if (IsFirstGamerTurn)
				{
					FirstGamer->SetHitOnPreviousTurn(1);
					FirstGamer->SetDestroyShipOnPreviousTurn(0);
					cout << "First gamer damaged (" << turn.x + 1 << ";" << turn.y + 1 << ")" << endl;
				}
				
				else
				{
					SecondGamer->SetHitOnPreviousTurn(1);
					SecondGamer->SetDestroyShipOnPreviousTurn(0);
					cout << "Second gamer damaged (" << turn.x + 1 << ";" << turn.y + 1 << ")" << endl;
				}

				break;
			case PointState::Destroyed:
				if (IsFirstGamerTurn)
				{
					FirstGamer->SetHitOnPreviousTurn(1);
					FirstGamer->SetDestroyShipOnPreviousTurn(1);
					cout << "First gamer destroyed enemy ship" << endl;
					Ref.FirstGamerShipsDestroyedCount++;
				}
				else
				{
					SecondGamer->SetHitOnPreviousTurn(1);
					SecondGamer->SetDestroyShipOnPreviousTurn(1);
					cout << "Second gamer destroyed enemy ship" << endl;
					Ref.SecondGamerShipsDestroyedCount++;
				}
				break;
			}
		}

		if (Ref.FirstGamerShipsDestroyedCount == TotalShipsCount)
		{
			FirstGamerRoundsCount++;
		}
		else
		{
			SecondGamerRoundsCount++;
		}

		cout << "First gamer score: " << FirstGamerRoundsCount << endl;
		cout << "Second gamer score: " << SecondGamerRoundsCount << endl;
	}
	if (FirstGamerRoundsCount > SecondGamerRoundsCount)
	{
		cout << "The First gamer wins";
	}
	else if (FirstGamerRoundsCount < SecondGamerRoundsCount)
	{
		cout << "The Second gamer wins";
	}
	else
	{
		cout << "Draw";
	}
}
