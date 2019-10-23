#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>

using namespace std;

const int SnakeMovePeriod = 5;

const int width = 20;
const int length = 20;
bool Game;

struct Snake
{
	int x, y;
}fruit, S[1000];
int nTail, scor, SnakeMoveCounter;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void Start()
{
	SnakeMoveCounter = scor = 0;

	nTail = 0;
	S[nTail].x = length / 2;
	S[nTail].y = width / 2;

	fruit.x = rand() % length;
	fruit.y = rand() % width;

	Game = true;
	srand (time(NULL));
}

void Draw()
{
	system("cls");
	for (int i = 0 ; i <= length ; i++)
	{
		for (int j = 0 ; j <= width ; j++)
		{
			if (fruit.x == i && fruit.y == j)
				cout << '*';
			else
			{

				bool print = false;
				for (int k = 0; k <= nTail; k++)
					if (S[k].x == i && S[k].y == j)
					{
						cout << 'o';
						print = true;
						break;
					}

				if (print == false)
				{
					if (j == 0 || j == width || i == 0 || i == length)
						cout << '#';
					else
						cout << ' ';
				}
			}
		}
		cout << '\n';
	}
	cout << "Score:" << scor;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;

		case 'w':
			dir = UP;
			break;

		case 'd':
			dir = RIGHT;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'p':
			dir = STOP;
			break;

		case 'o':
			Game = false;
			break;

		default:
			break;
		}
	}
}

void Move(int a, int b)
{
	S[0].x += a;
	S[0].y += b;
}

void Logic()
{
	int prevx, prevy, prevx2, prevy2,a,b;
	prevx = S[0].x;
	prevy = S[0].y;
	a = b = 0;

	switch (dir)
	{
	case LEFT:
		a = 0;
		b = -1;
		break;
	case UP:
		a = -1;
		b = 0;
		break;

	case RIGHT:
		a = 0;
		b = 1;
		break;

	case DOWN:
		a = 1;
		b = 0;
		break;

	default:
		break;
	}

	if (++SnakeMoveCounter >= SnakeMovePeriod)
	{
		SnakeMoveCounter = 0;
		Move(a, b);
		for (int k = 1; k <= nTail; k++)
		{
			prevx2 = S[k].x;
			prevy2 = S[k].y;

			S[k].x = prevx;
			S[k].y = prevy;

			prevx = prevx2;
			prevy = prevy2;
		}
	}

	if (S[0].x <= 0 || S[0].x >= length || S[0].y <= 0 || S[0].y >= width)
		Game = false;

	for (int k = 1; k <= nTail; k++)
		if (S[0].x == S[k].x && S[0].y == S[k].y)
			Game = false;

	if (S[0].x == fruit.x && S[0].y == fruit.y)
	{
		nTail++;
		scor += 10;

		bool ok = false;
		while (ok == false)
		{
			ok = true;
			fruit.x = rand() % length;
			fruit.y = rand() % width;

			if (fruit.x == 0 || fruit.y == 0)
			{
				ok = false;
				continue;
			}
			for (int k = 0; k <= nTail; k++)
				if (S[k].x == fruit.x && S[k].y == fruit.y)
				{
					ok = false;
					continue;
				}
		}
	}
}

int main()
{
	Start();
	while (Game == true)
	{
		Draw();
		Input();
		Logic();
	}
	system("cls");
	cout << "GAME OVER !!!!\n";
	return 0;
}
