#include <iostream>
#include "CppMaze.h"

using namespace std;

typedef pair<int, int> POINT_;
typedef vector<POINT_> PATH_;

/* 定义常量 */
const int ROW = 10;
const int COLUMN = 10;
const int LOOPPERCENT = 50;
char DIRECTIONS[4] = {'N', 'S', 'W', 'E'};
const int INDIVIDUALSNUM = 50;
const double HERITABILITY = 0.2;
const int ITERATENUM = 50;

/* 定义变量 */
POINT_ LastPoint = make_pair(1, 1);
PATH_ OptimalPath;
map<POINT_, double> AlterTropism;
map<POINT_, double> Tropism;
MAZE Maze = MAZE(ROW, COLUMN);
PATH_ Path;

int Manhattan(int x1, int y1, int x2, int y2);
double Euclid(int x1, int y1, int x2, int y2);
POINT_ Roulette(POINT_ EventList[], double ProList[]);
void MazeInit();
void TropismInit();
void WaneTropism(int Row, int Column);
void AddTropism(PATH_ PathList);
void UpdateTropism();
bool SingleMovement(int Row, int Column);
void GenerationMovement(int Row, int Column);

int main() {
    MazeInit();
    TropismInit();

    int IterateNum = 0;
    clock_t begin = clock();
    while(IterateNum <= ITERATENUM){
        GenerationMovement(1, 1);
        IterateNum += 1;
    }
    clock_t end = clock();
    Maze.DrawConsoleMaze();
    HANDLE hOnt = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Pos;
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    GetConsoleScreenBufferInfo(hOnt, &screenInfo);
    Pos.X = Pos.Y = 1;
    SetConsoleCursorPosition(hOnt, Pos);
    cout << "O";
    for(auto iter : OptimalPath) {
        if(Pos.X + 2 == 2 * iter.second - 1)
            Pos.X++;
        else if(Pos.X - 2 == 2 * iter.second - 1)
            Pos.X--;
        else if(Pos.Y + 2 == 2 * iter.first - 1)
            Pos.Y++;
        else if(Pos.Y - 2 == 2 * iter.first - 1)
            Pos.Y--;
        SetConsoleCursorPosition(hOnt, Pos);
        cout << "x";
        Pos.X = 2 * iter.second - 1;
        Pos.Y = 2 * iter.first - 1;
        SetConsoleCursorPosition(hOnt, Pos);
        if(Pos.Y != 2 * ROW - 1 || Pos.X != 2 * COLUMN - 1)
            cout << "x";
    }
    Pos.Y = 2 * ROW + 1;
    Pos.X = 0;
    SetConsoleCursorPosition(hOnt, Pos);
    cout << "Time used:" << (double)(end - begin) / CLOCKS_PER_SEC << "s";
    getchar();
    return 0;
}

int Manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

double Euclid(int x1, int y1, int x2, int y2) {
    return sqrt(abs(pow(x1, 2) - pow(x2, 2)) + abs(pow(y1, 2) - pow(y2, 2)));
}

POINT_ Roulette(PATH_ EventList, vector<double> ProList) {
    for(auto iter = ProList.begin() + 1; iter != ProList.end(); iter++)
        *iter += *(iter - 1);
    auto iter = ProList.end();
    iter--;
    *iter = 1;
    random_device RANDOM;
    double RandomNum = (RANDOM() % 100 + 1) / 100.0;
    for(auto iter = ProList.begin(); iter != ProList.end(); iter++)
        if(RandomNum <= *iter)
            return EventList[iter - ProList.begin()];
}

void MazeInit() {
    Maze.CreateMaze(ROW, COLUMN, LOOPPERCENT);
}

void TropismInit() {
    Tropism.clear();
    for(int i = 1; i <= ROW; i++)
        for(int j = 1; j <= COLUMN; j++) {
            Tropism.insert(make_pair(make_pair(i, j), Manhattan(1, 1, i, j) + pow(Euclid(1, 1, i + 1, j + 1), 0.2)));
            AlterTropism.insert(make_pair(make_pair(i, j), 0.0));
        }
}

void WaneTropism(int Row, int Column) {
    Tropism[make_pair(Row, Column)] = 0.1;
}

