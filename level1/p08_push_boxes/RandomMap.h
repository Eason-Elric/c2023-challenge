#ifndef _RANDOMMAP_H_
#define _RANDOMMAP_H_
#include <vector>
#include <string.h>
#include <random>

int MapSize = 10, BoxNum = 4;
int row = 0, colume = 0;
int Map[MAXSIZE][MAXSIZE] = {0};

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
    Point(int x_, int y_){
        x = x_;
        y = y_;
    }
};

Point Player = Point(0, 0);

std::vector<Block> block, StorageBlock;

std::vector<Point> Start, End;

std::random_device RandomDevice;

void InitMap();
void FindBlock();
void CreateMap();
bool CheckPoint(std::vector<Point> Vec, Point point);
void CheckBlock(std::vector<Block> Vec);
void FindConnect();
bool CheckConnect();

void InitMap(){
    row = 0;
    colume = 0;
    MapSize = 10;
    BoxNum = 4;
    memset(Map, WALL, sizeof(Map));
    std::vector<Point>().swap(Start);
    std::vector<Point>().swap(End);
    std::vector<Block>().swap(block);
    std::vector<Block>().swap(StorageBlock);
}

void FindBlock(){
    srand((unsigned)time(NULL));
    std::vector<int> Random;
    for(int i = 1; i <= 4; i++)
        Random.push_back(i);
    while(Random.size() != 0){
        int random = RandomDevice() % Random.size();
        switch (Random[random]) {
            case Up: {
                if (row - 1 > 1) // up
                    block.push_back(Block(row - 1, colume, Up));
                break;
            }
            case Down: {
                if (row + 1 <= MapSize - 1) // down
                    block.push_back(Block(row + 1, colume, Down));
                break;
            }
            case Left: {
                if (colume - 1 > 1) // left
                    block.push_back(Block(row, colume - 1, Left));
                break;
            }
            case Right: {
                if (colume + 1 <= MapSize - 1) // right
                    block.push_back(Block(row, colume + 1, Right));
                break;
            }
        }
        Random.erase(Random.begin() + random);
    }
}

void CreateMap(){
    Label:
    srand((unsigned)time(NULL));
    InitMap();
    while(BoxNum > 0){
        jump:
        std::vector<Block>().swap(block);
        std::vector<Block>().swap(StorageBlock);
        Point point = Point(RandomDevice() % (MapSize - 2) + 2, RandomDevice() % (MapSize - 2) + 2);
        if(CheckPoint(End, point) && CheckPoint(End, point)){
            row = point.x;
            colume = point.y;
            End.push_back(point);
        }
        else
            goto jump;
        FindBlock(); // 将起点旁墙壁压入栈
        int Step = RandomDevice() % MapSize + MapSize / 2 + MapSize / 3;
        while(Step > 0){
            Block SelectBlock = block[block.size() - 1];
            row = SelectBlock.x;
            colume = SelectBlock.y;
            StorageBlock.push_back(SelectBlock);
            block.erase(block.begin() + block.size() - 1);
            Map[row][colume] = PATH;
            FindBlock();
            Step--;
        }
        point = Point(row, colume);
        if(CheckPoint(Start, point) && CheckPoint(End, point)){
            Start.push_back(point);
            Map[row - 1][colume - 1] = Map[row - 1][colume] = Map[row - 1][colume + 1] = \
            Map[row][colume - 1] = Map[row][colume] = Map[row][colume + 1] = \
            Map[row + 1][colume - 1] = Map[row + 1][colume] = Map[row + 1][colume + 1] = PATH;
            Map[(End.begin() + End.size() - 1) -> x][(End.begin() + End.size() - 1) -> y] = PATH;
        }
        else{
            End.erase(End.begin() + End.size() - 1);
            goto jump;
        }
        CheckBlock(StorageBlock);
        BoxNum--;
    }
    if(!CheckConnect())
        goto Label;
    label:
    Player = Point(RandomDevice() % MapSize, RandomDevice() % MapSize);
    if(Map[Player.x][Player.y] == PATH && CheckPoint(Start, Player) && CheckPoint(End, Player))
        Map[Player.x][Player.y] = PLAYER;
    else
        goto label;
    for(int i = 0; i <= MapSize + 1; i++)
        for(int j = 0; j <= MapSize + 1; j++) {
            if (!CheckPoint(Start, Point(i, j)))
                Map[i][j] = BOX;
            else if (!CheckPoint(End, Point(i, j)))
                Map[i][j] = END;
        }
}

