#ifndef _MOVE_H_
#define _MOVE_H_
#include <iostream>
#include <windows.h>
#include <conio.h>

HANDLE hOnt = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Pos;
CONSOLE_SCREEN_BUFFER_INFO screenInfo;

char keystroke = '\0';

void GotoPos(int x, int y){
    Pos.X = x;
    Pos.Y = y;
    GetConsoleScreenBufferInfo(hOnt, &screenInfo);
    SetConsoleCursorPosition(hOnt, Pos);
}

void Move(){
    if(_getch() == CTRL){
        GotoPos(Pos.X, Pos.Y);
        std::cout << " ";
        keystroke = _getch();
        switch (keystroke) {
            case UP: {
                if(maze[Pos.Y - 1][Pos.X] != WALL)
                    Pos.Y--;
                break;
            }
            case DOWN: {
                if(maze[Pos.Y + 1][Pos.X] != WALL)
                    Pos.Y++;
                break;
            }
            case LEFT:{
                if(maze[Pos.Y][Pos.X - 1] != WALL)
                    Pos.X--;
                break;
            }
            case RIGHT:{
                if(maze[Pos.Y][Pos.X + 1] != WALL)
                    Pos.X++;
                break;
            }
            default:{
                system("cls");
                system("pause");
                exit(0);
            }
        }
        GotoPos(Pos.X, Pos.Y);
        std::cout << (char)0xa7 << (char)0xb0;
    }
    else{
        system("cls");
        system("pause");
        exit(0);
    }

}

#endif // _MOVE_H_