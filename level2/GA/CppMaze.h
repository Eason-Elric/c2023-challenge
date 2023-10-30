#ifndef CPPMAZE_H_
#define CPPMAZE_H_

#include <map>
#include <random>
#include <vector>
#include <algorithm>
#include <deque>
#include <set>
#include <cstdio>
#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <windows.h>

using namespace std;

typedef pair<int, int> POINT_;
typedef vector<POINT_> POINTLIST;
typedef map<POINT_, POINT_> PATH;

class MAZE;
class AGENT;

class MAZE {
    /* 参数 */
public:
    map<POINT_, map<char, bool>> MazeMap;
    PATH Path;

private:
    int Row;
    int Column;
    int GoalRow;
    int GoalColumn;
    POINTLIST Grid;
    POINT_ Goal;

    /* 函数 */
public:
    MAZE(int Row = 10, int Column = 10);
    void CreateMaze(int GoalRow_ = 1, int GoalColumn_ = 1, int LoopPercent = 0, char Pattern = '\0', bool SaveMaze = false, const string& LoadMaze = "");
    void DrawConsoleMaze();

    // 基本操作
private:
    bool FindPoint(POINT_ Point, POINTLIST Vec);
    bool FindPoint(POINT_ Point, const set<POINT_>& Set);
    static void SwapPoint(POINT_ &FirstPoint, POINT_ &SecondPoint);
    static string split(const string& str, char split);
private:
    void InitGrid();
    void OpenEast(int Row_, int Column_);
    void OpenWest(int Row_, int Column_);
    void OpenNorth(int Row_, int Column_);
    void OpenSouth(int Row_, int Column_);
    POINTLIST BlockedNeighbors(POINT_ Point);
    void RemoveBetweenWall(POINT_ FirstPoint, POINT_ SecondPoint);
    bool IsCyclic(POINT_ FirstPoint, POINT_ SecondPoint);
    PATH BFS(POINT_ Point);
    void LoadMazeFile(const string& LoadMaze);
    void SaveMazeFile();
};

MAZE::MAZE(int Row, int Column) {
    this -> Row = Row;
    this -> Column = Column;
}

