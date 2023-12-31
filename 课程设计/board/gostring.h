#ifndef GO_GOSTRING_H
#define GO_GOSTRING_H

#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

enum GridStatus {
    None = -1,
    Black = 0,
    White = 1
}; // 棋盘格点状态

struct Grid {
    int Row;
    int Column;

    Grid() {
        this -> Row = 0;
        this -> Column = 0;
    }

    explicit Grid(int Row, int Column) {
        this -> Row = Row;
        this -> Column = Column;
    }

    [[nodiscard]] vector<Grid> Neighbors() const {
        vector<Grid> Neighbors;
        if(this -> Row - 1 > 0)
            Neighbors.emplace_back(this -> Row - 1, this -> Column);
        if(this -> Row + 1 <=  19)
            Neighbors.emplace_back(this -> Row + 1, this -> Column);
        if(this -> Column - 1 > 0)
            Neighbors.emplace_back(this -> Row, this -> Column - 1);
        if(this -> Column + 1 <=  19)
            Neighbors.emplace_back(this -> Row, this -> Column + 1);
        return Neighbors;
    }

    [[nodiscard]] vector<Grid> Corners() const {
        vector<Grid> Corners;
        if(this -> Row - 1 > 0) {
            if(this -> Column - 1 > 0)
                Corners.emplace_back(this -> Row - 1, this -> Column - 1);
            if(this -> Column + 1 <=  19)
                Corners.emplace_back(this -> Row - 1, this -> Column + 1);
        }
        if(this -> Row + 1 <=  19) {
            if(this -> Column - 1 > 0)
                Corners.emplace_back(this -> Row + 1, this -> Column - 1);
            if(this -> Column + 1 <=  19)
                Corners.emplace_back(this -> Row + 1, this -> Column + 1);
        }
        return Corners;
    }

    inline bool operator == (const Grid &grid) const {
        return this -> Row == grid.Row && this -> Column == grid.Column;
    }

    inline bool operator < (const Grid &grid) const {
        return (this -> Row < grid.Row) || ((this -> Row == grid.Row) && (this -> Column < grid.Column));
    }
}; // 格点结构体

class FindMap {
    private:
        Grid grid;

    public:
        explicit FindMap(Grid grid_) : grid(grid_) {}
        bool operator()(pair<const Grid, GridStatus> grid_) const {
            return this -> grid == grid_.first;
        }
}; // Map查询

class FindVector {
    private:
        Grid grid;

    public:
        explicit FindVector(Grid grid_) : grid(grid_) {}
        bool operator()(Grid grid_) const {
            return this -> grid == grid_;
        }
}; // Vector查询

struct GoString {
    GridStatus StoneColor; // 棋链的颜色
    set<Grid> Stones; // 棋链中的棋子
    set<Grid> Liberties; // 棋链的气

    GoString() = default;

    GoString(GridStatus StoneColor, set<Grid> Stones, set<Grid> Liberties) {
        this -> StoneColor = StoneColor;
        this -> Stones = std::move(Stones);
        this -> Liberties = std::move(Liberties);
    }

    [[nodiscard]] GoString Merged(const GoString& OtherGoString) const {
        set<Grid> CombinedStones;
        set<Grid> CombinedLiberties;
        set<Grid> RealLiberties;

        CombinedStones.insert(OtherGoString.Stones.begin(), OtherGoString.Stones.end());
        CombinedStones.insert(this -> Stones.begin(), this -> Stones.end());

        CombinedLiberties.insert(OtherGoString.Liberties.begin(), OtherGoString.Liberties.end());
        CombinedLiberties.insert(this -> Liberties.begin(), this -> Liberties.end());
        std::set_difference(CombinedLiberties.begin(), CombinedLiberties.end(),
                            CombinedStones.begin(), CombinedStones.end(),
                            inserter(RealLiberties, RealLiberties.begin()));

        return {this -> StoneColor, CombinedStones, RealLiberties};
    }
};

#endif //GO_GOSTRING_H

