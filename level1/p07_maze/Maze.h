#ifndef _MAZE_H_
#define _MAZE_H_
#include <vector>
#include <string.h>
#include <random>

int maze_row = 0, maze_colume = 0;
int row = 1, colume = 1; // 当前位置
int maze[MAXSIZE][MAXSIZE];

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

std::random_device RandomDevice; // 随机数生成器
// rand()以秒为单位，随机性过弱，无法达到随机效果

void InitMaze();
void PrimFindBlock();
void CreatePrimMaze();
void DFSFindBlock();
void CreateDFSMaze();
void InitRecursiveMaze();
void CreateRecursiveMaze(int Maze[MAXSIZE][MAXSIZE], int x1, int y1, int x2, int y2);

void InitMaze(){
    maze_row += !(maze_row % 2);
    maze_colume += !(maze_colume % 2); // 保证迷宫大小为奇数
    memset(maze, WALL, sizeof(maze));
    maze[1][1] = PATH;
    Start.x = Start.y = 1;
}

void PrimFindBlock(){
    if(row - 1 > 0 && maze[row - 1][colume] == WALL) // up
        block.push_back(Block(row - 1, colume, Up));
    if(row + 1 <= maze_row && maze[row + 1][colume] == WALL) // down
        block.push_back(Block(row + 1, colume, Down));
    if(colume - 1 > 0 && maze[row][colume - 1] == WALL) // left
        block.push_back(Block(row, colume - 1, Left));
    if(colume + 1 <= maze_colume && maze[row][colume + 1] == WALL) // right
        block.push_back(Block(row, colume + 1, Right));
}

void CreatePrimMaze(){
    InitMaze();
    PrimFindBlock(); // 将起点旁墙壁压入栈
    srand((unsigned)time(NULL)); // 随机数种子
    while(block.size() != 0){
        int BlockSize = block.size();
        int random = RandomDevice() % BlockSize; // 随机选择vector中的墙
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
        if(maze[row][colume] == WALL){
            maze[SelectBlock.x][SelectBlock.y] = maze[row][colume] = PATH;
            PrimFindBlock();
        }
        block.erase(block.begin() + random);
    }
}

void DFSFindBlock(){
    srand((unsigned)time(NULL));
    std::vector<int> Random;
    for(int i = 1; i <= 4; i++)
        Random.push_back(i);
    while(Random.size() != 0){
        int random = RandomDevice() % Random.size();
        switch (Random[random]) {
            case Up: {
                if (row - 1 > 0 && maze[row - 1][colume] == WALL) // up
                    block.push_back(Block(row - 1, colume, Up));
                break;
            }
            case Down: {
                if (row + 1 <= maze_row && maze[row + 1][colume] == WALL) // down
                    block.push_back(Block(row + 1, colume, Down));
                break;
            }
            case Left: {
                if (colume - 1 > 0 && maze[row][colume - 1] == WALL) // left
                    block.push_back(Block(row, colume - 1, Left));
                break;
            }
            case Right: {
                if (colume + 1 <= maze_colume && maze[row][colume + 1] == WALL) // right
                    block.push_back(Block(row, colume + 1, Right));
                break;
            }
        }
        Random.erase(Random.begin() + random);
    }
}

void CreateDFSMaze(){
    InitMaze();
    DFSFindBlock(); // 将起点旁墙壁压入栈
    while(block.size() != 0){
        Block SelectBlock = block[block.size() - 1];
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
        block.erase(block.begin() + block.size() - 1);
        if(maze[row][colume] == WALL){
            maze[SelectBlock.x][SelectBlock.y] = maze[row][colume] = PATH;
            DFSFindBlock();
        }
    }
}

void InitRecursiveMaze(){
    maze_row += !(maze_row % 2);
    maze_colume += !(maze_colume % 2); // 保证迷宫大小为奇数
    for(int i = 1; i <= maze_row; i++)
        for(int j = 1; j <= maze_colume; j++)
            maze[i][j] = PATH;
    for(int i = 0; i <= maze_colume + 1; i++){
        maze[0][i] = WALL;
        maze[maze_row + 1][i] = WALL;
    }
    for(int i = 0; i <= maze_row + 1; i++){
        maze[i][0] = WALL;
        maze[i][maze_colume + 1] = WALL;
    }
    Start.x = Start.y = 1;
}

void CreateRecursiveMaze(int Maze[MAXSIZE][MAXSIZE], int x1, int y1, int x2, int y2){
    if(x2 - x1 < 2 || y2 - y1 < 2)
        return ;
    int x = x1 + 1 + RandomDevice() % (x2 - x1 - 1);
    int y = y1 + 1 + RandomDevice() % (y2 - y1 - 1);
    for(int i = y1; i <= y2; i++)
        Maze[x][i] = WALL;
    for(int i = x1; i <= x2; i++)
        Maze[i][y] = WALL;
    CreateRecursiveMaze(Maze, x1, y1, x - 1, y - 1);
    CreateRecursiveMaze(Maze, x + 1, y + 1, x2, y2);
    CreateRecursiveMaze(Maze, x + 1, y1, x2, y - 1);
    CreateRecursiveMaze(Maze, x1, y + 1, x - 1, y2);
    int Random[4] = {0};
    for(int i = 0; i < 4; i++)
        Random[i] = PATH;
    Random[RandomDevice() % 4] = WALL;
    for(int i = 0; i < 4; i++){
        int RandomX = x, RandomY = y;
        if(Random[i] == PATH){
            // (!Maze[RandomX - 1][RandomY]) + (!Maze[RandomX + 1][RandomY]) \
            // + (!Maze[RandomX][RandomY - 1]) + (!Maze[RandomX][RandomY + 1]) > 2 * (!WALL)
            // 保证连通两个区域
            switch(i){
                case 0:{
                    do{
                        RandomX = x1 + RandomDevice() % (x - x1);
                    }while((!Maze[RandomX - 1][RandomY]) + (!Maze[RandomX + 1][RandomY]) + (!Maze[RandomX][RandomY - 1]) + (!Maze[RandomX][RandomY + 1]) > 2 * (!WALL));
                    break;
                }
                case 1:{
                    do {
                        RandomY = y1 + RandomDevice() % (y - y1);
                    }while((!Maze[RandomX - 1][RandomY]) + (!Maze[RandomX + 1][RandomY]) + (!Maze[RandomX][RandomY - 1]) + (!Maze[RandomX][RandomY + 1]) > 2 * (!WALL));
                    break;
                }
                case 2:{
                    do{
                        RandomX = x + 1 + RandomDevice() % (x2 - x);
                    }while((!Maze[RandomX - 1][RandomY]) + (!Maze[RandomX + 1][RandomY]) + (!Maze[RandomX][RandomY - 1]) + (!Maze[RandomX][RandomY + 1]) > 2 * (!WALL));
                    break;
                }
                case 3:{
                    do{
                        RandomY = y + 1 + RandomDevice() % (y2 - y);
                    }while((!Maze[RandomX - 1][RandomY]) + (!Maze[RandomX + 1][RandomY]) + (!Maze[RandomX][RandomY - 1]) + (!Maze[RandomX][RandomY + 1]) > 2 * (!WALL));
                    break;
                }
            }
            Maze[RandomX][RandomY] = PATH;
        }
    }
}

#endif // _MAZE_H_