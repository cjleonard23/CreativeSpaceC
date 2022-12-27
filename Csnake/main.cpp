/**
 * @ Author: cjleoanrd23
 * @ Create Time: 2022-12-26 14:27:57
 * @ Modified by: cjleonard23
 * @ Modified time: 2022-12-27 14:45:09
 * @ Description: This is the main source code for snake in C++
 */

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;

//gameboard dimensions
const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
int tailX[100], tailY[100];
int nTail;
eDirection dir;


void Setup()
{
    gameOver = false;
    dir = STOP;

    //snake head centered at start of game
    x = width / 2;
    y = height / 3;

    //fruit placed at a random placement
    fruitX = rand() % width;
    fruitY = rand() % height;

    score = 0;
}
void Draw()
{
    system("cls");

    cout << "Snake in CMD Terminal"<< endl;
    cout << "Fruit = X, Head of Snake = O, Tail Pieces = o" << endl;
    //top border
    for(int i = 0; i<width+2; i++)
        cout << "#";
    cout << endl;

    //print map
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if ( i == fruitY && j == fruitX)
                cout << "X";
            else
            {
                
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j== width -1)
                cout << "#";
        }
        cout << endl;
    }

    //bottom border
    for(int i = 0; i<width+2; i++)
        cout << "#";
    cout << endl;

    //score counter at bottom of screen
    cout << "Score: " << score << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch(_getch())
        {
            case 'a':
                dir =  LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}
void Logic()
{
    
    //tail logic
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir)
    {      
        // keybaord logic
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if (x > width || x < 0 || y > height || y < 0)
        gameOver = true;
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] ==y)
            gameOver = true;
    }
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        
        //fruit placed at a random placement
        fruitX = rand() % width;
        fruitY = rand() % height;

        nTail++;
    }
}

int main()
{
    Setup();
    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(5);
    }
    return 0;
}
