#include <iostream>
#include "Parameter.h"
#include "GA.h"
using namespace std;

int main() {
    //ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    for(int i = 0; i <= MazeSize + 1; i++){
        for(int j = 0; j <= MazeSize + 1; j++){
            if(Maze[i][j] == PATH)
                cout << " ";
            else
                cout << (char)0xa8 << (char)0x80; // 输出小方块
        }
        cout << endl;
    }
    system("pause");
    return 0;
}