#include<iostream>
#include<windows.h>
#include"Maze.h"
using namespace std;

/*HANDLE hOnt = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Pos;
CONSOLE_SCREEN_BUFFER_INFO screenInfo;*/

int main(){
    //ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << "Please enter the row for the maze: ";
    cin >> maze_row;
    cout << "\nPlease enter the colume for the maze: ";
    cin >> maze_colume;
    cout << endl;
    /*Pos.X = Pos.Y = 1;
    GetConsoleScreenBufferInfo(hOnt, &screenInfo);*/
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
    system("pause");
    return 0;
}