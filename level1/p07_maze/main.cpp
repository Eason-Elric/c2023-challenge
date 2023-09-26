#include <iostream>
#include "ConstData.h"
#include "PrimMaze.h"
#include "Move.h"

using namespace std;

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
    CreatePrimMaze();
    if(maze[maze_row][maze_colume] != WALL){
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
            else if(maze[i][j] == PATH)
                cout << " ";
            else
                cout << (char)0xa8 << (char)0x80 ; // 输出小方块
        }
        cout << endl;
    }
    GotoPos(1, 1);
    while(1){
        Move();
        if(Pos.Y == End.x && Pos.X == End.y){
            system("cls");
            GotoPos(0, 0);
            cout << "Congratulate!\n";
            system("pause");
            exit(0);
        }
    }
    system("pause");
    return 0;
}