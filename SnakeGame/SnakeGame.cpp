// einfaches Snake Spiel

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
enum level {
    EASY = 40, MEDIUM = 20, HARD = 0
};
level lev;

void setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}
void draw() {
    
    system("cls");
    cout << "Score:" << score << endl;
    for (int i = 0; i < width+1; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height+1; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "|";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
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
                if(!print)
                    cout << " ";
            }
               
            if (j == width - 1)
                cout << "|";
        }
        cout << endl;
    }

    for (int i = 0; i < width+1; i++)
        cout << "-";
    cout << endl;
}
void input() {
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
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
void logic() {
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
    switch (dir) {
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
    for (int i = 1; i < nTail; i++)
    {
        if (tailX[0] == tailX[i] && tailY[0] == tailY[i])
            gameOver = true;
    }
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        nTail++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }

}
int main()
{ 
    bool playAgain = 1;
    while(playAgain == 1){
    cout << "Difficulty? (e,m or h):" << endl;
    switch (_getch())
    {
    case 'e':
        lev = EASY;
        break;
    case 'm':
        lev = MEDIUM;
        break;
    case 'h':
        lev = HARD;
        break;
    default:
        lev = EASY;
        break;
    }
        setup();
        while (!gameOver) {
            draw();
            input();
            logic();
            switch (lev) {
            case EASY:
                Sleep(EASY);
                break;
            case MEDIUM:
                Sleep(MEDIUM);
                break;
            case HARD:
                break;
            }
            Sleep(10);
        }
        Sleep(500);
        cout << "Game Over" << endl << "Score: " << score << endl << "Play Again? (y,n)" << endl;
        Sleep(100);
        stillPlaying:
        if (char again = _getch() == 'n')
            playAgain = 0;
        else if (again == 'y')
            playAgain = 1;
        else
            goto stillPlaying;
        }
    return 0;
}