void MAZE::CreateMaze(int GoalRow_, int GoalColumn_, int LoopPercent, char Pattern, bool SaveMaze, const string& LoadMaze) {
    InitGrid();
    GoalRow = GoalRow_;
    GoalColumn = GoalColumn_;
    POINTLIST Stack, ClosedGrid;
    Goal = make_pair(GoalRow_, GoalColumn_);
    int BiasLength = 2; // Pattern模式
    int Bias = 0;
    if(LoadMaze.empty()){
        Stack.emplace_back(GoalRow_, GoalColumn_);
        ClosedGrid.emplace_back(GoalRow_, GoalColumn_);
        if(Pattern != '\0' && tolower(Pattern) == 'h')
            BiasLength = max(Column / 10, BiasLength);
        if(Pattern != '\0' && tolower(Pattern) == 'v')
            BiasLength = max(Row / 10, BiasLength);
        while(!Stack.empty()) {
            string Cell;
            Bias++;
            if(!FindPoint(make_pair(GoalRow_, GoalColumn_ + 1), ClosedGrid) && FindPoint(make_pair(GoalRow_, GoalColumn_ + 1), Grid))
                Cell.append("E");
            if(!FindPoint(make_pair(GoalRow_, GoalColumn_ - 1), ClosedGrid) && FindPoint(make_pair(GoalRow_, GoalColumn_ - 1), Grid))
                Cell.append("W");
            if(!FindPoint(make_pair(GoalRow_ + 1, GoalColumn_), ClosedGrid) && FindPoint(make_pair(GoalRow_ + 1, GoalColumn_), Grid))
                Cell.append("S");
            if(!FindPoint(make_pair(GoalRow_ - 1, GoalColumn_), ClosedGrid) && FindPoint(make_pair(GoalRow_ - 1, GoalColumn_), Grid))
                Cell.append("N");
            if(!Cell.empty()) {
                if(tolower(Pattern) == 'h' && Bias <= BiasLength)
                    if(Cell.find('E') != string::npos || Cell.find('E') != string::npos){
                        if(Cell.find('S') != string::npos)
                            Cell.erase(Cell.find('S'));
                        if(Cell.find('N') != string::npos)
                            Cell.erase(Cell.find('N'));
                    }
                    else if(tolower(Pattern) == 'v' && Bias <= BiasLength)
                        if(Cell.find('N') != string::npos || Cell.find('S') != string::npos) {
                            if(Cell.find('E') != string::npos)
                                Cell.erase(Cell.find('E'));
                            if(Cell.find('W') != string::npos)
                                Cell.erase(Cell.find('W'));
                        }
                        else
                            Bias = 0;
                random_device Random;
                char CurrentCell = Cell[Random() % Cell.size()];
                if(CurrentCell == 'E') {
                    OpenEast(GoalRow_, GoalColumn_);
                    Path[make_pair(GoalRow_, GoalColumn_ + 1)] = make_pair(GoalRow_, GoalColumn_);
                    GoalColumn_++;
                    ClosedGrid.emplace_back(GoalRow_, GoalColumn_);
                    Stack.emplace_back(GoalRow_, GoalColumn_);
                }
                else if(CurrentCell == 'W') {
                    OpenWest(GoalRow_, GoalColumn_);
                    Path[make_pair(GoalRow_, GoalColumn_ - 1)] = make_pair(GoalRow_, GoalColumn_);
                    GoalColumn_--;
                    ClosedGrid.emplace_back(GoalRow_, GoalColumn_);
                    Stack.emplace_back(GoalRow_, GoalColumn_);
                }
                else if(CurrentCell == 'N') {
                    OpenNorth(GoalRow_, GoalColumn_);
                    Path[make_pair(GoalRow_ - 1, GoalColumn_)] = make_pair(GoalRow_, GoalColumn_);
                    GoalRow_--;
                    ClosedGrid.emplace_back(GoalRow_, GoalColumn_);
                    Stack.emplace_back(GoalRow_, GoalColumn_);
                }
                else if(CurrentCell == 'S') {
                    OpenSouth(GoalRow_, GoalColumn_);
                    Path[make_pair(GoalRow_ + 1, GoalColumn_)] = make_pair(GoalRow_, GoalColumn_);
                    GoalRow_++;
                    ClosedGrid.emplace_back(GoalRow_, GoalColumn_);
                    Stack.emplace_back(GoalRow_, GoalColumn_);
                }
            }
            else {
                GoalRow_ = Stack.back().first;
                GoalColumn_ = Stack.back().second;
                Stack.pop_back();
            }
        }

        // 产生多解图
        if(LoopPercent != 0) {
            GoalRow_ = Row;
            GoalColumn_ = Column;
            POINTLIST PathCells, NotPathCells;
            PathCells.emplace_back(GoalRow_, GoalColumn_);
            while(GoalRow_ != Row || GoalColumn_ != Column) {
                GoalRow_ = Path[make_pair(GoalRow_, GoalColumn_)].first;
                GoalColumn_ = Path[make_pair(GoalRow_, GoalColumn_)].second;
                PathCells.emplace_back(GoalRow_, GoalColumn_);
            }
            for(auto iter : Grid)
                if(!FindPoint(iter, PathCells))
                    NotPathCells.emplace_back(iter);
            shuffle(PathCells.begin(), PathCells.end(), std::mt19937(random_device()()));
            shuffle(NotPathCells.begin(), NotPathCells.end(), std::mt19937(random_device()()));
            double FirstCount = PathCells.size() / 3.0 * LoopPercent / 100.0;
            double SecondCount = NotPathCells.size() / 3.0 * LoopPercent / 100.0;

            int Count = 0;
            int i = 0;
            while(Count < FirstCount) {
                if(!BlockedNeighbors(PathCells[i]).empty()) {
                    random_device Random;
                    POINT_ ACell = BlockedNeighbors(PathCells[i])[Random() % BlockedNeighbors(PathCells[i]).size()];
                    if(!IsCyclic(ACell, PathCells[i])) {
                        RemoveBetweenWall(ACell, PathCells[i]);
                        Count++;
                    }
                }
                i++;
                if(i == PathCells.size())
                    break;
            }

            if(!NotPathCells.empty()) {
                Count = 0;
                i = 0;
                while(Count < SecondCount) {
                    if(!BlockedNeighbors(NotPathCells[i]).empty()) {
                        random_device Random;
                        POINT_ ACell = BlockedNeighbors(NotPathCells[i])[Random() % BlockedNeighbors(NotPathCells[i]).size()];
                        if(!IsCyclic(ACell, NotPathCells[i])) {
                            RemoveBetweenWall(ACell, NotPathCells[i]);
                            Count++;
                        }
                    }
                    i++;
                    if(i == NotPathCells.size())
                        break;
                }
            }
        }
    }
    else
        LoadMazeFile(LoadMaze);

    Path = BFS(make_pair(Row, Column));

    if(SaveMaze)
        SaveMazeFile();
}