void AddTropism(PATH_ PathList) {
    for(auto iter : PathList)
        AlterTropism[iter] += (ROW + COLUMN) / PathList.size() + Tropism[iter];
}

void UpdateTropism() {
    for(int i = 1; i <= ROW; i++)
        for(int j = 1; j <= COLUMN; j++) {
            Tropism[make_pair(i, j)] += AlterTropism[make_pair(i, j)];
            AlterTropism.insert(make_pair(make_pair(i, j), 0.0));
        }
}

bool SingleMovement(int Row, int Column) {
    PATH_ DirectionsList;
    vector<double> ProList;
    double TotalTropism = 0;

    WaneTropism(Row, Column);
    
    for(int i = 0; i < 4; i++)
        if(Maze.MazeMap[make_pair(Row, Column)][DIRECTIONS[i]])
            switch(DIRECTIONS[i]) {
                case 'N': {
                    if(LastPoint != make_pair(Row - 1, Column)) {
                        DirectionsList.emplace_back(Row - 1, Column);
                        TotalTropism += Tropism[make_pair(Row - 1, Column)];
                    }
                    break;
                }
                case 'S': {
                    if(LastPoint != make_pair(Row + 1, Column)) {
                        DirectionsList.emplace_back(Row + 1, Column);
                        TotalTropism += Tropism[make_pair(Row + 1, Column)];
                    }
                    break;
                }
                case 'W': {
                    if(LastPoint != make_pair(Row, Column - 1)) {
                        DirectionsList.emplace_back(Row, Column - 1);
                        TotalTropism += Tropism[make_pair(Row, Column - 1)];
                    }
                    break;
                }
                case 'E': {
                    if(LastPoint != make_pair(Row, Column + 1)) {
                        DirectionsList.emplace_back(Row, Column + 1);
                        TotalTropism += Tropism[make_pair(Row, Column + 1)];
                    }
                    break;
                }
            }

    POINT_ LastBifurcate;
    char LastDirection;

    if(!DirectionsList.empty()) {
        for(auto iter : DirectionsList)
            ProList.push_back(Tropism[iter] / TotalTropism);
        Path.push_back(Roulette(DirectionsList, ProList));
        LastPoint = make_pair(Row, Column);
        if(DirectionsList.size() > 1) {
            LastBifurcate = make_pair(Row, Column);
            if(Path[Path.size() - 1] == make_pair(Row - 1, Column))
                LastDirection = 'N';
            else if(Path[Path.size() - 1] == make_pair(Row + 1, Column))
                LastDirection = 'S';
            else if(Path[Path.size() - 1] == make_pair(Row, Column - 1))
                LastDirection = 'W';
            else if(Path[Path.size() - 1] == make_pair(Row, Column - 1))
                LastDirection = 'E';
        }
        return true;
    }

    Maze.MazeMap[LastBifurcate][LastDirection] = 0;
    return false;
}

void GenerationMovement(int Row, int Column) {
    map<int, PATH_> Paths;
    int IndividualNum = 0;
    if(!OptimalPath.empty())
        Paths.insert(make_pair(OptimalPath.size(), OptimalPath));
    while(IndividualNum <= INDIVIDUALSNUM) {
        Path.clear();
        int Step = 0;
        int Row = 1;
        int Column = 1;
        while(Step <= ROW * COLUMN) {
            if(SingleMovement(Row, Column)) {
                Row = (Path.end() - 1) -> first;
                Column = (Path.end() - 1) -> second;
                if(Row == ROW && Column == COLUMN) {
                    if(Paths.size() <= INDIVIDUALSNUM * HERITABILITY)
                        Paths.insert(make_pair(Path.size(), Path));
                    else {
                        auto iter = Paths.end();
                        iter--;
                        if (Path.size() < iter -> first) {
                            Paths.erase(iter);
                            Paths.insert(make_pair(Path.size(), Path));
                        }
                    }
                }
                Step++;
            }
            else
                break;
        }

        if(!Paths.empty()) {
            OptimalPath.clear();
            for(auto iter : Paths.begin() -> second)
                OptimalPath.push_back(iter);
        }
        for(const auto& iter : Paths)
            AddTropism(iter.second);
        UpdateTropism();
        IndividualNum += 1;
    }
}