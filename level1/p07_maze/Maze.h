#ifndef _MAZE_H_
#define _MAZE_H_
#include<vector>
#include<string.h>
#define max_size 10010
#define Wall 0
#define Path 1

int maze_row = 0, maze_colume = 0;
int row = 1, colume = 1; // 当前位置
int maze[max_size][max_size];

enum Direction{
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

std::vector<Block> block;

void init__(){
    maze_row += !(maze_row % 2);
    maze_colume += !(maze_colume % 2); // 保证迷宫大小为奇数
    memset(maze, Wall, sizeof(maze));
    maze[1][1] = Path;
    Start.x = Start.y = 1;
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

void CreateMaze(){
    srand((unsigned)time(NULL)); // 随机数种子
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
}

#endif // _MAZE_H_