void MAZE::DrawConsoleMaze() {
    HANDLE hOnt = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Pos;
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    GetConsoleScreenBufferInfo(hOnt, &screenInfo);
    for(const auto iter : MazeMap) {
        Pos.X = 2 * iter.first.first - 1;
        Pos.Y = 2 * iter.first.second - 1;
        for(const auto& iter_ : MazeMap[iter.first]) {
            Pos.Y = 2 * iter.first.first - 1;
            Pos.X = 2 * iter.first.second - 1;
            switch (iter_.first) {
                case 'E':
                    Pos.X++;
                    break;
                case 'W':
                    Pos.X--;
                    break;
                case 'N':
                    Pos.Y--;
                    break;
                case 'S':
                    Pos.Y++;
                    break;
            }
            SetConsoleCursorPosition(hOnt, Pos);
            if(!iter_.second)
                cout << (char)0xa8 << (char)0x80;
        }
    }
    for(int i = 0; i < 2 * Row + 1; i++)
        for(int j = 0; j < 2 * Column + 1; j++) {
            Pos.X = j;
            Pos.Y = i;
            if (!(i % 2) && !(j % 2)) {
                SetConsoleCursorPosition(hOnt, Pos);
                cout << (char)0xa8 << (char)0x80;
            }
            if(j == 2 * GoalRow - 1 && i == 2 * GoalColumn - 1) {
                SetConsoleCursorPosition(hOnt, Pos);
                cout << "@";
            }
        }
    cout << endl;
}

inline bool MAZE::FindPoint(POINT_ Point, POINTLIST Vec) {
    auto iter = find(Vec.begin(), Vec.end(), Point);
    if(iter != Vec.end())
        return true;
    return false;
}

inline bool MAZE::FindPoint(POINT_ Point, const set<POINT_>& Set) {
    auto iter = Set.find(Point);
    if(iter != Set.end())
        return true;
    return false;
}

inline void MAZE::SwapPoint(POINT_ &FirstPoint, POINT_ &SecondPoint) {
    POINT_ temp;
    temp = FirstPoint;
    FirstPoint = SecondPoint;
    SecondPoint = FirstPoint;
}

string MAZE::split(const string& str, const char split) {
    istringstream InStr(str);
    string Token, Res;
    while(getline(InStr, Token, split))
        Res.append(Token);
    return Res;
}

void MAZE::InitGrid() {
    for(int i = 1; i <= Row; i++)
        for(int j = 1; j <= Column; j++){
            Grid.emplace_back(i, j);
            MazeMap.insert({make_pair(i, j), {{'E', false}, {'W', false}, {'N', false}, {'S', false}}});
        }
}

void MAZE::OpenEast(int Row_, int Column_) {
    MazeMap[make_pair(Row_, Column_)]['E'] = true;
    if(Column_ + 1 <= Column)
        MazeMap[make_pair(Row_, Column_ + 1)]['W'] = true;
}

void MAZE::OpenWest(int Row_, int Column_) {
    MazeMap[make_pair(Row_, Column_)]['W'] = true;
    if(Column_ - 1 > 0)
        MazeMap[make_pair(Row_, Column_ - 1)]['E'] = true;
}

void MAZE::OpenNorth(int Row_, int Column_) {
    MazeMap[make_pair(Row_, Column_)]['N'] = true;
    if(Row_ - 1 > 0)
        MazeMap[make_pair(Row_ - 1, Column_)]['S'] = true;
}

void MAZE::OpenSouth(int Row_, int Column_) {
    MazeMap[make_pair(Row_, Column_)]['S'] = true;
    if(Row_ + 1 <= Row)
        MazeMap[make_pair(Row_ + 1, Column_)]['N'] = true;
}

