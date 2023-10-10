#ifndef _MOVE_H_
#define _MOVE_H_
#include <iostream>
#include <conio.h>
#include <windows.h>

HANDLE hOnt = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Pos;
CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;

char keystroke = '\0';

Point Check = Point(0, 0);

void GotoPos(int x, int y);
void Move();
bool CheckWin();

void GotoPos(int x, int y){
    Pos.X = x;
    Pos.Y = y;
    GetConsoleScreenBufferInfo(hOnt, &ScreenInfo);
    SetConsoleCursorPosition(hOnt, Pos);
    CONSOLE_CURSOR_INFO CursorInfo = {1, false};
    SetConsoleCursorInfo(hOnt, &CursorInfo);
}

void Move(){
    if(_getch() == CTRL){
        GotoPos(Pos.X, Pos.Y);
        if(Map[Pos.Y][Pos.X] == PATH || Map[Pos.Y][Pos.X] == PLAYER)
            std::cout << " ";
        else if(Map[Pos.Y][Pos.X] == END)
            std::cout << "x";
        keystroke = _getch();
        switch (keystroke) {
            case UP: {
                if(Map[Pos.Y - 1][Pos.X] != WALL){
                    if(Map[Pos.Y - 1][Pos.X] != BOX)
                        Pos.Y--;
                    else{
                        if(Map[Pos.Y - 2][Pos.X] != WALL && Map[Pos.Y - 2][Pos.X] != BOX){
                            Check = Point(Pos.Y - 1, Pos.X);
                            if(!CheckPoint(End, Check))
                                Map[Pos.Y - 1][Pos.X] = END;
                            else
                                Map[Pos.Y - 1][Pos.X] = PATH;
                            GotoPos(Pos.X, Pos.Y - 2);
                            if(Map[Pos.Y][Pos.X] == END)
                                std::cout << "*";
                            else
                                std::cout << "#";
                            Map[Pos.Y][Pos.X] = BOX;
                            Pos.Y++;
                        }
                    }
                }
                break;
            }
            case DOWN: {
                if(Map[Pos.Y + 1][Pos.X] != WALL){
                    if(Map[Pos.Y + 1][Pos.X] != BOX)
                        Pos.Y++;
                    else{
                        if(Map[Pos.Y + 2][Pos.X] != WALL && Map[Pos.Y + 2][Pos.X] != BOX){
                            Check = Point(Pos.Y + 1, Pos.X);
                            if(!CheckPoint(End, Check))
                                Map[Pos.Y + 1][Pos.X] = END;
                            else
                                Map[Pos.Y + 1][Pos.X] = PATH;
                            GotoPos(Pos.X, Pos.Y + 2);
                            if(Map[Pos.Y][Pos.X] == END)
                                std::cout << "*";
                            else
                                std::cout << "#";
                            Map[Pos.Y][Pos.X] = BOX;
                            Pos.Y--;
                        }
                    }
                }
                break;
            }
            case LEFT:{
                if(Map[Pos.Y][Pos.X - 1] != WALL){
                    if(Map[Pos.Y][Pos.X - 1] != BOX)
                        Pos.X--;
                    else{
                        if(Map[Pos.Y][Pos.X - 2] != WALL && Map[Pos.Y][Pos.X - 2] != BOX){
                            Check = Point(Pos.Y, Pos.X - 1);
                            if(!CheckPoint(End, Check))
                                Map[Pos.Y][Pos.X - 1] = END;
                            else
                                Map[Pos.Y][Pos.X - 1] = PATH;
                            GotoPos(Pos.X - 2, Pos.Y);
                            if(Map[Pos.Y][Pos.X] == END)
                                std::cout << "*";
                            else
                                std::cout << "#";
                            Map[Pos.Y][Pos.X] = BOX;
                            Pos.X++;
                        }
                    }
                }
                break;
            }
            case RIGHT:{
                if(Map[Pos.Y][Pos.X + 1] != WALL){
                    if(Map[Pos.Y][Pos.X + 1] != BOX)
                        Pos.X++;
                    else{
                        if(Map[Pos.Y][Pos.X + 2] != WALL && Map[Pos.Y][Pos.X + 2] != BOX){
                            Check = Point(Pos.Y, Pos.X + 1);
                            if(!CheckPoint(End, Check))
                                Map[Pos.Y][Pos.X + 1] = END;
                            else
                                Map[Pos.Y][Pos.X + 1] = PATH;
                            GotoPos(Pos.X + 2, Pos.Y);
                            if(Map[Pos.Y][Pos.X] == END)
                                std::cout << "*";
                            else
                                std::cout << "#";
                            Map[Pos.Y][Pos.X] = BOX;
                            Pos.X--;
                        }
                    }
                }
                break;
            }
            default: {
                SaveScore();
                system("cls");
                system("pause");
                exit(0);
            }
        }
        GotoPos(Pos.X, Pos.Y);
        std::cout << (char)0xa7 << (char)0xb0;
    }
    else{
        SaveScore();
        system("cls");
        system("pause");
        exit(0);
    }
}

bool CheckWin(){
    for(int i = 1; i <= MapSize; i++)
        for(int j = 1; j <= MapSize; j++)
            if(Map[i][j] == END)
                return false;
    return true;
}

#endif // _MOVE_H_
