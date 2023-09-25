#include<iostream>
#include<windows.h>
#include<conio.h>
#include"Maze.h"
#define CTRL 0xE0
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4B
#define RIGHT 0x4D

using namespace std;

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

int main(){
    //ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << "Please enter the row for the maze: ";
    cin >> maze_row;
    cout << "\nPlease enter the colume for the maze: ";
    cin >> maze_colume;
    system("cls");
    jump:
    init__();
    FindBlock(); // 将起点旁边的墙壁压入vector
    CreateMaze();
    if(maze[maze_row][maze_colume] != Wall){
        End.x = maze_row;
        End.y = maze_colume;
    }
    else
        goto jump;
    for(int i = 0; i <= maze_row + 1; i++){
        for(int j = 0; j <= maze_colume + 1; j++){
            if(i == Start.x && j == Start.y)
                cout << (char)0xa7 << (char)0xb0;
            else if(i == End.x && j == End.y)
                cout << "@";
            else if(maze[i][j] == Path)
                cout << " ";
            else
                cout << (char)0xa8 << (char)0x80 ; // 输出小方块
        }
        cout << endl;
    }
    GotoPos(1, 1);
    while(1){
        if(_getch() == CTRL){
            GotoPos(Pos.X, Pos.Y);
            cout << " ";
            keystroke = _getch();
            switch (keystroke) {
                case UP: {
                    if(maze[Pos.Y - 1][Pos.X] != Wall)
                        Pos.Y--;
                    break;
                }
                case DOWN: {
                    if(maze[Pos.Y + 1][Pos.X] != Wall)
                        Pos.Y++;
                    break;
                }
                case LEFT:{
                    if(maze[Pos.Y][Pos.X - 1] != Wall)
                        Pos.X--;
                    break;
                }
                case RIGHT:{
                    if(maze[Pos.Y][Pos.X + 1] != Wall)
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
            cout << (char)0xa7 << (char)0xb0;
        }
        if(Pos.X == End.x && Pos.Y == End.y){
            system("cls");
            GotoPos(0, 0);
            cout << "Congratulate!\n";
            system("pause");
        }
    }
    system("pause");
    return 0;
}