bool CheckPoint(std::vector<Point> Vec, Point point){
    for(std::vector<Point>::iterator iter = Vec.begin(); iter != Vec.end(); iter++)
        if(point.x == iter -> x && point.y == iter -> y)
            return false;
    return true;
}

void CheckBlock(std::vector<Block> Vec){
    for(std::vector<Block>::iterator iter = Vec.begin(); iter != Vec.end(); iter++) {
        if ((Map[(iter -> x) + 1][iter -> y] + Map[iter -> x][(iter -> y) + 1] == 0) && (iter -> direction == Right))
            Map[(iter -> x) - 1][(iter -> y) + 1] = Map[iter -> x][(iter -> y) + 1] = PATH;
        if ((Map[(iter -> x) + 1][iter -> y] + Map[iter -> x][(iter -> y) + 1] == 0) && (iter -> direction == Down))
            Map[(iter -> x) + 1][(iter -> y) - 1] = Map[(iter -> x) + 1][iter -> y] = PATH;
        if ((Map[(iter -> x) + 1][iter -> y] + Map[iter -> x][(iter -> y) - 1] == 0) && (iter -> direction == Left))
            Map[(iter -> x) - 1][(iter -> y) - 1] = Map[iter -> x][(iter -> y)  - 1] = PATH;
        if ((Map[(iter -> x) + 1][iter -> y] + Map[iter -> x][(iter -> y) - 1] == 0) && (iter -> direction == Down))
            Map[(iter -> x) + 1][iter -> y] = Map[(iter -> x) + 1][(iter -> y) + 1] = PATH;
        if ((Map[(iter -> x) - 1][iter -> y] + Map[iter -> x][(iter -> y) + 1] == 0) && (iter -> direction == Right))
            Map[iter -> x][(iter -> y) + 1] = Map[(iter -> x) + 1][(iter -> y) + 1] = PATH;
        if ((Map[(iter -> x) - 1][iter -> y] + Map[iter -> x][(iter -> y) + 1] == 0) && (iter -> direction == Up))
            Map[(iter -> x) - 1][(iter -> y) - 1] = Map[(iter -> x) - 1][iter -> y] = PATH;
        if ((Map[(iter -> x) - 1][iter -> y] + Map[iter -> x][(iter -> y) - 1] == 0) && (iter -> direction == Left))
            Map[(iter -> x) + 1][(iter -> y) - 1] = Map[iter -> x][(iter -> y) - 1] = PATH;
        if ((Map[(iter -> x) - 1][iter -> y] + Map[iter -> x][(iter -> y) - 1] == 0) && (iter -> direction == Up))
            Map[(iter -> x) - 1][iter -> y] = Map[(iter -> x) - 1][(iter -> y) + 1] = PATH;
    }
}

void FindConnect(){
    if(row - 1 > 0 && Map[row - 1][colume] == PATH) // up
        block.push_back(Block(row - 1, colume, Up));
    if(row + 1 <= MapSize && Map[row + 1][colume] == PATH) // down
        block.push_back(Block(row + 1, colume, Down));
    if(colume - 1 > 0 && Map[row][colume - 1] == PATH) // left
        block.push_back(Block(row, colume - 1, Left));
    if(colume + 1 <= MapSize && Map[row][colume + 1] == PATH) // right
        block.push_back(Block(row, colume + 1, Right));
}

bool CheckConnect(){
    int SumPath = 0;
    std::vector<Point> Check_;
    for(int i = 0; i <= MapSize + 1; i++)
        for(int j = 0; j <= MapSize + 1; j++)
            SumPath += Map[i][j];
    std::vector<Block>().swap(block);
    row = Start[0].x;
    colume = Start[0].y;
    Check_.push_back(Point(row, colume));
    SumPath--;
    FindConnect();
    while(block.size() > 0){
        if(CheckPoint(Check_, Point(block[0].x, block[0].y))){
            row = block[0].x;
            colume = block[0].y;
            Check_.push_back(Point(block[0].x, block[0].y));
            FindConnect();
            SumPath--;
        }
        block.erase(block.begin());
    }
    if(!SumPath)
        return true;
    return false;
}

#endif // _RANDOMMAP_H_

// 基本实现了随机生成推箱子地图的功能，保证了生成地图有解，但生成的部分地图不具备很强的可玩性
