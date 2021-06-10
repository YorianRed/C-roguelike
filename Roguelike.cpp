// Chiara B).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "entity.h"
#include <cstdlib>

using namespace std;

bool gameOver = false;
int const WIDTH = 90;
int const HEIGHT = 20;
int x, y;
char lastKey;
int hp, atk;
int dhp, datk, dx, dy;
int coinTurn = 1;

void flip() // Flips coin
{
    coinTurn *= -1;
}

void Setup()
{
    hp = 20;    // Player values
    atk = 2;
    x = 10;
    y = 10;

    dhp = 10;   // Dummy values
    datk = 2;
    dx = 18;
    dy = 18;

    entity dummy;
}

void Draw()
{
    system("cls");  // Screen clear

    for (int i = 0; i < WIDTH; i++) // Top frame
        cout << "#";

    cout << endl;

    for (int i = 1; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0 || j == WIDTH - 1)   // Middle frame
                cout << "#";

            else if (j == x && i == y)       // Player character    
            {
                cout << "@";
            }
            else if (j == dx && i == dy)    // Test Dummy
            {
                cout << "D";
            }
            else
                cout << " ";                // Empty space
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH; i++) // Bottom frame
        cout << "#";

    cout << endl;

    cout << "Player HP = " << hp << endl;
    cout << "Dummy HP = " << dhp << endl;
    cout << "Coin Turn: ";
    if (coinTurn == 1)
        cout << "Heads";
    else
        cout << "Tails";

}

void Input()
{
    if (_kbhit)
    {
        switch (_getch())   // Movement
        {
        case '5':   // Wait
            lastKey = '5';
            break;
        case '4':   // Left 
            x--;
            lastKey = '4';
            break;
        case '2':   // Down
            y++;
            lastKey = '2';
            break;
        case '8':   // Up
            y--;
            lastKey = '8';
            break;
        case '6':   // Right
            x++;
            lastKey = '6';
            break;
        case '1':   // Down Left
            x--;
            y++;
            lastKey = '1';
            break;
        case '7':   // Up Left
            x--;
            y--;
            lastKey = '7';
            break;
        case '9':   // Up Right
            x++;
            y--;
            lastKey = '9';
            break;
        case '3':   // Down Right
            x++;
            y++;
            lastKey = '3';
            break;
        case 'x':   // Close game
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    if (hp < 0) // Die
        gameOver = true;

    if (x == dx && y == dy) // Player-Enemy collision
    {
        switch (lastKey)
        {
        case '5':   // Wait
            break;
        case '4':   // Left 
            x++;
            dhp -= atk;
            break;
        case '2':   // Down
            y--;
            dhp -= atk;
            break;
        case '8':   // Up
            y++;
            dhp -= atk;
            break;
        case '6':   // Right
            x--;
            dhp -= atk;
            break;
        case '1':   // Down Left
            x++;
            y--;
            dhp -= atk;
            break;
        case '7':   // Up Left
            x++;
            y++;
            dhp -= atk;
            break;
        case '9':   // Up Right
            x--;
            y++;
            dhp -= atk;
            break;
        case '3':   // Down Right
            x--;
            y--;
            dhp -= atk;
            break;
        }

    }



    if (dhp <= 0)   // "Despawn" enemy
    {
        dx = -1;
        dy = -1;
    }

    if (x == dx - 1 || x == dx + 1)   // Take damage if within one tile of enemy AND coin is "tails"
        if (y == dy - 1 || y == dy + 1)
            if (coinTurn == -1)
                hp -= datk;

    flip(); // Flip coin

    if (x == WIDTH || x == 0 || y == HEIGHT || y == 0)  // Boundaries
        gameOver = true;

    if (dhp > 0)
    {
        if (coinTurn < 0)
        {
            if (!(dx == x && dy == y))
            {
                if (abs(x - dx) > abs(y - dy))
                    if (x > dx)
                        dx++;
                    else
                        dx--;
                else if (abs(x - dx) < abs(y - dy))
                    if (y > dy)
                        dy++;
                    else
                        dy--;
                else
                    if (abs(x - dx) % 2 == 0)
                        if (x > dx)
                            dx++;
                        else
                            dx--;
                    else
                        if (y > dy)
                            dy++;
                        else
                            dy--;
            }
        }
    }
}

int main()
{
    Setup();
    while (!gameOver)   // Main Game Loop
    {
        Draw();
        Input();
        Logic();
        Sleep(10);
    }
}