POINTLIST MAZE::BlockedNeighbors(POINT_ Point) {
    POINTLIST Grid_;
    for(auto iter : MazeMap[Point])
        if(!MazeMap[Point][iter.first]){
            if(iter.first == 'E' && FindPoint(make_pair(Point.first, Point.second + 1), Grid))
                Grid_.emplace_back(Point.first, Point.second + 1);
            else if (iter.first == 'W' && FindPoint(make_pair(Point.first, Point.second - 1), Grid))
                Grid_.emplace_back(Point.first, Point.second - 1);
            else if (iter.first == 'N' && FindPoint(make_pair(Point.first - 1, Point.second), Grid))
                Grid_.emplace_back(Point.first - 1, Point.second);
            else if (iter.first == 'S' && FindPoint(make_pair(Point.first + 1, Point.second), Grid))
                Grid_.emplace_back(Point.first + 1, Point.second);
        }
    return Grid_;
}

void MAZE::RemoveBetweenWall(POINT_ FirstPoint, POINT_ SecondPoint) {
    if(FirstPoint.first == SecondPoint.first) {
        if (FirstPoint.second == SecondPoint.second + 1) {
            MazeMap[FirstPoint]['W'] = true;
            MazeMap[SecondPoint]['E'] = true;
        } else {
            MazeMap[FirstPoint]['E'] = true;
            MazeMap[SecondPoint]['W'] = true;
        }
    }
    else {
        if (FirstPoint.first == SecondPoint.first + 1) {
            MazeMap[FirstPoint]['N'] = true;
            MazeMap[SecondPoint]['S'] = true;
        } else {
            MazeMap[FirstPoint]['S'] = true;
            MazeMap[SecondPoint]['N'] = true;
        }
    }
}

bool MAZE::IsCyclic(POINT_ FirstPoint, POINT_ SecondPoint) {
    if(FirstPoint.first == SecondPoint.first) {
        if(FirstPoint.second > SecondPoint.second)
            SwapPoint(FirstPoint, SecondPoint);
        if(MazeMap[FirstPoint]['S'] && MazeMap[SecondPoint]['S'])
            if(FindPoint(make_pair(FirstPoint.first + 1, FirstPoint.second), Grid) && MazeMap[make_pair(FirstPoint.first + 1, FirstPoint.second)]['E'])
                return true;
        if(MazeMap[FirstPoint]['N'] && MazeMap[SecondPoint]['N'])
            if(FindPoint(make_pair(FirstPoint.first - 1, FirstPoint.second), Grid) && MazeMap[make_pair(FirstPoint.first - 1, FirstPoint.second)]['E'])
                return true;
    }
    else {
        if(FirstPoint.first > SecondPoint.first)
            SwapPoint(FirstPoint, SecondPoint);
        if(MazeMap[FirstPoint]['E'] && MazeMap[SecondPoint]['E'])
            if(FindPoint(make_pair(FirstPoint.first, FirstPoint.second + 1), Grid) && MazeMap[make_pair(FirstPoint.first, FirstPoint.second + 1)]['S'])
                return true;
        if(MazeMap[FirstPoint]['W'] && MazeMap[SecondPoint]['W'])
            if(FindPoint(make_pair(FirstPoint.first, FirstPoint.second - 1), Grid) && MazeMap[make_pair(FirstPoint.first, FirstPoint.second - 1)]['E'])
                return true;
    }
    return false;
}

