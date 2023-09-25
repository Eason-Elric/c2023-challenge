#include<iostream>
#include<vector>
#include<windows.h>
#include<conio.h>
#define max_size 10010
#define Wall 0
#define Path 1
using namespace std;

HANDLE hOnt = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Pos;
CONSOLE_SCREEN_BUFFER_INFO screenInfo;

int maze_row = 0, maze_colume = 0;
int row = 1, colume = 1; // 当前位置
int maze[max_size][max_size];

enum Dicection{
    Up = 1, Down, Left, Right
};

struct Block{
    int x, y, direction;
    Block(int x_, int y_, int direction_){
        x = x_;
        y = y_;
        direction = direction_;
    }
};

struct Point{
    int x, y;
}Start, End;

vector<Block> block;

void init__(){
    maze_row += !(maze_row % 2);
    maze_colume += !(maze_colume % 2); // 保证迷宫大小为奇数
    memset(maze, Wall, sizeof(maze));
    maze[1][1] = Path;
    Start.x = Start.y = 1;
    Pos.X = Pos.Y = 1;
    GetConsoleScreenBufferInfo(hOnt, &screenInfo);
}

void FindBlock(){
    if(row - 1 > 0 && maze[row - 1][colume] == Wall) // up
        block.push_back(Block(row - 1, colume, Up));
    if(row + 1 <= maze_row && maze[row + 1][colume] == Wall) // down
        block.push_back(Block(row + 1, colume, Down));
    if(colume - 1 > 0 && maze[row][colume - 1] == Wall) // left
        block.push_back(Block(row, colume - 1, Left));
    if(colume + 1 <= maze_colume && maze[row][colume + 1] == Wall) // right
        block.push_back(Block(row, colume + 1, Right));
}

int main(){
    //ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << "Please enter the row for the maze:";
    cin >> maze_row;
    cout << "\nPlease enter the colume for the maze:";
    cin >> maze_colume;
    cout << endl;
    jump:
    init__();
    srand((unsigned)time(NULL)); // 随机数种子
    FindBlock(); // 将起点旁边的墙壁压入vector
    while(block.size() != 0){
        int BlockSize = block.size();
        int random = rand() % BlockSize; // 随机选择vector中的墙
        Block SelectBlock = block[random];
        row = SelectBlock.x;
        colume = SelectBlock.y;
        switch (SelectBlock.direction) {
            case Up: {
                row--;
                break;
            }
            case Down: {
                row++;
                break;
            }
            case Left: {
                colume--;
                break;
            }
            case Right:{
                colume++;
                break;
            }
        }
        if(maze[row][colume] == Wall){
            maze[SelectBlock.x][SelectBlock.y] = maze[row][colume] = Path;
            FindBlock();
        }
        block.erase(block.begin() + random);
    }
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