PATH MAZE::BFS(POINT_ Point) {
    deque<POINT_> frontier;
    frontier.push_back(Point);
    Path.clear();
    set<POINT_> VisitedPoint;
    VisitedPoint.insert(make_pair(Row, Column));
    POINT_ NextPoint;
    while(!frontier.empty()) {
        Point = frontier.front();
        frontier.pop_front();
        if(MazeMap[Point]['E'] && !FindPoint(make_pair(Point.first, Point.second + 1), VisitedPoint)){
            NextPoint = make_pair(Point.first, Point.second + 1);
            Path[NextPoint] = Point;
            frontier.push_back(NextPoint);
            VisitedPoint.insert(NextPoint);
        }
        if(MazeMap[Point]['W'] && !FindPoint(make_pair(Point.first, Point.second - 1), VisitedPoint)){
            NextPoint = make_pair(Point.first, Point.second - 1);
            Path[NextPoint] = Point;
            frontier.push_back(NextPoint);
            VisitedPoint.insert(NextPoint);
        }
        if(MazeMap[Point]['N'] && !FindPoint(make_pair(Point.first - 1, Point.second), VisitedPoint)){
            NextPoint = make_pair(Point.first - 1, Point.second);
            Path[NextPoint] = Point;
            frontier.push_back(NextPoint);
            VisitedPoint.insert(NextPoint);
        }
        if(MazeMap[Point]['S'] && !FindPoint(make_pair(Point.first + 1, Point.second), VisitedPoint)){
            NextPoint = make_pair(Point.first + 1, Point.second);
            Path[NextPoint] = Point;
            frontier.push_back(NextPoint);
            VisitedPoint.insert(NextPoint);
        }
    }
    PATH fwdPath;
    Point = Goal;
    while(Point != make_pair(Row, Column)) {
        try {
            fwdPath[Path[Point]] = Point;
            Point = Path[Point];
        }
        catch(...) {
            printf("Error: Path to goal not to find.");
            exit(-1);
        }
    }
    return fwdPath;
}

void MAZE::LoadMazeFile(const string& LoadMaze) {
    ifstream InMaze;
    string Line;
    string Word;
    vector<string> Words;
    istringstream StrIn;
    stringstream geek(Word);
    InMaze.open(LoadMaze, ios::in);
    if(!InMaze.is_open()) {
        printf("Error: File open failed.\n");
        exit(-1);
    }
    int index = -1;
    InMaze.seekg(0, ios::end);
    int length = InMaze.tellg();
    while(length) {
        char c;
        InMaze.seekg(index, ios::end);
        InMaze.get(c);
        if(c == '\n') {
            getline(InMaze, Line);
            StrIn.str(Line);
            getline(StrIn, Word, ',');
            Word = split(Word, '(');
            Row = Word[0] - '0';
            getline(StrIn, Word, ',');
            Word = split(Word, ')');
            Column = Word[0] - '0';
            break;
        }
        length--;
        index--;
    }
    InMaze.seekg(0, ios::beg);
    getline(InMaze, Line);
    while(getline(InMaze, Line)) {
        int CurrentRow = 0, CurrentColumn = 0;
        StrIn.clear();
        StrIn.str(Line);
        getline(StrIn, Word, ',');
        Word = split(Word, '(');
        CurrentRow = Word[0] - '0';
        getline(StrIn, Word, ',');
        Word = split(Word, ')');
        CurrentColumn = Word[0] - '0';
        getline(StrIn, Word, ',');
        MazeMap[make_pair(CurrentRow, CurrentColumn)]['E'] = Word[0] - '0';
        getline(StrIn, Word, ',');
        MazeMap[make_pair(CurrentRow, CurrentColumn)]['N'] = Word[0] - '0';
        getline(StrIn, Word, ',');
        MazeMap[make_pair(CurrentRow, CurrentColumn)]['S'] = Word[0] - '0';
        getline(StrIn, Word, ',');
        MazeMap[make_pair(CurrentRow, CurrentColumn)]['W'] = Word[0] - '0';
    }
}

void MAZE::SaveMazeFile() {
    time_t now = time(nullptr);
    string SaveTime = ctime(&now);
    SaveTime = split(SaveTime, ' ');
    SaveTime = split(SaveTime, '\n');
    SaveTime = split(SaveTime, ':');
    string SaveName = "Maze--" + SaveTime + ".csv";
    ofstream OutMaze;
    OutMaze.open(SaveName, ios::ate | ios::out);
    if(!OutMaze.is_open()) {
        printf("Error: File open failed.\n");
        exit(-1);
    }
    OutMaze << "Cell" << ','
            << "E" << ','
            << "N" << ','
            << "S" << ','
            << "W" << endl;
    for(const auto& iter : MazeMap) {
        int i = 1;
        OutMaze << "(" + to_string(iter.first.first) + "," + to_string(iter.first.second) + ")" << ',';
        for(auto iter_ : MazeMap[iter.first]) {
            OutMaze << to_string(iter_.second);
            if(i != 4)
                OutMaze << ',';
            else if(iter.first != make_pair(Row, Column))
                OutMaze << endl;
            i++;
        }
    }
    OutMaze.close();
}

#endif // CPPMAZE_H_
